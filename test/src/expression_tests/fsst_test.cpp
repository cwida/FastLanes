#include "fls_tester.hpp"

namespace fastlanes {

TEST_F(FastLanesReaderTester, TEST_FSST) {
	TestCorrectness(issues::ISSUE_002, {OperatorToken::EXP_FSST_DELTA});
}

} // namespace fastlanes