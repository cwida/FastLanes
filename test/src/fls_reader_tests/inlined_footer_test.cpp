#include "fls_tester.hpp"

namespace fastlanes {

// Public BI
TEST_F(FastLanesReaderTester, Inlined_Footer_Arade) {
	TestCorrectness(public_bi::Arade, {}, 64, true);
}

TEST_F(FastLanesReaderTester, Inlined_Footer_Bimbo) {
	TestCorrectness(public_bi::Bimbo, {}, 32, true);
}

TEST_F(FastLanesReaderTester, Inlined_Footer_CMSprovider) {
	TestCorrectness(public_bi::CMSprovider, {}, 32, true);
}

} // namespace fastlanes
