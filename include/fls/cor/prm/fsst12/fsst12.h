/*
 * the API for FSST12 compression -- (c) Peter Boncz, Viktor Leis and Thomas Neumann (CWI, TU Munich), 2018-2019
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
 * You can contact the authors via the FSST12 source repository : https://github.com/cwida/fsst12
 * ===================================================================================================================================
 *
 * FSST12: Fast Static Symbol Table compression
 * see the paper https://github.com/cwida/fsst12/raw/master/fsst12compression.pdf
 *
 * FSST12 is a compression scheme focused on string/text data: it can compress strings from distributions with many
 * different values (i.e. where dictionary compression will not work well). It allows *random-access* to compressed
 * data: it is not block-based, so individual strings can be decompressed without touching the surrounding data in a
 * compressed block. When compared to e.g. lz4 (which is block-based), FSST12 achieves similar decompression speed, (2x)
 * better compression speed and 30% better compression ratio on text.
 *
 * FSST12 encodes strings also using a symbol table -- but it works on pieces of the string, as it maps "symbols" (1-8
 * byte sequences) onto "codes" (single-bytes). FSST12 can also represent a byte as an exception (255 followed by the
 * original byte). Hence, compression transforms a sequence of bytes into a (supposedly shorter) sequence of codes or
 * escaped bytes. These shorter byte-sequences could be seen as strings again and fit in whatever your program is that
 * manipulates strings.
 *
 * useful property: FSST12 ensures that strings that are equal, are also equal in their compressed form.
 *
 * In this API, strings are considered byte-arrays (byte = unsigned char) and a batch of strings is represented as an
 * array of unsigned char* pointers to their starts. A seperate length array (of unsigned int) denotes how many bytes
 * each string consists of.
 *
 * This representation as unsigned char* pointers tries to assume as little as possible on the memory management of the
 * program that calls this API, and is also intended to allow passing strings into this API without copying (even if you
 * use C++ strings).
 *
 * This is the 12-bits version of FSST12: it uses a 4K dictionary (rather than the 256 dictionary and 8-bits codes)
 * 12-bits FSST12 often does not work better dan 8-bits, but it will outperform it on datasets that are more chaotic,
 * such as JSON and widely diverse URLs.
 */

// NOLINTBEGIN

#ifndef FSST12_INCLUDED_H
#define FSST12_INCLUDED_H

#include "assert.h"
using ulong = unsigned long;

