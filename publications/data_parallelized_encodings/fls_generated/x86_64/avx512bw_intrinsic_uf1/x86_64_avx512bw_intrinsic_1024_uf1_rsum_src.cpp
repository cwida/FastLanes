#include "fls_gen/rsum/rsum.hpp"
#include "fls_gen/macros.hpp"
#include <immintrin.h>
#define _mm128 _mm
#define _mm_set1_epi64 _mm_set1_epi64x
#define _mm256_set1_epi64 _mm256_set1_epi64x
namespace generated
{
	namespace rsum::x86_64
	{
		namespace avx512bw
		{
			void rsum(const uint8_t *__restrict a_in_p, uint8_t* __restrict a_out_p, const uint8_t* __restrict a_base_p)
			{
				[[maybe_unused]] auto out = reinterpret_cast<__m512i *>(a_out_p);
				[[maybe_unused]] const auto in = reinterpret_cast<const __m512i *>(a_in_p);
				[[maybe_unused]] const auto base = reinterpret_cast<const __m512i *>(a_base_p);
				[[maybe_unused]] __m512i register_0;
				[[maybe_unused]] __m512i tmp_0;
				[[maybe_unused]] __m512i base_0;
				for(int i = 0; i < 2; ++i)
				{
					register_0 = _mm512_loadu_si512(in + (0 * 2) + (i * 1) + 0);
					tmp_0 = _mm512_loadu_si512(base + (0 * 2) + (i * 1));
					tmp_0 = tmp_0 + register_0;
					_mm512_storeu_si512(out + (i * 1) + (0 * 2) + 0, tmp_0);
					register_0 = _mm512_loadu_si512(in + (0 * 2) + (i * 1) + 2);
					tmp_0 = tmp_0 + register_0;
					_mm512_storeu_si512(out + (i * 1) + (0 * 2) + 2, tmp_0);
					register_0 = _mm512_loadu_si512(in + (0 * 2) + (i * 1) + 4);
					tmp_0 = tmp_0 + register_0;
					_mm512_storeu_si512(out + (i * 1) + (0 * 2) + 4, tmp_0);
					register_0 = _mm512_loadu_si512(in + (0 * 2) + (i * 1) + 6);
					tmp_0 = tmp_0 + register_0;
					_mm512_storeu_si512(out + (i * 1) + (0 * 2) + 6, tmp_0);
					register_0 = _mm512_loadu_si512(in + (0 * 2) + (i * 1) + 8);
					tmp_0 = tmp_0 + register_0;
					_mm512_storeu_si512(out + (i * 1) + (0 * 2) + 8, tmp_0);
					register_0 = _mm512_loadu_si512(in + (0 * 2) + (i * 1) + 10);
					tmp_0 = tmp_0 + register_0;
					_mm512_storeu_si512(out + (i * 1) + (0 * 2) + 10, tmp_0);
					register_0 = _mm512_loadu_si512(in + (0 * 2) + (i * 1) + 12);
					tmp_0 = tmp_0 + register_0;
					_mm512_storeu_si512(out + (i * 1) + (0 * 2) + 12, tmp_0);
					register_0 = _mm512_loadu_si512(in + (0 * 2) + (i * 1) + 14);
					tmp_0 = tmp_0 + register_0;
					_mm512_storeu_si512(out + (i * 1) + (0 * 2) + 14, tmp_0);
				}
			}
			void rsum(const uint16_t *__restrict a_in_p, uint16_t* __restrict a_out_p, const uint16_t* __restrict a_base_p)
			{
				[[maybe_unused]] auto out = reinterpret_cast<__m512i *>(a_out_p);
				[[maybe_unused]] const auto in = reinterpret_cast<const __m512i *>(a_in_p);
				[[maybe_unused]] const auto base = reinterpret_cast<const __m512i *>(a_base_p);
				[[maybe_unused]] __m512i register_0;
				[[maybe_unused]] __m512i tmp_0;
				[[maybe_unused]] __m512i base_0;
				for(int i = 0; i < 2; ++i)
				{
					register_0 = _mm512_loadu_si512(in + (0 * 2) + (i * 1) + 0);
					tmp_0 = _mm512_loadu_si512(base + (0 * 2) + (i * 1));
					tmp_0 = tmp_0 + register_0;
					_mm512_storeu_si512(out + (i * 1) + (0 * 2) + 0, tmp_0);
					register_0 = _mm512_loadu_si512(in + (0 * 2) + (i * 1) + 4);
					tmp_0 = tmp_0 + register_0;
					_mm512_storeu_si512(out + (i * 1) + (0 * 2) + 4, tmp_0);
					register_0 = _mm512_loadu_si512(in + (0 * 2) + (i * 1) + 8);
					tmp_0 = tmp_0 + register_0;
					_mm512_storeu_si512(out + (i * 1) + (0 * 2) + 8, tmp_0);
					register_0 = _mm512_loadu_si512(in + (0 * 2) + (i * 1) + 12);
					tmp_0 = tmp_0 + register_0;
					_mm512_storeu_si512(out + (i * 1) + (0 * 2) + 12, tmp_0);
					register_0 = _mm512_loadu_si512(in + (0 * 2) + (i * 1) + 16);
					tmp_0 = tmp_0 + register_0;
					_mm512_storeu_si512(out + (i * 1) + (0 * 2) + 16, tmp_0);
					register_0 = _mm512_loadu_si512(in + (0 * 2) + (i * 1) + 20);
					tmp_0 = tmp_0 + register_0;
					_mm512_storeu_si512(out + (i * 1) + (0 * 2) + 20, tmp_0);
					register_0 = _mm512_loadu_si512(in + (0 * 2) + (i * 1) + 24);
					tmp_0 = tmp_0 + register_0;
					_mm512_storeu_si512(out + (i * 1) + (0 * 2) + 24, tmp_0);
					register_0 = _mm512_loadu_si512(in + (0 * 2) + (i * 1) + 28);
					tmp_0 = tmp_0 + register_0;
					_mm512_storeu_si512(out + (i * 1) + (0 * 2) + 28, tmp_0);
					register_0 = _mm512_loadu_si512(in + (0 * 2) + (i * 1) + 2);
					tmp_0 = tmp_0 + register_0;
					_mm512_storeu_si512(out + (i * 1) + (0 * 2) + 2, tmp_0);
					register_0 = _mm512_loadu_si512(in + (0 * 2) + (i * 1) + 6);
					tmp_0 = tmp_0 + register_0;
					_mm512_storeu_si512(out + (i * 1) + (0 * 2) + 6, tmp_0);
					register_0 = _mm512_loadu_si512(in + (0 * 2) + (i * 1) + 10);
					tmp_0 = tmp_0 + register_0;
					_mm512_storeu_si512(out + (i * 1) + (0 * 2) + 10, tmp_0);
					register_0 = _mm512_loadu_si512(in + (0 * 2) + (i * 1) + 14);
					tmp_0 = tmp_0 + register_0;
					_mm512_storeu_si512(out + (i * 1) + (0 * 2) + 14, tmp_0);
					register_0 = _mm512_loadu_si512(in + (0 * 2) + (i * 1) + 18);
					tmp_0 = tmp_0 + register_0;
					_mm512_storeu_si512(out + (i * 1) + (0 * 2) + 18, tmp_0);
					register_0 = _mm512_loadu_si512(in + (0 * 2) + (i * 1) + 22);
					tmp_0 = tmp_0 + register_0;
					_mm512_storeu_si512(out + (i * 1) + (0 * 2) + 22, tmp_0);
					register_0 = _mm512_loadu_si512(in + (0 * 2) + (i * 1) + 26);
					tmp_0 = tmp_0 + register_0;
					_mm512_storeu_si512(out + (i * 1) + (0 * 2) + 26, tmp_0);
					register_0 = _mm512_loadu_si512(in + (0 * 2) + (i * 1) + 30);
					tmp_0 = tmp_0 + register_0;
					_mm512_storeu_si512(out + (i * 1) + (0 * 2) + 30, tmp_0);
				}
			}
			void rsum(const uint32_t *__restrict a_in_p, uint32_t* __restrict a_out_p, const uint32_t* __restrict a_base_p)
			{
				[[maybe_unused]] auto out = reinterpret_cast<__m512i *>(a_out_p);
				[[maybe_unused]] const auto in = reinterpret_cast<const __m512i *>(a_in_p);
				[[maybe_unused]] const auto base = reinterpret_cast<const __m512i *>(a_base_p);
				[[maybe_unused]] __m512i register_0;
				[[maybe_unused]] __m512i tmp_0;
				[[maybe_unused]] __m512i base_0;
				for(int i = 0; i < 2; ++i)
				{
					register_0 = _mm512_loadu_si512(in + (0 * 2) + (i * 1) + 0);
					tmp_0 = _mm512_loadu_si512(base + (0 * 2) + (i * 1));
					tmp_0 = tmp_0 + register_0;
					_mm512_storeu_si512(out + (i * 1) + (0 * 2) + 0, tmp_0);
					register_0 = _mm512_loadu_si512(in + (0 * 2) + (i * 1) + 8);
					tmp_0 = tmp_0 + register_0;
					_mm512_storeu_si512(out + (i * 1) + (0 * 2) + 8, tmp_0);
					register_0 = _mm512_loadu_si512(in + (0 * 2) + (i * 1) + 16);
					tmp_0 = tmp_0 + register_0;
					_mm512_storeu_si512(out + (i * 1) + (0 * 2) + 16, tmp_0);
					register_0 = _mm512_loadu_si512(in + (0 * 2) + (i * 1) + 24);
					tmp_0 = tmp_0 + register_0;
					_mm512_storeu_si512(out + (i * 1) + (0 * 2) + 24, tmp_0);
					register_0 = _mm512_loadu_si512(in + (0 * 2) + (i * 1) + 32);
					tmp_0 = tmp_0 + register_0;
					_mm512_storeu_si512(out + (i * 1) + (0 * 2) + 32, tmp_0);
					register_0 = _mm512_loadu_si512(in + (0 * 2) + (i * 1) + 40);
					tmp_0 = tmp_0 + register_0;
					_mm512_storeu_si512(out + (i * 1) + (0 * 2) + 40, tmp_0);
					register_0 = _mm512_loadu_si512(in + (0 * 2) + (i * 1) + 48);
					tmp_0 = tmp_0 + register_0;
					_mm512_storeu_si512(out + (i * 1) + (0 * 2) + 48, tmp_0);
					register_0 = _mm512_loadu_si512(in + (0 * 2) + (i * 1) + 56);
					tmp_0 = tmp_0 + register_0;
					_mm512_storeu_si512(out + (i * 1) + (0 * 2) + 56, tmp_0);
					register_0 = _mm512_loadu_si512(in + (0 * 2) + (i * 1) + 4);
					tmp_0 = tmp_0 + register_0;
					_mm512_storeu_si512(out + (i * 1) + (0 * 2) + 4, tmp_0);
					register_0 = _mm512_loadu_si512(in + (0 * 2) + (i * 1) + 12);
					tmp_0 = tmp_0 + register_0;
					_mm512_storeu_si512(out + (i * 1) + (0 * 2) + 12, tmp_0);
					register_0 = _mm512_loadu_si512(in + (0 * 2) + (i * 1) + 20);
					tmp_0 = tmp_0 + register_0;
					_mm512_storeu_si512(out + (i * 1) + (0 * 2) + 20, tmp_0);
					register_0 = _mm512_loadu_si512(in + (0 * 2) + (i * 1) + 28);
					tmp_0 = tmp_0 + register_0;
					_mm512_storeu_si512(out + (i * 1) + (0 * 2) + 28, tmp_0);
					register_0 = _mm512_loadu_si512(in + (0 * 2) + (i * 1) + 36);
					tmp_0 = tmp_0 + register_0;
					_mm512_storeu_si512(out + (i * 1) + (0 * 2) + 36, tmp_0);
					register_0 = _mm512_loadu_si512(in + (0 * 2) + (i * 1) + 44);
					tmp_0 = tmp_0 + register_0;
					_mm512_storeu_si512(out + (i * 1) + (0 * 2) + 44, tmp_0);
					register_0 = _mm512_loadu_si512(in + (0 * 2) + (i * 1) + 52);
					tmp_0 = tmp_0 + register_0;
					_mm512_storeu_si512(out + (i * 1) + (0 * 2) + 52, tmp_0);
					register_0 = _mm512_loadu_si512(in + (0 * 2) + (i * 1) + 60);
					tmp_0 = tmp_0 + register_0;
					_mm512_storeu_si512(out + (i * 1) + (0 * 2) + 60, tmp_0);
					register_0 = _mm512_loadu_si512(in + (0 * 2) + (i * 1) + 2);
					tmp_0 = tmp_0 + register_0;
					_mm512_storeu_si512(out + (i * 1) + (0 * 2) + 2, tmp_0);
					register_0 = _mm512_loadu_si512(in + (0 * 2) + (i * 1) + 10);
					tmp_0 = tmp_0 + register_0;
					_mm512_storeu_si512(out + (i * 1) + (0 * 2) + 10, tmp_0);
					register_0 = _mm512_loadu_si512(in + (0 * 2) + (i * 1) + 18);
					tmp_0 = tmp_0 + register_0;
					_mm512_storeu_si512(out + (i * 1) + (0 * 2) + 18, tmp_0);
					register_0 = _mm512_loadu_si512(in + (0 * 2) + (i * 1) + 26);
					tmp_0 = tmp_0 + register_0;
					_mm512_storeu_si512(out + (i * 1) + (0 * 2) + 26, tmp_0);
					register_0 = _mm512_loadu_si512(in + (0 * 2) + (i * 1) + 34);
					tmp_0 = tmp_0 + register_0;
					_mm512_storeu_si512(out + (i * 1) + (0 * 2) + 34, tmp_0);
					register_0 = _mm512_loadu_si512(in + (0 * 2) + (i * 1) + 42);
					tmp_0 = tmp_0 + register_0;
					_mm512_storeu_si512(out + (i * 1) + (0 * 2) + 42, tmp_0);
					register_0 = _mm512_loadu_si512(in + (0 * 2) + (i * 1) + 50);
					tmp_0 = tmp_0 + register_0;
					_mm512_storeu_si512(out + (i * 1) + (0 * 2) + 50, tmp_0);
					register_0 = _mm512_loadu_si512(in + (0 * 2) + (i * 1) + 58);
					tmp_0 = tmp_0 + register_0;
					_mm512_storeu_si512(out + (i * 1) + (0 * 2) + 58, tmp_0);
					register_0 = _mm512_loadu_si512(in + (0 * 2) + (i * 1) + 6);
					tmp_0 = tmp_0 + register_0;
					_mm512_storeu_si512(out + (i * 1) + (0 * 2) + 6, tmp_0);
					register_0 = _mm512_loadu_si512(in + (0 * 2) + (i * 1) + 14);
					tmp_0 = tmp_0 + register_0;
					_mm512_storeu_si512(out + (i * 1) + (0 * 2) + 14, tmp_0);
					register_0 = _mm512_loadu_si512(in + (0 * 2) + (i * 1) + 22);
					tmp_0 = tmp_0 + register_0;
					_mm512_storeu_si512(out + (i * 1) + (0 * 2) + 22, tmp_0);
					register_0 = _mm512_loadu_si512(in + (0 * 2) + (i * 1) + 30);
					tmp_0 = tmp_0 + register_0;
					_mm512_storeu_si512(out + (i * 1) + (0 * 2) + 30, tmp_0);
					register_0 = _mm512_loadu_si512(in + (0 * 2) + (i * 1) + 38);
					tmp_0 = tmp_0 + register_0;
					_mm512_storeu_si512(out + (i * 1) + (0 * 2) + 38, tmp_0);
					register_0 = _mm512_loadu_si512(in + (0 * 2) + (i * 1) + 46);
					tmp_0 = tmp_0 + register_0;
					_mm512_storeu_si512(out + (i * 1) + (0 * 2) + 46, tmp_0);
					register_0 = _mm512_loadu_si512(in + (0 * 2) + (i * 1) + 54);
					tmp_0 = tmp_0 + register_0;
					_mm512_storeu_si512(out + (i * 1) + (0 * 2) + 54, tmp_0);
					register_0 = _mm512_loadu_si512(in + (0 * 2) + (i * 1) + 62);
					tmp_0 = tmp_0 + register_0;
					_mm512_storeu_si512(out + (i * 1) + (0 * 2) + 62, tmp_0);
				}
			}
			void rsum(const uint64_t *__restrict a_in_p, uint64_t* __restrict a_out_p, const uint64_t* __restrict a_base_p)
			{
				[[maybe_unused]] auto out = reinterpret_cast<__m512i *>(a_out_p);
				[[maybe_unused]] const auto in = reinterpret_cast<const __m512i *>(a_in_p);
				[[maybe_unused]] const auto base = reinterpret_cast<const __m512i *>(a_base_p);
				[[maybe_unused]] __m512i register_0;
				[[maybe_unused]] __m512i tmp_0;
				[[maybe_unused]] __m512i base_0;
				for(int i = 0; i < 2; ++i)
				{
					register_0 = _mm512_loadu_si512(in + (0 * 2) + (i * 1) + 0);
					tmp_0 = _mm512_loadu_si512(base + (0 * 2) + (i * 1));
					tmp_0 = tmp_0 + register_0;
					_mm512_storeu_si512(out + (i * 1) + (0 * 2) + 0, tmp_0);
					register_0 = _mm512_loadu_si512(in + (0 * 2) + (i * 1) + 16);
					tmp_0 = tmp_0 + register_0;
					_mm512_storeu_si512(out + (i * 1) + (0 * 2) + 16, tmp_0);
					register_0 = _mm512_loadu_si512(in + (0 * 2) + (i * 1) + 32);
					tmp_0 = tmp_0 + register_0;
					_mm512_storeu_si512(out + (i * 1) + (0 * 2) + 32, tmp_0);
					register_0 = _mm512_loadu_si512(in + (0 * 2) + (i * 1) + 48);
					tmp_0 = tmp_0 + register_0;
					_mm512_storeu_si512(out + (i * 1) + (0 * 2) + 48, tmp_0);
					register_0 = _mm512_loadu_si512(in + (0 * 2) + (i * 1) + 64);
					tmp_0 = tmp_0 + register_0;
					_mm512_storeu_si512(out + (i * 1) + (0 * 2) + 64, tmp_0);
					register_0 = _mm512_loadu_si512(in + (0 * 2) + (i * 1) + 80);
					tmp_0 = tmp_0 + register_0;
					_mm512_storeu_si512(out + (i * 1) + (0 * 2) + 80, tmp_0);
					register_0 = _mm512_loadu_si512(in + (0 * 2) + (i * 1) + 96);
					tmp_0 = tmp_0 + register_0;
					_mm512_storeu_si512(out + (i * 1) + (0 * 2) + 96, tmp_0);
					register_0 = _mm512_loadu_si512(in + (0 * 2) + (i * 1) + 112);
					tmp_0 = tmp_0 + register_0;
					_mm512_storeu_si512(out + (i * 1) + (0 * 2) + 112, tmp_0);
					register_0 = _mm512_loadu_si512(in + (0 * 2) + (i * 1) + 8);
					tmp_0 = tmp_0 + register_0;
					_mm512_storeu_si512(out + (i * 1) + (0 * 2) + 8, tmp_0);
					register_0 = _mm512_loadu_si512(in + (0 * 2) + (i * 1) + 24);
					tmp_0 = tmp_0 + register_0;
					_mm512_storeu_si512(out + (i * 1) + (0 * 2) + 24, tmp_0);
					register_0 = _mm512_loadu_si512(in + (0 * 2) + (i * 1) + 40);
					tmp_0 = tmp_0 + register_0;
					_mm512_storeu_si512(out + (i * 1) + (0 * 2) + 40, tmp_0);
					register_0 = _mm512_loadu_si512(in + (0 * 2) + (i * 1) + 56);
					tmp_0 = tmp_0 + register_0;
					_mm512_storeu_si512(out + (i * 1) + (0 * 2) + 56, tmp_0);
					register_0 = _mm512_loadu_si512(in + (0 * 2) + (i * 1) + 72);
					tmp_0 = tmp_0 + register_0;
					_mm512_storeu_si512(out + (i * 1) + (0 * 2) + 72, tmp_0);
					register_0 = _mm512_loadu_si512(in + (0 * 2) + (i * 1) + 88);
					tmp_0 = tmp_0 + register_0;
					_mm512_storeu_si512(out + (i * 1) + (0 * 2) + 88, tmp_0);
					register_0 = _mm512_loadu_si512(in + (0 * 2) + (i * 1) + 104);
					tmp_0 = tmp_0 + register_0;
					_mm512_storeu_si512(out + (i * 1) + (0 * 2) + 104, tmp_0);
					register_0 = _mm512_loadu_si512(in + (0 * 2) + (i * 1) + 120);
					tmp_0 = tmp_0 + register_0;
					_mm512_storeu_si512(out + (i * 1) + (0 * 2) + 120, tmp_0);
					register_0 = _mm512_loadu_si512(in + (0 * 2) + (i * 1) + 4);
					tmp_0 = tmp_0 + register_0;
					_mm512_storeu_si512(out + (i * 1) + (0 * 2) + 4, tmp_0);
					register_0 = _mm512_loadu_si512(in + (0 * 2) + (i * 1) + 20);
					tmp_0 = tmp_0 + register_0;
					_mm512_storeu_si512(out + (i * 1) + (0 * 2) + 20, tmp_0);
					register_0 = _mm512_loadu_si512(in + (0 * 2) + (i * 1) + 36);
					tmp_0 = tmp_0 + register_0;
					_mm512_storeu_si512(out + (i * 1) + (0 * 2) + 36, tmp_0);
					register_0 = _mm512_loadu_si512(in + (0 * 2) + (i * 1) + 52);
					tmp_0 = tmp_0 + register_0;
					_mm512_storeu_si512(out + (i * 1) + (0 * 2) + 52, tmp_0);
					register_0 = _mm512_loadu_si512(in + (0 * 2) + (i * 1) + 68);
					tmp_0 = tmp_0 + register_0;
					_mm512_storeu_si512(out + (i * 1) + (0 * 2) + 68, tmp_0);
					register_0 = _mm512_loadu_si512(in + (0 * 2) + (i * 1) + 84);
					tmp_0 = tmp_0 + register_0;
					_mm512_storeu_si512(out + (i * 1) + (0 * 2) + 84, tmp_0);
					register_0 = _mm512_loadu_si512(in + (0 * 2) + (i * 1) + 100);
					tmp_0 = tmp_0 + register_0;
					_mm512_storeu_si512(out + (i * 1) + (0 * 2) + 100, tmp_0);
					register_0 = _mm512_loadu_si512(in + (0 * 2) + (i * 1) + 116);
					tmp_0 = tmp_0 + register_0;
					_mm512_storeu_si512(out + (i * 1) + (0 * 2) + 116, tmp_0);
					register_0 = _mm512_loadu_si512(in + (0 * 2) + (i * 1) + 12);
					tmp_0 = tmp_0 + register_0;
					_mm512_storeu_si512(out + (i * 1) + (0 * 2) + 12, tmp_0);
					register_0 = _mm512_loadu_si512(in + (0 * 2) + (i * 1) + 28);
					tmp_0 = tmp_0 + register_0;
					_mm512_storeu_si512(out + (i * 1) + (0 * 2) + 28, tmp_0);
					register_0 = _mm512_loadu_si512(in + (0 * 2) + (i * 1) + 44);
					tmp_0 = tmp_0 + register_0;
					_mm512_storeu_si512(out + (i * 1) + (0 * 2) + 44, tmp_0);
					register_0 = _mm512_loadu_si512(in + (0 * 2) + (i * 1) + 60);
					tmp_0 = tmp_0 + register_0;
					_mm512_storeu_si512(out + (i * 1) + (0 * 2) + 60, tmp_0);
					register_0 = _mm512_loadu_si512(in + (0 * 2) + (i * 1) + 76);
					tmp_0 = tmp_0 + register_0;
					_mm512_storeu_si512(out + (i * 1) + (0 * 2) + 76, tmp_0);
					register_0 = _mm512_loadu_si512(in + (0 * 2) + (i * 1) + 92);
					tmp_0 = tmp_0 + register_0;
					_mm512_storeu_si512(out + (i * 1) + (0 * 2) + 92, tmp_0);
					register_0 = _mm512_loadu_si512(in + (0 * 2) + (i * 1) + 108);
					tmp_0 = tmp_0 + register_0;
					_mm512_storeu_si512(out + (i * 1) + (0 * 2) + 108, tmp_0);
					register_0 = _mm512_loadu_si512(in + (0 * 2) + (i * 1) + 124);
					tmp_0 = tmp_0 + register_0;
					_mm512_storeu_si512(out + (i * 1) + (0 * 2) + 124, tmp_0);
					register_0 = _mm512_loadu_si512(in + (0 * 2) + (i * 1) + 2);
					tmp_0 = tmp_0 + register_0;
					_mm512_storeu_si512(out + (i * 1) + (0 * 2) + 2, tmp_0);
					register_0 = _mm512_loadu_si512(in + (0 * 2) + (i * 1) + 18);
					tmp_0 = tmp_0 + register_0;
					_mm512_storeu_si512(out + (i * 1) + (0 * 2) + 18, tmp_0);
					register_0 = _mm512_loadu_si512(in + (0 * 2) + (i * 1) + 34);
					tmp_0 = tmp_0 + register_0;
					_mm512_storeu_si512(out + (i * 1) + (0 * 2) + 34, tmp_0);
					register_0 = _mm512_loadu_si512(in + (0 * 2) + (i * 1) + 50);
					tmp_0 = tmp_0 + register_0;
					_mm512_storeu_si512(out + (i * 1) + (0 * 2) + 50, tmp_0);
					register_0 = _mm512_loadu_si512(in + (0 * 2) + (i * 1) + 66);
					tmp_0 = tmp_0 + register_0;
					_mm512_storeu_si512(out + (i * 1) + (0 * 2) + 66, tmp_0);
					register_0 = _mm512_loadu_si512(in + (0 * 2) + (i * 1) + 82);
					tmp_0 = tmp_0 + register_0;
					_mm512_storeu_si512(out + (i * 1) + (0 * 2) + 82, tmp_0);
					register_0 = _mm512_loadu_si512(in + (0 * 2) + (i * 1) + 98);
					tmp_0 = tmp_0 + register_0;
					_mm512_storeu_si512(out + (i * 1) + (0 * 2) + 98, tmp_0);
					register_0 = _mm512_loadu_si512(in + (0 * 2) + (i * 1) + 114);
					tmp_0 = tmp_0 + register_0;
					_mm512_storeu_si512(out + (i * 1) + (0 * 2) + 114, tmp_0);
					register_0 = _mm512_loadu_si512(in + (0 * 2) + (i * 1) + 10);
					tmp_0 = tmp_0 + register_0;
					_mm512_storeu_si512(out + (i * 1) + (0 * 2) + 10, tmp_0);
					register_0 = _mm512_loadu_si512(in + (0 * 2) + (i * 1) + 26);
					tmp_0 = tmp_0 + register_0;
					_mm512_storeu_si512(out + (i * 1) + (0 * 2) + 26, tmp_0);
					register_0 = _mm512_loadu_si512(in + (0 * 2) + (i * 1) + 42);
					tmp_0 = tmp_0 + register_0;
					_mm512_storeu_si512(out + (i * 1) + (0 * 2) + 42, tmp_0);
					register_0 = _mm512_loadu_si512(in + (0 * 2) + (i * 1) + 58);
					tmp_0 = tmp_0 + register_0;
					_mm512_storeu_si512(out + (i * 1) + (0 * 2) + 58, tmp_0);
					register_0 = _mm512_loadu_si512(in + (0 * 2) + (i * 1) + 74);
					tmp_0 = tmp_0 + register_0;
					_mm512_storeu_si512(out + (i * 1) + (0 * 2) + 74, tmp_0);
					register_0 = _mm512_loadu_si512(in + (0 * 2) + (i * 1) + 90);
					tmp_0 = tmp_0 + register_0;
					_mm512_storeu_si512(out + (i * 1) + (0 * 2) + 90, tmp_0);
					register_0 = _mm512_loadu_si512(in + (0 * 2) + (i * 1) + 106);
					tmp_0 = tmp_0 + register_0;
					_mm512_storeu_si512(out + (i * 1) + (0 * 2) + 106, tmp_0);
					register_0 = _mm512_loadu_si512(in + (0 * 2) + (i * 1) + 122);
					tmp_0 = tmp_0 + register_0;
					_mm512_storeu_si512(out + (i * 1) + (0 * 2) + 122, tmp_0);
					register_0 = _mm512_loadu_si512(in + (0 * 2) + (i * 1) + 6);
					tmp_0 = tmp_0 + register_0;
					_mm512_storeu_si512(out + (i * 1) + (0 * 2) + 6, tmp_0);
					register_0 = _mm512_loadu_si512(in + (0 * 2) + (i * 1) + 22);
					tmp_0 = tmp_0 + register_0;
					_mm512_storeu_si512(out + (i * 1) + (0 * 2) + 22, tmp_0);
					register_0 = _mm512_loadu_si512(in + (0 * 2) + (i * 1) + 38);
					tmp_0 = tmp_0 + register_0;
					_mm512_storeu_si512(out + (i * 1) + (0 * 2) + 38, tmp_0);
					register_0 = _mm512_loadu_si512(in + (0 * 2) + (i * 1) + 54);
					tmp_0 = tmp_0 + register_0;
					_mm512_storeu_si512(out + (i * 1) + (0 * 2) + 54, tmp_0);
					register_0 = _mm512_loadu_si512(in + (0 * 2) + (i * 1) + 70);
					tmp_0 = tmp_0 + register_0;
					_mm512_storeu_si512(out + (i * 1) + (0 * 2) + 70, tmp_0);
					register_0 = _mm512_loadu_si512(in + (0 * 2) + (i * 1) + 86);
					tmp_0 = tmp_0 + register_0;
					_mm512_storeu_si512(out + (i * 1) + (0 * 2) + 86, tmp_0);
					register_0 = _mm512_loadu_si512(in + (0 * 2) + (i * 1) + 102);
					tmp_0 = tmp_0 + register_0;
					_mm512_storeu_si512(out + (i * 1) + (0 * 2) + 102, tmp_0);
					register_0 = _mm512_loadu_si512(in + (0 * 2) + (i * 1) + 118);
					tmp_0 = tmp_0 + register_0;
					_mm512_storeu_si512(out + (i * 1) + (0 * 2) + 118, tmp_0);
					register_0 = _mm512_loadu_si512(in + (0 * 2) + (i * 1) + 14);
					tmp_0 = tmp_0 + register_0;
					_mm512_storeu_si512(out + (i * 1) + (0 * 2) + 14, tmp_0);
					register_0 = _mm512_loadu_si512(in + (0 * 2) + (i * 1) + 30);
					tmp_0 = tmp_0 + register_0;
					_mm512_storeu_si512(out + (i * 1) + (0 * 2) + 30, tmp_0);
					register_0 = _mm512_loadu_si512(in + (0 * 2) + (i * 1) + 46);
					tmp_0 = tmp_0 + register_0;
					_mm512_storeu_si512(out + (i * 1) + (0 * 2) + 46, tmp_0);
					register_0 = _mm512_loadu_si512(in + (0 * 2) + (i * 1) + 62);
					tmp_0 = tmp_0 + register_0;
					_mm512_storeu_si512(out + (i * 1) + (0 * 2) + 62, tmp_0);
					register_0 = _mm512_loadu_si512(in + (0 * 2) + (i * 1) + 78);
					tmp_0 = tmp_0 + register_0;
					_mm512_storeu_si512(out + (i * 1) + (0 * 2) + 78, tmp_0);
					register_0 = _mm512_loadu_si512(in + (0 * 2) + (i * 1) + 94);
					tmp_0 = tmp_0 + register_0;
					_mm512_storeu_si512(out + (i * 1) + (0 * 2) + 94, tmp_0);
					register_0 = _mm512_loadu_si512(in + (0 * 2) + (i * 1) + 110);
					tmp_0 = tmp_0 + register_0;
					_mm512_storeu_si512(out + (i * 1) + (0 * 2) + 110, tmp_0);
					register_0 = _mm512_loadu_si512(in + (0 * 2) + (i * 1) + 126);
					tmp_0 = tmp_0 + register_0;
					_mm512_storeu_si512(out + (i * 1) + (0 * 2) + 126, tmp_0);
				}
			}
		}
	}
}