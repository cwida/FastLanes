#include "fls/footer/segment_descriptor.hpp"

namespace fastlanes {

SegmentDescriptor::SegmentDescriptor()
    : entrypoint_offset(0)
    , entrypoint_size(0)
    , data_offset(0)
    , data_size(0) {
}

SegmentDescriptor::SegmentDescriptor(n_t entrypoint_offset, n_t entrypoint_size, n_t data_offset, n_t data_size)
    : entrypoint_offset(entrypoint_offset)
    , entrypoint_size(entrypoint_size)
    , data_offset(data_offset)
    , data_size(data_size) {
}

} // namespace fastlanes