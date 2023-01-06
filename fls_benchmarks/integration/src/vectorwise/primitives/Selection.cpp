#include "common/runtime/Hash.hpp"
#include "common/runtime/SIMD.hpp"
#include "vectorwise/Operations.hpp"
#include "vectorwise/Primitives.hpp"
#include <functional>
#include <immintrin.h>
#include <string.h>

using namespace types;
using namespace std;

namespace vectorwise {
namespace primitives {

#define MK_SEL_COLCOL(type, op)                                                \
   F3 sel_##op##_##type##_col_##type##_col = (F3)&sel_col_col<type, op>;

#define MK_SEL_COLVAL(type, op)                                                \
   F3 sel_##op##_##type##_col_##type##_val = (F3)&sel_col_val<type, op>;

#define MK_SEL_COLVALORVAL(type, op)                                           \
   F4 sel_##op##_##type##_col_##type##_val_or_##type##_val =                   \
       (F4)&sel_col_val_or_val<type, op>;

#define MK_SELSEL_COLCOL(type, op)                                             \
   F4 selsel_##op##_##type##_col_##type##_col = (F4)&selsel_col_col<type, op>;

#define MK_SELSEL_COLVAL(type, op)                                             \
   F4 selsel_##op##_##type##_col_##type##_val = (F4)&selsel_col_val<type, op>;

#define MK_SEL_COLCOL_BF(type, op)                                             \
   F3 sel_##op##_##type##_col_##type##_col_bf = (F3)&sel_col_col_bf<type, op>;

#define MK_SEL_COLVAL_BF(type, op)                                             \
   F3 sel_##op##_##type##_col_##type##_val_bf = (F3)&sel_col_val_bf<type, op>;

#define MK_SELSEL_COLCOL_BF(type, op)                                          \
   F4 selsel_##op##_##type##_col_##type##_col_bf =                             \
       (F4)&selsel_col_col_bf<type, op>;

#define MK_SELSEL_COLVAL_BF(type, op)                                          \
   F4 selsel_##op##_##type##_col_##type##_val_bf =                             \
       (F4)&selsel_col_val_bf<type, op>;

// instantiate selection primitives for each type and for each comparator
EACH_COMP(EACH_TYPE, MK_SEL_COLCOL)
EACH_COMP(EACH_TYPE, MK_SEL_COLVAL)      // with second arg const
EACH_COMP(EACH_TYPE, MK_SEL_COLVALORVAL) // with second and third arg const
EACH_COMP(EACH_TYPE, MK_SELSEL_COLCOL)   // with input selection vector
EACH_COMP(EACH_TYPE, MK_SELSEL_COLVAL)   // with above and second arg const
EACH_COMP(EACH_TYPE, MK_SEL_COLCOL_BF)
EACH_COMP(EACH_TYPE, MK_SEL_COLVAL_BF)    // with second arg const
EACH_COMP(EACH_TYPE, MK_SELSEL_COLCOL_BF) // with input selection vector
EACH_COMP(EACH_TYPE, MK_SELSEL_COLVAL_BF) // with above and second arg const

template <typename T> struct Contains {
   bool operator()(const T& haystack, const T& needle) {
      return memmem(haystack.value, haystack.len, needle.value, needle.len) !=
             nullptr;
   }
};
F3 sel_contains_Varchar_55_col_Varchar_55_val =
    (F3)&sel_col_val<Varchar_55, Contains>;

#ifdef __AVX512F__

// #define PREFETCH(E) __builtin_prefetch(E);
#define PREFETCH(E)

pos_t sel_less_int32_t_col_int32_t_val_avx512_impl(pos_t n, pos_t* RES result,
                                                   int32_t* RES param1,
                                                   int32_t* RES param2) {
   static_assert(sizeof(pos_t) == 4,
                 "This implementation only supports sizeof(pos_t) == 4");
   uint64_t found = 0;
   size_t rest = n % 16;
   auto ids =
       _mm512_set_epi32(15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0);
   auto con = *param2;
   auto consts = _mm512_set1_epi32(con);
   for (uint64_t i = 0; i < n - rest; i += 16) {
      Vec8u in(param1 + i);
      __mmask16 less = _mm512_cmplt_epi32_mask(in, consts);
      _mm512_mask_compressstoreu_epi32(result + found, less, ids);
      found += __builtin_popcount(less);
      ids = _mm512_add_epi32(ids, _mm512_set1_epi32(16));
   }
   for (uint64_t i = n - rest; i < n; ++i)
      if (param1[i] < con) result[found++] = i;
   return found;
}

const size_t lead = 16;

pos_t selsel_greater_equal_int32_t_col_int32_t_val_avx512_impl(
    pos_t n, pos_t* RES inSel, pos_t* RES result, int32_t* RES param1,
    int32_t* RES param2) {
   static_assert(sizeof(pos_t) == 4,
                 "This implementation only supports sizeof(pos_t) == 4");

   uint64_t found = 0;
   size_t rest = n % 16;
   auto con = *param2;
   auto consts = _mm512_set1_epi32(con);
   for (uint64_t i = 0; i < n - rest; i += 16) {
      Vec8u idxs(inSel + i);
      auto in = _mm512_i32gather_epi32(idxs, param1, 4);
      PREFETCH(&param1[inSel[i + lead]]);
      __mmask16 ge = _mm512_cmpge_epi32_mask(in, consts);
      _mm512_mask_compressstoreu_epi32(result + found, ge, idxs);
      found += __builtin_popcount(ge);
   }
   for (uint64_t i = n - rest; i < n; ++i) {
      const auto idx = inSel[i];
      if (param1[idx] >= con) result[found++] = idx;
   }
   return found;
}

#ifdef __AVX512VL__

pos_t selsel_less_int64_t_col_int64_t_val_avx512_impl(pos_t n, pos_t* RES inSel,
                                                      pos_t* RES result,
                                                      int64_t* RES param1,
                                                      int64_t* RES param2) {
   static_assert(sizeof(pos_t) == 4,
                 "This implementation only supports sizeof(pos_t) == 4");

   uint64_t found = 0;
   size_t rest = n % 8;
   auto con = *param2;
   auto consts = _mm512_set1_epi64(con);
   for (uint64_t i = 0; i < n - rest; i += 8) {
      auto idxs = _mm256_loadu_si256((const __m256i*)(inSel + i));
      auto in = _mm512_i32gather_epi64(idxs, (const long long int*)param1, 8);
      PREFETCH(&param1[inSel[i + lead]]);
      __mmask8 less = _mm512_cmplt_epi64_mask(in, consts);
      _mm256_mask_compressstoreu_epi32(result + found, less, idxs);
      found += __builtin_popcount(less);
   }
   for (uint64_t i = n - rest; i < n; ++i) {
      const auto idx = inSel[i];
      if (param1[idx] < con) result[found++] = idx;
   }
   return found;
}

pos_t selsel_greater_equal_int64_t_col_int64_t_val_avx512_impl(
    pos_t n, pos_t* RES inSel, pos_t* RES result, int64_t* RES param1,
    int64_t* RES param2) {
   static_assert(sizeof(pos_t) == 4,
                 "This implementation only supports sizeof(pos_t) == 4");

   uint64_t found = 0;
   size_t rest = n % 8;
   auto con = *param2;
   auto consts = _mm512_set1_epi64(con);
   for (uint64_t i = 0; i < n - rest; i += 8) {
      auto idxs = _mm256_loadu_si256((const __m256i*)(inSel + i));
      auto in = _mm512_i32gather_epi64(idxs, (const long long int*)param1, 8);
      PREFETCH(&param1[inSel[i + lead]]);
      __mmask8 less = _mm512_cmpge_epi64_mask(in, consts);
      _mm256_mask_compressstoreu_epi32(result + found, less, idxs);
      found += __builtin_popcount(less);
   }
   for (uint64_t i = n - rest; i < n; ++i) {
      const auto idx = inSel[i];
      if (param1[idx] >= con) result[found++] = idx;
   }
   return found;
}

pos_t selsel_less_equal_int64_t_col_int64_t_val_avx512_impl(
    pos_t n, pos_t* RES inSel, pos_t* RES result, int64_t* RES param1,
    int64_t* RES param2) {
   static_assert(sizeof(pos_t) == 4,
                 "This implementation only supports sizeof(pos_t) == 4");

   uint64_t found = 0;
   size_t rest = n % 8;
   auto con = *param2;
   auto consts = _mm512_set1_epi64(con);
   for (uint64_t i = 0; i < n - rest; i += 8) {
      auto idxs = _mm256_loadu_si256((const __m256i*)(inSel + i));
      auto in = _mm512_i32gather_epi64(idxs, (const long long int*)param1, 8);
      PREFETCH(&param1[inSel[i + lead]]);
      __mmask8 less = _mm512_cmple_epi64_mask(in, consts);
      _mm256_mask_compressstoreu_epi32(result + found, less, idxs);
      found += __builtin_popcount(less);
   }
   for (uint64_t i = n - rest; i < n; ++i) {
      const auto idx = inSel[i];
      if (param1[idx] <= con) result[found++] = idx;
   }
   return found;
}

#else

pos_t selsel_less_int64_t_col_int64_t_val_avx512_impl(pos_t n, pos_t* RES inSel,
                                                      pos_t* RES result,
                                                      int64_t* RES param1,
                                                      int64_t* RES param2) {
   static_assert(sizeof(pos_t) == 4,
                 "This implementation only supports sizeof(pos_t) == 4");

   uint64_t found = 0;
   size_t rest = n % 16;
   auto con = *param2;
   auto consts = _mm512_set1_epi64(con);
   for (uint64_t i = 0; i < n - rest; i += 16) {
      __mmask16 l = 0;
      {
         auto idxs = _mm256_loadu_si256((const __m256i*)(inSel + i));
         auto in =
             _mm512_i32gather_epi64(idxs, (const long long int*)param1, 8);
         __mmask8 less = _mm512_cmplt_epi64_mask(in, consts);
         l = less;
      }
      {
         auto idxs = _mm256_loadu_si256((const __m256i*)(inSel + i + 8));
         auto in =
             _mm512_i32gather_epi64(idxs, (const long long int*)param1, 8);
         __mmask8 less = _mm512_cmplt_epi64_mask(in, consts);
         l |= less << 8;
      }

      _mm512_mask_compressstoreu_epi32(result + found, l,
                                       _mm512_loadu_si512(inSel + i));
      found += __builtin_popcount(l);
   }
   for (uint64_t i = n - rest; i < n; ++i) {
      const auto idx = inSel[i];
      if (param1[idx] < con) result[found++] = idx;
   }
   return found;
}

pos_t selsel_greater_equal_int64_t_col_int64_t_val_avx512_impl(
    pos_t n, pos_t* RES inSel, pos_t* RES result, int64_t* RES param1,
    int64_t* RES param2) {
   static_assert(sizeof(pos_t) == 4,
                 "This implementation only supports sizeof(pos_t) == 4");

   uint64_t found = 0;
   size_t rest = n % 16;
   auto con = *param2;
   auto consts = _mm512_set1_epi64(con);
   for (uint64_t i = 0; i < n - rest; i += 16) {
      __mmask16 l;
      {
         auto idxs = _mm256_loadu_si256((const __m256i*)(inSel + i));
         auto in =
             _mm512_i32gather_epi64(idxs, (const long long int*)param1, 8);
         __mmask8 less = _mm512_cmpge_epi64_mask(in, consts);
         l = less;
      }
      {
         auto idxs = _mm256_loadu_si256((const __m256i*)(inSel + i + 8));
         auto in =
             _mm512_i32gather_epi64(idxs, (const long long int*)param1, 8);
         __mmask16 less = _mm512_cmpge_epi64_mask(in, consts);
         l |= less << 8;
      }
      _mm512_mask_compressstoreu_epi32(result + found, l,
                                       _mm512_loadu_si512(inSel + i));
      found += __builtin_popcount(l);
   }
   for (uint64_t i = n - rest; i < n; ++i) {
      const auto idx = inSel[i];
      if (param1[idx] >= con) result[found++] = idx;
   }
   return found;
}

pos_t selsel_less_equal_int64_t_col_int64_t_val_avx512_impl(
    pos_t n, pos_t* RES inSel, pos_t* RES result, int64_t* RES param1,
    int64_t* RES param2) {
   static_assert(sizeof(pos_t) == 4,
                 "This implementation only supports sizeof(pos_t) == 4");

   uint64_t found = 0;
   size_t rest = n % 16;
   auto con = *param2;
   auto consts = _mm512_set1_epi64(con);
   for (uint64_t i = 0; i < n - rest; i += 16) {
      __mmask16 l = 0;

      {
         auto idxs = _mm256_loadu_si256((const __m256i*)(inSel + i));
         auto in =
             _mm512_i32gather_epi64(idxs, (const long long int*)param1, 8);
         __mmask8 less = _mm512_cmple_epi64_mask(in, consts);
         l = less;
      }

      {
         auto idxs = _mm256_loadu_si256((const __m256i*)(inSel + i + 8));
         auto in =
             _mm512_i32gather_epi64(idxs, (const long long int*)param1, 8);
         __mmask16 less = _mm512_cmple_epi64_mask(in, consts);
         l |= less << 8;
      }

      _mm512_mask_compressstoreu_epi32(result + found, l,
                                       _mm512_loadu_si512(inSel + i));
      found += __builtin_popcount(l);
   }
   for (uint64_t i = n - rest; i < n; ++i) {
      const auto idx = inSel[i];
      if (param1[idx] <= con) result[found++] = idx;
   }
   return found;
}

#endif

F3 sel_less_int32_t_col_int32_t_val_avx512 =
    (F3)&sel_less_int32_t_col_int32_t_val_avx512_impl;
F4 selsel_greater_equal_int32_t_col_int32_t_val_avx512 =
    (F4)&selsel_greater_equal_int32_t_col_int32_t_val_avx512_impl;
F4 selsel_less_int64_t_col_int64_t_val_avx512 =
    (F4)&selsel_less_int64_t_col_int64_t_val_avx512_impl;
F4 selsel_greater_equal_int64_t_col_int64_t_val_avx512 =
    (F4)&selsel_greater_equal_int64_t_col_int64_t_val_avx512_impl;
F4 selsel_less_equal_int64_t_col_int64_t_val_avx512 =
    (F4)&selsel_less_equal_int64_t_col_int64_t_val_avx512_impl;
#endif
}
} // namespace vectorwise
