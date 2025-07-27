// ────────────────────────────────────────────────────────
// |                      FastLanes                       |
// ────────────────────────────────────────────────────────
// test/src/expression_tests/rle_test.cpp
// ────────────────────────────────────────────────────────
#include "fls_tester.hpp"

namespace fastlanes {

TEST_F(FastLanesReaderTester, TEST_RLE) {
	TestCorrectness(GENERATED::ONE_VEC_DBLPT, {OperatorToken::EXP_RLE_DBL_U16});
}

} // namespace fastlanes
