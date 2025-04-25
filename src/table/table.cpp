#include "fls/table/table.hpp"
#include "fls/connection.hpp"
#include "fls/table/rowgroup.hpp"

namespace fastlanes {

Table::Table(const Connection& connection)
    : m_connection(connection) {
}
n_t Table::get_n_rowgroups() const {
	return m_rowgroups.size();
}

up<Table> Table::Project(const vector<idx_t>& idxs) {
	auto result_table_up = make_unique<Table>(m_connection);
	for (const auto& rowgroup : m_rowgroups) {
		result_table_up->m_rowgroups.push_back(rowgroup->Project(idxs, m_connection));
	}

	return result_table_up;
}

Rowgroup& Table::GetRowgroup(const n_t idx) const {
	return *m_rowgroups[idx];
}

TableComparisonResult Table::operator==(const Table& other_table) const {
	TableComparisonResult result {
	    true,
	    0,
	    0,
	    0,
	    "",
	};

	if (this->m_rowgroups.size() != other_table.m_rowgroups.size()) {
		result.is_equal    = false;
		result.description = "number of rowgroups does not match";
		return result;
	}

	for (n_t rowgroup_idx = 0; rowgroup_idx < this->m_rowgroups.size(); rowgroup_idx++) {
		const auto rowgroup_result = *m_rowgroups[rowgroup_idx] == *other_table.m_rowgroups[rowgroup_idx];
		if (!rowgroup_result.is_equal) {
			result.is_equal                  = false;
			result.first_failed_column_idx   = rowgroup_result.first_failed_column_idx;
			result.first_failed_rowgroup_idx = rowgroup_idx;

			result.description = "the content of table does not match at rowgroup"         //
			                     + std::to_string(rowgroup_idx)                            //
			                     + ", at column index"                                     //
			                     + std::to_string(rowgroup_result.first_failed_column_idx) //
			                     + "does not match.";
			return result;
		}
	}

	return result;
}

} // namespace fastlanes