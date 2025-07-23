// ────────────────────────────────────────────────────────
// |                      FastLanes                       |
// ────────────────────────────────────────────────────────
// test/src/dataset_tests/issues.cpp
// ────────────────────────────────────────────────────────
#include "fls_tester.hpp"

namespace fastlanes {

// examples
TEST_F(FastLanesReaderTester, issues_cwida_alp_37_diff_data) {
	TestCorrectness(issues::issues_cwida_alp_37_diff_data);
}

TEST_F(FastLanesReaderTester, issues_cwida_alp_37_kv_cache_original) {
	TestCorrectness(issues::issues_cwida_alp_37_kv_cache_original);
}

TEST_F(FastLanesReaderTester, issue_000) {
	TestCorrectness(issues::ISSUE_000);
}

} // namespace fastlanes