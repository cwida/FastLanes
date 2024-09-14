#ifndef FLS_UTL_BIT_UTIL_HPP
#define FLS_UTL_BIT_UTIL_HPP

#include "fls/common/common.hpp"

namespace fastlanes {
class bit {
public:
	static void set(uint64_t& unit, uint16_t pos);

	static bsz_t to_bytes(bsz_t bits);
};
} // namespace fastlanes
#endif // FLS_UTL_BIT_UTIL_HPP
