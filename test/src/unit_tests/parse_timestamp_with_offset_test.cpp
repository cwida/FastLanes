// ────────────────────────────────────────────────────────
// |                      FastLanes                       |
// ────────────────────────────────────────────────────────
// test/src/unit_tests/parse_timestamp_with_offset_test.cpp
// ────────────────────────────────────────────────────────
// test/src/unit_tests/parse_timestamp_with_offset_test.cpp

#include "fls/types/timestamp.hpp"
#include <gtest/gtest.h>
#include <limits>
#include <string>

namespace fastlanes {

// ──────────────────────────────────────────────────────────────
// parse_timestamp: Valid ISO-8601 with timezone offset
// ──────────────────────────────────────────────────────────────
TEST(ParseTimestamp_ISO8601_WithOffset, PositiveOffset) {
	// "2019-09-08T23:00:00+02:00" ⇒ UTC 2019-09-08T21:00:00 ⇒ 1567976400000000 µs
	EXPECT_EQ(parse_timestamp("2019-09-08T23:00:00+02:00"), 1567976400'000000LL);
}

TEST(ParseTimestamp_ISO8601_WithOffset, NegativeOffset) {
	// "2020-01-01T00:00:00-05:00" ⇒ UTC 2020-01-01T05:00:00 ⇒ 1577854800000000 µs
	EXPECT_EQ(parse_timestamp("2020-01-01T00:00:00-05:00"), 1577854800'000000LL);
}

TEST(ParseTimestamp_ISO8601_WithOffset_Fraction, NonZeroFraction) {
	// "2021-03-15T12:30:45.123456-04:30"
	//   local  = 2021-03-15T12:30:45.123456
	//   offset = -04:30 ⇒ UTC = local + 4h30m = 2021-03-15T17:00:45.123456
	//   timestamp for 2021-03-15T17:00:45.123456 UTC = 1615827645123456 µs
	EXPECT_EQ(parse_timestamp("2021-03-15T12:30:45.123456-04:30"), 1615827645'123456LL);
}

TEST(ParseTimestamp_ISO8601_WithOffset_ZeroOffsetFraction, ZeroFraction) {
	// "2021-03-15T12:30:45.000000+00:00" ⇒ same as UTC 2021-03-15T12:30:45.000000
	// timestamp for 2021-03-15T12:30:45 UTC = 1615811445000000 µs
	EXPECT_EQ(parse_timestamp("2021-03-15T12:30:45.000000+00:00"), 1615811445'000000LL);
}

// ──────────────────────────────────────────────────────────────
// parse_timestamp: Invalid-offset formats
// ──────────────────────────────────────────────────────────────
TEST(ParseTimestamp_InvalidOffsetFormat, MissingColonInOffset) {
	EXPECT_THROW(parse_timestamp("2021-01-01T00:00:00+0500"), std::invalid_argument);
}

TEST(ParseTimestamp_InvalidOffsetFormat, MissingDigitsInOffset) {
	EXPECT_THROW(parse_timestamp("2021-01-01T00:00:00+5:00"), std::invalid_argument);
}

TEST(ParseTimestamp_InvalidOffsetFormat, HourOutOfRange) {
	EXPECT_THROW(parse_timestamp("2021-01-01T00:00:00+24:00"), std::invalid_argument);
}

TEST(ParseTimestamp_InvalidOffsetFormat, MinuteOutOfRange) {
	EXPECT_THROW(parse_timestamp("2021-01-01T00:00:00-02:60"), std::invalid_argument);
}

// ──────────────────────────────────────────────────────────────
// parse_timestamp: Combined ISO / non-ISO cases remain unchanged
// ──────────────────────────────────────────────────────────────
TEST(ParseTimestamp_NoOffset, ISO8601_NoFraction) {
	EXPECT_EQ(parse_timestamp("2022-12-31T23:59:59"), 1672531199'000000LL);
}

TEST(ParseTimestamp_NoOffset, ISO8601_WithFraction) {
	EXPECT_EQ(parse_timestamp("2022-12-31T23:59:59.000123"), 1672531199'000123LL);
}

} // namespace fastlanes
