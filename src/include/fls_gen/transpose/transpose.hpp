#ifndef FLS_GEN_TRANSPOSE_TRANSPOSE_HPP
#define FLS_GEN_TRANSPOSE_TRANSPOSE_HPP

#include <cstdint>

namespace generated { namespace transpose {
namespace fallback { namespace scalar {
void        transpose_i(const double* __restrict in, double* __restrict out);
void        transpose_i(const uint64_t* __restrict in, uint64_t* __restrict out);
void        transpose_i(const uint32_t* __restrict in, uint32_t* __restrict out);
void        transpose_i(const uint16_t* __restrict in, uint16_t* __restrict out);
void        transpose_i(const uint8_t* __restrict in, uint8_t* __restrict out);
void        transpose_o(const double* __restrict in, double* __restrict out);
void        transpose_o(const uint64_t* __restrict in, uint64_t* __restrict out);
void        transpose_o(const uint32_t* __restrict in, uint32_t* __restrict out);
void        transpose_o(const uint16_t* __restrict in, uint16_t* __restrict out);
void        transpose_o(const uint8_t* __restrict in, uint8_t* __restrict out);
inline void transpose_i(const int64_t* __restrict in, int64_t* __restrict out) {
	transpose_i(reinterpret_cast<const uint64_t*>(in), reinterpret_cast<uint64_t*>(out));
}
inline void transpose_i(const int32_t* __restrict in, int32_t* __restrict out) {
	transpose_i(reinterpret_cast<const uint32_t*>(in), reinterpret_cast<uint32_t*>(out));
}
inline void transpose_i(const int16_t* __restrict in, int16_t* __restrict out) {
	transpose_i(reinterpret_cast<const uint16_t*>(in), reinterpret_cast<uint16_t*>(out));
}
inline void transpose_i(const int8_t* __restrict in, int8_t* __restrict out) {
	transpose_i(reinterpret_cast<const uint8_t*>(in), reinterpret_cast<uint8_t*>(out));
}

}} // namespace fallback::scalar

namespace helper { namespace scalar {
void transpose_i(const uint64_t* __restrict in, uint64_t* __restrict out);
void transpose_i(const uint32_t* __restrict in, uint32_t* __restrict out);
void transpose_i(const uint16_t* __restrict in, uint16_t* __restrict out);
void transpose_i(const uint8_t* __restrict in, uint8_t* __restrict out);
void transpose_o(const uint64_t* __restrict in, uint64_t* __restrict out);
void transpose_o(const uint32_t* __restrict in, uint32_t* __restrict out);
void transpose_o(const uint16_t* __restrict in, uint16_t* __restrict out);
void transpose_o(const uint8_t* __restrict in, uint8_t* __restrict out);
}} // namespace helper::scalar

namespace arm64v8 { namespace neon {
void transpose_i(const uint64_t* __restrict in, uint64_t* __restrict out);
void transpose_i(const uint32_t* __restrict in, uint32_t* __restrict out);
void transpose_i(const uint16_t* __restrict in, uint16_t* __restrict out);
void transpose_i(const uint8_t* __restrict in, uint8_t* __restrict out);
void transpose_o(const uint64_t* __restrict in, uint64_t* __restrict out);
void transpose_o(const uint32_t* __restrict in, uint32_t* __restrict out);
void transpose_o(const uint16_t* __restrict in, uint16_t* __restrict out);
void transpose_o(const uint8_t* __restrict in, uint8_t* __restrict out);
}} // namespace arm64v8::neon

namespace x86_64 {
namespace avx2 {
void transpose_i(const uint64_t* __restrict in, uint64_t* __restrict out);
void transpose_i(const uint32_t* __restrict in, uint32_t* __restrict out);
void transpose_i(const uint16_t* __restrict in, uint16_t* __restrict out);
void transpose_i(const uint8_t* __restrict in, uint8_t* __restrict out);
void transpose_o(const uint64_t* __restrict in, uint64_t* __restrict out);
void transpose_o(const uint32_t* __restrict in, uint32_t* __restrict out);
void transpose_o(const uint16_t* __restrict in, uint16_t* __restrict out);
void transpose_o(const uint8_t* __restrict in, uint8_t* __restrict out);
} // namespace avx2

namespace sse {
void transpose_i(const uint64_t* __restrict in, uint64_t* __restrict out);
void transpose_i(const uint32_t* __restrict in, uint32_t* __restrict out);
void transpose_i(const uint16_t* __restrict in, uint16_t* __restrict out);
void transpose_i(const uint8_t* __restrict in, uint8_t* __restrict out);
void transpose_o(const uint64_t* __restrict in, uint64_t* __restrict out);
void transpose_o(const uint32_t* __restrict in, uint32_t* __restrict out);
void transpose_o(const uint16_t* __restrict in, uint16_t* __restrict out);
void transpose_o(const uint8_t* __restrict in, uint8_t* __restrict out);
} // namespace sse

namespace avx512f {
void transpose_i(const uint64_t* __restrict in, uint64_t* __restrict out);
void transpose_i(const uint32_t* __restrict in, uint32_t* __restrict out);
void transpose_i(const uint16_t* __restrict in, uint16_t* __restrict out);
void transpose_i(const uint8_t* __restrict in, uint8_t* __restrict out);
void transpose_o(const uint64_t* __restrict in, uint64_t* __restrict out);
void transpose_o(const uint32_t* __restrict in, uint32_t* __restrict out);
void transpose_o(const uint16_t* __restrict in, uint16_t* __restrict out);
void transpose_o(const uint8_t* __restrict in, uint8_t* __restrict out);
} // namespace avx512f
} // namespace x86_64
}} // namespace generated::transpose

#endif
