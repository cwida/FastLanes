#ifndef FLS_FFOR_HPP
#define FLS_FFOR_HPP

#include <cstdint>

namespace generated { namespace ffor { namespace fallback { namespace scalar {
void ffor(const uint64_t* __restrict in, uint64_t* __restrict out, uint8_t bw, const uint64_t* __restrict a_base_p);
void ffor(const uint32_t* __restrict in, uint32_t* __restrict out, uint8_t bw, const uint32_t* __restrict a_base_p);
void ffor(const uint16_t* __restrict in, uint16_t* __restrict out, uint8_t bw, const uint16_t* __restrict a_base_p);
void ffor(const uint8_t* __restrict in, uint8_t* __restrict out, uint8_t bw, const uint8_t* __restrict a_base_p);
}}}} // namespace generated::ffor::fallback::scalar

namespace generated { namespace ffor { namespace helper { namespace scalar {
void ffor(const uint64_t* __restrict in, uint64_t* __restrict out, uint8_t bw, const uint64_t* __restrict a_base_p);
void ffor(const uint32_t* __restrict in, uint32_t* __restrict out, uint8_t bw, const uint32_t* __restrict a_base_p);
void ffor(const uint16_t* __restrict in, uint16_t* __restrict out, uint8_t bw, const uint16_t* __restrict a_base_p);
void ffor(const uint8_t* __restrict in, uint8_t* __restrict out, uint8_t bw, const uint8_t* __restrict a_base_p);
}}}} // namespace generated::ffor::helper::scalar

#endif // ARROW_FFOR_HPP
