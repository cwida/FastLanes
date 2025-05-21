#ifndef FLS_COMMON_DECIMAL_HPP
#define FLS_COMMON_DECIMAL_HPP

#include "fls/common/common.hpp"
#include "fls/footer/decimal_type_generated.h"

namespace fastlanes {

int64_t          make_decimal(const std::string& value, n_t scale);
up<DecimalTypeT> make_decimal_t(const std::string& value);

} // namespace fastlanes

#endif // FLS_COMMON_DECIMAL_HPP
