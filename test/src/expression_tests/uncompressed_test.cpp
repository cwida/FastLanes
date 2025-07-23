// ────────────────────────────────────────────────────────
// |                      FastLanes                       |
// ────────────────────────────────────────────────────────
// test/src/expression_tests/uncompressed_test.cpp
// ────────────────────────────────────────────────────────
#include "fls_tester.hpp"

namespace fastlanes {

TEST_F(FastLanesReaderTester, UNCOMPRESSED_TEST_SINGLE_COL) {
	TestCorrectness(GENERATED::SINGLE_COLUMN_STRPT, {OperatorToken::EXP_UNCOMPRESSED_STR});
}

TEST_F(FastLanesReaderTester, UNCOMPRESSED_TEST_SINGLE_VEC) {
	TestCorrectness(GENERATED::ONE_VEC_STRPT, {OperatorToken::EXP_UNCOMPRESSED_STR});
}

} // namespace fastlanes
