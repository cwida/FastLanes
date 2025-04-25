#include "fls/footer/column_descriptor.hpp"
#include "fls/expression/data_type.hpp"

namespace fastlanes {

ColumnDescriptor::ColumnDescriptor()
    : data_type(DataType::INVALID)
    , encoding_rpn {}
    , idx(0)
    , column_offset(0)
    , total_size {0}
    , n_null(0) {};

ColumnDescriptor::ColumnDescriptor(const idx_t idx, string name, const DataType type)
    : data_type(type)
    , idx(idx)
    , name {std::move(name)}
    , column_offset(0)
    , total_size(0)
    , n_null(0)
    , fix_me_decimal_type() {
}

} // namespace fastlanes
