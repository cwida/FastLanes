#ifndef FLS_GEN_PACK_PACK_HPP
#define FLS_GEN_PACK_PACK_HPP

#include <cstdint>

namespace generated { namespace pack { namespace fallback { namespace scalar {
void pack(const uint64_t* __restrict in, uint64_t* __restrict out, uint8_t bw);
void pack(const uint32_t* __restrict in, uint32_t* __restrict out, uint8_t bw);
void pack(const uint16_t* __restrict in, uint16_t* __restrict out, uint8_t bw);
void pack(const uint8_t* __restrict in, uint8_t* __restrict out, uint8_t bw);

inline void pack(const int64_t* __restrict in, int64_t* __restrict out, uint8_t bw) {
	pack(reinterpret_cast<const uint64_t*>(in), reinterpret_cast<uint64_t*>(out), bw);
}
inline void pack(const int32_t* __restrict in, int32_t* __restrict out, uint8_t bw) {
	pack(reinterpret_cast<const uint32_t*>(in), reinterpret_cast<uint32_t*>(out), bw);
}
inline void pack(const int16_t* __restrict in, int16_t* __restrict out, uint8_t bw) {
	pack(reinterpret_cast<const uint16_t*>(in), reinterpret_cast<uint16_t*>(out), bw);
}
inline void pack(const int8_t* __restrict in, int8_t* __restrict out, uint8_t bw) {
	pack(reinterpret_cast<const uint8_t*>(in), reinterpret_cast<uint8_t*>(out), bw);
}

}}}} // namespace generated::pack::fallback::scalar

#endif // FLS_GEN_PACK_PACK_HPP
