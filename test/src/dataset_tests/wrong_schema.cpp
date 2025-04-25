#include "fls_tester.hpp"

namespace fastlanes {

// examples
TEST_F(FastLanesReaderTester, WRONG_SCHEMA) {
	ASSERT_THROW(TestCorrectness(WRONG_SCHEMA::FLOAT), std::runtime_error);
}
} // namespace fastlanes