#include "fls_tester.hpp"

namespace fastlanes {

TEST_F(FastLanesReaderTester, TEST_FSST) {
	TestCorrectness(GENERATED::SINGLE_COLUMN_STRPT, {OperatorToken::EXP_FSST_DELTA});
}

} // namespace fastlanes
