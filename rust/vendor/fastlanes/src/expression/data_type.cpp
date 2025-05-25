#include "fls/expression/data_type.hpp"
#include "fls/common/common.hpp"
#include <iostream>

namespace fastlanes {

std::string ToStr(DataType type) {
	switch (type) {
	case DataType::INVALID:
		return "INVALID";
	case DataType::DOUBLE:
		return "DOUBLE";
	case DataType::INT8:
		return "INT8";
	case DataType::INT16:
		return "INT16";
	case DataType::INT32:
		return "INT32";
	case DataType::INT64:
		return "INT64";
	case DataType::UINT8:
		return "UINT8";
	case DataType::UINT16:
		return "UINT16";
	case DataType::UINT32:
		return "UINT32";
	case DataType::UINT64:
		return "UINT64";
	case DataType::STR:
		return "STR";
	case DataType::BOOLEAN:
		return "BOOLEAN";
	case DataType::DATE:
		return "DATE";
	case DataType::FLOAT:
		return "FLOAT";
	case DataType::BYTE_ARRAY:
		return "BYTE_ARRAY";
	case DataType::LIST:
		return "LIST";
	case DataType::STRUCT:
		return "STRUCT";
	case DataType::MAP:
		return "MAP";
	case DataType::FALLBACK:
		return "FALLBACK";
	case DataType::FLS_STR:
		return "FLS_STR";
	default:
		return "UNKNOWN";
	}
}

uint64_t SizeOf(const DataType datatype) {
	switch (datatype) {
	case DataType::INT64:
		return sizeof(i64_pt);
	case DataType::INT32:
		return sizeof(i32_pt);
	case DataType::INT16:
		return sizeof(i16_pt);
	case DataType::DOUBLE:
		return sizeof(dbl_pt);
	case DataType::FLOAT:
		return sizeof(flt_pt);
	default:
		FLS_UNREACHABLE();
	}
}

template <typename PT>
DataType get_physical_type() {
	if constexpr (std::is_same_v<PT, i64_pt>) {
		return DataType::INT64;
	} else if constexpr (std::is_same_v<PT, i32_pt>) {
		return DataType::INT32;
	} else if constexpr (std::is_same_v<PT, i16_pt>) {
		return DataType::INT16;
	} else if constexpr (std::is_same_v<PT, dbl_pt>) {
		return DataType::DOUBLE;
	} else if constexpr (std::is_same_v<PT, u08_pt>) {
		return DataType::UINT8;
	}
	FLS_UNREACHABLE()
};

std::ostream& operator<<(std::ostream& os, DataType type) {
	return os << ToStr(type);
}

template DataType get_physical_type<i64_pt>();
template DataType get_physical_type<i32_pt>();
template DataType get_physical_type<i16_pt>();
template DataType get_physical_type<i08_pt>();
template DataType get_physical_type<u64_pt>();
template DataType get_physical_type<u32_pt>();
template DataType get_physical_type<u16_pt>();
template DataType get_physical_type<u08_pt>();
template DataType get_physical_type<dbl_pt>();
template DataType get_physical_type<flt_pt>();
template DataType get_physical_type<str_pt>();

} // namespace fastlanes