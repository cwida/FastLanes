
#include "common/runtime/Hash.hpp"
#include "vectorwise/Operations.hpp"
#include "vectorwise/Primitives.hpp"
#include <functional>

using namespace types;
using namespace std;

namespace vectorwise {
namespace primitives {

#define MK_PROJ_COLCOL(type, op)                                               \
   F3 proj_##op##_##type##_col_##type##_col = (F3)&proj_col_col<type, op>;

#define MK_PROJ_COLVAL(type, op)                                               \
   F3 proj_##op##_##type##_col_##type##_val = (F3)&proj_col_val<type, op>;

#define MK_PROJ_SEL_BOTH_COLCOL(type, op)                                      \
   F4 proj_sel_both_##op##_##type##_col_##type##_col =                         \
       (F4)&proj_sel_both_col_col<type, op>;

#define MK_PROJ_SEL_COLCOL(type, op)                                           \
   F4 proj_##op##_sel_##type##_col_##type##_col =                              \
       (F4)&proj_sel_col_col<type, op>;
#define MK_PROJ_COL_SEL_COL(type, op)                                          \
   F4 proj_##op##_##type##_col_sel_##type##_col =                              \
       (F4)&proj_col_sel_col<type, op>;
#define MK_PROJ_SEL_COL_SEL_COL(type, op)                                      \
   F5 proj_##op##_sel_##type##_col_sel_##type##_col =                          \
       (F5)&proj_sel_col_sel_col<type, op>;

#define MK_PROJ_SEL_COLVAL(type, op)                                           \
   F4 proj_sel_##op##_##type##_col_##type##_val =                              \
       (F4)&proj_sel_col_val<type, op>;

#define MK_PROJ_VALCOL(type, op)                                               \
   F3 proj_##op##_##type##_val_##type##_col = (F3)&proj_val_col<type, op>;

#define MK_PROJ_SEL_VALCOL(type, op)                                           \
   F4 proj_sel_##op##_##type##_val_##type##_col =                              \
       (F4)&proj_sel_val_col<type, op>;

pos_t lookup_sel_(pos_t n, pos_t* target, pos_t* sel, pos_t* source) {
   for (size_t i = 0; i < n; ++i) target[i] = source[sel[i]];
   return n;
}
F3 lookup_sel = (F3)&lookup_sel_;

template <typename int64_t> struct ExtractYear {
   Integer operator()(int64_t& d) { return types::extractYear(d); }
};
F2 apply_extract_year_col = (F2)&apply_col<Date, Integer, ExtractYear>;
F3 apply_extract_year_sel_col = (F3)&apply_sel_col<Date, Integer, ExtractYear>;

EACH_ARITH(EACH_TYPE_FULL, MK_PROJ_COLCOL)
EACH_ARITH(EACH_TYPE_FULL, MK_PROJ_COLVAL) // with second arg const
EACH_ARITH(EACH_TYPE_FULL,
           MK_PROJ_SEL_BOTH_COLCOL) // with input selection vector

EACH_ARITH(EACH_TYPE_FULL, MK_PROJ_SEL_COLCOL)
EACH_ARITH(EACH_TYPE_FULL, MK_PROJ_COL_SEL_COL)
EACH_ARITH(EACH_TYPE_FULL, MK_PROJ_SEL_COL_SEL_COL)

EACH_ARITH(EACH_TYPE_FULL,
           MK_PROJ_SEL_COLVAL) // with above and second arg const
EACH_ARITH_NON_COMM(EACH_TYPE_FULL, MK_PROJ_VALCOL)
EACH_ARITH_NON_COMM(EACH_TYPE_FULL, MK_PROJ_SEL_VALCOL)


#ifdef __AVX512F__

pos_t proj_sel8_minus_int64_t_val_int64_t_col_impl(pos_t n, pos_t* RES inSel, int64_t* RES result, int64_t* RES param1,
                                              int64_t* RES param2){
  size_t rest = n % 8;
  const auto constant = *param1;
  Vec8u consts = _mm512_set1_epi64(constant);
  for (uint64_t i = 0; i < n - rest; i += 8){
    auto idxs = _mm256_loadu_si256((const __m256i*)(inSel + i));
    Vec8u in = _mm512_i32gather_epi64(idxs, (const long long int*)param2, 8);
    auto res = consts - in;
    _mm512_store_epi64(result + i, res);
  }
  for (uint64_t i = n-rest; i < n; ++i) {
    const auto idx = inSel[i];
    result[i] = constant - param2[idx];
  }
  return n;
}
pos_t proj_sel8_plus_int64_t_col_int64_t_val_impl(pos_t n, pos_t* RES inSel, int64_t* RES result, int64_t* RES param1,
                                        int64_t* RES param2){
  size_t rest = n % 8;
  const auto constant = *param2;
  Vec8u consts = _mm512_set1_epi64(constant);
  for (uint64_t i = 0; i < n - rest; i += 8){
    auto idxs = _mm256_loadu_si256((const __m256i*)(inSel + i));
    Vec8u in = _mm512_i32gather_epi64(idxs, (const long long int*)param1, 8);
    auto res = consts + in;
    _mm512_store_epi64(result + i, res);
  }
  for (uint64_t i = n-rest; i < n; ++i) {
    const auto idx = inSel[i];
    result[i] = constant + param1[idx];
  }
  return n;
}

F4 proj_sel8_minus_int64_t_val_int64_t_col = (F4)&proj_sel8_minus_int64_t_val_int64_t_col_impl;
F4 proj_sel8_plus_int64_t_col_int64_t_val = (F4)&proj_sel8_plus_int64_t_col_int64_t_val_impl;
#endif


#ifdef __AVX512DQ__
pos_t proj8_multiplies_int64_t_col_int64_t_col_impl(pos_t n, int64_t* RES result,
                                              int64_t* RES param1, int64_t* RES param2){
  size_t rest = n % 8;
  for (uint64_t i = 0; i < n - rest; i += 8){
    Vec8u in1(param1 + i);
    Vec8u in2(param2 + i);
    auto res = in1 * in2;
    _mm512_store_epi64(result + i, res);
  }
  for (uint64_t i = n-rest; i < n; ++i) result[i] = param1[i] * param2[i];
  return n;
};
pos_t proj8_multiplies_sel_int64_t_col_int64_t_col_impl(pos_t n, pos_t* RES inSel, int64_t* RES result, int64_t* RES param1,
                                                    int64_t* RES param2){
  size_t rest = n % 8;
  for (uint64_t i = 0; i < n - rest; i += 8){
    auto idxs = _mm256_loadu_si256((const __m256i*)(inSel + i));
    Vec8u in1 = _mm512_i32gather_epi64(idxs, (const long long int*)param1, 8);
    Vec8u in2(param2 + i);
    auto res = in1 * in2;
    _mm512_store_epi64(result + i, res);
  }
  for (uint64_t i = n-rest; i < n; ++i) {
    const auto idx = inSel[i];
    result[i] = param1[idx] * param2[i];
  }
  return n;
}

F3 proj8_multiplies_int64_t_col_int64_t_col = (F3)&proj8_multiplies_int64_t_col_int64_t_col_impl;
F4 proj8_multiplies_sel_int64_t_col_int64_t_col = (F4)&proj8_multiplies_sel_int64_t_col_int64_t_col_impl;
#endif
}
}
