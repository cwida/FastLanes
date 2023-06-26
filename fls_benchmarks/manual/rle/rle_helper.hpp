#ifndef FAST_LANES_FLS_BENCHMARKS_DELTA_DELTA_HELPER_HPP
#define FAST_LANES_FLS_BENCHMARKS_DELTA_DELTA_HELPER_HPP

#include <immintrin.h>
#include <stdint.h>

namespace manual { namespace rle {
template <typename T>
size_t scalar_rle_compress(T* value, T* length, T* input) {
	auto   cur_val {input[0]};
	auto   nex_val {input[1]};
	auto   cur_len {0};
	size_t counter {0};
	for (size_t i {1}; i < 1024; ++i) {
		nex_val = input[i];
		if (cur_val != nex_val) {
			value[counter]  = cur_val;
			length[counter] = cur_len;
			cur_len         = 0;
			cur_val         = input[i];
			counter++;
		} else {
			cur_len++;
		}
	}
	value[counter]  = cur_val;
	length[counter] = cur_len;

	return (counter++);
}

template <typename T>
void scalar_rle_decompress(T* value, T* length, T* output) {
	size_t length_tmp {0};
	size_t length_off {0};
	size_t output_off {0};
	while (output_off < 1024) {
		length_tmp = length[length_off] + 1;
		for (int j = 0; j < length_tmp; ++j) {
			output[output_off + j] = value[length_off];
		}
		output_off += length_tmp;
		length_off += 1;
	}
}

void simd_rle_avx512_32(uint32_t* value, uint32_t* length, uint32_t* output) {
	size_t  length_tmp {0};
	size_t  length_off {0};
	size_t  output_off {0};
	__m512i tmp;

	size_t leftover {0};
	while (output_off < 1024) {
		length_tmp = length[length_off] + 1;
		for (int i = 0; i < length_tmp; i += 16) {
			if (output_off + i + 16 >= 1024) { // stop!
				while (output_off < 1024) {
					length_tmp = length[length_off] + 1;
					for (int j = 0; j < length_tmp; ++j) {
						output[output_off + j] = value[length_off];
					}
					output_off += length_tmp;
					length_off += 1;
				}
				break;
			}

			tmp = _mm512_set1_epi32(value[length_off]);
			_mm512_storeu_si512(output + i + output_off, tmp);
		}

		output_off += length_tmp;
		length_off += 1;
	}
}

void simd_rle_avx512_16(uint16_t* value, uint16_t* length, uint16_t* output) {
	size_t  length_tmp {0};
	size_t  length_off {0};
	size_t  output_off {0};
	__m512i tmp;

	while (output_off < 1024) {
		length_tmp = length[length_off] + 1;

		tmp = _mm512_set1_epi16(value[length_off]);

		for (int i = 0; i < length_tmp; i += 32) {
			if (output_off + i + 32 >= 1024) { // stop!
				while (output_off < 1024) {
					length_tmp = length[length_off] + 1;
					for (int j = 0; j < length_tmp; ++j) {
						output[output_off + j] = value[length_off];
					}
					output_off += length_tmp;
					length_off += 1;
				}
				break;
			}

			_mm512_storeu_si512(output + i + output_off, tmp);
		}

		output_off += length_tmp;
		length_off += 1;
	}
}

}} // namespace manual::rle
#endif
