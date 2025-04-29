#ifndef FLS_PRIMITIVE_FLS_MEMSET_FLS_FLS_MEMSET_HPP
#define FLS_PRIMITIVE_FLS_MEMSET_FLS_FLS_MEMSET_HPP

#include "fls/common/concept.hpp"
#include <cstdint>

namespace fastlanes {

template <typename PT>
void fls_memset(const PT* __restrict in_p, PT* __restrict out_p);

template <typename PT1, typename PT2>
requires SAME_SIZE_TYPE<PT1, PT2>
void fls_memset(const PT1* __restrict in_p, PT2* __restrict out_p) {
	copy(in_p, reinterpret_cast<PT1*>(out_p)); // Ensure the proper call
}

} // namespace fastlanes
#endif // FLS_PRIMITIVE_FLS_MEMSET_FLS_FLS_MEMSET_HPP
