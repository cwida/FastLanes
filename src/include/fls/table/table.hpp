#ifndef FLS_TABLE_TABLE_HPP
#define FLS_TABLE_TABLE_HPP

#include "fls/common/alias.hpp"
#include "fls/std/vector.hpp"
#include <fls/std/string.hpp>

namespace fastlanes {
/*--------------------------------------------------------------------------------------------------------------------*/
class Rowgroup;
class Connection;
/*--------------------------------------------------------------------------------------------------------------------*/
class TableComparisonResult {
public:
	bool   is_equal {true};
	n_t    first_failed_rowgroup_idx {0};
	n_t    first_failed_column_idx {0};
	n_t    first_failed_row_idx {0};
	string description;
};

class Table {
public:
	Table(const Connection& connection);

public:
	n_t get_n_rowgroups() const;

public:
	//
	[[nodiscard]] up<Table> Project(const vector<idx_t>& idxs);
	//
	[[nodiscard]] Rowgroup& GetRowgroup(n_t idx) const;
	//
	TableComparisonResult operator==(const Table& other_table) const;

public:
	vector<up<Rowgroup>> m_rowgroups;
	const Connection&    m_connection;
};
} // namespace fastlanes

#endif // FLS_TABLE_TABLE_HPP
