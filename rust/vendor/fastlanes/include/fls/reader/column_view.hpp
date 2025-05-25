#ifndef FLS_READER_COLUMN_VIEW_HPP
#define FLS_READER_COLUMN_VIEW_HPP

#include "fls/common/alias.hpp"
#include "fls/std/span.hpp"
#include "fls/std/vector.hpp"

namespace fastlanes {
/*--------------------------------------------------------------------------------------------------------------------*/
struct ColumnDescriptorT;
struct RowgroupDescriptorT;
class SegmentView;
/*--------------------------------------------------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------------------------------------------------*\
 * ColumnView
\*--------------------------------------------------------------------------------------------------------------------*/
class ColumnView {
public:
	explicit ColumnView(span<std::byte>            column_span,
	                    const ColumnDescriptorT&   column_descriptor,
	                    const RowgroupDescriptorT& rowgroup_descriptor);
	[[nodiscard]] SegmentView GetSegment(n_t segment_idx) const;

public:
	span<std::byte>          column_span;
	const ColumnDescriptorT& column_descriptor;
	vector<ColumnView>       children;
};

} // namespace fastlanes

#endif // FLS_READER_COLUMN_VIEW_HPP