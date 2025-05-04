/*
 * the API for FSST compression -- (c) Peter Boncz, Viktor Leis and Thomas Neumann (CWI, TU Munich), 2018-2019
 *
 * ===================================================================================================================================
 * this software is distributed under the MIT License (http://www.opensource.org/licenses/MIT):
 *
 * Copyright 2018-2020, CWI, TU Munich, FSU Jena
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated
 * documentation files (the "Software"), to deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * - The above copyright notice and this permission notice shall be included in all copies or substantial portions of
 * the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
 * OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * You can contact the authors via the FSST source repository : https://github.com/cwida/fsst
 * ===================================================================================================================================
 *
 * FSST: Fast Static Symbol Table compression
 * see the paper https://github.com/cwida/fsst/raw/master/fsstcompression.pdf
 *
 * FSST is a compression scheme focused on string/text data: it can compress strings from distributions with many
 * different values (i.e. where dictionary compression will not work well). It allows *random-access* to compressed
 * data: it is not block-based, so individual strings can be decompressed without touching the surrounding data in a
 * compressed block. When compared to e.g. lz4 (which is block-based), FSST achieves similar decompression speed, (2x)
 * better compression speed and 30% better compression ratio on text.
 *
 * FSST encodes strings also using a symbol table -- but it works on pieces of the string, as it maps "symbols" (1-8
 * byte sequences) onto "codes" (single-bytes). FSST can also represent a byte as an exception (255 followed by the
 * original byte). Hence, compression transforms a sequence of bytes into a (supposedly shorter) sequence of codes or
 * escaped bytes. These shorter byte-sequences could be seen as strings again and fit in whatever your program is that
 * manipulates strings.
 *
 * useful property: FSST ensures that strings that are equal, are also equal in their compressed form.
 *
 * In this API, strings are considered byte-arrays (byte = unsigned char) and a batch of strings is represented as an
 * array of unsigned char* pointers to their starts. A seperate length array (of unsigned int) denotes how many bytes
 * each string consists of.
 *
 * This representation as unsigned char* pointers tries to assume as little as possible on the memory management of the
 * program that calls this API, and is also intended to allow passing strings into this API without copying (even if you
 * use C++ strings).
 *
 * We optionally support C-style zero-terminated strings (zero appearing only at the end). In this case, the compressed
 * strings are also zero-terminated strings. In zero-terminated mode, the zero-byte at the end *is* counted in the
 * string byte-length.
 */

// NOLINTBEGIN
#ifndef FSST_INCLUDED_H
#define FSST_INCLUDED_H

#ifdef _MSC_VER
#define __restrict__
#define __BYTE_ORDER__          __ORDER_LITTLE_ENDIAN__
#define __ORDER_LITTLE_ENDIAN__ 2
#include <intrin.h>
static inline int __builtin_ctzl(unsigned long long x) {
	unsigned long ret;
	_BitScanForward64(&ret, x);
	return (int)ret;
}
#endif

