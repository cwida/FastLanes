#include "fls_tester.hpp"

namespace fastlanes {

TEST_F(FastLanesReaderTester, TEST_FREQUENCY_DBL) {
	TestCorrectness(GENERATED::FREQUENCY_DBL_EXPR, {OperatorToken::EXP_FREQUENCY_DBL});
}

TEST_F(FastLanesReaderTester, TEST_FREQUENCY_STR) {
	TestCorrectness(GENERATED::FREQUENCY_STR_EXPR, {OperatorToken::EXP_FREQUENCY_STR});
}

} // namespace fastlanes