#pragma once
#include <algorithm>
#include <immintrin.h>
#include <iostream>
#include <ostream>
#include <vector>

struct Vec8u {
   union {
      __m512i reg;
      uint64_t entry[8];
   };

   // constructor
   explicit Vec8u(uint64_t x) { reg = _mm512_set1_epi64(x); };
   explicit Vec8u(void* p) { reg = _mm512_loadu_si512(p); };
   Vec8u(__m512i x) { reg = x; };
   Vec8u(uint64_t x0, uint64_t x1, uint64_t x2, uint64_t x3, uint64_t x4, uint64_t x5, uint64_t x6, uint64_t x7) { reg = _mm512_set_epi64(x0, x1, x2, x3, x4, x5, x6, x7); };

   // implicit conversion to register
   operator __m512i() { return reg; }

   // print vector (for debugging)
   friend std::ostream& operator<< (std::ostream& stream, const Vec8u& v) {
      for (auto& e : v.entry)
         stream << e << " ";
      return stream;
   }
};

struct Vec8uM{
   Vec8u vec;
   __mmask8 mask;
};

inline Vec8u operator+ (const Vec8u& a, const Vec8u& b) { return _mm512_add_epi64(a.reg, b.reg); }
inline Vec8u operator- (const Vec8u& a, const Vec8u& b) { return _mm512_sub_epi64(a.reg, b.reg); }
inline Vec8u operator* (const Vec8u& a, const Vec8u& b) { return _mm512_mullo_epi64(a.reg, b.reg); }
inline Vec8u operator^ (const Vec8u& a, const Vec8u& b) { return _mm512_xor_epi64(a.reg, b.reg); }
inline Vec8u operator>> (const Vec8u& a, const unsigned shift) { return _mm512_srli_epi64(a.reg, shift); }
inline Vec8u operator<< (const Vec8u& a, const unsigned shift) { return _mm512_slli_epi64(a.reg, shift); }
inline Vec8u operator>> (const Vec8u& a, const Vec8u& shift) { return _mm512_srlv_epi64(a.reg, shift.reg); }
inline Vec8u operator<< (const Vec8u& a, const Vec8u& shift) { return _mm512_sllv_epi64(a.reg, shift.reg); }
inline Vec8u operator& (const Vec8u& a, const Vec8u& b) { return _mm512_and_epi64(a.reg, b.reg); }
inline __mmask8 operator== (const Vec8u& a, const Vec8u& b) { return _mm512_cmpeq_epi64_mask(a.reg, b.reg); }
inline __mmask8 operator!= (const Vec8u& a, const Vec8u& b) { return _mm512_cmpneq_epi64_mask(a.reg, b.reg); }
inline __mmask8 operator< (const Vec8u& a, const Vec8u& b) { return _mm512_cmplt_epi64_mask(a.reg, b.reg); }
inline __mmask8 operator<= (const Vec8u& a, const Vec8u& b) { return _mm512_cmple_epi64_mask(a.reg, b.reg); }
inline __mmask8 operator> (const Vec8u& a, const Vec8u& b) { return _mm512_cmpgt_epi64_mask(a.reg, b.reg); }
inline __mmask8 operator>= (const Vec8u& a, const Vec8u& b) { return _mm512_cmpge_epi64_mask(a.reg, b.reg); }


struct Vec16u {
   union {
      __m512i reg;
      uint32_t entry[16];
   };

   // constructor
   explicit Vec16u(uint32_t x) { reg = _mm512_set1_epi32(x); };
   explicit Vec16u(void* p) { reg = _mm512_loadu_si512(p); };
   Vec16u(__m512i x) { reg = x; };
   Vec16u(uint32_t x0, uint32_t x1, uint32_t x2, uint32_t x3, uint32_t x4,
          uint32_t x5, uint32_t x6, uint32_t x7, uint32_t x8, uint32_t x9,
          uint32_t x10, uint32_t x11, uint32_t x12, uint32_t x13, uint32_t x14,
          uint32_t x15) {
      reg = _mm512_set_epi32(x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11,
                             x12, x13, x14, x15);
   };

   // implicit conversion to register
   operator __m512i() { return reg; }

   // print vector (for debugging)
   friend std::ostream& operator<< (std::ostream& stream, const Vec16u& v) {
      for (auto& e : v.entry)
         stream << e << " ";
      return stream;
   }
};

struct Vec16uM{
   Vec16u vec;
   __mmask8 mask;
};

inline Vec16u operator+ (const Vec16u& a, const Vec16u& b) { return _mm512_add_epi32(a.reg, b.reg); }
inline Vec16u operator- (const Vec16u& a, const Vec16u& b) { return _mm512_sub_epi32(a.reg, b.reg); }
inline Vec16u operator* (const Vec16u& a, const Vec16u& b) { return _mm512_mullo_epi32(a.reg, b.reg); }
inline Vec16u operator^ (const Vec16u& a, const Vec16u& b) { return _mm512_xor_epi32(a.reg, b.reg); }
inline Vec16u operator>> (const Vec16u& a, const unsigned shift) { return _mm512_srli_epi32(a.reg, shift); }
inline Vec16u operator<< (const Vec16u& a, const unsigned shift) { return _mm512_slli_epi32(a.reg, shift); }
inline Vec16u operator>> (const Vec16u& a, const Vec16u& shift) { return _mm512_srlv_epi32(a.reg, shift.reg); }
inline Vec16u operator<< (const Vec16u& a, const Vec16u& shift) { return _mm512_sllv_epi32(a.reg, shift.reg); }
inline Vec16u operator& (const Vec16u& a, const Vec16u& b) { return _mm512_and_epi32(a.reg, b.reg); }
inline __mmask16 operator== (const Vec16u& a, const Vec16u& b) { return _mm512_cmpeq_epi32_mask(a.reg, b.reg); }
inline __mmask16 operator!= (const Vec16u& a, const Vec16u& b) { return _mm512_cmpneq_epi32_mask(a.reg, b.reg); }
inline __mmask16 operator< (const Vec16u& a, const Vec16u& b) { return _mm512_cmplt_epi32_mask(a.reg, b.reg); }
inline __mmask16 operator<= (const Vec16u& a, const Vec16u& b) { return _mm512_cmple_epi32_mask(a.reg, b.reg); }
inline __mmask16 operator> (const Vec16u& a, const Vec16u& b) { return _mm512_cmpgt_epi32_mask(a.reg, b.reg); }
inline __mmask16 operator>= (const Vec16u& a, const Vec16u& b) { return _mm512_cmpge_epi32_mask(a.reg, b.reg); }
