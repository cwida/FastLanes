// ────────────────────────────────────────────────────────
// |                      FastLanes                       |
// ────────────────────────────────────────────────────────
// src/include/fls/primitive/copy/fls_copy.hpp
// ────────────────────────────────────────────────────────
#ifndef FLS_PRIMITIVE_COPY_FLS_COPY_HPP
#define FLS_PRIMITIVE_COPY_FLS_COPY_HPP

#include "fls/common/concept.hpp"
#include "fls/common/restrict.hpp"
#include <cstdint>

namespace fastlanes {

template <typename PT>
void copy(const PT* FLS_RESTRICT in_p, PT* FLS_RESTRICT out_p);

template <typename PT1, typename PT2>
requires SAME_SIZE_TYPE<PT1, PT2>
void copy(const PT1* FLS_RESTRICT in_p, PT2* FLS_RESTRICT out_p) {
	copy(in_p, reinterpret_cast<PT1*>(out_p)); // Ensure the proper call
}

} // namespace fastlanes
#endif // FLS_PRIMITIVE_COPY_FLS_COPY_HPP
