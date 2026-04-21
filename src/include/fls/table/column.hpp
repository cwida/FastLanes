// ────────────────────────────────────────────────────────
// |                      FastLanes                       |
// ────────────────────────────────────────────────────────
// src/include/fls/table/column.hpp
// ────────────────────────────────────────────────────────
#ifndef FLS_TABLE_COLUMN_HPP
#define FLS_TABLE_COLUMN_HPP

#include "fls/api/api.hpp"
#include "fls/table/rowgroup.hpp"

namespace fastlanes {
/*--------------------------------------------------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------------------------------------------------*/
class FLS_API Column {
public:
	static bool is_good_for_ditionary_encoding(const col_pt& col);
};

} // namespace fastlanes
#endif // FLS_TABLE_COLUMN_HPP
