#include "fls/cfg/cfg.hpp"
#include "fls/common/common.hpp"
#include "fls/cor/eng/compressor.hpp"
#include "fls/cor/lyt/vec.hpp"
#include "fls/cor/mtd.hpp"
#include "fls/cor/prm/ffor_prm.hpp"
#include "fls/cor/prm/patch/patch.hpp"
#include "fls/logger/logger.hpp"
#include "fls/stt/histogram.hpp"
#include "fls/utl/to_str.hpp"
#include "fls/utl/util.hpp"
#include <climits>
#include <cmath>
#include <cstring>

#pragma clang diagnostic ignored "-Wconversion"

namespace fastlanes {
template <typename T>
bool ffor_prm<T>::is_exception(Params<T> params, T val) {
	if constexpr (std::is_same<T, uint64_t>() || std::is_same<T, uint32_t>() || std::is_same<T, uint16_t>() ||
	              std::is_same<T, uint8_t>()) {
		FLS_ASSERT_CORRECT_BW(params.bw)
		FLS_ASSERT_CORRECT_N(params.exc_c)
		FLS_ASSERT_CORRECT_SZ(params.size())
		// [fixme]
		if (params.bw == TYPE_BIT<T>::VALUE) {
			return false;
		}

		T lower_bound = static_cast<T>(params.base);

		if (val < lower_bound) {
			return true;
		}
		if (val - lower_bound > MAX_BIT(params.bw)) {
			return true;
		}
		return false;
	} else {
		FLS_ABORT("THIS IT NOT SUPPORTED")
		return false;
	}
}

template <typename T>
Params<T> ffor_prm<T>::find_best_params(Histogram<T>& histogram, n_t idx) {
	if constexpr (std::is_same<T, uint64_t>() || std::is_same<T, uint32_t>() || std::is_same<T, uint16_t>() ||
	              std::is_same<T, uint8_t>()) {

		/* Initialize */
		Params<T> best, next;
		auto&     val_vec     = histogram.val_vec;
		auto&     rep_vec     = histogram.rep_vec;
		const T   lower_bound = val_vec[idx];
		T         upper_bound = lower_bound;

		/* best = worst */
		best = {TYPE_BIT<T>::VALUE, 0, 0};

		// can we do better?
		for (int i = TYPE_BIT<T>::VALUE - 1; i >= 0; --i) {
			/* Compute the upperbound*/
			upper_bound = SafeUpperBound(lower_bound, i);

			/* Compute the next setting*/
			next = {
			    static_cast<bw_t>(i),
			    lower_bound,
			    static_cast<vec_idx_t>(typed_patch<T>::count_exceptions(lower_bound, upper_bound, val_vec, rep_vec))};

			FLS_ASSERT_CORRECT_EXC_C(next.exc_c)
			/* Check to see if there is a better setting. */
			if (next.size() < best.size() & next.exc_c <= CFG::PATCH::EXC_LIMIT_C) {
				best = next;
			}
		}

		return best;
	} else {
		FLS_ABORT("THIS IT NOT SUPPORTED")
		return Params<T>();
	}
}

template <typename T>
void ffor_analyze(Vec& src_vec, Vec& des_vec, CompressState& stt) {
	/* copy data into des.*/
	memcpy(
	    des_vec.buf_arr[stt.cur_des_buff + 1].mutable_data(), src_vec.buf_arr[stt.cur_src_buff].data(), vec_bsz<T>());

	auto min = std::numeric_limits<T>::max();
	auto max = std::numeric_limits<T>::min();

	auto* in_p = reinterpret_cast<const T*>(des_vec.buf_arr[stt.cur_des_buff + 1].data());
	for (size_t i {0}; i < 1024; ++i) {
		if (in_p[i] < min) {
			min = in_p[i];
		}
		if (in_p[i] > max) {
			max = in_p[i];
		}
	}

	uint64_t delta          = (static_cast<uint64_t>(max) - static_cast<uint64_t>(min));
	auto     bits_per_digit = ceil(log2(delta + 1));
	uint8_t  bw             = bits_per_digit;

	stt.bw = bw;
	std::memcpy(stt.base, &min, sizeof(T));
	//	base_p[0]               = min;
	FLS_PLOG_KEY_VALUE("bw", std::to_string(stt.bw))
	FLS_PLOG_KEY_VALUE("min", std::to_string(min))
	FLS_PLOG_KEY_VALUE("max", std::to_string(max))
}

template <typename T>
void ffor_patch_analyze(Vec& src_vec, Vec& des_vec, CompressState& stt) {
	/* copy data into stt_buf.*/
	Params<T> best, next;
	memcpy(des_vec.buf_arr[1].mutable_data(), src_vec.buf_arr[0].data(), vec_bsz<T>());

	/* [op]: the tmp buf is sorted already, the minmax is the first and last element.  */
	/* [op]: move to stt to reduce allocation. */
	auto histo   = Histogram<T>::cal(des_vec.buf_arr[1].mutable_data());
	auto min_max = MinMax<T>::cal(des_vec.buf_arr[1].mutable_data());
	n_t  base_c  = histo->rep_vec.size();

	best = ffor_prm<T>::find_best_params(*histo, 0);

	/* Compute. */
	for (size_t i {1}; i < base_c; ++i) {
		next = ffor_prm<T>::find_best_params(*histo, i);

		if (next.size() < best.size()) {
			best = next;
		}
	}

	stt.bw = best.bw;
	std::memcpy(stt.base, &best.base, sizeof(T));
	FLS_ASSERT_CORRECT_BASE_UB(best.base, min_max->max)

	stt.exc_c = best.exc_c;

	/* Add exception positions . */
	uint16_t exc_c {0};

	for (size_t i {0}; i < vec_n_tup(); ++i) {
		T& val = reinterpret_cast<T*>(src_vec.buf_arr[0].mutable_data())[i];
		if (ffor_prm<T>::is_exception(best, val)) {
			stt.exc_pos_arr[exc_c++] = i;
		}
	}

	FLS_PLOG_KEY_VALUE("VEC", ToStr::to_str<T>(reinterpret_cast<T*>(src_vec.buf_arr[0].mutable_data())))
	FLS_PLOG_KEY_VALUE("BW", std::to_string(stt.bw))
	FLS_PLOG_KEY_VALUE("EXC_C", ToStr::to_str<uint16_t>(exc_c))
	FLS_PLOG_KEY_VALUE("BASE", ToStr::to_hex(stt.base, sizeof(T)));
}

template <typename T>
cmpr_fun_t ffor_prm<T>::ResolveAnalyzeFunc() {
	if constexpr (std::is_same<T, i64_pt>()) {
		return ffor_analyze<i64_pt>;
	} else if constexpr (std::is_same<T, uint64_t>()) {
		return ffor_analyze<uint64_t>;
	} else if constexpr (std::is_same<T, int32_t>()) {
		return ffor_analyze<uint32_t>;
	} else if constexpr (std::is_same<T, uint32_t>()) {
		return ffor_analyze<uint32_t>;
	} else if constexpr (std::is_same<T, uint16_t>()) {
		return ffor_analyze<uint16_t>;
	} else if constexpr (std::is_same<T, uint8_t>()) {
		return ffor_analyze<uint8_t>;
	} else {
		FLS_ABORT("THIS IT NOT SUPPORTED")
		return nullptr;
	}
}

template <typename T>
cmpr_fun_t ffor_prm<T>::ResolvePatchAnalyzeFunc() {
	if constexpr (std::is_same<T, int64_t>()) {
		return ffor_patch_analyze<uint64_t>;
	} else if constexpr (std::is_same<T, uint64_t>()) {
		return ffor_patch_analyze<uint64_t>;
	} else if constexpr (std::is_same<T, int32_t>()) {
		return ffor_patch_analyze<uint32_t>;
	} else if constexpr (std::is_same<T, uint32_t>()) {
		return ffor_patch_analyze<uint32_t>;
	} else {
		FLS_ABORT("THIS IT NOT SUPPORTED")
		return nullptr;
	}
}

/*---------------------------------------------------------------------------------------------------------------------\
 * Specialization
\---------------------------------------------------------------------------------------------------------------------*/
FLS_ALL_CTS(ffor_prm)
} // namespace fastlanes