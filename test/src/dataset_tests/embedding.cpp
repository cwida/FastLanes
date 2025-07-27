// ────────────────────────────────────────────────────────
// |                      FastLanes                       |
// ────────────────────────────────────────────────────────
// test/src/dataset_tests/embedding.cpp
// ────────────────────────────────────────────────────────
#include "fls_tester.hpp"

namespace fastlanes {

// examples
TEST_F(FastLanesReaderTester, EMBEDDING) {
	TestCorrectness(EMBEDDING::N1);
}

} // namespace fastlanes
