#include "fls_tester.hpp"

namespace fastlanes {

// Equalities
TEST_F(FastLanesReaderTester, ALL_TYPES_1) {
	TestCorrectness<JSON>(GENERATED::ALL_TYPES, //
	                      {},                   //
	                      1);
}

TEST_F(FastLanesReaderTester, ALL_TYPES_64) {
	TestCorrectness<JSON>(GENERATED::ALL_TYPES, //
	                      {},                   //
	                      64);
}

TEST_F(FastLanesReaderTester, ALL_TYPES_32) {
	TestCorrectness<JSON>(GENERATED::ALL_TYPES, //
	                      {},                   //
	                      32);
}

} // namespace fastlanes