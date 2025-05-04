#include "fls_tester.hpp"

namespace fastlanes {

// Public BI
TEST_F(FastLanesReaderTester, ANY_VALUE_COUNT_I64_1) {
	TestCorrectness(GENERATED::ANY_VALUE_COUNT_I64_1);
}

TEST_F(FastLanesReaderTester, ANY_VALUE_COUNT_I64_666) {
	TestCorrectness(GENERATED::ANY_VALUE_COUNT_I64_666);
}

TEST_F(FastLanesReaderTester, ANY_VALUE_COUNT_I64_52422) {
	TestCorrectness(GENERATED::ANY_VALUE_COUNT_I64_52422);
}

} // namespace fastlanes
