#ifndef FLS_PRIMITIVE_UNFFOR_UNFFOR_HPP
#define FLS_PRIMITIVE_UNFFOR_UNFFOR_HPP

#include <cstdint>

namespace fastlanes::generated::unffor::fallback::scalar {
void unffor(const int64_t* __restrict in, int64_t* __restrict out, uint8_t bw, const int64_t* __restrict a_base_p);
void unffor(const int32_t* __restrict in, int32_t* __restrict out, uint8_t bw, const int32_t* __restrict a_base_p);
void unffor(const int16_t* __restrict in, int16_t* __restrict out, uint8_t bw, const int16_t* __restrict a_base_p);
void unffor(const int8_t* __restrict in, int8_t* __restrict out, uint8_t bw, const int8_t* __restrict a_base_p);
} // namespace fastlanes::generated::unffor::fallback::scalar

#endif // FLS_PRIMITIVE_UNFFOR_UNFFOR_HPP
