#ifndef FLS_COMMON_DOUBLE_HPP
#define FLS_COMMON_DOUBLE_HPP

#include "fls/common/common.hpp"

namespace fastlanes {
class Double {
public:
	static bool is_safely_castable_to_int64(dbl_pt value);
};
} // namespace fastlanes

#endif // FLS_COMMON_DOUBLE_HPP
