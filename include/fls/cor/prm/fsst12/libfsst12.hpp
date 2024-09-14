#ifndef FLS_COR_PRM_FSST12_LIBFSST12_HPP
#define FLS_COR_PRM_FSST12_LIBFSST12_HPP

// NOLINTBEGIN
#pragma clang diagnostic ignored "-Wconversion"
#pragma clang diagnostic ignored "-Wshorten-64-to-32"

// this software is distributed under the MIT License (http://www.opensource.org/licenses/MIT):
//
// Copyright 2018-2019, CWI, TU Munich
//
// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated
// documentation files (the "Software"), to deal in the Software without restriction, including without limitation the
// rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to
// permit persons to whom the Software is furnished to do so, subject to the following conditions:
//
// - The above copyright notice and this permission notice shall be included in all copies or substantial portions of
// the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
// COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
// OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
//
// You can contact the authors via the FSST12 source repository : https://github.com/cwida/fsst12
#include <algorithm>
#include <cassert>
#include <cstring>
#include <fcntl.h>
#include <fstream>
#include <iostream>
#include <memory>
#include <numeric>
#include <queue>
#include <string>
#if defined(_WIN32)
#include <windows.h> // For Windows memory-mapping
#else
#include <sys/mman.h> // For POSIX memory-mapping
#endif
#include <sys/stat.h>
#include <sys/types.h>
#include <unordered_set>
#include <vector>

// [FLS_CHG]
// clang-format off
using namespace std;

#include "fsst12.h" // the official FSST12 API -- also usable by C mortals

/* workhorse type for string and buffer lengths: 64-bits on 64-bits platforms and 32-bits on 32-bits platforms */
using ulong = unsigned long;

/* unsigned integers */
typedef uint8_t  u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

#define FSST12_ENDIAN_MARKER    ((u64)1)
#define FSST12_VERSION_20190218 20190218
#define FSST12_VERSION          ((u64)FSST12_VERSION_20190218)

// "symbols" are character sequences (up to 8 bytes)
// A symbol is compressed into a "code" of, 1.5 bytes (12 bits)
#define FSST12_CODE_MAX         4096
#define FSST12_CODE_MASK        ((u16)(FSST12_CODE_MAX - 1))

inline uint64_t fsst12_unaligned_load(u8 const* V) {
	uint64_t Ret;
	memcpy(&Ret, V, sizeof(uint64_t)); // compiler will generate efficient code (unaligned load, where possible)
	return Ret;
}

struct Symbol12 {
	static const unsigned maxLength = 8;

	// gcl = u32 garbageBits:16,code:12,length:4 -- but we avoid exposing this bit-field notation
	u32 gcl; // use a single u32 to be sure "code" is accessed with one load and can be compared with one comparison
	mutable u32 gain; // mutable because gain value should be ignored in find() on unordered_set of Symbol12s

	// the byte sequence that this symbol stands for
	u8 symbol[maxLength];

	Symbol12()
	    : gcl(0) {}

	explicit Symbol12(u8 c, u16 code)
	    : gcl((1 << 28) | (code << 16) | 7) {
		*(u64*)symbol = c;
	} // single-char symbol
	explicit Symbol12(const char* input, u32 len) {
		if (len < 8) {
			*(u64*)symbol = 0;
			for (u32 i = 0; i < len; i++)
				symbol[i] = input[i];
			set_code_len(FSST12_CODE_MASK, len);
		} else {
			*(u64*)symbol = *(u64*)input;
			set_code_len(FSST12_CODE_MASK, 8);
		}
	}
	explicit Symbol12(const char* begin, const char* end)
	    : Symbol12(begin, end - begin) {}
	explicit Symbol12(u8* begin, u8* end)
	    : Symbol12((const char*)begin, end - begin) {}
	void set_code_len(u32 code, u32 len) { gcl = (len << 28) | (code << 16) | ((8 - len) * 8); }

	u8  length() const { return gcl >> 28; }
	u16 code() const { return (gcl >> 16) & FSST12_CODE_MASK; }
	u8  garbageBits() const { return gcl; }

