#ifndef FLS_FOOTER_COLUMN_DESCRIPTOR_HPP
#define FLS_FOOTER_COLUMN_DESCRIPTOR_HPP

#include "fls/common/alias.hpp"
#include "fls/common/decimal.hpp"
#include "fls/expression/data_type.hpp"
#include "fls/expression/rpn.hpp" // for NewRPN
#include "fls/footer/column_descriptor_generated.h"
#include "fls/footer/decimal_type_generated.h"
#include "fls/footer/footer_generated.h"
#include "fls/std/string.hpp"
#include "fls/std/unordered_map.hpp"
#include "fls/std/vector.hpp"

namespace fastlanes {
/*--------------------------------------------------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------------------------------------------*\
 * ColumnDescriptor
\*--------------------------------------------------------------------------------------------------------------------*/
using ColumnDescriptors = vector<up<struct ColumnDescriptorT>>;

/*--------------------------------------------------------------------------------------------------------------------*\
 * set index
\*--------------------------------------------------------------------------------------------------------------------*/
void set_index(vector<up<ColumnDescriptorT>>& column_descriptors);

} // namespace fastlanes
#endif // FLS_FOOTER_COLUMN_DESCRIPTOR_HPP
