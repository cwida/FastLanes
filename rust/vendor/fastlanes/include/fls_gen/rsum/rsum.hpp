#ifndef FLS_GEN_RSUM_RSUM_HPP
#define FLS_GEN_RSUM_RSUM_HPP

#include <cstdint>

namespace generated { namespace rsum {
namespace fallback {
namespace scalar {
void        rsum(const uint8_t* __restrict in, uint8_t* __restrict out, const uint8_t* __restrict base);
void        rsum(const uint16_t* __restrict in, uint16_t* __restrict out, const uint16_t* __restrict base);
void        rsum(const uint32_t* __restrict in, uint32_t* __restrict out, const uint32_t* __restrict base);
void        rsum(const uint64_t* __restrict in, uint64_t* __restrict out, const uint64_t* __restrict base);
inline void rsum(const int64_t* __restrict in, int64_t* __restrict out, const int64_t* __restrict base) {
	rsum(reinterpret_cast<const uint64_t*>(in),
	     reinterpret_cast<uint64_t*>(out),
	     reinterpret_cast<const uint64_t*>(base));
}
inline void rsum(const int32_t* __restrict in, int32_t* __restrict out, const int32_t* __restrict base) {
	rsum(reinterpret_cast<const uint32_t*>(in),
	     reinterpret_cast<uint32_t*>(out),
	     reinterpret_cast<const uint32_t*>(base));
}
inline void rsum(const int16_t* __restrict in, int16_t* __restrict out, const int16_t* __restrict base) {
	rsum(reinterpret_cast<const uint16_t*>(in),
	     reinterpret_cast<uint16_t*>(out),
	     reinterpret_cast<const uint16_t*>(base));
}
inline void rsum(const int8_t* __restrict in, int8_t* __restrict out, const int8_t* __restrict base) {
	rsum(reinterpret_cast<const uint8_t*>(in), reinterpret_cast<uint8_t*>(out), reinterpret_cast<const uint8_t*>(base));
}

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