	u8  first() const { return 0xFF & *(u64*)symbol; }
	u16 first2() const {
		assert(length() > 1);
		return (0xFFFF & *(u64*)symbol);
	}

#define FSST12_HASH_LOG2SIZE 14
#define FSST12_HASH_SHIFT    15
#define FSST12_HASH_PRIME1   2971215073LL
#define FSST12_HASH(w)       (((w) * FSST12_HASH_PRIME1) ^ (((w) * FSST12_HASH_PRIME1) >> 13))
	ulong hash() const {
		uint32_t v0 = 0xFFFFFFFF & *(ulong*)symbol;
		return FSST12_HASH(v0);
	}

	bool operator==(const Symbol12& other) const {
		return *(u64*)symbol == *(u64*)other.symbol && length() == other.length();
	}
};

// during search for the best dictionary, we probe both (in this order, first wins):
// - Symbol12 hashtable[8192] (keyed by the next four bytes, for s.length>2 -- certain 4-byte sequences will map to the
// same 3-byte symbol),
// - u16 shortCodes[65536] array at the position of the next two-byte pattern (s.length==2) and
// this search will yield a u16 code, it points into Symbol12 symbols[4096].
// you always find a hit, because the lowest 256 codes are all single-byte symbols

// in the hash table, the gcl field contains (low-to-high) garbageBits:16,code:12,length:4
#define FSST12_GCL_FREE                                                                                                \
	((15 << 28) |                                                                                                      \
	 (((u32)FSST12_CODE_MASK) << 16)) // high bits of gcl (len=15,code=FSST12_CODE_MASK) indicates free bucket

// garbageBits is (8-length)*8, which is the amount of high bits to zero in the input word before comparing with the
// hashtable key
//             ..it could of course be computed from len during lookup, but storing it precomputed in some loose bits is
//             faster
//
// the gain field is only used in the symbol queue that sorts symbols on gain

struct Symbol12Map {
	static const u32 hashTabSize = 1 << FSST12_HASH_LOG2SIZE; // smallest size that incurs no precision loss

	// lookup table using the next two bytes (65536 codes), or just the next single byte
	u16 shortCodes[65536]; // shortCode[X] contains code for 2-byte symbol, contains 1-byte code X&255 if there is no
	                       // 2-byte symbol

	// 'symbols' is the current symbol  table symbol[code].symbol is the max 8-byte 'symbol' for single-byte 'code'
	Symbol12 symbols[4096];

	// replicate long symbols in hashTab (avoid indirection).
	Symbol12 hashTab[hashTabSize]; // used for all symbols of 3 and more bytes

	u32  symbolCount;    // amount of symbols in the map (max 4096)
	bool zeroTerminated; // whether we are expecting zero-terminated strings (we then also produce zero-terminated
	                     // compressed strings)
	u16 lenHisto[8];     // lenHisto[x] is the amount of symbols of byte-length (x+1) in this Symbol12Map

	Symbol12Map()
	    : symbolCount(256)
	    , zeroTerminated(false) {
		// stuff done once at startup
		Symbol12 unused = Symbol12(0, FSST12_CODE_MASK); // single-char symbol, exception code
		for (u32 i = 0; i < 256; i++) {
			symbols[i] = Symbol12((u8)i, i); // single-byte symbol
		}
		for (u32 i = 256; i < 4096; i++) {
			symbols[i] = unused; // all other symbols are unused.
		}
		// stuff done when re-using a symbolmap during the search for the best map
		clear(); // clears the arrays (hortCodes and hashTab) and histo
	}

	void clear() {
		Symbol12 s;
		s.gcl  = FSST12_GCL_FREE; // marks empty in hashtab
		s.gain = 0;
		for (u32 i = 0; i < hashTabSize; i++)
			hashTab[i] = s;
		for (u32 i = 0; i < 65536; i++)
			shortCodes[i] = 4096 | (i & 255);  // single-byte symbol
		memset(lenHisto, 0, sizeof(lenHisto)); // all unused
		lenHisto[0] = symbolCount = 256;       // no need to clean symbols[] as no symbols are used
	}

	u32 load() {
		u32 ret = 0;
		for (u32 i = 0; i < hashTabSize; i++)
			ret += (hashTab[i].gcl < FSST12_GCL_FREE);
		return ret;
	}

