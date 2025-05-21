#include "fls/common/decimal.hpp"
#include "gtest/gtest.h"

using namespace fastlanes; // NOLINT

// 🚀 Test suite for make_decimal function
class MakeDecimalTest : public ::testing::Test {};

// ✅ Test basic scaling behavior
TEST_F(MakeDecimalTest, BasicScaling) {
	EXPECT_EQ(make_decimal("123.456", 6), 123456000);
	EXPECT_EQ(make_decimal("99.99", 2), 9999);
	EXPECT_EQ(make_decimal("5.1", 5), 510000);
	EXPECT_EQ(make_decimal("0.0001", 6), 100);
}

// ✅ Test negative numbers
TEST_F(MakeDecimalTest, NegativeNumbers) {
	EXPECT_EQ(make_decimal("-123.456", 6), -123456000);
	EXPECT_EQ(make_decimal("-0.987", 4), -9870);
	EXPECT_EQ(make_decimal("-99.99", 2), -9999);
	EXPECT_EQ(make_decimal("-5.1", 5), -510000);
}

// ✅ Test zero handling
TEST_F(MakeDecimalTest, ZeroCases) {
	EXPECT_EQ(make_decimal("0", 6), 0);
	EXPECT_EQ(make_decimal("0.0", 6), 0);
	EXPECT_EQ(make_decimal("-0.0", 6), 0);
}

// ✅ Test cases where input has fewer decimals than the given scale
TEST_F(MakeDecimalTest, FewerDecimalsThanScale) {
	EXPECT_EQ(make_decimal("123.4", 6), 123400000); // "123.4" → 123400000 (6 decimal places)
	EXPECT_EQ(make_decimal("0.01", 5), 1000);       // "0.01" → 1000 (5 decimal places)
	EXPECT_EQ(make_decimal("-99.9", 4), -999000);   // "-99.9" → -999000 (4 decimal places)
}

// ✅ Test edge cases with very large numbers
TEST_F(MakeDecimalTest, LargeNumbers) {
	EXPECT_EQ(make_decimal("999999999999.999", 3), 999999999999999); // Large number scaling
	EXPECT_EQ(make_decimal("-999999999999.99", 2), -99999999999999); // Large negative number
}

// ✅ Test cases with integers (should behave as expected)
TEST_F(MakeDecimalTest, Integers) {
	EXPECT_EQ(make_decimal("42", 6), 42000000);
	EXPECT_EQ(make_decimal("1000000", 2), 100000000);
	EXPECT_EQ(make_decimal("-5000", 5), -500000000);
}

TEST_F(MakeDecimalTest, MoreDecimalsThanScale) {
	EXPECT_THROW(make_decimal("1.1234567", 6), std::invalid_argument);
	EXPECT_THROW(make_decimal("0.9876543", 4), std::invalid_argument);
	EXPECT_THROW(make_decimal("-5.555555", 5), std::invalid_argument);
}

// 🚀 Test fixture for make_decimal_t function
class MakeDecimalTTest : public ::testing::Test {};

// ✅ Test valid "decimal(p, s)" parsing cases
TEST_F(MakeDecimalTTest, ValidDecimalFormatParsing) {
	auto d1 = make_decimal_t("decimal(11, 6)");
	EXPECT_EQ(d1->precision, 11);
	EXPECT_EQ(d1->scale, 6);

	auto d2 = make_decimal_t("decimal(20,10)");
	EXPECT_EQ(d2->precision, 20);
	EXPECT_EQ(d2->scale, 10);

	auto d3 = make_decimal_t("decimal(5,2)");
	EXPECT_EQ(d3->precision, 5);
	EXPECT_EQ(d3->scale, 2);
}

// ❌ Test invalid formats (should throw exceptions)
TEST_F(MakeDecimalTTest, InvalidDecimalFormatParsing) {
	EXPECT_THROW(make_decimal_t("decimal(5)"), std::invalid_argument);      // Missing scale
	EXPECT_THROW(make_decimal_t("decimal(abc, 6)"), std::invalid_argument); // Non-numeric precision
	EXPECT_THROW(make_decimal_t("decimal(5, xyz)"), std::invalid_argument); // Non-numeric scale
	EXPECT_THROW(make_decimal_t("decimal5,6)"), std::invalid_argument);     // Missing parentheses
	EXPECT_THROW(make_decimal_t("dec(11,6)"), std::invalid_argument);       // Incorrect keyword
}
