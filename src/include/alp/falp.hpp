// ────────────────────────────────────────────────────────
// |                      FastLanes                       |
// ────────────────────────────────────────────────────────
// src/include/alp/falp.hpp
// ────────────────────────────────────────────────────────
#ifndef ALP_FALP_HPP
#define ALP_FALP_HPP

#include <cstdint>

namespace generated::falp::fallback::scalar {

void falp(const uint64_t* __restrict in,
          double* __restrict out,
          uint8_t bw,
          const uint64_t* __restrict a_base_p,
          uint8_t factor,
          uint8_t exponent);

inline void falp(const int64_t* __restrict in,
                 double* __restrict out,
                 uint8_t bw,
                 const int64_t* __restrict base,
                 const uint8_t factor,
                 uint8_t       exponent) {
	const auto* in_p   = reinterpret_cast<const uint64_t*>(in);
	const auto* base_p = reinterpret_cast<const uint64_t*>(base);
	falp(in_p, out, bw, base_p, factor, exponent);
}

void falp(const uint32_t* __restrict in,
          float* __restrict out,
          uint8_t bw,
          const uint32_t* __restrict base,
          uint8_t factor,
          uint8_t exponent);

inline void falp(const int32_t* __restrict in,
                 float* __restrict out,
                 uint8_t bw,
                 const int32_t* __restrict base,
                 uint8_t factor,
                 uint8_t exponent) {
	const auto* in_p   = reinterpret_cast<const uint32_t*>(in);
	const auto* base_p = reinterpret_cast<const uint32_t*>(base);
	falp(in_p, out, bw, base_p, factor, exponent);
}
} // namespace generated::falp::fallback::scalar

#endif // ALP_FALP_HPP
