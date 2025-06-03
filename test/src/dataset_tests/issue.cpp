#include "fls_tester.hpp"

namespace fastlanes {

// examples
TEST_F(FastLanesReaderTester, issue_000) {
	TestCorrectness(issue::ISSUE_000);
}
} // namespace fastlanes