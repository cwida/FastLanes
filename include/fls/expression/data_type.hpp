#ifndef FLS_EXPRESSION_DATA_TYPE_HPP
#define FLS_EXPRESSION_DATA_TYPE_HPP

#include "fls/footer/datatype_generated.h"
#include <cstdint>
#include <string>

namespace fastlanes {

/*--------------------------------------------------------------------------------------------------------------------*\
 * ToSt :
\*--------------------------------------------------------------------------------------------------------------------*/
std::string ToStr(DataType type);

/*--------------------------------------------------------------------------------------------------------------------*\
 * SizeOf :
\*--------------------------------------------------------------------------------------------------------------------*/
uint64_t SizeOf(DataType datatype);

/*--------------------------------------------------------------------------------------------------------------------*\
 * Overload << operator
\*--------------------------------------------------------------------------------------------------------------------*/
std::ostream& operator<<(std::ostream& os, DataType type);

/*--------------------------------------------------------------------------------------------------------------------*\
 * PT
\*--------------------------------------------------------------------------------------------------------------------*/
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

/*--------------------------------------------------------------------------------------------------------------------*\
 * get_physical_type
\*--------------------------------------------------------------------------------------------------------------------*/
template <typename PT>
DataType get_physical_type();

template <typename T>
static constexpr bool is_str() {
	if constexpr (std::is_same_v<str_pt, T>) {
		return true;
	}
	return false;
}

template <typename T>
static constexpr bool is_list() {
	if constexpr (std::is_same_v<class List, T>) {
		return false;
	}
	return true;
}

template <typename T>
static constexpr bool is_struct() {
	if constexpr (std::is_same_v<class Struct, T>) {
		return false;
	}
	return true;
}

template <typename T>
static constexpr bool is_numeric() {
	return !is_str<T>() && !is_list<T>() && !is_struct<T>();
}
} // namespace fastlanes

#endif