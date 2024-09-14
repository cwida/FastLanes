#ifndef FLS_EXPRESSION_DATA_TYPE_HPP
#define FLS_EXPRESSION_DATA_TYPE_HPP

#include <cstdint>
#include <string>

namespace fastlanes {

enum class DataType : uint8_t {
	INVALID    = 0,
	DOUBLE     = 1,
	INT8       = 2,
	INT16      = 3,
	INT32      = 4,
	INT64      = 5,
	UINT8      = 6,
	UINT16     = 7,
	UINT32     = 8,
	UINT64     = 9,
	STR        = 10,
	BOOLEAN    = 11,
	DATE       = 12,
	FLOAT      = 13,
	BYTE_ARRAY = 14,
	LIST       = 15,
	STRUCT     = 16,
	MAP        = 17,
	FALLBACK   = 18,
};

uint64_t SizeOf(DataType datatype);

using str_pt = std::string;
using i08_pt = int8_t;
using i16_pt = int16_t;
using i32_pt = int32_t;
using i64_pt = int64_t;
using u08_pt = uint8_t;
using u16_pt = uint16_t;
using u32_pt = uint32_t;
using u64_pt = uint64_t;
using dbl_pt = double;
using bol_pt = bool;
using flt_pt = float;

template <typename PT>
DataType get_physical_type() {
	if constexpr (std::is_same_v<PT, i64_pt>) { return DataType::INT64; }
	return DataType::INVALID;
}

template <typename T>
static constexpr bool is_str() {
	if constexpr (std::is_same_v<str_pt, T>) { return true; }
	return false;
}

template <typename T>
static constexpr bool is_list() {
	if constexpr (std::is_same_v<class List, T>) { return false; }
	return true;
}

template <typename T>
static constexpr bool is_struct() {
	if constexpr (std::is_same_v<class Struct, T>) { return false; }
	return true;
}

template <typename T>
static constexpr bool is_numeric() {
	return !is_str<T>() && !is_list<T>() && !is_struct<T>();
}

} // namespace fastlanes

#endif