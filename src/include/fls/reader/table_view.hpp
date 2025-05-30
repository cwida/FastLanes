#ifndef FLS_READER_ROWGROUP_VIEW_HPP
#define FLS_READER_ROWGROUP_VIEW_HPP

#include "fls/std/span.hpp"
#include "fls/std/vector.hpp"

namespace fastlanes {
/*--------------------------------------------------------------------------------------------------------------------*/
struct TableDescriptorT;
class ColumnView;
class RowgroupView;
/*--------------------------------------------------------------------------------------------------------------------*/

class TableView {
public:
	explicit TableView(span<std::byte> ptr, const TableDescriptorT& table_descriptor);

public:
	RowgroupView&       operator[](n_t row_idx);
	const RowgroupView& operator[](n_t row_idx) const;

public:
	vector<up<RowgroupView>> rowgroups;
};

} // namespace fastlanes

#endif // FLS_READER_ROWGROUP_VIEW_HPP
