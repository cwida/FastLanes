#ifndef FLS_READER_CSV_READER_HPP
#define FLS_READER_CSV_READER_HPP

#include "fls/common/alias.hpp" // for up, idx_t
#include "fls/std/filesystem.hpp"

namespace fastlanes {
/*--------------------------------------------------------------------------------------------------------------------*/
class Table;
struct RowgroupDescriptorT;
class Connection;
/*--------------------------------------------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------------------------------------------*\
 * CsvReader
\*--------------------------------------------------------------------------------------------------------------------*/
class CsvReader {
public:
	static up<Table> Read(const path& dir_path, const Connection& connection);
};

} // namespace fastlanes

#endif // FLS_READER_CSV_READER_HPP
