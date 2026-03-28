// ────────────────────────────────────────────────────────
// |                      FastLanes                       |
// ────────────────────────────────────────────────────────
// src/include/fls/common/restrict.hpp
// ────────────────────────────────────────────────────────
/* fastlanes/detail/restrict.hpp ----------------------------------------- */
#ifndef FASTLANES_DETAIL_RESTRICT_HPP_
#define FASTLANES_DETAIL_RESTRICT_HPP_

// C++23 has the standard attribute [[restrict]], but very few compilers
// expose it yet, so we fall back to vendor extensions first.
#if defined(__has_cpp_attribute)
#if __has_cpp_attribute(restrict) // Clang ≥ 18, GCC ≥ 15
#define FLS_RESTRICT [[restrict]]
#endif
#endif

#ifndef FLS_RESTRICT // GNU / Clang (all platforms, incl. macOS)
#if defined(__GNUC__) || defined(__clang__)
#define FLS_RESTRICT __restrict__
#endif
#endif

#ifndef FLS_RESTRICT // Microsoft Visual C++
#if defined(_MSC_VER)
#define FLS_RESTRICT __restrict
#endif
#endif

#ifndef FLS_RESTRICT // Very old or exotic compilers
#define FLS_RESTRICT /* nothing */
#endif

#endif /* FASTLANES_DETAIL_RESTRICT_HPP_ */
