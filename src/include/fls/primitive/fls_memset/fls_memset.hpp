// ────────────────────────────────────────────────────────
// |                      FastLanes                       |
// ────────────────────────────────────────────────────────
// src/include/fls/primitive/fls_memset/fls_memset.hpp
// ────────────────────────────────────────────────────────
#ifndef FLS_PRIMITIVE_FLS_MEMSET_FLS_FLS_MEMSET_HPP
#define FLS_PRIMITIVE_FLS_MEMSET_FLS_FLS_MEMSET_HPP

#include "fls/common/concept.hpp"
#include "fls/common/restrict.hpp"
#include <cstdint>

namespace fastlanes {

template <typename PT>
void fls_memset(const PT* FLS_RESTRICT in_p, PT* FLS_RESTRICT out_p);

template <typename PT1, typename PT2>
requires SAME_SIZE_TYPE<PT1, PT2>
void fls_memset(const PT1* FLS_RESTRICT in_p, PT2* FLS_RESTRICT out_p) {
	copy(in_p, reinterpret_cast<PT1*>(out_p)); // Ensure the proper call
}

} // namespace fastlanes
#endif // FLS_PRIMITIVE_FLS_MEMSET_FLS_FLS_MEMSET_HPP
