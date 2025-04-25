#ifndef FLS_GEN_UNTRANSPOSE_UNTRANSPOSE_HPP
#define FLS_GEN_UNTRANSPOSE_UNTRANSPOSE_HPP

#include <cstdint>

namespace generated { namespace untranspose {
namespace fallback { namespace scalar {
void        untranspose_i(const double* __restrict in, double* __restrict out);
void        untranspose_i(const uint64_t* __restrict in, uint64_t* __restrict out);
void        untranspose_i(const uint32_t* __restrict in, uint32_t* __restrict out);
void        untranspose_i(const uint16_t* __restrict in, uint16_t* __restrict out);
void        untranspose_i(const uint8_t* __restrict in, uint8_t* __restrict out);
void        untranspose_o(const double* __restrict in, double* __restrict out);
void        untranspose_o(const uint64_t* __restrict in, uint64_t* __restrict out);
void        untranspose_o(const uint32_t* __restrict in, uint32_t* __restrict out);
void        untranspose_o(const uint16_t* __restrict in, uint16_t* __restrict out);
void        untranspose_o(const uint8_t* __restrict in, uint8_t* __restrict out);
inline void untranspose_i(const int64_t* __restrict in, int64_t* __restrict out) {
	untranspose_i(reinterpret_cast<const uint64_t*>(in), reinterpret_cast<uint64_t*>(out));
}
inline void untranspose_i(const int32_t* __restrict in, int32_t* __restrict out) {
	untranspose_i(reinterpret_cast<const uint32_t*>(in), reinterpret_cast<uint32_t*>(out));
}
inline void untranspose_i(const float* __restrict in, float* __restrict out) {
	untranspose_i(reinterpret_cast<const uint32_t*>(in), reinterpret_cast<uint32_t*>(out));
}
inline void untranspose_i(const int16_t* __restrict in, int16_t* __restrict out) {
	untranspose_i(reinterpret_cast<const uint16_t*>(in), reinterpret_cast<uint16_t*>(out));
}
inline void untranspose_i(const int8_t* __restrict in, int8_t* __restrict out) {
	untranspose_i(reinterpret_cast<const uint8_t*>(in), reinterpret_cast<uint8_t*>(out));
}
}} // namespace fallback::scalar

namespace helper { namespace scalar {
void untranspose_i(const uint64_t* __restrict in, uint64_t* __restrict out);
void untranspose_i(const uint32_t* __restrict in, uint32_t* __restrict out);
void untranspose_i(const uint16_t* __restrict in, uint16_t* __restrict out);
void untranspose_i(const uint8_t* __restrict in, uint8_t* __restrict out);
void untranspose_o(const uint64_t* __restrict in, uint64_t* __restrict out);
void untranspose_o(const uint32_t* __restrict in, uint32_t* __restrict out);
void untranspose_o(const uint16_t* __restrict in, uint16_t* __restrict out);
void untranspose_o(const uint8_t* __restrict in, uint8_t* __restrict out);
}} // namespace helper::scalar

namespace neon {
void untranspose_i(const uint64_t* __restrict in, uint64_t* __restrict out);
void untranspose_i(const uint32_t* __restrict in, uint32_t* __restrict out);
void untranspose_i(const uint16_t* __restrict in, uint16_t* __restrict out);
void untranspose_i(const uint8_t* __restrict in, uint8_t* __restrict out);
void untranspose_o(const uint64_t* __restrict in, uint64_t* __restrict out);
void untranspose_o(const uint32_t* __restrict in, uint32_t* __restrict out);
void untranspose_o(const uint16_t* __restrict in, uint16_t* __restrict out);
void untranspose_o(const uint8_t* __restrict in, uint8_t* __restrict out);
} // namespace neon

namespace avx2 {
void untranspose_i(const uint64_t* __restrict in, uint64_t* __restrict out);
void untranspose_i(const uint32_t* __restrict in, uint32_t* __restrict out);
void untranspose_i(const uint16_t* __restrict in, uint16_t* __restrict out);
void untranspose_i(const uint8_t* __restrict in, uint8_t* __restrict out);
void untranspose_o(const uint64_t* __restrict in, uint64_t* __restrict out);
void untranspose_o(const uint32_t* __restrict in, uint32_t* __restrict out);
void untranspose_o(const uint16_t* __restrict in, uint16_t* __restrict out);
void untranspose_o(const uint8_t* __restrict in, uint8_t* __restrict out);
} // namespace avx2

namespace sse {
void untranspose_i(const uint64_t* __restrict in, uint64_t* __restrict out);
void untranspose_i(const uint32_t* __restrict in, uint32_t* __restrict out);
void untranspose_i(const uint16_t* __restrict in, uint16_t* __restrict out);
void untranspose_i(const uint8_t* __restrict in, uint8_t* __restrict out);
void untranspose_o(const uint64_t* __restrict in, uint64_t* __restrict out);
void untranspose_o(const uint32_t* __restrict in, uint32_t* __restrict out);
void untranspose_o(const uint16_t* __restrict in, uint16_t* __restrict out);
void untranspose_o(const uint8_t* __restrict in, uint8_t* __restrict out);
} // namespace sse

namespace avx512bw {
void untranspose_i(const uint64_t* __restrict in, uint64_t* __restrict out);
void untranspose_i(const uint32_t* __restrict in, uint32_t* __restrict out);
void untranspose_i(const uint16_t* __restrict in, uint16_t* __restrict out);
void untranspose_i(const uint8_t* __restrict in, uint8_t* __restrict out);
void untranspose_o(const uint64_t* __restrict in, uint64_t* __restrict out);
void untranspose_o(const uint32_t* __restrict in, uint32_t* __restrict out);
void untranspose_o(const uint16_t* __restrict in, uint16_t* __restrict out);
void untranspose_o(const uint8_t* __restrict in, uint8_t* __restrict out);
} // namespace avx512bw
}} // namespace generated::untranspose

#endif
