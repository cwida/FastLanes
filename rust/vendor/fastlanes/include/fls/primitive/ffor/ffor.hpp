#ifndef FLS_PRIMITIVE_FFOR_FFOR_HPP
#define FLS_PRIMITIVE_FFOR_FFOR_HPP

#include <cstdint>

namespace fastlanes::generated::ffor::fallback::scalar {
void ffor(const int64_t* __restrict in, int64_t* __restrict out, uint8_t bw, const int64_t* __restrict a_base_p);
void ffor(const int32_t* __restrict in, int32_t* __restrict out, uint8_t bw, const int32_t* __restrict a_base_p);
void ffor(const int16_t* __restrict in, int16_t* __restrict out, uint8_t bw, const int16_t* __restrict a_base_p);
void ffor(const int8_t* __restrict in, int8_t* __restrict out, uint8_t bw, const int8_t* __restrict a_base_p);
} // namespace fastlanes::generated::ffor::fallback::scalar

#endif // FLS_PRIMITIVE_FFOR_FFOR_HPP