	bool hashInsert(Symbol12 s) {
		u32  idx   = s.hash() & (hashTabSize - 1);
		bool taken = (hashTab[idx].gcl < FSST12_GCL_FREE);
		if (taken) return false; // collision in hash table
		hashTab[idx].gcl           = s.gcl;
		hashTab[idx].gain          = 0;
		*(u64*)hashTab[idx].symbol = (*(u64*)s.symbol) & (0xFFFFFFFFFFFFFFFF >> (u8)s.gcl);
		return true;
	}
	bool add(Symbol12 s) {
		assert(symbolCount < 4096);
		u32 len = s.length();
		assert(len > 1);
		s.set_code_len(symbolCount, len);
		if (len == 2) {
			assert(shortCodes[s.first2()] == 4096 + s.first()); // cannot be in use
			shortCodes[s.first2()] = 8192 + symbolCount;        // 8192 = (len == 2) << 12
		} else if (!hashInsert(s)) {
			return false;
		}
		symbols[symbolCount++] = s;
		lenHisto[len - 1]++;
		return true;
	}
	/// Find symbol in hash table, return code
	u16 hashFind(Symbol12 s) const {
		ulong idx = s.hash() & (hashTabSize - 1);
		if (hashTab[idx].gcl <= s.gcl &&
		    *(u64*)hashTab[idx].symbol == (*(u64*)s.symbol & (0xFFFFFFFFFFFFFFFF >> ((u8)hashTab[idx].gcl))))
			return (hashTab[idx].gcl >> 16); // matched a long symbol
		return 0;
	}
	/// Find longest expansion, return code
	u16 findExpansion(Symbol12 s) const {
		if (s.length() == 1) { return 4096 + s.first(); }
		u16 ret = hashFind(s);
		return ret ? ret : shortCodes[s.first2()];
	}
};

#if 0 // def NONOPT_FSST12
struct Counters {
   u16 count1[FSST12_CODE_MAX];   // array to count frequency of symbols as they occur in the sample
   u16 count2[FSST12_CODE_MAX][FSST12_CODE_MAX]; // array to count subsequent combinations of two symbols in the sample

   void count1Set(u32 pos1, u16 val) {
      count1[pos1] = val;
   }
   void count1Inc(u32 pos1) {
      count1[pos1]++;
   }
   void count2Inc(u32 pos1, u32 pos2) {
      count2[pos1][pos2]++;
   }
   u32 count1GetNext(u32 &pos1) {
      return count1[pos1];
   }
   u32 count2GetNext(u32 pos1, u32 &pos2) {
      return count2[pos1][pos2];
   }
   void backup1(u8 *buf) {
      memcpy(buf, count1, FSST12_CODE_MAX*sizeof(u16));
   }
   void restore1(u8 *buf) {
      memcpy(count1, buf, FSST12_CODE_MAX*sizeof(u16));
   }
};
#else
// we keep two counters count1[pos] and count2[pos1][pos2] of resp 16 and 12-bits. Both are split into two columns for
// performance reasons first reason is to make the column we update the most during symbolTable construction (the low
// bits) thinner, thus reducing CPU cache pressure. second reason is that when scanning the array, after seeing a
// 64-bits 0 in the high bits column, we can quickly skip over many codes (15 or 7)
struct Counters12 {
	// high arrays come before low arrays, because our GetNext() methods may overrun their 64-bits reads a few bytes
	u8 count1High[FSST12_CODE_MAX]; // array to count frequency of symbols as they occur in the sample (16-bits)
	u8 count1Low[FSST12_CODE_MAX];  // it is split in a low and high byte: cnt = count1High*256 + count1Low
	u8 count2High[FSST12_CODE_MAX][FSST12_CODE_MAX / 2]; // array to count subsequent combinations of two symbols in the
	                                                     // sample (12-bits: 8-bits low, 4-bits high)
	u8 count2Low[FSST12_CODE_MAX][FSST12_CODE_MAX]; // its value is (count2High*256+count2Low) -- but high is 4-bits (we
	                                                // put two numbers in one, hence /2)
	// 385KB  -- but hot area likely just 10 + 30*4 = 130 cache lines (=8KB)

