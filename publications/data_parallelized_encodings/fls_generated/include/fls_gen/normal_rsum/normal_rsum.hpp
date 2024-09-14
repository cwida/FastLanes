
#ifndef NORMAL_RSUM_HPP
#define NORMAL_RSUM_HPP

#include <cstdint>
namespace generated { namespace normal_rsum {
namespace scalar {
void rsum(const int8_t* __restrict delta, int8_t* __restrict out, const int8_t* __restrict base);
void rsum(const int16_t* __restrict in, int16_t* __restrict out, const int16_t* __restrict base);
void rsum(const int32_t* __restrict in, int32_t* __restrict out, const int32_t* __restrict base);
void rsum(const int64_t* __restrict in, int64_t* __restrict out, const int64_t* __restrict base);
void unrolled_rsum(const int8_t* __restrict delta, int8_t* __restrict out, const int8_t* __restrict base);
void unrolled_rsum(const int16_t* __restrict in, int16_t* __restrict out, const int16_t* __restrict base);
void unrolled_rsum(const int32_t* __restrict in, int32_t* __restrict out, const int32_t* __restrict base);
void unrolled_rsum(const int64_t* __restrict in, int64_t* __restrict out, const int64_t* __restrict base);
} // namespace scalar
namespace neon {
void rsum(const int8_t* __restrict delta, int8_t* __restrict out, const int8_t* __restrict base);
void rsum(const int16_t* __restrict in, int16_t* __restrict out, const int16_t* __restrict base);
void rsum(const int32_t* __restrict in, int32_t* __restrict out, const int32_t* __restrict base);
void rsum(const int64_t* __restrict in, int64_t* __restrict out, const int64_t* __restrict base);
void unrolled_rsum(const int8_t* __restrict delta, int8_t* __restrict out, const int8_t* __restrict base);
void unrolled_rsum(const int16_t* __restrict in, int16_t* __restrict out, const int16_t* __restrict base);
void unrolled_rsum(const int32_t* __restrict in, int32_t* __restrict out, const int32_t* __restrict base);
void unrolled_rsum(const int64_t* __restrict in, int64_t* __restrict out, const int64_t* __restrict base);
} // namespace neon
}} // namespace generated::normal_rsum
#endif
