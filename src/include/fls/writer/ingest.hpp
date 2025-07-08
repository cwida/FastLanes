#ifndef FLS_WRITER_INGEST_HPP
#define FLS_WRITER_INGEST_HPP

#include "fls/common/double.hpp"
#include "fls/table/rowgroup.hpp"

#include <span>
#include <string>

namespace fastlanes {

struct Ingest {
	template <typename PT>
	static PT TypedNull() {
		static constexpr i08_pt I08_NULL   = 0;
		static constexpr i16_pt I16_NULL   = 0;
		static constexpr i32_pt I32_NULL   = 0;
		static constexpr i64_pt I64_NULL   = 0;
		static constexpr u08_pt U08_NULL   = 0;
		static constexpr u16_pt U16_NULL   = 0;
		static constexpr u32_pt U32_NULL   = 0;
		static constexpr u64_pt U64_NULL   = 0;
		static constexpr bol_pt BOOL_NULL  = false;
		static constexpr flt_pt FLOAT_NULL = 0.0;
		static constexpr dbl_pt DBL_NULL   = 0.0;
		static constexpr char   STR_NULL[] = "NULL";

		if constexpr (std::is_same_v<PT, i08_pt>) {
			return I08_NULL;
		} else if constexpr (std::is_same_v<PT, i16_pt>) {
			return I16_NULL;
		} else if constexpr (std::is_same_v<PT, i32_pt>) {
			return I32_NULL;
		} else if constexpr (std::is_same_v<PT, i64_pt>) {
			return I64_NULL;
		} else if constexpr (std::is_same_v<PT, u08_pt>) {
			return U08_NULL;
		} else if constexpr (std::is_same_v<PT, u16_pt>) {
			return U16_NULL;
		} else if constexpr (std::is_same_v<PT, u32_pt>) {
			return U32_NULL;
		} else if constexpr (std::is_same_v<PT, u64_pt>) {
			return U64_NULL;
		} else if constexpr (std::is_same_v<PT, str_pt>) {
			return STR_NULL;
		} else if constexpr (std::is_same_v<PT, bol_pt>) {
			return BOOL_NULL;
		} else if constexpr (std::is_same_v<PT, flt_pt>) {
			return FLOAT_NULL;
		} else if constexpr (std::is_same_v<PT, dbl_pt>) {
			return DBL_NULL;
		}

		FLS_UNREACHABLE();
	}

	template <typename PT>
	static void TypedIngest(TypedCol<PT>& typed_column, std::span<const PT> src_column) {
		auto  count = src_column.size();
		auto& stats = typed_column.m_stats;
		auto& data  = typed_column.data;
		auto& nulls = typed_column.null_map_arr;

		if (typed_column.data.empty()) {
			typed_column.m_stats.last_seen_val = TypedNull<PT>();
			if constexpr (std::is_same_v<PT, dbl_pt>) {
				stats.is_double_castable = true;
			}
		}

		const idx_t prev_size = data.size();
		data.resize(prev_size + count);
		nulls.resize(prev_size + count);

		auto target_ptr = data.data() + prev_size;
		auto null_ptr   = nulls.data() + prev_size;

		PT&   min                = stats.min;
		PT&   max                = stats.max;
		auto& last_seen_val      = stats.last_seen_val;
		auto& n_nulls            = stats.n_nulls;
		bool& is_double_castable = stats.is_double_castable;

		for (idx_t i = 0; i < count; i++) {
			PT         value   = src_column[i];
			const bool is_null = value == TypedNull<PT>();
			null_ptr[i]        = is_null;

			if (is_null) {
				++n_nulls;
				target_ptr[i] = last_seen_val;
			} else {
				target_ptr[i] = value;
				last_seen_val = value;

				min = std::min(min, value);
				max = std::max(max, value);

				if constexpr (std::is_same_v<PT, dbl_pt>) {
					if (is_double_castable && !Double::is_safely_castable_to_int64(value)) {
						is_double_castable = false;
					}
				}
			}
		}

		stats.min           = min;
		stats.max           = max;
		stats.last_seen_val = last_seen_val;
		stats.n_nulls       = n_nulls;

		if constexpr (std::is_same_v<PT, dbl_pt>) {
			stats.is_double_castable = is_double_castable;
		}
	}

	static void FLSStringIngest(FLSStrColumn& fls_str_column, std::span<const str_pt> src_column);
};

} // namespace fastlanes

#endif // FLS_WRITER_INGEST_HPP