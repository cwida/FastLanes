// test/src/primitive_tests/fsst_test.cpp

#include "fls/cor/prm/fsst/fsst.h"
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <gtest/gtest.h>

// Build a decoder where codes 1–4 each expand to 8 bytes
static fsst_decoder_t make_decoder() {
	fsst_decoder_t d {};
	for (uint8_t c = 1; c <= 4; ++c) {
		d.len[c]    = 8;
		d.symbol[c] = 0x4242424242424242ULL + c; // distinct 8-byte patterns
	}
	return d;
}

// This test will FAIL (ASan abort) if fsst.h still has “+24”
// and PASS if it has been changed to “+32”.
TEST(FSSTTailGuard, NoOverflowWithFixedGuard) {
	auto          dec   = make_decoder();
	unsigned char in[4] = {1, 2, 3, 4}; // these four codes expand to 32 bytes total

	// Allocate exactly 25 bytes on the heap. ASan places red-zones immediately after.
	auto buf = reinterpret_cast<unsigned char*>(std::malloc(25));
	ASSERT_NE(buf, nullptr);

	// If the tail-handler guard in fsst.h is still “pos_out + 24 <= size”,
	// fsst_decompress(...) will overflow by 7 bytes under ASan → abort → exit-code ≠ 0 → EXPECT_EXIT fails.
	//
	// If the guard has been patched to “pos_out + 32 <= size”,
	// it skips the fast path and writes only 25 in-range bytes → exits normally → EXPECT_EXIT sees code 0 → pass.
	EXPECT_EXIT(
	    {
		    fsst_decompress(&dec, /*len_in=*/4, /*str_in=*/in, /*size=*/25, /*output=*/buf);
		    _exit(0);
	    },
	    ::testing::ExitedWithCode(0),
	    "");

	std::free(buf);
}