#ifdef __cplusplus
#include <cstring>
extern "C" {
#endif

/* Data structure needed for compressing strings - use fsst12_duplicate() to create thread-local copies. Use
 * fsst12_destroy() to free. */
typedef void* fsst12_encoder_t; /* opaque type - it wraps around a rather large (~3MB) C++ object */

/* Data structure needed for decompressing strings - read-only and thus can be shared between multiple decompressing
 * threads. */
using fsst12_decoder_t = struct fsst12_decoder_t {
	unsigned long long version;   /* version id */
	unsigned char      len[4096]; /* len[x] is the byte-length of the symbol x (1 < len[x] <= 8). */
	unsigned long long
	    symbol[4096]; /* symbol[x] contains in LITTLE_ENDIAN the bytesequence that code x represents (0 <= x < 255). */
};

/* Calibrate a FSST12 dictionary from a batch of strings (it is best to provide at least 16KB of data). */
fsst12_encoder_t* fsst12_create(ulong          n,       /* IN: number of strings in batch to sample from. */
                                uint32_t       lenIn[], /* IN: byte-lengths of the inputs */
                                unsigned char* strIn[], /* IN: string start pointers. */
                                int            dummy);

/* Create another encoder instance, necessary to do multi-threaded encoding using the same dictionary. */
fsst12_encoder_t* fsst12_duplicate(fsst12_encoder_t* encoder /* IN: the dictionary to duplicate. */
);

#define FSST12_MAXHEADER                                                                                               \
	(8 + 16 + 4096 +                                                                                                   \
	 32768) /* maxlen of deserialized fsst12 header, produced/consumed by fsst12_export() resp. fsst12_import() */

/* Space-efficient dictionary serialization (smaller than sizeof(fsst12_decoder_t) - by saving on the unused bytes in
 * symbols of len < 8). */
unsigned int                             /* OUT: number of bytes written in buf, at most sizeof(fsst12_decoder_t) */
fsst12_export(fsst12_encoder_t* encoder, /* IN: the dictionary to dump. */
              unsigned char*    buf      /* OUT: pointer to a byte-buffer where to serialize this dictionary. */
);

/* Deallocate encoder. */
void fsst12_destroy(fsst12_encoder_t*);

/* Return a decoder structure from serialized format (typically used in a block-, file- or row-group header). */
unsigned int                             /* OUT: number of bytes consumed in buf (0 on failure). */
fsst12_import(fsst12_decoder_t* decoder, /* IN: this dictionary will be overwritten. */
              const uint8_t* buf /* OUT: pointer to a byte-buffer where fsst12_export() serialized this dictionary. */
);

/* Return a decoder structure from an encoder. */
fsst12_decoder_t fsst12_decoder(fsst12_encoder_t* encoder);

/* Compress a batch of strings (on AVX512 machines best performance is obtained by compressing more than 32KB of string
 * volume). */
/* The output buffer must be large; at least "conservative space" (7+2*inputlength) for the first string for something
 * to happen. */
ulong /* OUT: the number of compressed strings (<=n) that fit the output buffer. */
fsst12_compress(
    fsst12_encoder_t* encoder,  /* IN: encoder obtained from fsst12_create(). */
    ulong             nstrings, /* IN: number of strings in batch to compress. */
    uint32_t          lenIn[],  /* IN: byte-lengths of the inputs */
    unsigned char*    strIn[],  /* IN: input string start pointers. */
    ulong             outsize,  /* IN: byte-length of output buffer. */
    unsigned char*    output,   /* OUT: memory buffer to put the compressed strings in (one after the other). */
    uint32_t          lenOut[], /* OUT: byte-lengths of the compressed strings. */
    unsigned char*    strOut[]  /* OUT: output string start pointers. Will all point into [output,output+size). */
);

/* Decompress a single string, inlined for speed. */
inline unsigned long /* OUT: bytesize of the decompressed string. If > size, the decoded output is truncated to size. */
fsst12_decompress(fsst12_decoder_t* decoder, /* IN: use this dictionary for compression. */
                  unsigned long     lenIn,   /* IN: byte-length of compressed string. */
                  unsigned char*    strIn,   /* IN: compressed string. */
                  unsigned long     size,    /* IN: byte-length of output buffer. */
                  unsigned char*    output   /* OUT: memory buffer to put the decompressed string in. */
) {
	unsigned char* __restrict__ len    = (unsigned char* __restrict__)decoder->len;
	unsigned long* __restrict__ symbol = (unsigned long* __restrict__)decoder->symbol;
	unsigned char* __restrict__ strOut = (unsigned char* __restrict__)output;
	unsigned long posOut = 0, posIn = 0;
#define FSST12_UNALIGNED_STORE(dst, src) memcpy((unsigned long long*)(dst), &(src), sizeof(unsigned long long))
	while (posIn + 3 <= lenIn) {
		unsigned int code, code0, code1;
		memcpy(&code, strIn + posIn, sizeof(unsigned int));
		code0 = code & 4095;
		code1 = (code >> 12) & 4095;
		posIn += 3;
		unsigned char* __restrict__ src, * __restrict__ lim, * __restrict__ dst = strOut + posOut;
		for (lim = strOut + ((posOut + len[code0]) > size ? size : posOut + len[code0]),
		    src  = (unsigned char* __restrict__)&symbol[code0];
		     dst < lim;
		     dst++, src++)
			*dst = *src;
		posOut += len[code0];
		for (lim = strOut + ((posOut + len[code1]) > size ? size : posOut + len[code1]),
		    src  = (unsigned char* __restrict__)&symbol[code1];
		     dst < lim;
		     dst++, src++)
			*dst = *src;
		posOut += len[code1];
	}
	if (posIn < lenIn) {
		unsigned short code;
		memcpy(&code, strIn + posIn, sizeof(unsigned short));
		code &= 4095;
		posIn = lenIn;
		unsigned char* __restrict__ src, * __restrict__ lim, * __restrict__ dst = strOut + posOut;
		for (lim = strOut + ((posOut + len[code]) > size ? size : posOut + len[code]),
		    src  = (unsigned char* __restrict__)&symbol[code];
		     dst < lim;
		     dst++, src++)
			*dst = *src;
		posOut += len[code];
	}
	return posOut; /* full size of decompressed string (could be >size, then the actually decompressed part) */
}

#ifdef __cplusplus
}
#endif

#endif /* _FSST12_INCLUDED_H_ */

// NOLINTEND