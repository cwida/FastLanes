// ────────────────────────────────────────────────────────
// |                      FastLanes                       |
// ────────────────────────────────────────────────────────
// test/src/unit_tests/parse_integer_test.cpp
// ────────────────────────────────────────────────────────
#include "fls/types/integer.hpp" // fastlanes::parse_integer<PT>
#include <gtest/gtest.h>
#include <limits>
#include <string>

namespace fastlanes {

// ──────────────────────────────────────────────────────────────
// uint8_t
// ──────────────────────────────────────────────────────────────
TEST(ParseInteger_Uint8, Valid) {
	EXPECT_EQ(parse_integer<uint8_t>("0"), static_cast<uint8_t>(0));
	EXPECT_EQ(parse_integer<uint8_t>("255"), static_cast<uint8_t>(255));
}
TEST(ParseInteger_Uint8, OutOfRange) {
	EXPECT_THROW(parse_integer<uint8_t>("256"), std::out_of_range);
}
TEST(ParseInteger_Uint8, Invalid) {
	EXPECT_THROW(parse_integer<uint8_t>("12a"), std::invalid_argument);
	EXPECT_THROW(parse_integer<uint8_t>(""), std::invalid_argument);
	EXPECT_THROW(parse_integer<uint8_t>(" 42"), std::invalid_argument);
	EXPECT_THROW(parse_integer<uint8_t>("42 "), std::invalid_argument);
	EXPECT_THROW(parse_integer<uint8_t>("-1"), std::invalid_argument);
}

// ──────────────────────────────────────────────────────────────
// uint16_t
// ──────────────────────────────────────────────────────────────
TEST(ParseInteger_Uint16, Valid) {
	EXPECT_EQ(parse_integer<uint16_t>("0"), static_cast<uint16_t>(0));
	EXPECT_EQ(parse_integer<uint16_t>("65535"), static_cast<uint16_t>(65535));
}
TEST(ParseInteger_Uint16, OutOfRange) {
	EXPECT_THROW(parse_integer<uint16_t>("65536"), std::out_of_range);
}
TEST(ParseInteger_Uint16, Invalid) {
	EXPECT_THROW(parse_integer<uint16_t>("1234abc"), std::invalid_argument);
	EXPECT_THROW(parse_integer<uint16_t>("+"), std::invalid_argument);
	EXPECT_THROW(parse_integer<uint16_t>("-42"), std::invalid_argument);
}

// ──────────────────────────────────────────────────────────────
// uint32_t
// ──────────────────────────────────────────────────────────────
TEST(ParseInteger_Uint32, Valid) {
	EXPECT_EQ(parse_integer<uint32_t>("0"), static_cast<uint32_t>(0));
	EXPECT_EQ(parse_integer<uint32_t>("4294967295"), static_cast<uint32_t>(4294967295u));
}
TEST(ParseInteger_Uint32, OutOfRange) {
	EXPECT_THROW(parse_integer<uint32_t>("4294967296"), std::out_of_range);
}
TEST(ParseInteger_Uint32, Invalid) {
	EXPECT_THROW(parse_integer<uint32_t>("3.14"), std::invalid_argument);
	EXPECT_THROW(parse_integer<uint32_t>("abc"), std::invalid_argument);
}

// ──────────────────────────────────────────────────────────────
// uint64_t
// ──────────────────────────────────────────────────────────────
TEST(ParseInteger_Uint64, Valid) {
	EXPECT_EQ(parse_integer<uint64_t>("0"), static_cast<uint64_t>(0));
	EXPECT_EQ(parse_integer<uint64_t>("18446744073709551615"), static_cast<uint64_t>(18446744073709551615ull));
}
TEST(ParseInteger_Uint64, OutOfRange) {
	EXPECT_THROW(parse_integer<uint64_t>("18446744073709551616"), std::out_of_range);
}
TEST(ParseInteger_Uint64, Invalid) {
	EXPECT_THROW(parse_integer<uint64_t>("12.34e1"), std::invalid_argument);
	EXPECT_THROW(parse_integer<uint64_t>(" 100"), std::invalid_argument);
}

// ──────────────────────────────────────────────────────────────
// int8_t
// ──────────────────────────────────────────────────────────────
TEST(ParseInteger_Int8, Valid) {
	EXPECT_EQ(parse_integer<int8_t>("0"), static_cast<int8_t>(0));
	EXPECT_EQ(parse_integer<int8_t>("127"), static_cast<int8_t>(127));
	EXPECT_EQ(parse_integer<int8_t>("-128"), static_cast<int8_t>(-128));
}
TEST(ParseInteger_Int8, OutOfRange) {
	EXPECT_THROW(parse_integer<int8_t>("128"), std::out_of_range);
	EXPECT_THROW(parse_integer<int8_t>("-129"), std::out_of_range);
}
TEST(ParseInteger_Int8, Invalid) {
	EXPECT_THROW(parse_integer<int8_t>("12a"), std::invalid_argument);
	EXPECT_THROW(parse_integer<int8_t>("+"), std::invalid_argument);
}

// ──────────────────────────────────────────────────────────────
// int16_t
// ──────────────────────────────────────────────────────────────
TEST(ParseInteger_Int16, Valid) {
	EXPECT_EQ(parse_integer<int16_t>("0"), static_cast<int16_t>(0));
	EXPECT_EQ(parse_integer<int16_t>("32767"), static_cast<int16_t>(32767));
	EXPECT_EQ(parse_integer<int16_t>("-32768"), static_cast<int16_t>(-32768));
}
TEST(ParseInteger_Int16, OutOfRange) {
	EXPECT_THROW(parse_integer<int16_t>("32768"), std::out_of_range);
	EXPECT_THROW(parse_integer<int16_t>("-32769"), std::out_of_range);
}
TEST(ParseInteger_Int16, Invalid) {
	EXPECT_THROW(parse_integer<int16_t>("123.0"), std::invalid_argument);
	EXPECT_THROW(parse_integer<int16_t>("abc"), std::invalid_argument);
}

// ──────────────────────────────────────────────────────────────
// int32_t
// ──────────────────────────────────────────────────────────────
TEST(ParseInteger_Int32, Valid) {
	EXPECT_EQ(parse_integer<int32_t>("0"), static_cast<int32_t>(0));
	EXPECT_EQ(parse_integer<int32_t>("2147483647"), std::numeric_limits<int32_t>::max());
	EXPECT_EQ(parse_integer<int32_t>("-2147483648"), std::numeric_limits<int32_t>::min());
}
TEST(ParseInteger_Int32, OutOfRange) {
	EXPECT_THROW(parse_integer<int32_t>("2147483648"), std::out_of_range);
	EXPECT_THROW(parse_integer<int32_t>("-2147483649"), std::out_of_range);
}
TEST(ParseInteger_Int32, Invalid) {
	EXPECT_THROW(parse_integer<int32_t>("42abc"), std::invalid_argument);
	EXPECT_THROW(parse_integer<int32_t>(" 42"), std::invalid_argument);
	EXPECT_THROW(parse_integer<int32_t>("42 "), std::invalid_argument);
}

// ──────────────────────────────────────────────────────────────
// int64_t
// ──────────────────────────────────────────────────────────────
TEST(ParseInteger_Int64, Valid) {
	EXPECT_EQ(parse_integer<int64_t>("0"), static_cast<int64_t>(0));
	EXPECT_EQ(parse_integer<int64_t>("9223372036854775807"), std::numeric_limits<int64_t>::max());
	EXPECT_EQ(parse_integer<int64_t>("-9223372036854775808"), std::numeric_limits<int64_t>::min());
}
TEST(ParseInteger_Int64, OutOfRange) {
	EXPECT_THROW(parse_integer<int64_t>("9223372036854775808"), std::out_of_range);
	EXPECT_THROW(parse_integer<int64_t>("-9223372036854775809"), std::out_of_range);
}
TEST(ParseInteger_Int64, Invalid) {
	EXPECT_THROW(parse_integer<int64_t>("3.1415"), std::invalid_argument);
	EXPECT_THROW(parse_integer<int64_t>("foo"), std::invalid_argument);
}

} // namespace fastlanes
