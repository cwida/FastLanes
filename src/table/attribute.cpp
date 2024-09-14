#include "fls/table/attribute.hpp"
#include "fls/cfg/cfg.hpp"
#include "fls/common/common.hpp"
#include "fls/common/macros.hpp"
#include "fls/expression/data_type.hpp"
#include "fls/table/rowgroup.hpp"
#include <algorithm>

namespace fastlanes {

template <typename PT>
bool Attribute<PT>::IsNull(const string& val_str) {
	/**/
	const bool rule_1 = val_str == "null";
	/**/
	const bool rule_2 = val_str.empty();

	return (rule_1 || rule_2);
}

template <typename PT>
PT Attribute<PT>::Cast(const string& val_str) {
	if constexpr (std::is_same_v<PT, u08_pt>) {
		return static_cast<u08_pt>(stoul(val_str));
	} else if constexpr (std::is_same_v<PT, u16_pt>) {
		return static_cast<u16_pt>(stoul(val_str));
	} else if constexpr (std::is_same_v<PT, u32_pt>) {
		return static_cast<u32_pt>(std::stoul(val_str));
	} else if constexpr (std::is_same_v<PT, u64_pt>) {
		return std::stoull(val_str);
	} else if constexpr (std::is_same_v<PT, i08_pt>) {
		return static_cast<i08_pt>(std::stoi(val_str));
	} else if constexpr (std::is_same_v<PT, i16_pt>) {
		return static_cast<i16_pt>(std::stoi(val_str));
	} else if constexpr (std::is_same_v<PT, i32_pt>) {
		return std::stoi(val_str);
	} else if constexpr (std::is_same_v<PT, i64_pt>) {
		return std::stoll(val_str);
	} else if constexpr (std::is_same_v<PT, bol_pt>) {
		return val_str == "true";
	} else if constexpr (std::is_same_v<PT, flt_pt>) {
		return stof(val_str);
	} else if constexpr (std::is_same_v<PT, dbl_pt>) {
		return stod(val_str);
	} else if constexpr (std::is_same_v<PT, str_pt>) {
		return val_str;
	}
	FLS_UNREACHABLE();
	return {};
}

template <typename PT>
PT Attribute<PT>::Null() {
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
	return {};
}

template <typename PT>
void Attribute<PT>::Ingest(TypedCol<PT>& typed_column, const string& val_str) {
	// init
	auto& n_null      = typed_column.m_stats.n_null;
	auto& is_constant = typed_column.m_stats.is_constant;
	auto& n_run       = typed_column.m_stats.n_run;
	auto& min         = typed_column.m_stats.min;
	auto& max         = typed_column.m_stats.max;
	auto& dictionary  = typed_column.m_stats.dict;
	// check if it  NULL
	const bool is_null = IsNull(val_str);

	// ingest
	typed_column.null_map_arr.push_back(is_null);
	if (is_null) {
		n_null = n_null + 1;
		typed_column.data.push_back(Null());
	} else {
		typed_column.data.push_back(Cast(val_str));
	}

	const n_t current_pos = typed_column.data.size() - 1;

	// into the dictionary
	{
		const auto& value         = typed_column.data[current_pos];
		auto        dict_elemenet = dictionary.find(value);
		if (dict_elemenet == dictionary.end()) {
			dictionary.emplace(value, current_pos);
		} else {
			dict_elemenet->second.repetition = dict_elemenet->second.repetition + 1;
		}
	}

	// for cases where comparison with previous value is needed
	const auto current_value = typed_column.data[current_pos];
	if (typed_column.data.size() >= 2) {
		const auto last_pos   = typed_column.data.size() - 2;
		const auto last_value = typed_column.data[last_pos];

		// check constness!
		if (is_constant && (current_value != last_value)) { is_constant = false; }
		// number of runs!
		if (current_value != last_value) { n_run = n_run + 1; }
	}

	{
		if constexpr (!std::is_same_v<PT, bol_pt>) {
			min = std::min(min, current_value);
			max = std::max(max, current_value);
		}
	}
}

FLS_ALL_CTS(Attribute)

} // namespace fastlanes