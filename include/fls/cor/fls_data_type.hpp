#ifndef FLS_COR_FLS_DATA_TYPE_HPP
#define FLS_COR_FLS_DATA_TYPE_HPP

#include <cstdint>

namespace fastlanes {
enum class fls_t : uint8_t { // NOLINT
	FLS08_T = 1,
	FLS16_T = 2,
	FLS32_T = 3,
	FLS64_T = 4,
	FLS_SMT = 5, /* same type, propagate the encoder type. */
	FLS_DBT = 6, /* same type, propagate the encoder type. */

};
} // namespace fastlanes
#endif // FLS_COR_FLS_DATA_TYPE_HPP
