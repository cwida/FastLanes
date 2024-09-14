#include "fls/footer/col_description.hpp"
#include "fls/expression/data_type.hpp"

namespace fastlanes {
ColDescription::ColDescription(const idx_t idx, string name, const DataType data_t)
    : idx(idx)
    , name {std::move(name)}
    , type(data_t) {}

} // namespace fastlanes
