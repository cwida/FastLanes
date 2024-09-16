#include "fls/expression/data_type.hpp"
#include <fls/common/common.hpp>

namespace fastlanes {

uint64_t SizeOf(const DataType datatype) {
	switch (datatype) {
	case DataType::INT64:
		return sizeof(i64_pt);
	case DataType::DOUBLE:
		return sizeof(double);
	default:
		FLS_IMPLEMENT_THIS()
	}
}

} // namespace fastlanes