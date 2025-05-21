#include "fls/expression/analyze_operator.hpp"
#include "fls/cfg/cfg.hpp"
#include "fls/cor/lyt/buf.hpp"
#include "fls/cor/prm/ffor_prm.hpp"
#include "fls/expression/encoding_operator.hpp"
#include "fls/expression/physical_expression.hpp"
#include "fls/expression/rsum_operator.hpp"
#include "fls/ffor.hpp"
#include "fls/ffor_util.hpp"
#include "fls/primitive/copy/fls_copy.hpp"
#include "fls/stt/minmax.hpp"
#include "fls/utl/util.hpp"
#include <algorithm>

namespace fastlanes {

static constexpr uint64_t LOCAL_EXC_LIMIT_C = 20; // between 5 and 10 percent

template <typename T>
class Option {
public:
	n_t size() {
		return (1024 * bw / CHAR_BIT) + n_exceptions * sizeof(T) + n_exceptions * sizeof(vec_idx_t);
	} //
public:
	bw_t      bw;           //
	T         base;         //
	vec_idx_t n_exceptions; //
	T         upper;        //
};

template <typename PT>
void Histogram<PT>::Cal(PT* data) {
	val_vec.clear();
	rep_vec.clear();

	/* Sort. */
	std::sort(data, data + CFG::VEC_SZ);

	/* Push the first one. */
	val_vec.push_back(data[0]);
	rep_vec.push_back(1);

	/* Make the histogram. */
	for (n_t i = 1; i < CFG::VEC_SZ; ++i) {
		/* Same value. Increase the rep*/
		if (data[i] == data[i - 1]) {
			rep_vec.back() += 1;
		}
		/* New seq. add it to vec. Set the rep to one. */
		else {
			val_vec.push_back(data[i]);
			rep_vec.push_back(1);
		}
	}
}

template <typename T>
constexpr T pow2(uint8_t bw) {
	static_assert(std::is_unsigned<T>::value, "pow2() only supports unsigned integer types");

	if (bw >= sizeof(T) * 8) {
		return 0; // Avoid undefined behavior
	}

	return static_cast<T>(T(1) << bw); // Ensure correct type before shifting
}

template <typename T>
bool is_exception(Option<T>& option, T val) {
	FLS_ASSERT_CORRECT_BW(option.bw)
	FLS_ASSERT_CORRECT_N(option.n_exceptions)
	FLS_ASSERT_CORRECT_SZ(option.size())

	make_unsigned_t<T> a          = *reinterpret_cast<make_unsigned_t<T>*>(&option.base);
	make_unsigned_t<T> b          = a + pow2<make_unsigned_t<T>>(option.bw);
	T                  real_upper = *reinterpret_cast<T*>(&b);

	if (val < option.base) {
		return true;
	}
	if (val >= real_upper) {
		return true;
	}
	return false;
}

template <typename T>
bool is_exception(T lower_bound, T upper_bound, T val) {
	if (val <= upper_bound && val >= lower_bound) {
		return false;
	}
	return true;
}

template <typename T>
n_t count_exceptions(const T                      lower_bound,
                     const T                      upper_bound,
                     const std::vector<T>&        val_vec,
                     const std::vector<uint16_t>& rep_vec) {

	FLS_ASSERT(!val_vec.empty(), "an empty vec", " ");
	FLS_ASSERT(!rep_vec.empty(), "an empty vec", " ");

	n_t  result {0};
	bool is_exc {false};

	for (n_t i = 0; i < val_vec.size(); ++i) {
		is_exc = is_exception<T>(lower_bound, upper_bound, val_vec[i]);
		if (!is_exc) {
			continue;
		}
		/* It is an exception.
		 * Increase the number of exception by the repetition of this value.
		 */
		result += rep_vec[i];
	}

	return result;
}

template <typename T>
Option<T> find_best_option(Histogram<T>& histogram, vec_idx_t first_base_idx, vec_idx_t next_base_idx) {
	/* Initialize */
	Option<T> result;

	auto&   val_vec     = histogram.val_vec;
	auto&   rep_vec     = histogram.rep_vec;
	const T lower_bound = val_vec[first_base_idx];
	const T upper_bound = val_vec[next_base_idx];

	vec_idx_t n_non_exceptions {0};
	for (vec_idx_t val_idx {first_base_idx}; val_idx <= next_base_idx; val_idx++) {
		n_non_exceptions += rep_vec[val_idx];
	}
	bw_t bw = count_bits<T>(upper_bound, lower_bound);

	result.base         = lower_bound;
	result.bw           = bw;
	result.n_exceptions = 1024 - n_non_exceptions;
	result.upper        = upper_bound;

	return result;
}

template <typename PT>
void Histogram<PT>::Reset() {
	val_vec.clear();
	rep_vec.clear();
} //

template class Histogram<u16_pt>;
template class Histogram<u32_pt>;
template class Histogram<u64_pt>;
template class Histogram<i16_pt>;
template class Histogram<i32_pt>;
template class Histogram<i64_pt>;

template <typename PT, bool IS_PATCHED>
enc_analyze_opr<PT, IS_PATCHED>::enc_analyze_opr(const PhysicalExpr& expr,
                                                 const col_pt&       col,
                                                 ColumnDescriptorT&  column_descriptor,
                                                 InterpreterState&   state)
    : null_map_view(col) {

	is_rsum = false;
	visit(overloaded {
	          [&](const sp<enc_scan_opr<PT>>& opr) { data = opr->data; },
	          [&](const sp<enc_rsum_opr<PT>>& opr) {
		          data    = opr->deltas;
		          is_rsum = true;
	          },
	          [&]<typename VALUE_PT>(const sp<enc_dict_map_opr<VALUE_PT, PT>>& opr) { data = opr->index_arr; },
	          [&](std::monostate&) { FLS_UNREACHABLE(); },
	          [&](auto&) { FLS_UNREACHABLE(); },
	      },
	      expr.operators.back());
}

template <typename PT, bool USE_PATCH>
void enc_analyze_opr<PT, USE_PATCH>::Analyze() {
	auto* null_map_arr = null_map_view.NullMap();

	if constexpr (!USE_PATCH) {
		if (is_rsum) {
			auto min = std::numeric_limits<PT>::max();
			auto max = std::numeric_limits<PT>::min();

			for (size_t i {0}; i < CFG::VEC_SZ; ++i) {
				if (data[i] < min) {
					min = data[i];
				}
				if (data[i] > max) {
					max = data[i];
				}
			}
			bw   = count_bits<PT>(max, min);
			base = min;
			return;
		}
		auto min = std::numeric_limits<PT>::max();
		auto max = std::numeric_limits<PT>::min();

		bool all_null = true;

		for (size_t i {0}; i < CFG::VEC_SZ; ++i) {
			if (data[i] < min && !null_map_arr[i]) {
				min      = data[i];
				all_null = false;
			}
			if (data[i] > max && !null_map_arr[i]) {
				max      = data[i];
				all_null = false;
			}
		}

		for (size_t i {0}; i < CFG::VEC_SZ; ++i) {
			if (null_map_arr[i]) {
				data[i] = min;
			}
		}

		if (all_null) {
			bw   = 0;
			base = 0;
		} else {
			bw   = count_bits<PT>(max, min);
			base = min;
		}
	} else {
		if (is_rsum) {
			/* copy data into stt_buf.*/
			Option<PT> best {64, 0, 0};
			copy<PT>(data, copy_of_data);

			histogram.Reset();
			histogram.Cal(copy_of_data);
			const n_t n_option = histogram.rep_vec.size();

			/* Compute. */
			for (vec_idx_t i {0}; i < n_option; ++i) {
				for (vec_idx_t j {i}; j < n_option; ++j) {
					auto next = find_best_option<PT>(histogram, i, j);
					if (next.size() < best.size() && next.n_exceptions < LOCAL_EXC_LIMIT_C) {
						best = next;
					}
				}
			}

			bw           = best.bw;
			base         = best.base;
			n_exceptions = best.n_exceptions;

			/* Add exception positions . */
			uint16_t exc_c {0};

			for (alp::exp_c_t i {0}; i < vec_n_tup(); ++i) {
				if (const auto& val = data[i]; is_exception(best, val)) {
					exception_pos_arr[exc_c] = i;
					exceptions[exc_c]        = data[i];
					exc_c++;
				}
			}

			n_exceptions = exc_c;
			return;
		}
		/* copy data into stt_buf.*/
		Option<PT> best {64, 0, 0};
		copy<PT>(data, copy_of_data);

		histogram.Reset();
		histogram.Cal(copy_of_data);
		const n_t n_option = histogram.rep_vec.size();

		/* Compute. */
		for (vec_idx_t i {0}; i < n_option; ++i) {
			for (vec_idx_t j {i}; j < n_option; ++j) {
				auto next = find_best_option<PT>(histogram, i, j);
				if (next.size() < best.size() && next.n_exceptions < LOCAL_EXC_LIMIT_C) {
					best = next;
				}
			}
		}

		bw           = best.bw;
		base         = best.base;
		n_exceptions = best.n_exceptions;

		/* Add exception positions . */
		uint16_t exc_c {0};

		for (alp::exp_c_t i {0}; i < vec_n_tup(); ++i) {
			if (const auto& val = data[i]; is_exception(best, val) && !null_map_arr[i]) {
				exception_pos_arr[exc_c] = i;
				exceptions[exc_c]        = data[i];
				exc_c++;
			}
		}

		for (size_t i {0}; i < CFG::VEC_SZ; ++i) {
			if (null_map_arr[i]) {
				data[i] = base;
			}
		}

		n_exceptions = exc_c;
	}
}

template <typename PT, bool IS_PATCHED>
void enc_analyze_opr<PT, IS_PATCHED>::PointTo(n_t vec_idx) {
	null_map_view.PointTo(vec_idx);
}

template struct enc_analyze_opr<u64_pt, false>;
template struct enc_analyze_opr<u32_pt, false>;
template struct enc_analyze_opr<u16_pt, false>;
template struct enc_analyze_opr<u08_pt, false>;
template struct enc_analyze_opr<u64_pt, true>;
template struct enc_analyze_opr<u32_pt, true>;
template struct enc_analyze_opr<u16_pt, true>;
template struct enc_analyze_opr<u08_pt, true>;
template struct enc_analyze_opr<i64_pt, false>;
template struct enc_analyze_opr<i32_pt, false>;
template struct enc_analyze_opr<i16_pt, false>;
template struct enc_analyze_opr<i08_pt, false>;
template struct enc_analyze_opr<i64_pt, true>;
template struct enc_analyze_opr<i32_pt, true>;
template struct enc_analyze_opr<i16_pt, true>;
template struct enc_analyze_opr<i08_pt, true>;
} // namespace fastlanes