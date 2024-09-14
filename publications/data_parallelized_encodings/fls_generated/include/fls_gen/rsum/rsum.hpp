#ifndef RSUM_HPP
#define RSUM_HPP

#include <cstdint>

namespace generated { namespace rsum {
namespace fallback {
namespace scalar {
void rsum(const uint8_t* __restrict in, uint8_t* __restrict out, const uint8_t* __restrict base);
void rsum(const uint16_t* __restrict in, uint16_t* __restrict out, const uint16_t* __restrict base);
void rsum(const uint32_t* __restrict in, uint32_t* __restrict out, const uint32_t* __restrict base);
void rsum(const uint64_t* __restrict in, uint64_t* __restrict out, const uint64_t* __restrict base);
} // namespace scalar
namespace unit64 {
void rsum(const uint8_t* __restrict in, uint8_t* __restrict out, const uint8_t* __restrict base);
void rsum(const uint16_t* __restrict in, uint16_t* __restrict out, const uint16_t* __restrict base);
void rsum(const uint32_t* __restrict in, uint32_t* __restrict out, const uint32_t* __restrict base);
void rsum(const uint64_t* __restrict in, uint64_t* __restrict out, const uint64_t* __restrict base);
} // namespace unit64
} // namespace fallback

namespace helper { namespace scalar {
void rsum(const uint8_t* __restrict in, uint8_t* __restrict out, const uint8_t* __restrict base);
void rsum(const uint16_t* __restrict in, uint16_t* __restrict out, const uint16_t* __restrict base);
void rsum(const uint32_t* __restrict in, uint32_t* __restrict out, const uint32_t* __restrict base);
void rsum(const uint64_t* __restrict in, uint64_t* __restrict out, const uint64_t* __restrict base);
}} // namespace helper::scalar

namespace arm64v8 { namespace neon {
void rsum(const uint8_t* __restrict in, uint8_t* __restrict out, const uint8_t* __restrict base);
void rsum(const uint16_t* __restrict in, uint16_t* __restrict out, const uint16_t* __restrict base);
void rsum(const uint32_t* __restrict in, uint32_t* __restrict out, const uint32_t* __restrict base);
void rsum(const uint64_t* __restrict in, uint64_t* __restrict out, const uint64_t* __restrict base);
}} // namespace arm64v8::neon

namespace x86_64 {
namespace avx2 {
void rsum(const uint8_t* __restrict in, uint8_t* __restrict out, const uint8_t* __restrict base);
void rsum(const uint16_t* __restrict in, uint16_t* __restrict out, const uint16_t* __restrict base);
void rsum(const uint32_t* __restrict in, uint32_t* __restrict out, const uint32_t* __restrict base);
void rsum(const uint64_t* __restrict in, uint64_t* __restrict out, const uint64_t* __restrict base);
} // namespace avx2

namespace sse {
void rsum(const uint8_t* __restrict in, uint8_t* __restrict out, const uint8_t* __restrict base);
void rsum(const uint16_t* __restrict in, uint16_t* __restrict out, const uint16_t* __restrict base);
void rsum(const uint32_t* __restrict in, uint32_t* __restrict out, const uint32_t* __restrict base);
void rsum(const uint64_t* __restrict in, uint64_t* __restrict out, const uint64_t* __restrict base);
} // namespace sse

namespace avx512bw {
void rsum(const uint8_t* __restrict in, uint8_t* __restrict out, const uint8_t* __restrict base);
void rsum(const uint16_t* __restrict in, uint16_t* __restrict out, const uint16_t* __restrict base);
void rsum(const uint32_t* __restrict in, uint32_t* __restrict out, const uint32_t* __restrict base);
void rsum(const uint64_t* __restrict in, uint64_t* __restrict out, const uint64_t* __restrict base);
} // namespace avx512bw
} // namespace x86_64
}} // namespace generated::rsum

#endif
