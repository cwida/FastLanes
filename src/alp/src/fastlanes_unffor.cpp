// ────────────────────────────────────────────────────────
// |                      FastLanes                       |
// ────────────────────────────────────────────────────────
// src/alp/src/fastlanes_unffor.cpp
// ────────────────────────────────────────────────────────
#include "fls/common/restrict.hpp"
#include "fls/unffor.hpp"
#include <cstdint>

namespace fastlanes::generated::unffor::fallback::scalar {

void unffor(const int64_t* FLS_RESTRICT in,
            int64_t* FLS_RESTRICT       out,
            uint8_t                     bw,
            const int64_t* FLS_RESTRICT a_base_p) {
	auto const* in_u   = reinterpret_cast<const uint64_t*>(in);
	auto*       out_u  = reinterpret_cast<uint64_t*>(out);
	auto const* base_u = reinterpret_cast<const uint64_t*>(a_base_p);

	unffor(in_u, out_u, bw, base_u);
}

void unffor(const int32_t* FLS_RESTRICT in,
            int32_t* FLS_RESTRICT       out,
            uint8_t                     bw,
            const int32_t* FLS_RESTRICT a_base_p) {
	auto const* in_u   = reinterpret_cast<const uint32_t*>(in);
	auto*       out_u  = reinterpret_cast<uint32_t*>(out);
	auto const* base_u = reinterpret_cast<const uint32_t*>(a_base_p);

	unffor(in_u, out_u, bw, base_u);
}

void unffor(const int16_t* FLS_RESTRICT in,
            int16_t* FLS_RESTRICT       out,
            uint8_t                     bw,
            const int16_t* FLS_RESTRICT a_base_p) {
	auto const* in_u   = reinterpret_cast<const uint16_t*>(in);
	auto*       out_u  = reinterpret_cast<uint16_t*>(out);
	auto const* base_u = reinterpret_cast<const uint16_t*>(a_base_p);

	unffor(in_u, out_u, bw, base_u);
}

void unffor(const int8_t* FLS_RESTRICT in, int8_t* FLS_RESTRICT out, uint8_t bw, const int8_t* FLS_RESTRICT a_base_p) {
	auto const* in_u   = reinterpret_cast<const uint8_t*>(in);
	auto*       out_u  = reinterpret_cast<uint8_t*>(out);
	auto const* base_u = reinterpret_cast<const uint8_t*>(a_base_p);

	unffor(in_u, out_u, bw, base_u);
}
} // namespace fastlanes::generated::unffor::fallback::scalar
