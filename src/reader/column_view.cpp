#include "fls/reader/column_view.hpp"
#include "fls/common/assert.hpp"
#include "fls/footer/column_descriptor.hpp"
#include "fls/footer/rowgroup_descriptor.hpp"
#include "fls/logger/logger.hpp"
#include "fls/reader/segment.hpp"

namespace fastlanes {

ColumnView::ColumnView(const span<std::byte>      column_span,
                       const ColumnDescriptorT&   column_descriptor,
                       const RowgroupDescriptorT& rowgroup_descriptor)
    : column_span(column_span)
    , column_descriptor(column_descriptor) {
	for (n_t child_col_idx {0}; child_col_idx < column_descriptor.children.size(); ++child_col_idx) {

		auto& child_column_descriptor = column_descriptor.children[child_col_idx];
		children.emplace_back(column_span, *child_column_descriptor, rowgroup_descriptor);
	}
}

SegmentView ColumnView::GetSegment(n_t segment_idx) const {
	FLS_ASSERT_L(segment_idx, column_descriptor.segment_descriptors.size());

	return make_segment_view(column_span, *column_descriptor.segment_descriptors[segment_idx]);
}

} // namespace fastlanes