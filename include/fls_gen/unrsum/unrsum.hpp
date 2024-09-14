#ifndef FLS_GEN_UNRSUM_UNRSUM_HPP
#define FLS_GEN_UNRSUM_UNRSUM_HPP

#include <cstdint>

namespace generated { namespace unrsum {
namespace fallback { namespace scalar {
void unrsum(const uint8_t* in, uint8_t* out);
void unrsum(const uint16_t* in, uint16_t* out);
void unrsum(const uint32_t* in, uint32_t* out);
void unrsum(const uint64_t* in, uint64_t* out);
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