	void count1Set(u32 pos1, u16 val) {
		count1Low[pos1]  = val & 255;
		count1High[pos1] = val >> 8;
	}
	void count1Inc(u32 pos1) {
		if (!count1Low[pos1]++) // increment high early (when low==0, not when low==255). This means (high > 0) <=> (cnt
		                        // > 0)
			count1High[pos1]++; //(0,0)->(1,1)->..->(255,1)->(0,1)->(1,2)->(2,2)->(3,2)..(255,2)->(0,2)->(1,3)->(2,3)...
	}
	void count2Inc(u32 pos1, u32 pos2) {
		if (!count2Low[pos1][pos2]++) // increment high early (when low==0, not when low==255). This means (high > 0)
		                              // <=> (cnt > 0)
			// inc 4-bits high counter with 1<<0 (1) or 1<<4 (16) -- depending on whether pos2 is even or odd,
			// repectively
			count2High[pos1][(pos2) >> 1] +=
			    1 << (((pos2) & 1) << 2); // we take our chances with overflow.. (4K maxval, on a 8K sample)
	}
	u32 count1GetNext(u32& pos1) { // note: we will advance pos1 to the next nonzero counter in register range
		// read 16-bits single symbol counter, split into two 8-bits numbers (count1Low, count1High), while skipping
		// over zeros
		u64 high = *(u64*)&count1High[pos1]; // note: this reads 8 subsequent counters [pos1..pos1+7]

		u32 zero = high ? (__builtin_ctzl(high) >> 3) : 7; // number of zero bytes
		high     = (high >> (zero << 3)) & 255;            // advance to nonzero counter
		if (((pos1 += zero) >= FSST12_CODE_MAX) || !high)  // SKIP! advance pos2
			return 0;                                      // all zero

		u64 low = count1Low[pos1];
		if (low) high--; // high is incremented early and low late, so decrement high (unless low==0)
		return (high << 8) + low;
	}
	u32 count2GetNext(u32 pos1, u32& pos2) { // note: we will advance pos2 to the next nonzero counter in register range
		// read 12-bits pairwise symbol counter, split into low 8-bits and high 4-bits number while skipping over zeros
		u64 high = *(u64*)&count2High[pos1][pos2 >> 1]; // note: this reads 16 subsequent counters [pos2..pos2+15]
		high >>= (pos2 & 1) << 2;                       // odd pos2: ignore the lowest 4 bits & we see only 15 counters

		u32 zero = high ? (__builtin_ctzl(high) >> 2) : (15 - (pos2 & 1)); // number of zero 4-bits counters
		high     = (high >> (zero << 2)) & 15;                             // advance to nonzero counter
		if (((pos2 += zero) >= FSST12_CODE_MAX) || !high)                  // SKIP! advance pos2
			return 0;                                                      // all zero

		u64 low = count2Low[pos1][pos2];
		if (low) high--; // high is incremented early and low late, so decrement high (unless low==0)
		return (high << 8) + low;
	}
	void backup1(u8* buf) {
		memcpy(buf, count1High, FSST12_CODE_MAX);
		memcpy(buf + FSST12_CODE_MAX, count1Low, FSST12_CODE_MAX);
	}
	void restore1(u8* buf) {
		memcpy(count1High, buf, FSST12_CODE_MAX);
		memcpy(count1Low, buf + FSST12_CODE_MAX, FSST12_CODE_MAX);
	}
};
#endif

// an encoder is a symbolmap plus some bufferspace, needed during map construction as well as compression
struct Encoder12 {
	shared_ptr<Symbol12Map>
	    symbolMap; // symbols, plus metadata and data structures for quick compression (shortCode,hashTab, etc)
	union {
		Counters12 counters; // for counting symbol occurences during map construction
	};
};

// C++ fsst12-compress function with some more control of how the compression happens (algorithm flavor, simd unroll
// degree)
ulong compressImpl(Encoder12* encoder,
                   ulong      n,
                   ulong      lenIn[],
                   u8*        strIn[],
                   ulong      size,
                   u8*        output,
                   ulong*     lenOut,
                   u8*        strOut[],
                   bool       noSuffixOpt,
                   bool       avoidBranch,
                   int        simd);
ulong compressAuto(Encoder12* encoder,
                   ulong      n,
                   ulong      lenIn[],
                   u8*        strIn[],
                   ulong      size,
                   u8*        output,
                   ulong*     lenOut,
                   u8*        strOut[],
                   int        simd);

#endif

// NOLINTEND