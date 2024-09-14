
#include "common/runtime/Hash.hpp"
#include "vectorwise/Operations.hpp"
#include "vectorwise/Primitives.hpp"
#include <functional>

using namespace types;
using namespace std;

namespace vectorwise {
namespace primitives {


#if HASH_SIZE == 32
#define DEFAULT_HASH runtime::MurMurHash3
#else
#define DEFAULT_HASH runtime::MurMurHash
#endif
#define MK_HASH(type) F2 hash_##type##_col = (F2)&hash<type, DEFAULT_HASH>;
#define MK_HASH_SEL(type)                                                      \
   F3 hash_sel_##type##_col = (F3)&hash_sel<type, DEFAULT_HASH>;
#define MK_REHASH(type)                                                        \
   F2 rehash_##type##_col = (F2)&rehash<type, DEFAULT_HASH>;
#define MK_REHASH_SEL(type)                                                    \
   F3 rehash_sel_##type##_col = (F3)&rehash_sel<type, DEFAULT_HASH>;

EACH_TYPE(NIL, MK_HASH)
EACH_TYPE(NIL, MK_HASH_SEL)
EACH_TYPE(NIL, MK_REHASH)
EACH_TYPE(NIL, MK_REHASH_SEL)

// SIMD hashes
#ifdef __AVX512F__
#if HASH_SIZE != 32

#ifndef __AVX512DQ__
static_assert(false, "On this platform only 32-bit hashes are supported.");
#endif

F2 hash8_int64_t_col = (F2)&hash8<int64_t, DEFAULT_HASH>;
// F3 hash8_sel_int64_t_col = (F3)&hash8_sel<int64_t, DEFAULT_HASH>;
// F2 rehash8_int64_t_col = (F2)&rehash8<int64_t, DEFAULT_HASH>;
// F3 rehash8_sel_int64_t_col = (F3)&rehash8_sel<int64_t, DEFAULT_HASH>;

/*
 * This variant is a workaround for bad code generation of gcc. It is semantically equivalent
 * to hash4_sel<int32_t, DEFAULT_HASH>
 */
pos_t hash4_selASM(pos_t n, pos_t* RES inSel, hash_t* RES result, int32_t* RES input)
/// compute hash for input column
{
  size_t rest = n % 8;
  Vec8u seeds(seed);
  asm(
    "movabsq	$29875498475984, %%r8;"
    "vpbroadcastq	%%r8, %%zmm6;"
    "leaq	64(%2,%3), %%r11;"
    "movl	$-1, %%r8d;"
    "kmovb	%%r8d, %%k1;"
    "movabsq	$-4132994306676758123, %%r8;"
    "vpbroadcastq	%%r8, %%zmm2;"
    "movl	$47, %%r8d;"
    "vpbroadcastq	%%r8, %%zmm3;"
    "movl	$8, %%r8d;"
    "vpbroadcastq	%%r8, %%zmm5;"
    "movabsq	$-8915484478836094702, %%r8;"
    "vpmullq	%%zmm2, %%zmm5, %%zmm5;"
    "vpbroadcastq	%%r8, %%zmm4;"
    "vpxorq	%%zmm6, %%zmm4, %%zmm4;"
    ".Hash4SelInner:;"
    "vmovdqu32	(%0), %%ymm1;"
    "kmovb	%%k1, %%k2;"
    "addq	$64, %2;"
    "addq	$32, %0;"
    "vpgatherdd	(%1,%%ymm1,4), %%ymm0%{%%k2%};"
    "vpmovzxdq	%%ymm0, %%zmm0;"
    "vpmullq	%%zmm2, %%zmm0, %%zmm1;"
    "vpsrlvq	%%zmm3, %%zmm1, %%zmm7;"
    "vpxorq	%%zmm1, %%zmm7, %%zmm8;"
    "vpmullq	%%zmm2, %%zmm8, %%zmm9;"
    "vpxorq	%%zmm5, %%zmm9, %%zmm10;"
    "vpxorq	%%zmm4, %%zmm10, %%zmm11;"
    "vpmullq	%%zmm2, %%zmm11, %%zmm12;"
    "vpsrlvq	%%zmm3, %%zmm12, %%zmm13;"
    "vpxorq	%%zmm12, %%zmm13, %%zmm14;"
    "vpmullq	%%zmm2, %%zmm14, %%zmm15;"
    "vpsrlvq	%%zmm3, %%zmm15, %%zmm16;"
    "vpxorq	%%zmm15, %%zmm16, %%zmm17;"
    "vmovdqu64	%%zmm17, -64(%2);"
    "cmpq	%%r11, %2;"
    "jne	.Hash4SelInner;"
    ::
     "r"(inSel), // pointer to selection vector
     "r"(input), // pointer to data for gathering
     "r"(result), // pointer to output vector
     "r"((n-rest)*8)
    : "k1", "k2", "r11", "r10", "r8","ymm1",
      "zmm0", "zmm1","zmm2","zmm3","zmm4", "zmm5", "zmm6",
      "zmm7", "zmm8","zmm9","zmm10","zmm11", "zmm12", "zmm13",
      "zmm14", "zmm15","zmm16","zmm17");

  if(rest){
    __mmask16 remaining = (1 << rest) - 1;
    auto inSels = _mm256_loadu_si256((const __m256i *)(inSel + n - rest));//ignore mask here?
    Vec8u in = _mm512_cvtepu32_epi64(_mm256_mmask_i32gather_epi32(inSels, remaining, inSels, input, 4));
    auto hashes = DEFAULT_HASH().hashKey(in, seeds);
    _mm512_mask_storeu_epi64(result + n - rest, remaining, hashes);
  }
  return n;
}

F2 hash4_int32_t_col = (F2)&hash4<int32_t, DEFAULT_HASH>;
// F3 hash4_sel_int32_t_col = (F3)&hash4_sel<int32_t, DEFAULT_HASH>;
F3 hash4_sel_int32_t_col = (F3)&hash4_selASM;
F2 rehash4_int32_t_col = (F2)&rehash4<int32_t, DEFAULT_HASH>;
F3 rehash4_sel_int32_t_col = (F3)&rehash4_sel<int32_t, DEFAULT_HASH>;

#else

F2 hash4_int32_t_col = (F2)&hash4_16<int32_t, DEFAULT_HASH>;
F3 hash4_sel_int32_t_col = (F3)&hash4_16_sel<int32_t, DEFAULT_HASH>;
F2 rehash4_int32_t_col = (F2)&rehash4_16<int32_t, DEFAULT_HASH>;
F3 rehash4_sel_int32_t_col = (F3)&rehash4_16_sel<int32_t, DEFAULT_HASH>;

#endif
#endif
}
}
