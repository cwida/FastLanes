// ────────────────────────────────────────────────────────
// |                      FastLanes                       |
// ────────────────────────────────────────────────────────
// src/include/fls/common/decimal.hpp
// ────────────────────────────────────────────────────────
#ifndef FLS_COMMON_DECIMAL_HPP
#define FLS_COMMON_DECIMAL_HPP

#include "fls/api/api.hpp"
#include "fls/common/common.hpp"
#include "fls/footer/decimal_type_generated.h"

namespace fastlanes {

FLS_API int64_t make_decimal(const std::string& value, n_t scale);
FLS_API up<DecimalTypeT> make_decimal_t(const std::string& value);

} // namespace fastlanes

#endif // FLS_COMMON_DECIMAL_HPP
