#include "fls_tester.hpp"

namespace fastlanes {

TEST_F(FastLanesReaderTester, TEST_CROSS_RLE_I16) {
	TestCorrectness(GENERATED::EXP_CROSS_RLE_i16, {OperatorToken::EXP_CROSS_RLE_I16});
}

TEST_F(FastLanesReaderTester, TEST_CROSS_RLE_STR) {
	TestCorrectness(GENERATED::EXP_CROSS_RLE_STR, {OperatorToken::EXP_CROSS_RLE_STR});
}

} // namespace fastlanes