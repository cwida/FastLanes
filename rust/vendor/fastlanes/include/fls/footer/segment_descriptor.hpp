#ifndef FLS_FOOTER_SEGMENT_DESCRIPTOR_HPP
#define FLS_FOOTER_SEGMENT_DESCRIPTOR_HPP

#include "fls/footer/footer_generated.h"

namespace fastlanes {
constexpr size_t sizeof_entry_point_type(EntryPointType type) {
	switch (type) {
	case EntryPointType::UINT8:
		return 1;
	case EntryPointType::UINT16:
		return 2;
	case EntryPointType::UINT32:
		return 4;
	case EntryPointType::UINT64:
		return 8;
	default:
		return 0; // Handle unexpected values
	}
}

} // namespace fastlanes
#endif // FLS_FOOTER_SEGMENT_DESCRIPTOR_HPP