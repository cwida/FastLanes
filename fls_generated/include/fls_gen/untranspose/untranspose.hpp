#ifndef UT_HPP
#define UT_HPP

#include <cstdint>

namespace generated { namespace untranspose {
namespace fallback { namespace scalar {
void untranspose_i(const uint64_t* __restrict in, uint64_t* __restrict out);
void untranspose_i(const uint32_t* __restrict in, uint32_t* __restrict out);
void untranspose_i(const uint16_t* __restrict in, uint16_t* __restrict out);
void untranspose_i(const uint8_t* __restrict in, uint8_t* __restrict out);
void untranspose_o(const uint64_t* __restrict in, uint64_t* __restrict out);
void untranspose_o(const uint32_t* __restrict in, uint32_t* __restrict out);
void untranspose_o(const uint16_t* __restrict in, uint16_t* __restrict out);
void untranspose_o(const uint8_t* __restrict in, uint8_t* __restrict out);
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
