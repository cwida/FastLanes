#include "fls/common/double.hpp"
#include "gtest/gtest.h"

using namespace fastlanes; // NOLINT

// Google Test Suite
class DoubleCastableTest : public ::testing::Test {};

// ✅ **Safe Cases**
TEST_F(DoubleCastableTest, SafeIntegers) {
	EXPECT_TRUE(Double::is_safely_castable_to_int64(0.0));
	EXPECT_TRUE(Double::is_safely_castable_to_int64(1000000.0));
	EXPECT_TRUE(Double::is_safely_castable_to_int64(9007199254740991.0));  // 2^53 - 1
	EXPECT_TRUE(Double::is_safely_castable_to_int64(-9007199254740991.0)); // -2^53 - 1
}

// ❌ **Unsafe Cases**
TEST_F(DoubleCastableTest, OutOfRangeValues) {
	EXPECT_FALSE(Double::is_safely_castable_to_int64(9007199254740993.0));     // 2^53 + 1 (not exactly representable)
	EXPECT_FALSE(Double::is_safely_castable_to_int64(-9007199254740993.0));    // -2^53 - 1
	EXPECT_FALSE(Double::is_safely_castable_to_int64(9223372036854775807.0));  // int64_t max (precision loss)
	EXPECT_FALSE(Double::is_safely_castable_to_int64(-9223372036854775808.0)); // int64_t min (precision loss)
}

// ❌ **Fractional Numbers**
TEST_F(DoubleCastableTest, FractionalValues) {
	EXPECT_FALSE(Double::is_safely_castable_to_int64(10.5));
	EXPECT_FALSE(Double::is_safely_castable_to_int64(-10.1));
	EXPECT_FALSE(Double::is_safely_castable_to_int64(9007199254740992.1));  // 2^53 + 0.1
	EXPECT_FALSE(Double::is_safely_castable_to_int64(-9007199254740992.9)); // -2^53 - 0.9
}

// ✅ **Edge Cases**
TEST_F(DoubleCastableTest, EdgeCases) {
	EXPECT_TRUE(Double::is_safely_castable_to_int64(1.0));  // Smallest valid integer
	EXPECT_TRUE(Double::is_safely_castable_to_int64(-1.0)); // Negative smallest valid integer
	EXPECT_TRUE(Double::is_safely_castable_to_int64(2.0));  // Another valid integer
}
