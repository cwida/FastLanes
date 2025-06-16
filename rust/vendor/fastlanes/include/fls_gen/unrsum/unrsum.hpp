#ifndef FLS_GEN_UNRSUM_UNRSUM_HPP
#define FLS_GEN_UNRSUM_UNRSUM_HPP

#include <cstdint>

namespace generated { namespace unrsum {
namespace fallback { namespace scalar {
void        unrsum(const uint8_t* in, uint8_t* out);
void        unrsum(const uint16_t* in, uint16_t* out);
void        unrsum(const uint32_t* in, uint32_t* out);
void        unrsum(const uint64_t* in, uint64_t* out);
inline void unrsum(const int64_t* in, int64_t* out) {
	unrsum(reinterpret_cast<const uint64_t*>(in), reinterpret_cast<uint64_t*>(out));
}
inline void unrsum(const int32_t* in, int32_t* out) {
	unrsum(reinterpret_cast<const uint32_t*>(in), reinterpret_cast<uint32_t*>(out));
}
inline void unrsum(const int16_t* in, int16_t* out) {
	unrsum(reinterpret_cast<const uint16_t*>(in), reinterpret_cast<uint16_t*>(out));
}
inline void unrsum(const int8_t* in, int8_t* out) {
	unrsum(reinterpret_cast<const uint8_t*>(in), reinterpret_cast<uint8_t*>(out));
}

void unrsum_inplace(uint8_t* in);
void unrsum_inplace(uint16_t* in);
void unrsum_inplace(uint32_t* in);
void unrsum_inplace(uint64_t* in);
}} // namespace fallback::scalar

namespace helper { namespace scalar {
void unrsum(const uint8_t* in, uint8_t* out);
void unrsum(const uint16_t* in, uint16_t* out);
void unrsum(const uint32_t* in, uint32_t* out);
void unrsum(const uint64_t* in, uint64_t* out);
void unrsum_inplace(uint8_t* in);
void unrsum_inplace(uint16_t* in);
void unrsum_inplace(uint32_t* in);
void unrsum_inplace(uint64_t* in);
}} // namespace helper::scalar

namespace neon {
void unrsum(const uint8_t* in, uint8_t* out);
void unrsum(const uint16_t* in, uint16_t* out);
void unrsum(const uint32_t* in, uint32_t* out);
void unrsum(const uint64_t* in, uint64_t* out);
} // namespace neon

namespace avx2 {
void unrsum(const uint8_t* in, uint8_t* out);
void unrsum(const uint16_t* in, uint16_t* out);
void unrsum(const uint32_t* in, uint32_t* out);
void unrsum(const uint64_t* in, uint64_t* out);
} // namespace avx2

namespace sse {
void unrsum(const uint8_t* in, uint8_t* out);
void unrsum(const uint16_t* in, uint16_t* out);
void unrsum(const uint32_t* in, uint32_t* out);
void unrsum(const uint64_t* in, uint64_t* out);
} // namespace sse

namespace avx512f {
void unrsum(const uint8_t* in, uint8_t* out);
void unrsum(const uint16_t* in, uint16_t* out);
void unrsum(const uint32_t* in, uint32_t* out);
void unrsum(const uint64_t* in, uint64_t* out);
} // namespace avx512f
}} // namespace generated::unrsum

#endif
