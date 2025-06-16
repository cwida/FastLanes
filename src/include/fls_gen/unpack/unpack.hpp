#ifndef FLS_GEN_UNPACK_UNPACK_HPP
#define FLS_GEN_UNPACK_UNPACK_HPP

#include <cstdint>

namespace generated::unpack { namespace fallback::scalar {
void unpack(const uint64_t* __restrict in, uint64_t* __restrict out, uint8_t bw);
void unpack(const uint32_t* __restrict in, uint32_t* __restrict out, uint8_t bw);
void unpack(const uint16_t* __restrict in, uint16_t* __restrict out, uint8_t bw);
void unpack(const uint8_t* __restrict in, uint8_t* __restrict out, uint8_t bw);
}} // namespace generated::unpack::fallback::scalar

#endif
