#include <cstdint>

namespace rut {
namespace scalar {
void transpose_i(const int64_t* __restrict in, int64_t* __restrict out);
void transpose_i(const int32_t* __restrict in, int32_t* __restrict out);
void transpose_i(const int16_t* __restrict in, int16_t* __restrict out);
void transpose_i(const int8_t* __restrict in, int8_t* __restrict out);
void transpose_o(const int64_t* __restrict in, int64_t* __restrict out);
void transpose_o(const int32_t* __restrict in, int32_t* __restrict out);
void transpose_o(const int16_t* __restrict in, int16_t* __restrict out);
void transpose_o(const int8_t* __restrict in, int8_t* __restrict out);
void untranspose_i(const int64_t* __restrict in, int64_t* __restrict out);
void untranspose_i(const int32_t* __restrict in, int32_t* __restrict out);
void untranspose_i(const int16_t* __restrict in, int16_t* __restrict out);
void untranspose_i(const int8_t* __restrict in, int8_t* __restrict out);
void untranspose_o(const int64_t* __restrict in, int64_t* __restrict out);
void untranspose_o(const int32_t* __restrict in, int32_t* __restrict out);
void untranspose_o(const int16_t* __restrict in, int16_t* __restrict out);
void untranspose_o(const int8_t* __restrict in, int8_t* __restrict out);
void rsum(const int8_t* __restrict delta, int8_t* __restrict out, const int8_t* __restrict base);
void rsum(const int16_t* __restrict delta, int16_t* __restrict out, const int16_t* __restrict base);
void rsum(const int32_t* __restrict delta, int32_t* __restrict out, const int32_t* __restrict base);
void rsum(const int64_t* __restrict delta, int64_t* __restrict out, const int64_t* __restrict base);
void rsum_and_untranspose(const int8_t* __restrict delta, int8_t* __restrict out, const int8_t* __restrict base);
void rsum_and_untranspose(const int16_t* __restrict delta, int16_t* __restrict out, const int16_t* __restrict base);
void rsum_and_untranspose(const int32_t* __restrict delta, int32_t* __restrict out, const int32_t* __restrict base);
void rsum_and_untranspose(const int64_t* __restrict delta, int64_t* __restrict out, const int64_t* __restrict base);
void rle(const int8_t* __restrict val, const uint8_t* __restrict len, int runs_count, int8_t* __restrict out);
void rle(const int16_t* __restrict val, const uint8_t* __restrict len, int runs_count, int16_t* __restrict out);
void rle(const int32_t* __restrict val, const uint8_t* __restrict len, int runs_count, int32_t* __restrict out);
void rle(const int64_t* __restrict val, const uint8_t* __restrict len, int runs_count, int64_t* __restrict out);
void scalar_rle(const int8_t* __restrict val, const uint8_t* __restrict len, int runs_count, int8_t* __restrict out);
void scalar_rle(const int16_t* __restrict val, const uint8_t* __restrict len, int runs_count, int16_t* __restrict out);
void scalar_rle(const int32_t* __restrict val, const uint8_t* __restrict len, int runs_count, int32_t* __restrict out);
void scalar_rle(const int64_t* __restrict val, const uint8_t* __restrict len, int runs_count, int64_t* __restrict out);
void rle_and_untranspose(const int8_t* __restrict val,
                         const uint8_t* __restrict len,
                         int runs_count,
                         int8_t* __restrict out);
void rle_and_untranspose(const int16_t* __restrict val,
                         const uint8_t* __restrict len,
                         int runs_count,
                         int16_t* __restrict out);
void rle_and_untranspose(const int32_t* __restrict val,
                         const uint8_t* __restrict len,
                         int runs_count,
                         int32_t* __restrict out);
void rle_and_untranspose(const int64_t* __restrict val,
                         const uint8_t* __restrict len,
                         int runs_count,
                         int64_t* __restrict out);
} // namespace scalar
namespace neon {
void transpose_i(const int64_t* __restrict in, int64_t* __restrict out);
void transpose_i(const int32_t* __restrict in, int32_t* __restrict out);
void transpose_i(const int16_t* __restrict in, int16_t* __restrict out);
void transpose_i(const int8_t* __restrict in, int8_t* __restrict out);
void transpose_o(const int64_t* __restrict in, int64_t* __restrict out);
void transpose_o(const int32_t* __restrict in, int32_t* __restrict out);
void transpose_o(const int16_t* __restrict in, int16_t* __restrict out);
void transpose_o(const int8_t* __restrict in, int8_t* __restrict out);
void untranspose_i(const int64_t* __restrict in, int64_t* __restrict out);
void untranspose_i(const int32_t* __restrict in, int32_t* __restrict out);
void untranspose_i(const int16_t* __restrict in, int16_t* __restrict out);
void untranspose_i(const int8_t* __restrict in, int8_t* __restrict out);
void untranspose_o(const int64_t* __restrict in, int64_t* __restrict out);
void untranspose_o(const int32_t* __restrict in, int32_t* __restrict out);
void untranspose_o(const int16_t* __restrict in, int16_t* __restrict out);
void untranspose_o(const int8_t* __restrict in, int8_t* __restrict out);
void rsum(const int8_t* __restrict delta, int8_t* __restrict out, const int8_t* __restrict base);
void rsum(const int16_t* __restrict delta, int16_t* __restrict out, const int16_t* __restrict base);
void rsum(const int32_t* __restrict delta, int32_t* __restrict out, const int32_t* __restrict base);
void rsum(const int64_t* __restrict delta, int64_t* __restrict out, const int64_t* __restrict base);
void rsum_and_untranspose(const int8_t* __restrict delta, int8_t* __restrict out, const int8_t* __restrict base);
void rsum_and_untranspose(const int16_t* __restrict delta, int16_t* __restrict out, const int16_t* __restrict base);
void rsum_and_untranspose(const int32_t* __restrict delta, int32_t* __restrict out, const int32_t* __restrict base);
void rsum_and_untranspose(const int64_t* __restrict delta, int64_t* __restrict out, const int64_t* __restrict base);
} // namespace neon
} // namespace rut
