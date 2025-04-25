#include "fls_tester.hpp"

namespace fastlanes {

TEST_F(FastLanesReaderTester, TEST_ALP_FLOAT) {
	TestCorrectness(GENERATED::EXP_ALP_FLT, {OperatorToken::EXP_ALP_FLT});
}

TEST_F(FastLanesReaderTester, TEST_ALP_DOUBLE) {
	TestCorrectness(GENERATED::EXP_ALP_DBL, {OperatorToken::EXP_ALP_DBL});
}

} // namespace fastlanes