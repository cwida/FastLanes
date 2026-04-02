// ────────────────────────────────────────────────────────
// |                      FastLanes                       |
// ────────────────────────────────────────────────────────
// src/include/fls/reader/table_view.hpp
// ────────────────────────────────────────────────────────
#ifndef FLS_READER_TABLE_VIEW_HPP
#define FLS_READER_TABLE_VIEW_HPP

#include "fls/api/api.hpp"
#include "fls/reader/rowgroup_view.hpp"
#include "fls/std/span.hpp"
#include "fls/std/vector.hpp"

namespace fastlanes {
/*--------------------------------------------------------------------------------------------------------------------*/
struct TableDescriptorT;
/*--------------------------------------------------------------------------------------------------------------------*/

class FLS_API TableView {
public:
	explicit TableView(span<std::byte> ptr, const TableDescriptorT& table_descriptor);

	~TableView();
	TableView(const TableView&)            = delete;
	TableView& operator=(const TableView&) = delete;
	TableView(TableView&&) noexcept;
	TableView& operator=(TableView&&) noexcept;

public:
	RowgroupView&       operator[](n_t row_idx);
	const RowgroupView& operator[](n_t row_idx) const;

public:
	vector<up<RowgroupView>> rowgroups;
};

} // namespace fastlanes

#endif // FLS_READER_TABLE_VIEW_HPP
