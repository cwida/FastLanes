// ────────────────────────────────────────────────────────
// |                      FastLanes                       |
// ────────────────────────────────────────────────────────
// test/src/primitive_tests/fsst_test.cpp
// ────────────────────────────────────────────────────────
// tests/fsst_tail_guard_24_vs_32.cpp

#include "fls/cor/prm/fsst/fsst.h"
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <gtest/gtest.h>
#include <vector>

static fsst_decoder_t make_decoder() {
	fsst_decoder_t d {};
	const char*    sym[] = {"AAAAAAAA", "BBBBBBBB", "CCCCCCCC"};
	for (uint8_t c = 1; c <= 3; ++c) {
		d.len[c] = 8;
		std::memcpy(&d.symbol[c], sym[c - 1], 8);
	}
	return d;
}

/*  Compressed input:
      1, 2, 255, 'x', 3
      = code1, code2, ESC,literal, code3
      Fast tail-path worst-case write:
        raw 'x'      1
        sym[1]       8
        sym[2]       8
        sym[3]       8   → total 25 bytes
*/
TEST(FSSTTailGuard, Old24OverflowsBut32IsSafe) {
	auto          dec           = make_decoder();
	unsigned char compressed[5] = {1, 2, FSST_ESC, 0x78 /*'x'*/, 3};

	std::vector<unsigned char> buf(24);

	/* Old guard (+24)  → 0+24 ≤ 24, fast path writes 25 bytes → ASan aborts
	   New guard (+32)  → 0+32 > 24, fast path skipped, slow loop writes ≤24 → clean exit */
	fsst_decompress(&dec, 5, compressed, buf.size(), buf.data());
}
