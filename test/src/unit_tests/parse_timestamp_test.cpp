// ────────────────────────────────────────────────────────
// |                      FastLanes                       |
// ────────────────────────────────────────────────────────
// test/src/unit_tests/parse_timestamp_test.cpp
// ────────────────────────────────────────────────────────
// test/src/unit_tests/timestamp_test.cpp

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
// parse_timestamp: Valid cases with space delimiter
// ──────────────────────────────────────────────────────────────
TEST(ParseTimestamp_Valid_SpaceDelimiter, NoFraction) {
	// "2013-09-01 19:10:00" should parse and format back with 'T'
	const std::string input     = "2013-09-01 19:10:00";
	int64_t           micros    = parse_timestamp(input);
	std::string       formatted = timestamp_formatter(micros);
	EXPECT_EQ(formatted, "2013-09-01T19:10:00");
}

TEST(ParseTimestamp_Valid_SpaceDelimiter, WithFraction) {
	// "2013-09-01 19:10:00.000000" should parse and format back with 'T'
	const std::string input     = "2013-09-01 19:10:00.000000";
	int64_t           micros    = parse_timestamp(input);
	std::string       formatted = timestamp_formatter(micros);
	EXPECT_EQ(formatted, "2013-09-01T19:10:00");
}

TEST(ParseTimestamp_Valid_SpaceDelimiter_TruncatedFraction, OneDigit) {
	// "2020-01-01 00:00:00.1" ⇒ 1577836800 * 1_000_000 + 100_000 = 1577836800_100000
	EXPECT_EQ(parse_timestamp("2020-01-01 00:00:00.1"), 1'577'836'800'100'000LL);
}

TEST(ParseTimestamp_Space_vs_T, RoundTripConsistency) {
	// If two inputs differ only by ' ' vs. 'T', they should yield the same µs
	const std::string t_form   = "2022-12-31T23:59:59";
	const std::string s_form   = "2022-12-31 23:59:59";
	int64_t           t_micros = parse_timestamp(t_form);
	int64_t           s_micros = parse_timestamp(s_form);
	EXPECT_EQ(t_micros, s_micros);
}

// ──────────────────────────────────────────────────────────────
// parse_timestamp: Invalid-format cases
// ──────────────────────────────────────────────────────────────
TEST(ParseTimestamp_InvalidFormat, TooShort) {
	EXPECT_THROW(parse_timestamp("2025-06-04T13:45"), std::invalid_argument);
}

TEST(ParseTimestamp_InvalidFormat, MissingTandSpace) {
	EXPECT_THROW(parse_timestamp("2025-06-04X13:45:30"), std::invalid_argument);
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
	// Leading space causes invalid_argument
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
	const int64_t micros = 1'678'034'730'123'456LL; // arbitrary timestamp
	std::string   str    = timestamp_formatter(micros);
	int64_t       parsed = parse_timestamp(str);
	EXPECT_EQ(parsed, micros);
}

// ──────────────────────────────────────────────────────────────
// timestamp_formatter: Valid formatting for space‐parsed inputs
// ──────────────────────────────────────────────────────────────
TEST(TimestampFormatter_FromSpaceParsed, NoFraction) {
	// If parse_timestamp accepts a space delimiter, formatter always uses 'T'
	int64_t micros = parse_timestamp("2015-07-20 12:34:56");
	EXPECT_EQ(timestamp_formatter(micros), "2015-07-20T12:34:56");
}

} // namespace fastlanes
