#ifndef FLS_READER_TABLE_READER_HPP
#define FLS_READER_TABLE_READER_HPP

#include "fls/common/alias.hpp"
#include "fls/std/filesystem.hpp"
#include "fls/std/string.hpp"

namespace fastlanes {
/*--------------------------------------------------------------------------------------------------------------------*/
class Connection;
class RowgroupReader;
struct TableDescriptorT;
class Table;
/*--------------------------------------------------------------------------------------------------------------------*/
class TableReader {
public:
	explicit TableReader(const path& file_path, Connection& fls);

public:
	up<RowgroupReader> operator[](n_t rowgroup_idx) const;
	//
	[[nodiscard]] up<RowgroupReader> get_rowgroup_reader(n_t rowgroup_idx) const;
	//
	[[nodiscard]] up<Table> materialize() const;
	// API: append to the existing csv.
	// write to the fle path
	void to_csv(const path& file_path) const;
	void to_csv(const string& file_path) const;
	void to_csv(const char* file_path) const;

private:
	up<TableDescriptorT> m_table_descriptor;
	Connection&          m_connection;
	const path           m_file_path;
};

} // namespace fastlanes

#endif
