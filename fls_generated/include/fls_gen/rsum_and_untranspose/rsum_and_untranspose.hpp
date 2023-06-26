#ifndef RSUM_AND_UNTRANSPOSE_HPP
#define RSUM_AND_UNTRANSPOSE_HPP

#include <cstdint>

namespace generated { namespace rsum_and_untranspose {
namespace fallback { namespace scalar {
void rsum_and_untranspose(const uint8_t* __restrict in, uint8_t* __restrict out, const uint8_t* __restrict base);
void rsum_and_untranspose(const uint16_t* __restrict in, uint16_t* __restrict out, const uint16_t* __restrict base);
void rsum_and_untranspose(const uint32_t* __restrict in, uint32_t* __restrict out, const uint32_t* __restrict base);
void rsum_and_untranspose(const uint64_t* __restrict in, uint64_t* __restrict out, const uint64_t* __restrict base);
}} // namespace fallback::scalar

namespace helper { namespace scalar {
void rsum_and_untranspose(const uint8_t* __restrict in, uint8_t* __restrict out, const uint8_t* __restrict base);
void rsum_and_untranspose(const uint16_t* __restrict in, uint16_t* __restrict out, const uint16_t* __restrict base);
void rsum_and_untranspose(const uint32_t* __restrict in, uint32_t* __restrict out, const uint32_t* __restrict base);
void rsum_and_untranspose(const uint64_t* __restrict in, uint64_t* __restrict out, const uint64_t* __restrict base);
}} // namespace helper::scalar

namespace arm64v8 { namespace neon {
void rsum_and_untranspose(const uint8_t* __restrict in, uint8_t* __restrict out, const uint8_t* __restrict base);
void rsum_and_untranspose(const uint16_t* __restrict in, uint16_t* __restrict out, const uint16_t* __restrict base);
void rsum_and_untranspose(const uint32_t* __restrict in, uint32_t* __restrict out, const uint32_t* __restrict base);
void rsum_and_untranspose(const uint64_t* __restrict in, uint64_t* __restrict out, const uint64_t* __restrict base);
}} // namespace arm64v8::neon

namespace x86_64 {
namespace avx2 {
void rsum_and_untranspose(const uint8_t* __restrict in, uint8_t* __restrict out, const uint8_t* __restrict base);
void rsum_and_untranspose(const uint16_t* __restrict in, uint16_t* __restrict out, const uint16_t* __restrict base);
void rsum_and_untranspose(const uint32_t* __restrict in, uint32_t* __restrict out, const uint32_t* __restrict base);
void rsum_and_untranspose(const uint64_t* __restrict in, uint64_t* __restrict out, const uint64_t* __restrict base);
} // namespace avx2

namespace sse {
void rsum_and_untranspose(const uint8_t* __restrict in, uint8_t* __restrict out, const uint8_t* __restrict base);
void rsum_and_untranspose(const uint16_t* __restrict in, uint16_t* __restrict out, const uint16_t* __restrict base);
void rsum_and_untranspose(const uint32_t* __restrict in, uint32_t* __restrict out, const uint32_t* __restrict base);
void rsum_and_untranspose(const uint64_t* __restrict in, uint64_t* __restrict out, const uint64_t* __restrict base);
} // namespace sse

namespace avx512f {
void rsum_and_untranspose(const uint8_t* __restrict in, uint8_t* __restrict out, const uint8_t* __restrict base);
void rsum_and_untranspose(const uint16_t* __restrict in, uint16_t* __restrict out, const uint16_t* __restrict base);
void rsum_and_untranspose(const uint32_t* __restrict in, uint32_t* __restrict out, const uint32_t* __restrict base);
void rsum_and_untranspose(const uint64_t* __restrict in, uint64_t* __restrict out, const uint64_t* __restrict base);
} // namespace avx512f
} // namespace x86_64
}} // namespace generated::rsum_and_untranspose

#endif
