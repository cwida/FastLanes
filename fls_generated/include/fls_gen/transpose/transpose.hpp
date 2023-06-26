#ifndef TRANSPOSE_HPP
#define TRANSPOSE_HPP

#include <cstdint>

namespace generated { namespace transpose {
namespace fallback { namespace scalar {
void transpose_i(const uint64_t* __restrict in, uint64_t* __restrict out);
void transpose_i(const uint32_t* __restrict in, uint32_t* __restrict out);
void transpose_i(const uint16_t* __restrict in, uint16_t* __restrict out);
void transpose_i(const uint8_t* __restrict in, uint8_t* __restrict out);
void transpose_o(const uint64_t* __restrict in, uint64_t* __restrict out);
void transpose_o(const uint32_t* __restrict in, uint32_t* __restrict out);
void transpose_o(const uint16_t* __restrict in, uint16_t* __restrict out);
void transpose_o(const uint8_t* __restrict in, uint8_t* __restrict out);
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
