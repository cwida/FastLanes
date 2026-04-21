// ────────────────────────────────────────────────────────
// |                      FastLanes                       |
// ────────────────────────────────────────────────────────
// src/include/fls/reader/fls_rowgroup.hpp
// ────────────────────────────────────────────────────────
#ifndef FLS_READER_FLS_ROWGROUP_HPP
#define FLS_READER_FLS_ROWGROUP_HPP

#include "fls/api/api.hpp"
#include "fls/std/span.hpp"
#include "fls/std/vector.hpp"

namespace fastlanes {
/*--------------------------------------------------------------------------------------------------------------------*/
class RowgroupDescriptor;
class ColumnView;
/*--------------------------------------------------------------------------------------------------------------------*/

class FLS_API RowgroupView {
public:
	explicit RowgroupView(span<std::byte> ptr, const RowgroupDescriptor& footer);

public:
	ColumnView&       operator[](n_t col_idx);
	const ColumnView& operator[](n_t col_idx) const;

public:
	vector<up<ColumnView>> columns;
};

} // namespace fastlanes

#endif // FLS_READER_FLS_ROWGROUP_HPP