#ifdef __cplusplus
#define FSST_FALLTHROUGH [[fallthrough]]
#include <cstring>
extern "C" {
#else
#define FSST_FALLTHROUGH
#endif

#include <cstdint>
#include <stddef.h>

/* A compressed string is simply a string of 1-byte codes; except for code 255, which is followed by an uncompressed
 * byte. */
#define FSST_ESC 255

/* Data structure needed for compressing strings - use fsst_duplicate() to create thread-local copies. Use
 * fsst_destroy() to free. */
using fsst_encoder_t = void*; /* opaque type - it wraps around a rather large (~900KB) C++ object */

/* Data structure needed for decompressing strings - read-only and thus can be shared between multiple decompressing
 * threads. */
using fsst_decoder_t = struct fsst_decoder_t {
	unsigned long long version;         /* version id */
	unsigned char      zero_terminated; /* terminator is a single-byte code that does not appear in longer symbols */
	unsigned char      len[255];        /* len[x] is the byte-length of the symbol x (1 < len[x] <= 8). */
	unsigned long long
	    symbol[255]; /* symbol[x] contains in LITTLE_ENDIAN the bytesequence that code x represents (0 <= x < 255). */
};

/* Calibrate a FSST symboltable from a batch of strings (it is best to provide at least 16KB of data). */
fsst_encoder_t* fsst_create(size_t         n,        /* IN: number of strings in batch to sample from. */
                            uint32_t       len_in[], /* IN: byte-lengths of the inputs */
                            unsigned char* str_in[], /* IN: string start pointers. */
                            int zero_terminated /* IN: whether input strings are zero-terminated. If so, encoded strings
                                                  are as well (i.e. symbol[0]=""). */
);

/* Create another encoder instance, necessary to do multi-threaded encoding using the same symbol table. */
fsst_encoder_t* fsst_duplicate(fsst_encoder_t* encoder /* IN: the symbol table to duplicate. */
);

#define FSST_MAXHEADER                                                                                                 \
	(8 + 1 + 8 + 2048 +                                                                                                \
	 1) /* maxlen of deserialized fsst header, produced/consumed by fsst_export() resp. fsst_import() */

/* Space-efficient symbol table serialization (smaller than sizeof(fsst_decoder_t) - by saving on the unused bytes in
 * symbols of len < 8). */
unsigned int                         /* OUT: number of bytes written in buf, at most sizeof(fsst_decoder_t) */
fsst_export(fsst_encoder_t* encoder, /* IN: the symbol table to dump. */
            unsigned char*  buf      /* OUT: pointer to a byte-buffer where to serialize this symbol table. */
);

/* Deallocate encoder. */
void fsst_destroy(fsst_encoder_t*);

/* Return a decoder structure from serialized format (typically used in a block-, file- or row-group header). */
unsigned int                         /* OUT: number of bytes consumed in buf (0 on failure). */
fsst_import(fsst_decoder_t* decoder, /* IN: this symbol table will be overwritten. */
            const uint8_t*  buf /* OUT: pointer to a byte-buffer where fsst_export() serialized this symbol table. */
);

/* Return a decoder structure from an encoder. */
fsst_decoder_t fsst_decoder(fsst_encoder_t* encoder);

/* Compress a batch of strings (on AVX512 machines best performance is obtained by compressing more than 32KB of string
 * volume). */
/* The output buffer must be large; at least "conservative space" (7+2*inputlength) for the first string for something
 * to happen. */
size_t /* OUT: the number of compressed strings (<=n) that fit the output buffer. */
fsst_compress(
    fsst_encoder_t* encoder,   /* IN: encoder obtained from fsst_create(). */
    size_t          nstrings,  /* IN: number of strings in batch to compress. */
    uint32_t        len_in[],  /* IN: byte-lengths of the inputs */
    unsigned char*  str_in[],  /* IN: input string start pointers. */
    size_t          outsize,   /* IN: byte-length of output buffer. */
    unsigned char*  output,    /* OUT: memory buffer to put the compressed strings in (one after the other). */
    uint32_t        len_out[], /* OUT: byte-lengths of the compressed strings. */
    unsigned char*  str_out[]  /* OUT: output string start pointers. Will all point into [output,output+size). */
);

/* Decompress a single string, inlined for speed. */
inline size_t /* OUT: bytesize of the decompressed string. If > size, the decoded output is truncated to size. */
fsst_decompress(fsst_decoder_t* decoder, /* IN: use this symbol table for compression. */
                size_t          len_in,  /* IN: byte-length of compressed string. */
                unsigned char*  str_in,  /* IN: compressed string. */
                size_t          size,    /* IN: byte-length of output buffer. */
                unsigned char*  output   /* OUT: memory buffer to put the decompressed string in. */
) {
	unsigned char* __restrict__ len         = (unsigned char* __restrict__)decoder->len;
	unsigned char* __restrict__ str_out     = (unsigned char* __restrict__)output;
	unsigned long long* __restrict__ symbol = (unsigned long long* __restrict__)decoder->symbol;
	size_t code, pos_out = 0, pos_in = 0;
#ifndef FSST_MUST_ALIGN /* defining on platforms that require aligned memory access may help their performance */
#define FSST_UNALIGNED_STORE(dst, src) memcpy((unsigned long long*)(dst), &(src), sizeof(unsigned long long))
#if defined(__BYTE_ORDER__) && defined(__ORDER_LITTLE_ENDIAN__) && (__BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__)
	while (pos_out + 32 <= size && pos_in + 4 <= len_in) {
		unsigned int next_block, escape_mask;
		memcpy(&next_block, str_in + pos_in, sizeof(unsigned int));
		escape_mask = (next_block & 0x80808080u) & ((((~next_block) & 0x7F7F7F7Fu) + 0x7F7F7F7Fu) ^ 0x80808080u);
		if (escape_mask == 0) {
			code = str_in[pos_in++];
			FSST_UNALIGNED_STORE(str_out + pos_out, symbol[code]);
			pos_out += len[code];
			code = str_in[pos_in++];
			FSST_UNALIGNED_STORE(str_out + pos_out, symbol[code]);
			pos_out += len[code];
			code = str_in[pos_in++];
			FSST_UNALIGNED_STORE(str_out + pos_out, symbol[code]);
			pos_out += len[code];
			code = str_in[pos_in++];
			FSST_UNALIGNED_STORE(str_out + pos_out, symbol[code]);
			pos_out += len[code];
		} else {
			unsigned long first_escape_pos =
			    static_cast<unsigned long>(__builtin_ctzl(static_cast<unsigned long>(escape_mask))) >> 3;
			switch (first_escape_pos) { /* Duff's device */
			case 3:
				code = str_in[pos_in++];
				FSST_UNALIGNED_STORE(str_out + pos_out, symbol[code]);
				pos_out += len[code];
			case 2:
				code = str_in[pos_in++];
				FSST_UNALIGNED_STORE(str_out + pos_out, symbol[code]);
				pos_out += len[code];
			case 1:
				code = str_in[pos_in++];
				FSST_UNALIGNED_STORE(str_out + pos_out, symbol[code]);
				pos_out += len[code];
			case 0:
				pos_in += 2;
				str_out[pos_out++] = str_in[pos_in - 1]; /* decompress an escaped byte */
			}
		}
	}
	if (pos_out + 24 <= size) { // handle the possibly 3 last bytes without a loop
		if (pos_in + 2 <= len_in) {
			str_out[pos_out] = str_in[pos_in + 1];
			if (str_in[pos_in] != FSST_ESC) {
				code = str_in[pos_in++];
				FSST_UNALIGNED_STORE(str_out + pos_out, symbol[code]);
				pos_out += len[code];
				if (str_in[pos_in] != FSST_ESC) {
					code = str_in[pos_in++];
					FSST_UNALIGNED_STORE(str_out + pos_out, symbol[code]);
					pos_out += len[code];
				} else {
					pos_in += 2;
					str_out[pos_out++] = str_in[pos_in - 1];
				}
			} else {
				pos_in += 2;
				pos_out++;
			}
		}
		if (pos_in < len_in) { // last code cannot be an escape
			code = str_in[pos_in++];
			FSST_UNALIGNED_STORE(str_out + pos_out, symbol[code]);
			pos_out += len[code];
		}
	}
#else
	while (posOut + 8 <= size && posIn < lenIn)
		if ((code = strIn[posIn++]) < FSST_ESC) {                /* symbol compressed as code? */
			FSST_UNALIGNED_STORE(strOut + posOut, symbol[code]); /* unaligned memory write */
			posOut += len[code];
		} else {
			strOut[posOut] = strIn[posIn]; /* decompress an escaped byte */
			posIn++;
			posOut++;
		}
#endif
#endif
	while (pos_in < len_in) {
		if ((code = str_in[pos_in++]) < FSST_ESC) {
			size_t pos_write = pos_out, end_write = pos_out + len[code];
			unsigned char* __restrict__ symbol_pointer = ((unsigned char* __restrict__)&symbol[code]) - pos_write;
			if ((pos_out = end_write) > size) {
				end_write = size;
			}
			for (; pos_write < end_write; pos_write++) { /* only write if there is room */
				str_out[pos_write] = symbol_pointer[pos_write];
			}
		} else {
			if (pos_out < size) {
				str_out[pos_out] = str_in[pos_in]; /* idem */
			}
			pos_in++;
			pos_out++;
		}
	}
	if (pos_out >= size && (decoder->zero_terminated & 1)) {
		str_out[size - 1] = 0;
	}
	return pos_out; /* full size of decompressed string (could be >size, then the actually decompressed part) */
}

#ifdef __cplusplus
}
#endif
#endif /* FSST_INCLUDED_H */

// NOLINTEND
