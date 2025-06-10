#include "fls_tester.hpp"

namespace fastlanes {

// examples
TEST_F(FastLanesReaderTester, issue_000) {
	TestCorrectness(issues::ISSUE_000);
}
} // namespace fastlanes