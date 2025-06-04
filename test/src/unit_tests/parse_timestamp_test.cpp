// timestamp_test.cpp

#include "fls/types/timestamp.hpp"
#include <gtest/gtest.h>
#include <limits>
#include <string>

namespace fastlanes {

// ──────────────────────────────────────────────────────────────
// parse_timestamp: Valid cases
// ──────────────────────────────────────────────────────────────
TEST(ParseTimestamp_Valid_NoFraction, Epoch) {
	// 1970-01-01T00:00:00 ⇒ 0 microseconds since epoch
	EXPECT_EQ(parse_timestamp("1970-01-01T00:00:00"), 0LL);
}

TEST(ParseTimestamp_Valid_NoFraction, OneSecondLater) {
	// 1970-01-01T00:00:01 ⇒ 1 second ⇒ 1,000,000 µs
	EXPECT_EQ(parse_timestamp("1970-01-01T00:00:01"), 1'000'000LL);
}

TEST(ParseTimestamp_Valid_WithFraction, MicrosecondPrecision) {
	// 1970-01-01T00:00:00.000001 ⇒ 1 µs
	EXPECT_EQ(parse_timestamp("1970-01-01T00:00:00.000001"), 1LL);
}

TEST(ParseTimestamp_Valid_WithFraction_Truncated, ThreeDigits) {
	// 1970-01-01T00:00:00.123 ⇒ 123,000 µs (right-padded to 6 digits)
	EXPECT_EQ(parse_timestamp("1970-01-01T00:00:00.123"), 123'000LL);
}

TEST(ParseTimestamp_Valid_Negative, BeforeEpoch) {
	// 1969-12-31T23:59:59 ⇒ –1 second ⇒ –1,000,000 µs
	EXPECT_EQ(parse_timestamp("1969-12-31T23:59:59"), -1'000'000LL);
}

TEST(ParseTimestamp_RoundTrip, FormatterInverse) {
	const std::string input     = "2025-06-04T13:45:30.123456";
	int64_t           micros    = parse_timestamp(input);
	std::string       formatted = timestamp_formatter(micros);
	EXPECT_EQ(formatted, input);
}

// ──────────────────────────────────────────────────────────────
// parse_timestamp: Invalid-format cases
// ──────────────────────────────────────────────────────────────
TEST(ParseTimestamp_InvalidFormat, TooShort) {
	EXPECT_THROW(parse_timestamp("2025-06-04T13:45"), std::invalid_argument);
}

TEST(ParseTimestamp_InvalidFormat, MissingT) {
	EXPECT_THROW(parse_timestamp("2025-06-04 13:45:30"), std::invalid_argument);
}

TEST(ParseTimestamp_InvalidFormat, BadSeparators) {
	EXPECT_THROW(parse_timestamp("2025/06/04T13:45:30"), std::invalid_argument);
	EXPECT_THROW(parse_timestamp("2025-06-04T13.45.30"), std::invalid_argument);
}

TEST(ParseTimestamp_InvalidFormat, NonDigitInDate) {
	EXPECT_THROW(parse_timestamp("202A-06-04T13:45:30"), std::invalid_argument);
	EXPECT_THROW(parse_timestamp("2025-06-0XT13:45:30"), std::invalid_argument);
}

TEST(ParseTimestamp_InvalidFormat, FractionalTooLong) {
	EXPECT_THROW(parse_timestamp("2025-06-04T13:45:30.1234567"), std::invalid_argument);
}

// ──────────────────────────────────────────────────────────────
// parse_timestamp: Out-of-range cases
// ──────────────────────────────────────────────────────────────
TEST(ParseTimestamp_OutOfRange, YearTooLarge) {
	// A year far beyond int64_t range when converted to microseconds
	EXPECT_THROW(parse_timestamp("300000-01-01T00:00:00"), std::out_of_range);
}

TEST(ParseTimestamp_OutOfRange, YearTooNegative) {
	// A year far before epoch leading to underflow
	EXPECT_THROW(parse_timestamp(" -300000-01-01T00:00:00"), std::invalid_argument);
}

// ──────────────────────────────────────────────────────────────
// timestamp_formatter: Valid cases
// ──────────────────────────────────────────────────────────────
TEST(TimestampFormatter_Valid_NoFraction, Epoch) {
	// 0 ⇒ "1970-01-01T00:00:00"
	EXPECT_EQ(timestamp_formatter(0LL), "1970-01-01T00:00:00");
}

TEST(TimestampFormatter_Valid_WithFraction, MicrosecondPrecision) {
	// 1 ⇒ "1970-01-01T00:00:00.000001"
	EXPECT_EQ(timestamp_formatter(1LL), "1970-01-01T00:00:00.000001");
}

TEST(TimestampFormatter_RoundTrip, ParserInverse) {
	// Convert a known microsecond count, then parse back
	const int64_t micros = 1'678'034'730'123'456LL; // roughly 2023-04-01T12:34:90.123456
	std::string   str    = timestamp_formatter(micros);
	int64_t       parsed = parse_timestamp(str);
	EXPECT_EQ(parsed, micros);
}

} // namespace fastlanes
