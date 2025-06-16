#ifndef FLS_FOOTER_ROWGROUP_DESCRIPTOR_HPP
#define FLS_FOOTER_ROWGROUP_DESCRIPTOR_HPP

#include "fls/footer/column_descriptor.hpp"
#include "fls/footer/rowgroup_descriptor_generated.h"
#include "fls/std/filesystem.hpp"

namespace fastlanes {
/*--------------------------------------------------------------------------------------------------------------------*/
class Rowgroup;
enum class DataType : uint8_t;
/*--------------------------------------------------------------------------------------------------------------------*/

using col_description_it       = vector<up<ColumnDescriptorT>>::iterator;
using const_col_description_it = vector<up<ColumnDescriptorT>>::const_iterator;

up<RowgroupDescriptorT> make_rowgroup_descriptor(const Rowgroup& rowgroup);
up<RowgroupDescriptorT> make_rowgroup_descriptor(const path& dir_path);

} // namespace fastlanes

#endif // FLS_FOOTER_ROWGROUP_DESCRIPTOR_HPP
