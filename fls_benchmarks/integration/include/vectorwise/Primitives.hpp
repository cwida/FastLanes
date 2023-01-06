#pragma once
#include "common/defs.hpp"
#include "common/runtime/HashmapSmall.hpp"
#include "common/runtime/SIMD.hpp"
#include "common/runtime/Types.hpp"
#include "common/runtime/Util.hpp"
#include "vectorwise/VectorAllocator.hpp"
#include "vectorwise/defs.hpp"
#include <unordered_map>
// #include "/home/kersten/tools/iaca-lin64/iacaMarks.h"

namespace vectorwise {
namespace primitives {

//------------------------------------------------------------------------------
//--- selection templates
template <typename T, template <typename> class Op>
pos_t sel_col_val(pos_t n, pos_t* RES result, T* RES param1, T* RES param2)
/// select with column and constant
{
   uint64_t found = 0;
   const auto& con = *param2;
   for (uint64_t i = 0; i < n; ++i)
      if (Op<T>()(param1[i], con)) result[found++] = i;
   return found;
}

template <typename T, template <typename> class Op>
pos_t sel_col_val_or_val(pos_t n, pos_t* RES result, T* RES param1,
                         T* RES param2, T* RES param3)
/// select with column and two possible constants
{
   const auto& con1 = *param2;
   const auto& con2 = *param3;
   auto rStart = result;
   for (uint64_t i = 0; i < n; ++i) {
     bool decision = Op<T>()(param1[i], con1) | Op<T>()(param1[i], con2);
     *result = i;
     result += decision;
   }
   return result - rStart;
}

template <typename T, template <typename> class Op>
pos_t sel_col_col(pos_t n, pos_t* RES result, T* RES param1, T* RES param2)
/// select two columns
{
   uint64_t found = 0;
   for (uint64_t i = 0; i < n; ++i)
      if (Op<T>()(param1[i], param2[i])) result[found++] = i;
   return found;
}

template <typename T, template <typename> class Op>
pos_t selsel_col_val(pos_t n, pos_t* RES inSel, pos_t* RES result,
                     T* RES param1, T* RES param2)
/// select with input selection vector and two columns
{
   uint64_t found = 0;
   const auto con = *param2;
   for (uint64_t i = 0; i < n; ++i) {
      const auto idx = inSel[i];
      if (Op<T>()(param1[idx], con)) result[found++] = idx;
   }
   return found;
}

template <typename T, template <typename> class Op>
pos_t selsel_col_col(pos_t n, pos_t* RES inSel, pos_t* RES result,
                     T* RES param1, T* RES param2)
/// select with input selection vector and two columns
{
   uint64_t found = 0;
   for (uint64_t i = 0; i < n; ++i) {
      const auto idx = inSel[i];
      if (Op<T>()(param1[idx], param2[idx])) result[found++] = idx;
   }
   return found;
}

// --- branchfree selection templates
template <typename T, template <typename> class Op>
pos_t sel_col_val_bf(pos_t n, pos_t* RES result, T* RES param1, T* RES param2)
/// select with column and constant
{
   const auto con = *param2;
   auto rStart = result;
   for (uint64_t i = 0; i < n; ++i) {
      bool decision = Op<T>()(param1[i], con);
      *result = i;
      result += decision;
   }
   return result - rStart;
}

template <typename T, template <typename> class Op>
pos_t sel_col_col_bf(pos_t n, pos_t* RES result, T* RES param1, T* RES param2)
/// select with column and constant
{
   auto rStart = result;
   for (uint64_t i = 0; i < n; ++i) {
      bool decision = Op<T>()(param1[i], param2[i]);
      *result = i;
      result += decision;
   }
   return result - rStart;
}

template <typename T, template <typename> class Op>
pos_t selsel_col_val_bf(pos_t n, pos_t* RES inSel, pos_t* RES result,
                        T* RES param1, T* RES param2)
/// select with input selection vector and two columns
{
   auto rStart = result;
   const auto con = *param2;
   for (uint64_t i = 0; i < n; ++i) {
      const auto idx = inSel[i];
      bool decision = Op<T>()(param1[idx], con);
      *result = idx;
      result += decision;
   }
   return result - rStart;
}

template <typename T, template <typename> class Op>
pos_t selsel_col_col_bf(pos_t n, pos_t* RES inSel, pos_t* RES result,
                        T* RES param1, T* RES param2)
/// select with input selection vector and two columns
{
   auto rStart = result;
   for (uint64_t i = 0; i < n; ++i) {
      const auto idx = inSel[i];
      bool decision = Op<T>()(param1[idx], param2[idx]);
      *result = idx;
      result += decision;
   }
   return result - rStart;
}

//------------------------------------------------------------------------------
//--- projection templates
template <typename T, template <typename> class Op>
pos_t proj_col_val(pos_t n, T* RES result, T* RES param1, T* RES param2)
/// project with column and constant
{
   const auto constant = *param2;
   for (uint64_t i = 0; i < n; ++i) result[i] = Op<T>()(param1[i], constant);
   return n;
}

template <typename T, template <typename> class Op>
pos_t proj_val_col(pos_t n, T* RES result, T* RES param1, T* RES param2)
/// project with constant and column
{
   const auto constant = *param1;
   for (uint64_t i = 0; i < n; ++i) result[i] = Op<T>()(constant, param2[i]);
   return n;
}

template <typename T, template <typename> class Op>
pos_t proj_col_col(pos_t n, T* RES result, T* RES param1, T* RES param2)
/// project with two columns
{
   for (uint64_t i = 0; i < n; ++i) result[i] = Op<T>()(param1[i], param2[i]);
   return n;
}

template <typename T, template <typename> class Op>
pos_t proj_sel_col_val(pos_t n, pos_t* RES inSel, T* RES result, T* RES param1,
                       T* RES param2)
/// project with input selection vector and column and constant
{
   const auto constant = *param2;
   for (uint64_t i = 0; i < n; ++i) {
      const auto idx = inSel[i];
      result[i] = Op<T>()(param1[idx], constant);
   }
   return n;
}

template <typename T, template <typename> class Op>
pos_t proj_sel_val_col(pos_t n, pos_t* RES inSel, T* RES result, T* RES param1,
                       T* RES param2)
/// project with input selection vector and constant and column
{
   const auto constant = *param1;
   for (uint64_t i = 0; i < n; ++i) {
      const auto idx = inSel[i];
      result[i] = Op<T>()(constant, param2[idx]);
   }
   return n;
}

template <typename T, template <typename> class Op>
pos_t proj_sel_both_col_col(pos_t n, pos_t* RES inSel, T* RES result,
                            T* RES param1, T* RES param2)
/// project with input selection vector for both of two columns
{
   for (uint64_t i = 0; i < n; ++i) {
      const auto idx = inSel[i];
      result[i] = Op<T>()(param1[idx], param2[idx]);
   }
   return n;
}

template <typename T, template <typename> class Op>
pos_t proj_sel_col_col(pos_t n, pos_t* RES inSel, T* RES result, T* RES param1,
                       T* RES param2)
/// project with input selection vector first of two columns
{
   for (uint64_t i = 0; i < n; ++i) {
      const auto idx = inSel[i];
      result[i] = Op<T>()(param1[idx], param2[i]);
   }
   return n;
}

template <typename T, template <typename> class Op>
pos_t proj_col_sel_col(pos_t n, pos_t* RES inSel, T* RES result, T* RES param1,
                       T* RES param2)
/// project with input selection vector for second of two columns
{
   for (uint64_t i = 0; i < n; ++i) {
      const auto idx = inSel[i];
      result[i] = Op<T>()(param1[i], param2[idx]);
   }
   return n;
}

template <typename T, template <typename> class Op>
pos_t proj_sel_col_sel_col(pos_t n, pos_t* RES inSel1, pos_t* RES inSel2,
                           T* RES result, T* RES param1, T* RES param2)
/// project with separate input selection vector for each of two columns
{
   for (uint64_t i = 0; i < n; ++i) {
      const auto idx1 = inSel1[i];
      const auto idx2 = inSel2[i];
      result[i] = Op<T>()(param1[idx1], param2[idx2]);
   }
   return n;
}

template <typename T, typename R, template <typename> class Op>
pos_t apply_col(pos_t n, R* RES result, T* RES param1)
/// project with input selection vector and constant and column
{
   for (uint64_t i = 0; i < n; ++i) { result[i] = Op<T>()(param1[i]); }
   return n;
}

template <typename T, typename R, template <typename> class Op>
pos_t apply_sel_col(pos_t n, R* RES result, pos_t* RES inSel, T* RES param1)
/// project with input selection vector and constant and column
{
   for (uint64_t i = 0; i < n; ++i) {
      const auto idx = inSel[i];
      result[i] = Op<T>()(param1[idx]);
   }
   return n;
}

//------------------------------------------------------------------------------
//--- aggregation templates
template <typename T, template <typename> class Op>
pos_t aggr_static_col(pos_t n, T* RES result, T* RES param1)
/// aggregate column into single value
{
   auto aggregator = *result;
   for (uint64_t i = 0; i < n; ++i) aggregator = Op<T>()(param1[i], aggregator);
   *result = aggregator;
   return n > 0;
}

template <typename T, template <typename> class Op>
pos_t aggr_static_sel_col(pos_t n, pos_t* RES inSel, T* RES result,
                          T* RES param1)
/// aggregate with input selection vector and column into single value
{
   auto aggregator = *result;
   for (uint64_t i = 0; i < n; ++i) {
      const auto idx = inSel[i];
      aggregator = Op<T>()(param1[idx], aggregator);
   }
   *result = aggregator;
   return n;
}

template <typename T, template <typename> class Op>
pos_t aggr_col(pos_t n, T* RES entries[], T* RES param1, size_t offset)
/// aggregate into multiple aggregators given by result
{
   auto p1 = param1;
   for (auto e = entries, end = e + n; e < end; ++e, ++p1) {
      auto aggregate = addBytes(*e, offset);
      *aggregate = Op<T>()(*p1, *aggregate);
   }
   return n;
}

template <typename T, template <typename> class Op>
pos_t aggr_sel_col(pos_t n, T* RES entries[], pos_t* selParam1, T* RES param1,
                   size_t offset)
/// aggregate into multiple aggregators given by result, param1 has selection
/// vector
{
   auto s = selParam1;
   for (auto e = entries, end = e + n; e < end; ++e, ++s) {
      auto aggregate = addBytes(*e, offset);
      *aggregate = Op<T>()(param1[*s], *aggregate);
   }
   return n;
}

template <typename T, template <typename> class Op>
pos_t aggr_row(pos_t n, T* RES entries[], size_t offset, T** RES dataPtr,
               size_t* inSizePtr, size_t inOffset)
/// aggregate into multiple aggregators given by result
{
   auto data = addBytes(*dataPtr, inOffset);
   auto inSize = *inSizePtr;
   for (auto e = entries, end = e + n; e < end;
        ++e, data = addBytes(data, inSize)) {
      auto aggregate = addBytes(*e, offset);
      *aggregate = Op<T>()(*data, *aggregate);
   }
   return n;
}

template <typename T, template <typename> class Op> struct OpTraits;
template <typename T> struct OpTraits<T, std::plus> {
   static const T neutral = 0;
};
template <typename T> struct OpTraits<T, std::minus> {
   static const T neutral = 0;
};
template <typename T> struct OpTraits<T, std::multiplies> {
   static const T neutral = 1;
};
template <typename T> struct OpTraits<T, std::divides> {
   static const T neutral = 1;
};
template <typename T> struct OpTraits<T, std::modulus> {
   static const T neutral = 1;
};

template <typename T, template <typename> class Op>
pos_t aggr_init(pos_t n, T** RES toInit, size_t* struct_size, size_t offset) {
   auto step = *struct_size;
   auto current = addBytes(*toInit, offset);
   for (size_t i = 0; i < n; ++i, current = addBytes(current, step))
      *current = OpTraits<T, Op>::neutral;
   return n;
}

//------------------------------------------------------------------------------
//--- scatter templates
template <typename T>
pos_t scatter(pos_t n, T* RES input, T** RES start, size_t* step,
              size_t offset) {
   const auto s = *step;
   auto current = addBytes(*start, offset);
   for (size_t i = 0; i < n; ++i, current = addBytes(current, s))
      *current = input[i];
   return n;
}

template <typename T>
pos_t scatter_sel(pos_t n, pos_t* RES inSel, T* RES input, T** RES start,
                  size_t* step, size_t offset) {
   const auto s = *step;
   auto current = addBytes(*start, offset);
   for (uint64_t i = 0; i < n; ++i, current = addBytes(current, s))
      *current = input[inSel[i]];
   return n;
}

template <typename T>
pos_t scatter_sel_row(pos_t n, pos_t* RES inSel, T** RES inputPtr,
                      size_t* inStepPtr, size_t inOffset, T** RES start,
                      size_t* step, size_t offset) {
   const auto s = *step;
   auto input = *inputPtr;
   auto inStep = *inStepPtr;
   auto current = addBytes(*start, offset);
   for (uint64_t i = 0; i < n; ++i, current = addBytes(current, s))
      *current = *addBytes(input, inSel[i] * inStep + inOffset);
   return n;
}

//------------------------------------------------------------------------------
//--- gather templates
template <typename T>
pos_t gather_col(pos_t n, T* RES input[], size_t offset, T* RES out)
/// gathers using a list of pointers
{
   for (size_t i = 0; i < n; ++i) out[i] = *addBytes(input[i], offset);
   return n;
}

template <typename T>
pos_t gather_sel_col(pos_t n, pos_t* RES inSel, T* RES input[], size_t offset,
                     T* RES out)
/// gathers using a selection vector into a list of pointers
{
   for (size_t i = 0; i < n; ++i) {
      const auto idx = inSel[i];
      out[i] = *addBytes(input[idx], offset);
   }
   return n;
}

template <typename T>
pos_t gather_val(pos_t n, T** RES input, size_t offset, size_t* struct_size,
                 T* RES out)
/// gathers from a block of memory
{
   auto current = addBytes(*input, offset);
   auto size = *struct_size;
   for (size_t i = 0; i < n; ++i) {
      out[i] = *current;
      current = addBytes(current, size);
   }
   return n;
}

//------------------------------------------------------------------------------
//--- hashing templates
using hash_t = defs::hash_t;
#if HASH_SIZE == 32
const hash_t seed = 4000932304;
#else
const hash_t seed = 29875498475984;
#endif

template <typename T, typename Op>
pos_t hash(pos_t n, hash_t* RES result, T* RES input)
/// compute hash for input column
{
   for (uint64_t i = 0; i < n; ++i) result[i] = Op()(input[i], seed);
   return n;
}

template <typename T, typename Op>
pos_t hash_sel(pos_t n, pos_t* RES inSel, hash_t* RES result, T* RES input)
/// compute hash for input column
{
   for (uint64_t i = 0; i < n; ++i) {
      // IACA_START
      const auto idx = inSel[i];
      result[i] = Op()(input[idx], seed);
   }
   // IACA_END
   return n;
}

template <typename T, typename Op>
pos_t rehash(pos_t n, hash_t* RES result, T* RES input)
/// compute hash for input column, taking the value in result as seed
{
   for (uint64_t i = 0; i < n; ++i) result[i] = Op()(input[i], result[i]);
   return n;
}

template <typename T, typename Op>
pos_t rehash_sel(pos_t n, pos_t* RES inSel, hash_t* RES result, T* RES input)
/// compute hash for input column with selection vector, taking the value in
/// result as seed
{
   for (uint64_t i = 0; i < n; ++i) {
      const auto idx = inSel[i];
      result[i] = Op()(input[idx], result[i]);
   }
   return n;
}

template <typename T, typename Op>
pos_t hash8(pos_t n, hash_t* RES result, T* RES input)
/// compute hash for input column
{
   static_assert(sizeof(T) == 8, "Can only be used for inputs types of size 8");
   size_t rest = n % 8;
   Vec8u seeds(seed);
   for (uint64_t i = 0; i < n - rest; i += 8) {
      Vec8u in(input + i);
      auto hashes = Op().hashKey(
          in, seeds); // function call operator overloading is not working ?!
      _mm512_store_epi64(result + i, hashes);
   }
   if (rest) {
      __mmask8 remaining = (1 << rest) - 1;
      Vec8u in = _mm512_maskz_loadu_epi64(remaining, input + n - rest);
      auto hashes = Op().hashKey(in, seeds);
      _mm512_mask_store_epi64(result + n - rest, remaining, hashes);
   }
   return n;
}

template <typename T, typename Op>
pos_t hash4(pos_t n, hash_t* RES result, T* RES input)
/// compute hash for input column
{
   static_assert(sizeof(T) == 4, "Can only be used for inputs types of size 4");
   size_t rest = n % 8;
   Vec8u seeds(seed);
   for (uint64_t i = 0; i < n - rest; i += 8) {
      Vec8u in(_mm512_cvtepu32_epi64(
          _mm256_loadu_si256((const __m256i*)(input + i))));
      auto hashes = Op().hashKey(
          in, seeds); // function call operator overloading is not working ?!
      // _mm512_store_epi64(result + i, hashes);
      _mm512_mask_storeu_epi64(result + i, ~0, hashes);
   }
   if (rest) {
      __mmask16 remaining = (1 << rest) - 1;
      Vec8u in(_mm512_cvtepu32_epi64(
          _mm256_maskz_loadu_epi32(remaining, input + n - rest)));
      auto hashes = Op().hashKey(in, seeds);
      _mm512_mask_storeu_epi64(result + n - rest, remaining, hashes);
   }
   return n;
}

template <typename T, typename Op>
pos_t hash4_16(pos_t n, hash_t* RES result, T* RES input)
/// compute hash for input column
{
   static_assert(sizeof(T) == 4, "Can only be used for inputs types of size 4");
   size_t rest = n % 16;
   Vec16u seeds(seed);
   for (uint64_t i = 0; i < n - rest; i += 16) {
      Vec16u in(input + i);
      auto hashes = Op().hashKey(
          in, seeds); // function call operator overloading is not working ?!
      // _mm512_store_epi64(result + i, hashes);
      _mm512_mask_storeu_epi64(result + i, ~0, hashes);
   }
   if (rest) {
      __mmask16 remaining = (1 << rest) - 1;
      Vec16u in(input + n - rest);
      auto hashes = Op().hashKey(in, seeds);
      _mm512_mask_storeu_epi64(result + n - rest, remaining, hashes);
   }
   return n;
}

template <typename T, typename Op>
pos_t rehash4(pos_t n, hash_t* RES result, T* RES input)
/// compute hash for input column
{
   static_assert(sizeof(T) == 4, "Can only be used for inputs types of size 4");
   size_t rest = n % 8;
   for (uint64_t i = 0; i < n - rest; i += 8) {
      Vec8u seeds(result + i);
      Vec8u in(_mm512_cvtepu32_epi64(
          _mm256_loadu_si256((const __m256i*)(input + i))));
      auto hashes = Op().hashKey(
          in, seeds); // function call operator overloading is not working ?!
      // _mm512_store_epi64(result + i, hashes);
      _mm512_mask_storeu_epi64(result + i, ~0, hashes);
   }
   if (rest) {
      __mmask16 remaining = (1 << rest) - 1;
      Vec8u seeds = _mm512_maskz_loadu_epi64(remaining, result + n - rest);
      Vec8u in(_mm512_cvtepu32_epi64(
          _mm256_maskz_loadu_epi32(remaining, input + n - rest)));
      auto hashes = Op().hashKey(in, seeds);
      _mm512_mask_storeu_epi64(result + n - rest, remaining, hashes);
   }
   return n;
}

template <typename T, typename Op>
pos_t rehash4_16(pos_t n, hash_t* RES result, T* RES input)
/// compute hash for input column
{
   static_assert(sizeof(T) == 4, "Can only be used for inputs types of size 4");
   size_t rest = n % 16;
   for (uint64_t i = 0; i < n - rest; i += 16) {
      Vec16u seeds(result + i);
      Vec16u in(input + i);
      auto hashes = Op().hashKey(
          in, seeds); // function call operator overloading is not working ?!
      // _mm512_store_epi64(result + i, hashes);
      _mm512_mask_storeu_epi64(result + i, ~0, hashes);
   }
   if (rest) {
      __mmask16 remaining = (1 << rest) - 1;
      Vec16u seeds = _mm512_maskz_loadu_epi64(remaining, result + n - rest);
      Vec16u in(input + n - rest);
      auto hashes = Op().hashKey(in, seeds);
      _mm512_mask_storeu_epi64(result + n - rest, remaining, hashes);
   }
   return n;
}

template <typename T, typename Op>
pos_t hash4_sel(pos_t n, pos_t* RES inSel, hash_t* RES result, T* RES input)
/// compute hash for input column
{
   static_assert(sizeof(T) == 4, "Can only be used for inputs types of size 4");
   size_t rest = n % 8;
   Vec8u seeds(seed);
   __mmask16 all = ~0;
   for (uint64_t i = 0; i < n - rest; i += 8) {
      auto inSels = _mm256_loadu_si256((const __m256i*)(inSel + i));
      Vec8u in = _mm512_cvtepu32_epi64(
          _mm256_mmask_i32gather_epi32(inSels, all, inSels, input, 4));
      auto hashes = Op().hashKey(
          in, seeds); // function call operator overloading is not working ?!
      _mm512_mask_storeu_epi64(result + i, all, hashes);
   }
   if (rest) {
      __mmask16 remaining = (1 << rest) - 1;
      auto inSels = _mm256_loadu_si256(
          (const __m256i*)(inSel + n - rest)); // ignore mask here?
      Vec8u in = _mm512_cvtepu32_epi64(
          _mm256_mmask_i32gather_epi32(inSels, remaining, inSels, input, 4));
      auto hashes = Op().hashKey(in, seeds);
      _mm512_mask_storeu_epi64(result + n - rest, remaining, hashes);
   }
   return n;
}

template <typename T, typename Op>
pos_t hash4_16_sel(pos_t n, pos_t* RES inSel, hash_t* RES result, T* RES input)
/// compute hash for input column
{
   static_assert(sizeof(T) == 4, "Can only be used for inputs types of size 4");
   size_t rest = n % 16;
   Vec16u seeds(seed);
   __mmask16 all = ~0;
   for (uint64_t i = 0; i < n - rest; i += 16) {
      Vec16u inSels(inSel + i);
      Vec16u in = _mm512_i32gather_epi32(inSels, input, 4);
      auto hashes = Op().hashKey(in, seeds);
      _mm512_mask_storeu_epi64(result + i, all, hashes);
   }
   if (rest) {
      __mmask16 remaining = (1 << rest) - 1;
      Vec16u inSels(inSel + n - rest);
      Vec16u in = _mm512_mask_i32gather_epi32(inSels, all, inSels, input, 4);
      auto hashes = Op().hashKey(in, seeds);
      _mm512_mask_storeu_epi64(result + n - rest, remaining, hashes);
   }
   return n;
}

template <typename T, typename Op>
pos_t rehash4_sel(pos_t n, pos_t* RES inSel, hash_t* RES result, T* RES input)
/// compute hash for input column
{
   static_assert(sizeof(T) == 4, "Can only be used for inputs types of size 4");
   size_t rest = n % 8;
   for (uint64_t i = 0; i < n - rest; i += 8) {
      Vec8u seeds(result + i);
      auto inSels = _mm256_loadu_si256((const __m256i*)(inSel + i));
      Vec8u in = _mm512_cvtepu32_epi64(
          _mm256_mmask_i32gather_epi32(inSels, ~0, inSels, input, 4));
      auto hashes = Op().hashKey(
          in, seeds); // function call operator overloading is not working ?!
      _mm512_mask_storeu_epi64(result + i, ~0, hashes); // ??
   }
   if (rest) {
      __mmask16 remaining = (1 << rest) - 1;
      Vec8u seeds = _mm512_maskz_loadu_epi64(remaining, result + n - rest);
      auto inSels = _mm256_loadu_si256(
          (const __m256i*)(inSel + n - rest)); // ignore mask here?
      Vec8u in = _mm512_cvtepu32_epi64(
          _mm256_mmask_i32gather_epi32(inSels, remaining, inSels, input, 4));
      auto hashes = Op().hashKey(in, seeds);
      _mm512_mask_storeu_epi64(result + n - rest, remaining, hashes); // ??
   }
   return n;
}

template <typename T, typename Op>
pos_t rehash4_16_sel(pos_t n, pos_t* RES inSel, hash_t* RES result,
                     T* RES input)
/// compute hash for input column
{
   static_assert(sizeof(T) == 4, "Can only be used for inputs types of size 4");
   size_t rest = n % 16;
   for (uint64_t i = 0; i < n - rest; i += 16) {
      Vec16u seeds(result + i);
      Vec16u inSels(inSel + i);
      Vec16u in = _mm512_i32gather_epi32(inSels, input, 4);
      auto hashes = Op().hashKey(
          in, seeds); // function call operator overloading is not working ?!
      _mm512_mask_storeu_epi64(result + i, ~0, hashes); // ??
   }
   if (rest) {
      __mmask16 remaining = (1 << rest) - 1;
      Vec16u seeds = _mm512_maskz_loadu_epi64(remaining, result + n - rest);
      Vec16u inSels(inSel + n - rest);
      Vec16u in =
          _mm512_mask_i32gather_epi32(inSels, remaining, inSels, input, 4);
      auto hashes = Op().hashKey(in, seeds);
      _mm512_mask_storeu_epi64(result + n - rest, remaining, hashes);
   }
   return n;
}
//------------------------------------------------------------------------------
//--- key equality check for hashjoin
template <typename T, template <typename> class Op>
pos_t keys_equal(pos_t n, T* RES buildEntry[], size_t offset, pos_t* probeIdx,
                 T* RES probeKey)
/// takes join result Entry*[], probeIdx, compares keys for equality and writes
/// back equal keys
{
   uint64_t found = 0;
   for (uint64_t i = 0; i < n; ++i) {
      auto buildKey = addBytes(buildEntry[i], offset);
      if (Op<T>()(*buildKey, probeKey[probeIdx[i]])) {
         buildEntry[found] = buildEntry[i];
         probeIdx[found++] = probeIdx[i];
      }
   }
   return found;
}

//------------------------------------------------------------------------------
//--- key equality check for groupby
template <typename T>
pos_t keys_not_equal(pos_t n, pos_t* RES entryIdx, T* RES entry[],
                     T* RES probeKey, size_t offset,
                     SizeBuffer<pos_t>* RES notEq)
/// takes join result Entry*[], probeIdx, compares keys for equality and writes
/// back key ids that did not match
{
   auto idxWriter = entryIdx;
   for (auto idx = entryIdx, end = idx + n; idx < end; ++idx) {
      auto i = *idx;
      auto keyInHt = addBytes(entry[i], offset);
      if (*keyInHt == probeKey[i]) {
         *idxWriter++ = i;
      } else {
         notEq->push_back(i);
      }
   }
   return idxWriter - entryIdx;
}

template <typename T>
pos_t keys_not_equal_sel(pos_t n, pos_t* RES entryIdx, T* RES entry[],
                         pos_t* RES probeSel, T* RES probeKey, size_t offset,
                         SizeBuffer<pos_t>* RES notEq)
/// takes join result Entry*[], probeIdx, compares keys for equality and writes
/// back key ids that did not match
{
   auto idxWriter = entryIdx;
   for (auto idx = entryIdx, end = idx + n; idx < end; ++idx) {
      auto i = *idx;
      const auto probeSelIdx = probeSel[i];
      auto keyInHt = addBytes(entry[i], offset);
      if (*keyInHt == probeKey[probeSelIdx]) {
         *idxWriter++ = i;
      } else {
         notEq->push_back(i);
      }
   }
   return idxWriter - entryIdx;
}

template <typename T>
pos_t keys_not_equal_sel_bf(pos_t n, pos_t* RES entryIdx, T* RES entry[],
                            pos_t* RES probeSel, T* RES probeKey, size_t offset,
                            SizeBuffer<pos_t>* RES notEq)
/// takes join result Entry*[], probeIdx, compares keys for equality and writes
/// back key ids that did not match
{
   auto idxWriter = entryIdx;
   auto neqCount = notEq->size();
   auto neqWriter = notEq->data() + neqCount;
   for (auto idx = entryIdx, end = entryIdx + n; idx < end; ++idx) {
      const auto idxV = *idx;
      const auto probeSelIdx = probeSel[idxV];
      auto keyInHt = addBytes(entry[idxV], offset);
      bool eq = *keyInHt == probeKey[probeSelIdx];
      *idxWriter = idxV;
      idxWriter += eq;
      *neqWriter = idxV;
      neqWriter += !eq;
   }
   notEq->setSize(neqWriter - notEq->data());
   return idxWriter - entryIdx;
}

template <typename T>
pos_t keys_not_equal_row(pos_t n, pos_t* RES entryIdx, T* RES entry[],
                         T** RES probeKeyPtr, size_t offset,
                         size_t* entrySizePtr, size_t rowEntryOffset,
                         SizeBuffer<pos_t>* RES notEq)
/// takes join result Entry*[], probeIdx, compares keys for equality and writes
/// back key ids that did not match
/// Keys to compare against are in row format
{
   auto idxWriter = entryIdx;
   auto probeKey = *probeKeyPtr;
   auto entrySize = *entrySizePtr;
   for (size_t j = 0; j < n; ++j) {
      auto& i = entryIdx[j];
      auto keyInHt = addBytes(entry[i], offset);
      auto dataKey = addBytes(probeKey, i * entrySize + rowEntryOffset);
      if (*keyInHt == *dataKey) {
         *idxWriter++ = i;
      } else {
         notEq->push_back(i);
      }
   }
   return idxWriter - entryIdx;
}

//------------------------------------------------------------------------------
//--- partitioning by key
template <typename T>
pos_t partition_by_key(pos_t n, pos_t* sel, T* keys, hash_t* hashes,
                       pos_t* partitionBounds, pos_t* selOut,
                       pos_t* partitionBoundsOut,
                       runtime::HashmapSmall<pos_t, pos_t>* ht)
/// Input: n: number of partitions in partitionBounds
///        sel: Selection vector which selects from keys and hashes
///        keys: Buffer with values to distinguish
///        hashes: hashes of keys
///        partitionsBounds: positions exisiting partition ends in 'sel'
///        selOut: permutation of 'sel' with consecutive partitions
///        partitionsBoundsOut: positions of partition ends in 'selOut'
///        ht: a hashtable used during partitioning
{
   pos_t startCurPart = 0;
   pos_t outPartition = 0;

   // TODO: try two variants: map<T, pos_t> for type -> count
   //                        map<pos_t, pos_t> for type position in keys ->
   //                        count
   for (pos_t p = 0; p < n; ++p) { // each partition
      for (pos_t i = startCurPart, end = partitionBounds[p]; i < end; ++i)
      // Pass 1: Determine frequency for each value
      {
         auto& s = sel[i];
         auto& key = keys[s];
         auto& hash = hashes[s];
         auto el =
             ht->findFirst(hash, [&](pos_t pos) { return key == keys[pos]; });
         if (el)
            (*el)++;
         else {
            pos_t one = 1;
            ht->insert(s, hash, one);
         }
      }

      // convert group frequencies into offsets for writing
      auto partitionStart = startCurPart;
      for (auto& entry : *ht) {
         auto count = entry.value;
         entry.value = startCurPart;
         startCurPart += count;
         partitionBoundsOut[outPartition++] = startCurPart;
      }

      for (pos_t i = partitionStart, end = partitionBounds[p]; i < end; ++i)
      // Pass 2: Use offsets to scatter sel indices
      {
         auto pos = sel[i];
         auto& key = keys[pos];
         auto& groupOffset = *(ht->findFirst(
             hashes[pos], [&](pos_t cand) { return key == keys[cand]; }));
         selOut[groupOffset++] = sel[i];
      }
      ht->clear([&](auto& ht) {
         for (pos_t i = partitionStart, end = partitionBounds[p]; i < end;
              ++i) {
            auto pos = sel[i];
            ht.clear(hashes[pos]);
         }
      });
      startCurPart = partitionBounds[p];
   }
   return outPartition;
}

template <typename T>
pos_t partition_by_key_sel(pos_t n, pos_t* sel, pos_t* selK, T* keys,
                           hash_t* hashes, pos_t* partitionBounds,
                           pos_t* selOut, pos_t* partitionBoundsOut,
                           runtime::HashmapSmall<pos_t, pos_t>* ht)
/// Input: n: number of partitions in partitionBounds
///        sel: Selection vector which selects from selK and hashes
///        selK: Selection vector which selects keys
///        keys: Buffer with values to distinguish
///        hashes: hashes of keys
///        partitionsBounds: positions exisiting partition ends in 'sel'
///        selOut: permutation of 'sel' with consecutive partitions
///        partitionsBoundsOut: positions of partition ends in 'selOut'
///        ht: a hashtable used during partitioning
{
   pos_t startCurPart = 0;
   pos_t outPartition = 0;
   for (pos_t p = 0; p < n; ++p) { // each partition
      for (pos_t i = startCurPart, end = partitionBounds[p]; i < end; ++i)
      // Pass 1: Determine frequency for each value
      {
         auto idx = sel[i];
         auto& s = selK[idx];
         auto& key = keys[s];
         auto& hash = hashes[idx];
         auto el =
             ht->findFirst(hash, [&](pos_t pos) { return key == keys[pos]; });
         if (el)
            (*el)++;
         else {
            pos_t one = 1;
            ht->insert(s, hash, one);
         }
      }

      // convert group frequencies into offsets for writing
      auto partitionStart = startCurPart;
      for (auto& entry : *ht) {
         auto count = entry.value;
         entry.value = startCurPart;
         startCurPart += count;
         partitionBoundsOut[outPartition++] = startCurPart;
      }
      for (pos_t i = partitionStart, end = partitionBounds[p]; i < end; ++i)
      // Pass 2: Use frequency to scatter sel indices
      {
         auto idx = sel[i];
         auto pos = selK[idx];
         auto& key = keys[pos];
         auto& groupOffset = *(ht->findFirst(
             hashes[idx], [&](pos_t cand) { return key == keys[cand]; }));
         selOut[groupOffset++] = sel[i];
      }
      ht->clear([&](auto& ht) {
         for (pos_t i = partitionStart, end = partitionBounds[p]; i < end;
              ++i) {
            auto pos = sel[i];
            ht.clear(hashes[pos]);
         }
      });
      startCurPart = partitionBounds[p];
   }
   return outPartition;
}

template <typename T>
pos_t partition_by_key_row(pos_t n, pos_t* sel, T** rowDataStartPtr,
                           size_t hashOffset, size_t* entrySizePtr,
                           size_t dataOffset, pos_t* partitionBounds,
                           pos_t* selOut, pos_t* partitionBoundsOut,
                           runtime::HashmapSmall<pos_t, pos_t>* ht)
/// Input: n: number of partitions in partitionBounds
///        sel: Selection vector which selects from keys and hashes
///        rowDataStartPtr: Pointer to pointer to input data
///        hashOffset: offset in row where to find hash for row
///        entrySizePtr: size of one row in bytes
///        dataOffset: offset of key within row
///        partitionsBounds: positions exisiting partition ends in 'sel'
///        selOut: permutation of 'sel' with consecutive partitions
///        partitionsBoundsOut: positions of partition ends in 'selOut'
///        ht: a hashtable used during partitioning
{
   pos_t startCurPart = 0;
   pos_t outPartition = 0;
   auto rowDataStart = *rowDataStartPtr;
   auto entrySize = *entrySizePtr;
   for (pos_t p = 0; p < n; ++p) { // each partition
      for (pos_t i = startCurPart, end = partitionBounds[p]; i < end; ++i)
      // Pass 1: Determine frequency for each value
      {
         auto pos = sel[i];
         auto& key = *addBytes(rowDataStart, pos * entrySize + dataOffset);
         auto& hash =
             *addBytes((hash_t*)rowDataStart, pos * entrySize + hashOffset);
         auto el = ht->findFirst(hash, [&](pos_t cand) {
            return key ==
                   *addBytes(rowDataStart, cand * entrySize + dataOffset);
         });
         if (el)
            (*el)++;
         else {
            pos_t one = 1;
            ht->insert(pos, hash, one);
         }
      }

      // convert group frequencies into offsets for writing
      auto partitionStart = startCurPart;
      for (auto& entry : *ht) {
         auto count = entry.value;
         entry.value = startCurPart;
         startCurPart += count;
         partitionBoundsOut[outPartition++] = startCurPart;
      }

      for (pos_t i = partitionStart, end = partitionBounds[p]; i < end; ++i)
      // Pass 2: Use frequency to scatter sel indices
      {
         auto pos = sel[i];
         auto& key = *addBytes(rowDataStart, pos * entrySize + dataOffset);
         auto& hash =
             *addBytes((hash_t*)rowDataStart, pos * entrySize + hashOffset);
         auto& groupOffset = *(ht->findFirst(hash, [&](pos_t cand) {
            return key ==
                   *addBytes(rowDataStart, cand * entrySize + dataOffset);
         }));
         selOut[groupOffset++] = sel[i];
      }
      ht->clear([&](auto& ht) {
         for (pos_t i = partitionStart, end = partitionBounds[p]; i < end;
              ++i) {
            auto pos = sel[i];
            auto& hash =
                *addBytes((hash_t*)rowDataStart, pos * entrySize + hashOffset);
            ht.clear(hash);
         }
      });
      startCurPart = partitionBounds[p];
   }
   return outPartition;
}

//------------------------------------------------------------------------------
//--- primitive function pointer types
/// primitive that produces a selection vector, takes one arg
using F1 = pos_t (*)(pos_t n, void* result);
/// primitive that produces a selection vector, takes two args
using F2 = pos_t (*)(pos_t n, void* result, void* param1);
/// primitive that produces a selection vector, takes two args
using F3 = pos_t (*)(pos_t n, void* result, void* param1, void* param2);
/// primitive that takes and produces a selection vector, takes two args
using F4 = pos_t (*)(pos_t n, void* inputSel, void* result, void* param1,
                     void* param2);
using F5 = pos_t (*)(pos_t n, void* param1, void* param2, void* param3,
                     void* param4, void* param5);
using F6 = pos_t (*)(pos_t n, void* param1, void* param2, void* param3,
                     void* param4, void* param5, void* param6);
using F7 = pos_t (*)(pos_t n, void* param1, void* param2, void* param3,
                     void* param4, void* param5, void* param6, void* param7);
/// primitive that performs key comparison for hashjoin
using EQCheck = size_t (*)(pos_t n, void* buildEntry[], size_t offset,
                           pos_t* probeIdx, void* probeKey);
/// primitive to perform key comparison and write out non matching keys
using NEQCheck = pos_t (*)(pos_t n, pos_t* RES entryIdx, void* RES entry[],
                           void* RES probeKey, size_t offset,
                           SizeBuffer<pos_t>* notEq);
using NEQCheckSel = pos_t (*)(pos_t n, pos_t* RES entryIdx, void* RES entry[],
                              pos_t* probeSel, void* RES probeKey,
                              size_t offset, SizeBuffer<pos_t>* notEq);
using NEQCheckRow = pos_t (*)(pos_t n, pos_t* RES entryIdx, void* RES entry[],
                              void** RES probeKeyPtr, size_t offset,
                              size_t* entrySizePtr, size_t rowEntryOffset,
                              SizeBuffer<pos_t>* RES notEq);
using FScatter = pos_t (*)(pos_t n, void* RES input, void** RES start,
                           size_t* step, size_t offset);
using FScatterSel = pos_t (*)(pos_t n, pos_t* RES inSel, void* RES input,
                              void** RES start, size_t* step, size_t offset);
using FScatterSelRow = pos_t (*)(pos_t n, pos_t* RES inSel, void** RES inputPtr,
                                 size_t* inStepPtr, size_t inOffset,
                                 void** RES start, size_t* step, size_t offset);
/// primitive that gathers attributes from data in row format pointed to by
/// input and creates column format
using FGather = pos_t (*)(pos_t n, void* RES input[], size_t offset,
                          void* RES out);
using FGatherSel = pos_t (*)(pos_t n, pos_t* RES inSel, void* RES input[],
                             size_t offset, void* RES out);
using FGatherVal = pos_t (*)(pos_t n, void** RES input, size_t offset,
                             size_t* struct_size, void* RES out);
/// function type for aggregation
using FAggr = pos_t (*)(pos_t n, void* RES result[], void* RES param1,
                        size_t offset);
using FAggrSel = pos_t (*)(pos_t n, void* RES result[], pos_t* selParam1,
                           void* RES param1, size_t offset);
using FAggrRow = pos_t (*)(pos_t n, void* RES entries[], size_t offset,
                           void** RES dataPtr, size_t* inSizePtr,
                           size_t inOffset);
using FAggrInit = pos_t (*)(pos_t n, void** RES toInit, size_t* struct_size,
                            size_t offset);
/// function types for partitioning
using FPartitionByKey = pos_t (*)(pos_t n, pos_t* sel, void* keys,
                                  hash_t* hashes, pos_t* partitionBounds,
                                  pos_t* selOut, pos_t* partitionBoundsOut,
                                  runtime::HashmapSmall<pos_t, pos_t>*);
using FPartitionByKeySel = pos_t (*)(pos_t n, pos_t* sel, pos_t* selK,
                                     void* keys, hash_t* hashes,
                                     pos_t* partitionBounds, pos_t* selOut,
                                     pos_t* partitionBoundsOut,
                                     runtime::HashmapSmall<pos_t, pos_t>* ht);
using FPartitionByKeyRow = pos_t (*)(pos_t n, pos_t* sel,
                                     void** rowDataStartPtr,
                                     size_t /*hashOffset*/,
                                     size_t* entrySizePtr, size_t dataOffset,
                                     pos_t* partitionBounds, pos_t* selOut,
                                     pos_t* partitionBoundsOut,
                                     runtime::HashmapSmall<pos_t, pos_t>* ht);

//---------------------------------------------------------------------------
//--- pointers to instantiated primitives

// remark: if more preprocessing power is needed, e.g. arbitrary crossproduct,
// if statement in macros etc., refer to examples
// here http://www.boost.org/doc/libs/1_37_0/libs/preprocessor/doc/index.html

/// apply all comparators as second argument to m, pass c as first arg
#define EACH_COMP(m, c)                                                        \
   m(c, equal_to) m(c, greater_equal) m(c, greater) m(c, less_equal) m(c, less)

#define EACH_ARITH_COMM(m, c) m(c, plus) m(c, multiplies)
#define EACH_ARITH_NON_COMM(m, c) m(c, minus) m(c, divides) m(c, modulus)
#define EACH_ARITH(m, c) EACH_ARITH_COMM(m, c) EACH_ARITH_NON_COMM(m, c)

using Char_1 = types::Char<1>;
using Char_6 = types::Char<6>;
using Char_7 = types::Char<7>;
using Char_9 = types::Char<9>;
using Char_10 = types::Char<10>;
using Char_12 = types::Char<12>;
using Char_15 = types::Char<15>;
using Char_25 = types::Char<25>;
using Char_55 = types::Char<55>;
using Varchar_55 = types::Varchar<55>;

/// apply all types as first argument to m, pass c as second arg
#define EACH_TYPE_BASIC(m, c)                                                  \
   m(Date, c) m(Char_1, c) m(Char_6, c) m(Char_7, c) m(Char_9, c)              \
       m(Char_10, c) m(Char_12, c) m(Char_15, c) m(Char_25, c) m(hash_t, c)
#define EACH_TYPE_FULL(m, c)                                                   \
   m(int32_t, c) m(int64_t, c) m(int8_t, c) m(int16_t, c)
#define EACH_TYPE(m, c) EACH_TYPE_BASIC(m, c) EACH_TYPE_FULL(m, c)

#define NIL(t, m) m(t)

#define MK_SEL_COLCOL_DECL(type, op)                                           \
   extern F3 sel_##op##_##type##_col_##type##_col;
#define MK_SEL_COLVAL_DECL(type, op)                                           \
   extern F3 sel_##op##_##type##_col_##type##_val;
#define MK_SEL_COLVALORVAL_DECL(type, op)                                      \
   extern F4 sel_##op##_##type##_col_##type##_val_or_##type##_val;
#define MK_SELSEL_COLCOL_DECL(type, op)                                        \
   extern F4 selsel_##op##_##type##_col_##type##_col;
#define MK_SELSEL_COLVAL_DECL(type, op)                                        \
   extern F4 selsel_##op##_##type##_col_##type##_val;

#define MK_SEL_COLCOL_BF_DECL(type, op)                                        \
   extern F3 sel_##op##_##type##_col_##type##_col_bf;
#define MK_SEL_COLVAL_BF_DECL(type, op)                                        \
   extern F3 sel_##op##_##type##_col_##type##_val_bf;
#define MK_SELSEL_COLCOL_BF_DECL(type, op)                                     \
   extern F4 selsel_##op##_##type##_col_##type##_col_bf;
#define MK_SELSEL_COLVAL_BF_DECL(type, op)                                     \
   extern F4 selsel_##op##_##type##_col_##type##_val_bf;

#define MK_PROJ_COLCOL_DECL(type, op)                                          \
   extern F3 proj_##op##_##type##_col_##type##_col;
#define MK_PROJ_COLVAL_DECL(type, op)                                          \
   extern F3 proj_##op##_##type##_col_##type##_val;
#define MK_PROJ_VALCOL_DECL(type, op)                                          \
   extern F3 proj_##op##_##type##_val_##type##_col;
#define MK_PROJ_SEL_BOTH_COLCOL_DECL(type, op)                                 \
   extern F4 proj_sel_both_##op##_##type##_col_##type##_col;
#define MK_PROJ_SEL_COLCOL_DECL(type, op)                                      \
   extern F4 proj_##op##_sel_##type##_col_##type##_col;
#define MK_PROJ_COL_SEL_COL_DECL(type, op)                                     \
   extern F4 proj_##op##_##type##_col_sel_##type##_col;
#define MK_PROJ_SEL_COL_SEL_COL_DECL(type, op)                                 \
   extern F5 proj_##op##_sel_##type##_col_sel_##type##_col;
#define MK_PROJ_SEL_COLVAL_DECL(type, op)                                      \
   extern F4 proj_sel_##op##_##type##_col_##type##_val;
#define MK_PROJ_SEL_VALCOL_DECL(type, op)                                      \
   extern F4 proj_sel_##op##_##type##_val_##type##_col;

#define MK_AGGR_STATIC_COL_DECL(type, op)                                      \
   extern F2 aggr_static_##op##_##type##_col;
#define MK_AGGR_STATIC_SEL_COL_DECL(type, op)                                  \
   extern F3 aggr_static_sel_##op##_##type##_col;
#define MK_AGGR_COL_DECL(type, op) extern FAggr aggr_##op##_##type##_col;
#define MK_AGGR_SEL_COL_DECL(type, op)                                         \
   extern FAggrSel aggr_sel_##op##_##type##_col;
#define MK_AGGR_ROW_DECL(type, op) extern FAggrRow aggr_row_##op##_##type##_col;
#define MK_AGGR_INIT_DECL(type, op)                                            \
   extern FAggrInit aggr_init_##op##_##type##_col;

#define MK_HASH_DECL(type) extern F2 hash_##type##_col;
#define MK_HASH_SEL_DECL(type) extern F3 hash_sel_##type##_col;
#define MK_REHASH_DECL(type) extern F2 rehash_##type##_col;
#define MK_REHASH_SEL_DECL(type) extern F3 rehash_sel_##type##_col;

#define MK_SCATTER_DECL(type) extern FScatter scatter_##type##_col;
#define MK_SCATTER_SEL_DECL(type) extern FScatterSel scatter_sel_##type##_col;
#define MK_SCATTER_SEL_ROW_DECL(type)                                          \
   extern FScatterSelRow scatter_sel_row_##type##_col;

#define MK_GATHER_COL_DECL(type) extern FGather gather_col_##type##_col;
#define MK_GATHER_SEL_COL_DECL(type)                                           \
   extern FGatherSel gather_sel_col_##type##_col;
#define MK_GATHER_VAL_DECL(type) extern FGatherVal gather_val_##type##_col;

#define MK_KEYS_EQUAL_DECL(type) extern EQCheck keys_equal_##type##_col;
#define MK_KEYS_NOT_EQUAL_DECL(type)                                           \
   extern NEQCheck keys_not_equal_##type##_col;
#define MK_KEYS_NOT_EQUAL_SEL_DECL(type)                                       \
   extern NEQCheckSel keys_not_equal_sel_##type##_col;
#define MK_KEYS_NOT_EQUAL_ROW_DECL(type)                                       \
   extern NEQCheckRow keys_not_equal_row_##type##_col;

#define MK_PARTITION_DECL(type)                                                \
   extern FPartitionByKey partition_by_key_##type##_col;
#define MK_PARTITION_SEL_DECL(type)                                            \
   extern FPartitionByKeySel partition_by_key_sel_##type##_col;
#define MK_PARTITION_ROW_DECL(type)                                            \
   extern FPartitionByKeyRow partition_by_key_row_##type##_col;

// create declarations
EACH_COMP(EACH_TYPE, MK_SEL_COLCOL_DECL)
EACH_COMP(EACH_TYPE, MK_SEL_COLVALORVAL_DECL)
EACH_COMP(EACH_TYPE, MK_SEL_COLVAL_DECL)
EACH_COMP(EACH_TYPE, MK_SELSEL_COLCOL_DECL)
EACH_COMP(EACH_TYPE, MK_SELSEL_COLVAL_DECL)

EACH_COMP(EACH_TYPE, MK_SEL_COLCOL_BF_DECL)
EACH_COMP(EACH_TYPE, MK_SEL_COLVAL_BF_DECL)
EACH_COMP(EACH_TYPE, MK_SELSEL_COLCOL_BF_DECL)
EACH_COMP(EACH_TYPE, MK_SELSEL_COLVAL_BF_DECL)

extern F3 sel_contains_Varchar_55_col_Varchar_55_val;

EACH_ARITH(EACH_TYPE_FULL, MK_PROJ_COLCOL_DECL)
EACH_ARITH(EACH_TYPE_FULL, MK_PROJ_COLVAL_DECL)
EACH_ARITH(EACH_TYPE_FULL, MK_PROJ_SEL_BOTH_COLCOL_DECL)
EACH_ARITH(EACH_TYPE_FULL, MK_PROJ_SEL_COLCOL_DECL)
EACH_ARITH(EACH_TYPE_FULL, MK_PROJ_COL_SEL_COL_DECL)
EACH_ARITH(EACH_TYPE_FULL, MK_PROJ_SEL_COL_SEL_COL_DECL)
EACH_ARITH(EACH_TYPE_FULL, MK_PROJ_SEL_COLVAL_DECL)
EACH_ARITH_NON_COMM(EACH_TYPE_FULL, MK_PROJ_VALCOL_DECL)
EACH_ARITH_NON_COMM(EACH_TYPE_FULL, MK_PROJ_SEL_VALCOL_DECL)

extern F2 apply_extract_year_col;
extern F3 apply_extract_year_sel_col;

EACH_ARITH(EACH_TYPE_FULL, MK_AGGR_STATIC_COL_DECL)
EACH_ARITH(EACH_TYPE_FULL, MK_AGGR_STATIC_SEL_COL_DECL)
EACH_ARITH(EACH_TYPE_FULL, MK_AGGR_COL_DECL)
EACH_ARITH(EACH_TYPE_FULL, MK_AGGR_SEL_COL_DECL)
EACH_ARITH(EACH_TYPE_FULL, MK_AGGR_ROW_DECL)
EACH_ARITH(EACH_TYPE_FULL, MK_AGGR_INIT_DECL)
extern F1 aggr_static_count_star;
extern FAggr aggr_count_star;

EACH_TYPE(NIL, MK_HASH_DECL)
EACH_TYPE(NIL, MK_HASH_SEL_DECL)
EACH_TYPE(NIL, MK_REHASH_DECL)
EACH_TYPE(NIL, MK_REHASH_SEL_DECL)

EACH_TYPE(NIL, MK_SCATTER_DECL)
EACH_TYPE(NIL, MK_SCATTER_SEL_DECL)
EACH_TYPE(NIL, MK_SCATTER_SEL_ROW_DECL)

EACH_TYPE(NIL, MK_GATHER_COL_DECL)
EACH_TYPE(NIL, MK_GATHER_SEL_COL_DECL)
EACH_TYPE(NIL, MK_GATHER_VAL_DECL)

EACH_TYPE(NIL, MK_KEYS_EQUAL_DECL)
EACH_TYPE(NIL, MK_KEYS_NOT_EQUAL_DECL)
EACH_TYPE(NIL, MK_KEYS_NOT_EQUAL_SEL_DECL)
EACH_TYPE(NIL, MK_KEYS_NOT_EQUAL_ROW_DECL)
extern F3 lookup_sel;

EACH_TYPE(NIL, MK_PARTITION_DECL);
EACH_TYPE(NIL, MK_PARTITION_SEL_DECL);
EACH_TYPE(NIL, MK_PARTITION_ROW_DECL);

// Specializations
#ifdef __AVX512F__
extern F2 hash8_int64_t_col;
// extern F3 hash8_sel_int64_t_col;
// extern F2 rehash8_int64_t_col;
// extern F3 rehash8_sel_int64_t_col;

extern F2 hash4_int32_t_col;
extern F3 hash4_sel_int32_t_col;
extern F2 rehash4_int32_t_col;
extern F3 rehash4_sel_int32_t_col;

extern F4 proj_sel8_minus_int64_t_val_int64_t_col;
extern F4 proj_sel8_plus_int64_t_col_int64_t_val;
extern F3 proj8_multiplies_int64_t_col_int64_t_col;
extern F4 proj8_multiplies_sel_int64_t_col_int64_t_col;

extern F3 sel_less_int32_t_col_int32_t_val_avx512;
extern F4 selsel_greater_equal_int32_t_col_int32_t_val_avx512;
extern F4 selsel_greater_equal_int64_t_col_int64_t_val_avx512;
extern F4 selsel_less_int64_t_col_int64_t_val_avx512;
extern F4 selsel_less_equal_int64_t_col_int64_t_val_avx512;
#endif
} // namespace primitives
} // namespace vectorwise

// switch for choosing branching or branch free implementations
#ifdef BRANCHING
#define BF(FUNC) FUNC
#else
#define BF(FUNC) FUNC##_bf
#endif
