#ifndef FLS_TABLE_COLUMN_HPP
#define FLS_TABLE_COLUMN_HPP

#include "fls/table/rowgroup.hpp"

namespace fastlanes {
/*--------------------------------------------------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------------------------------------------------*/
class Column {
public:
	static bool is_good_for_ditionary_encoding(const col_pt& col);
};

} // namespace fastlanes
#endif // FLS_TABLE_COLUMN_HPP