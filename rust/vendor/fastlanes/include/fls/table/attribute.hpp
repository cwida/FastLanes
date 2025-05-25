#ifndef FLS_TABLE_ATTRIBUTE_HPP
#define FLS_TABLE_ATTRIBUTE_HPP

#include "fls/common/common.hpp"
#include "fls/std/string.hpp"
#include "fls/table/rowgroup.hpp"

namespace fastlanes {
/*--------------------------------------------------------------------------------------------------------------------*/
template <typename PT>
class TypedCol;
/*--------------------------------------------------------------------------------------------------------------------*/
class Attribute {
public:
	Attribute() = delete;

public:
	static void   Ingest(col_pt& typed_column, const string& val_str, const ColumnDescriptorT& column_descriptor);
	static string ToStr(const col_pt& typed_column, n_t row_idx);
};

} // namespace fastlanes
#endif // FLS_TABLE_ATTRIBUTE_HPP
