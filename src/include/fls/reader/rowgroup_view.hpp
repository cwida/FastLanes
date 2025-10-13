// ────────────────────────────────────────────────────────
// |                      FastLanes                       |
// ────────────────────────────────────────────────────────
// src/include/fls/reader/rowgroup_view.hpp
// ────────────────────────────────────────────────────────
#ifndef FLS_READER_ROWGROUP_VIEW_HPP
#define FLS_READER_ROWGROUP_VIEW_HPP

#include "fls/std/span.hpp"
#include "fls/std/vector.hpp"

namespace fastlanes {
/*--------------------------------------------------------------------------------------------------------------------*/
struct RowgroupDescriptor;
class ColumnView;
/*--------------------------------------------------------------------------------------------------------------------*/

class RowgroupView {
public:
	explicit RowgroupView(span<std::byte> ptr, const RowgroupDescriptor& footer);

public:
	ColumnView&       operator[](n_t col_idx);
	const ColumnView& operator[](n_t col_idx) const;

public:
	vector<up<ColumnView>> columns;
};

} // namespace fastlanes

#endif // FLS_READER_ROWGROUP_VIEW_HPP
