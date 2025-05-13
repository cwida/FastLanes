#include "fls/table/attribute.hpp"
#include "fls/common/common.hpp"
#include "fls/common/decimal.hpp"
#include "fls/common/double.hpp"
#include "fls/common/string.hpp"
#include "fls/expression/data_type.hpp"
#include <algorithm>
#include <cstring>
#include <limits>
#include <sstream>
#include <stdexcept>

namespace fastlanes {

// https://sqlite.org/forum/forumpost/d3bad034ce32e6f9?
// https://docs.snowflake.com/en/user-guide/data-unload-considerations
bool IsNull(const string& val_str) {
	// rule 1
	const bool rule_1 = val_str == "null";
	// rule 2
	const bool rule_2 = val_str.empty();
	// rule 3
	const bool rule_3 = val_str == "NULL";
	// rule 4
	const bool rule_4 = val_str == "NA";
	// rule 5
	const bool rule_5 = val_str == "N/A";
	// rule 6
	const bool rule_6 = val_str == "none";
	// rule 7
	const bool rule_7 = val_str == "null\r";
	// rule 8
	const bool rule_8 = val_str == "Null";

	return (rule_1 || rule_2 || rule_3 || rule_4 || rule_5 || rule_6 || rule_7 || rule_8);
}

template <typename PT>
PT TypedCast(const std::string& val_str) {
	try {
		if constexpr (std::is_same_v<PT, u08_pt>) {
			const auto value = stoul(val_str);
			if (value > std::numeric_limits<u08_pt>::max())
				throw std::out_of_range("Value exceeds u08_pt range");
			return static_cast<u08_pt>(value);
		} else if constexpr (std::is_same_v<PT, u16_pt>) {
			const auto value = stoul(val_str);
			if (value > std::numeric_limits<u16_pt>::max())
				throw std::out_of_range("Value exceeds u16_pt range");
			return static_cast<u16_pt>(value);
		} else if constexpr (std::is_same_v<PT, u32_pt>) {
			return static_cast<u32_pt>(std::stoul(val_str)); // stoul already checks range for uint32
		} else if constexpr (std::is_same_v<PT, u64_pt>) {
			return std::stoull(val_str); // stoull already checks range for uint64
		} else if constexpr (std::is_same_v<PT, i08_pt>) {
			const auto value = std::stoi(val_str);
			if (value < std::numeric_limits<i08_pt>::min() || value > std::numeric_limits<i08_pt>::max())
				throw std::out_of_range("Value exceeds i08_pt range");
			return static_cast<i08_pt>(value);
		} else if constexpr (std::is_same_v<PT, i16_pt>) {
			const auto value = std::stoi(val_str);
			if (value < std::numeric_limits<i16_pt>::min() || value > std::numeric_limits<i16_pt>::max())
				throw std::out_of_range("Value exceeds i16_pt range");
			return static_cast<i16_pt>(value);
		} else if constexpr (std::is_same_v<PT, i32_pt>) {
			return std::stoi(val_str); // stoi already checks range for int32
		} else if constexpr (std::is_same_v<PT, i64_pt>) {
			return std::stoll(val_str); // stoll already checks range for int64
		} else if constexpr (std::is_same_v<PT, bol_pt>) {
			if (val_str != "true" && val_str != "false")
				throw std::invalid_argument("Invalid boolean value");
			return val_str == "true";
		} else if constexpr (std::is_same_v<PT, flt_pt>) {
			return std::stof(val_str);
		} else if constexpr (std::is_same_v<PT, dbl_pt>) {
			auto value = stod(val_str);
			if (value < std::numeric_limits<dbl_pt>::lowest() || value > std::numeric_limits<dbl_pt>::max())
				throw std::out_of_range("Value exceeds dbl_pt range");
			return value;
		} else if constexpr (std::is_same_v<PT, str_pt>) {
			return val_str;
		}
	} catch (const std::exception& e) {
		// Include the input value in the runtime error message
		throw std::runtime_error(std::string("Error in TypedCast for input '") + val_str + "': " + e.what());
	}
	FLS_UNREACHABLE();
}

template <typename PT>
PT TypedNull() {
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
std::string TypedToStr(TypedCol<PT>& typed_column, n_t row_idx) {
	if constexpr (std::is_arithmetic_v<PT>) {
		if constexpr (std::is_floating_point_v<PT>) {
			// Handle floating-point types with full precision
			std::ostringstream oss;
			oss << std::setprecision(std::numeric_limits<PT>::max_digits10) << typed_column.data[row_idx];
			return oss.str();
		} else {
			// Handle integral types
			return std::to_string(typed_column.data[row_idx]);
		}
	}
	FLS_UNREACHABLE();
}

template <typename PT>
void TypedIngest(TypedCol<PT>& typed_column, const string& val_str, const ColumnDescriptorT& column_descriptor) {
	// init
	auto& n_nulls            = typed_column.m_stats.n_nulls;
	auto& min                = typed_column.m_stats.min;
	auto& max                = typed_column.m_stats.max;
	auto& is_double_castable = typed_column.m_stats.is_double_castable;

	if (typed_column.data.size() == 0) {
		typed_column.m_stats.last_seen_val = TypedNull<PT>();
	}

	// is_double_castable
	if constexpr (std::is_same_v<PT, dbl_pt>) {
		if (typed_column.data.empty()) {
			is_double_castable = true;
		}
	}

	// check if it  NULL
	const bool is_null = IsNull(val_str);
	if (is_null) {
		n_nulls = n_nulls + 1;
	}

	// ingest
	typed_column.null_map_arr.push_back(is_null);
	PT current_val;
	if (!is_null && column_descriptor.data_type == DataType::DECIMAL) {
		if constexpr (std::is_same_v<PT, int64_t>) { // fix me
			current_val                        = make_decimal(val_str, column_descriptor.fix_me_decimal_type->scale);
			typed_column.m_stats.last_seen_val = current_val;
		}
	} else if (!is_null) {
		current_val                        = TypedCast<PT>(val_str);
		typed_column.m_stats.last_seen_val = current_val;
	} else {
		current_val = typed_column.m_stats.last_seen_val;
	}
	typed_column.data.push_back(current_val);

	min = std::min(min, current_val);
	max = std::max(max, current_val);

	// is_double_castable
	if constexpr (std::is_same_v<PT, dbl_pt>) {
		if (typed_column.data.empty()) {
			is_double_castable = true;
		}
		if (is_double_castable && !is_null && !Double::is_safely_castable_to_int64(current_val)) {
			is_double_castable = false;
		}
	}
}

bool IsNumeric(const string& val_str) {
	if (val_str.empty()) {
		return false; // Empty string is not an integer
	}

	const size_t startIndex = (val_str[0] == '+' || val_str[0] == '-') ? 1 : 0;

	for (size_t i = startIndex; i < val_str.size(); ++i) {
		if (!std::isdigit(val_str[i])) {
			return false;
		}
	}

	return true;
}

bool isValidUint64(const std::string& str) {
	if (str.empty())
		return false;

	// Check if the string contains only digits
	for (char c : str) {
		if (!std::isdigit(c))
			return false;
	}

	try {
		// Convert to unsigned long long and check if it's within uint64_t range
		uint64_t value = std::stoull(str);
		return value <= std::numeric_limits<uint64_t>::max();
	} catch (const std::exception&) {
		return false; // Overflow or invalid conversion
	}
}

bool isValidSignedNumber(const std::string& str) {
	if (str.empty())
		return false;

	char* end = nullptr;

	// Use std::strtod to check for valid signed numbers
	std::strtod(str.c_str(), &end);

	// Ensure the entire string was parsed successfully
	return end != nullptr && *end == '\0';
}

bool isValidDouble(const std::string& str) {
	if (str.empty())
		return false;

	char* end = nullptr;
	std::strtod(str.c_str(), &end); // Try converting to double

	// Check if the entire string was parsed successfully
	return end != nullptr && *end == '\0';
}

bool isValidUint32(const std::string& str) {
	if (str.empty())
		return false;

	for (char c : str) {
		if (!std::isdigit(c))
			return false;
	}

	try {
		u64_pt value = std::stoul(str);
		return value <= std::numeric_limits<uint32_t>::max();
	} catch (const std::exception&) { return false; }
}

bool isValidInt32(const std::string& str) {
	if (str.empty())
		return false;

	size_t start = 0;
	if (str[0] == '-' || str[0] == '+') {
		if (str.size() == 1) // Just a sign, invalid number
			return false;
		start = 1;
	}

	// Check if the remaining string contains only digits
	for (size_t i = start; i < str.size(); ++i) {
		if (!std::isdigit(str[i]))
			return false;
	}

	try {
		// Convert string to long and check the range
		const int64_t value = std::stol(str);
		return value >= std::numeric_limits<int32_t>::min() && value <= std::numeric_limits<int32_t>::max();
	} catch (const std::exception&) {
		return false; // Overflow or invalid conversion
	}
}

bool isValidUint16(const std::string& str) {
	if (str.empty())
		return false;

	// Check if the string contains only digits
	for (char c : str) {
		if (!std::isdigit(c))
			return false;
	}

	try {
		// Convert string to unsigned long and check the range
		unsigned long value = std::stoul(str);
		return value <= std::numeric_limits<uint16_t>::max();
	} catch (const std::exception&) {
		return false; // Overflow or invalid conversion
	}
}

void FLSStringIngest(FLSStrColumn& fls_str_column, const string& val_str) {
	if (val_str.size() > CFG::String::max_bytes_per_string) {
		throw std::runtime_error("String of size " + std::to_string(val_str.size()) +
		                         " exceeds the maximum allowed size of " +
		                         std::to_string(CFG::String::max_bytes_per_string) + " bytes.");
	}

	// init
	auto& byte_arr            = fls_str_column.byte_arr;
	auto& ofs_arr             = fls_str_column.ofs_arr;
	auto& max_n_bytes_p_value = fls_str_column.m_stats.maximum_n_bytes_p_value;
	auto& length_arr          = fls_str_column.length_arr;
	auto& is_numeric          = fls_str_column.m_stats.is_numeric;

	auto& fsst_byte_arr   = fls_str_column.fsst_byte_arr;
	auto& fsst_length_arr = fls_str_column.fsst_length_arr;

	if (length_arr.empty()) {
		is_numeric = true;
	}
	// check if it NULL
	const bool is_null = IsNull(val_str);
	fls_str_column.null_map_arr.push_back(is_null);
	string current_val;
	if (!is_null) {
		current_val                          = val_str;
		fls_str_column.m_stats.last_seen_val = current_val;
	} else {
		current_val = fls_str_column.m_stats.last_seen_val;
	}

	// is numeric
	if (is_numeric && !is_null && !isValidUint64(current_val)) {
		is_numeric = false;
	}

	// push
	const size_t old_size = byte_arr.size(); // Save the current size
	ofs_arr.push_back(static_cast<ofs_t>(byte_arr.size()));
	byte_arr.resize(byte_arr.size() + current_val.size());
	std::memcpy(byte_arr.data() + old_size, current_val.data(), current_val.size());
	length_arr.push_back(static_cast<len_t>(current_val.size()));

	// calculate maximum size of a value
	max_n_bytes_p_value = (max_n_bytes_p_value > current_val.size()) ? max_n_bytes_p_value : current_val.size();
	is_numeric          = is_numeric && IsNumeric(val_str);

	// FSST
	{
		// check if it NULL
		if (!is_null) {
			current_val                          = val_str;
			fls_str_column.m_stats.last_seen_val = current_val;
		} else {
			current_val = "";
		}

		// push
		const size_t fsst_old_size = fsst_byte_arr.size(); // Save the current size
		fsst_byte_arr.resize(fsst_byte_arr.size() + current_val.size());
		std::memcpy(fsst_byte_arr.data() + fsst_old_size, current_val.data(), current_val.size());
		fsst_length_arr.push_back(static_cast<len_t>(current_val.size()));
	}
}

void Attribute::Ingest(col_pt& column, const string& val_str, const ColumnDescriptorT& column_descriptor) {
	visit(overloaded {
	          [&]<typename PT>(up<TypedCol<PT>>& typed_column) {
		          TypedIngest<PT>(*typed_column, val_str, column_descriptor);
	          },
	          [&](up<FLSStrColumn>& fls_str_column) { FLSStringIngest(*fls_str_column, val_str); },
	          [](auto&) { FLS_UNREACHABLE(); },
	          [](std::monostate&) { FLS_UNREACHABLE(); },
	      } // namespace fastlanes
	      ,
	      column);
}

struct rowgroup_visitor {
	explicit rowgroup_visitor(string& res, n_t row_idx)
	    : value(res)
	    , row_idx(row_idx) {};
	string&   value;
	const n_t row_idx;

	template <typename PT>
	void operator()(const up<TypedCol<PT>>& typed_col) {
		value = TypedToStr(*typed_col, row_idx);
	}

	void operator()(const up<Struct>& struct_col) {
		for (n_t col_idx {0}; col_idx < struct_col->internal_rowgroup.size(); ++col_idx) {
			string new_val;

			std::visit(rowgroup_visitor {new_val, row_idx}, struct_col->internal_rowgroup[col_idx]);

			if (col_idx == FIRST_IDX) {
				value = "{" + new_val;
				continue;
			}

			value = value + ", " + new_val;
		}
		value = value + "}";
	}

	void operator()(const up<FLSStrColumn>& str_col) {
		value = string(reinterpret_cast<const char*>(str_col->str_p_arr[row_idx]), str_col->length_arr[row_idx]);
	}

	void operator()(const auto&) {
		FLS_UNREACHABLE()
	}
};

string Attribute::ToStr(const col_pt& physical_column, n_t row_idx) {
	string res;
	visit(rowgroup_visitor {res, row_idx}, physical_column);

	return res;
}

} // namespace fastlanes