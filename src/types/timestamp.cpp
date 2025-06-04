// src/types/timestamp.cpp
#include "fls/types/timestamp.hpp"
#include <charconv>
#include <chrono>
#include <cmath> // std::llabs
#include <cstdint>
#include <format>
#include <limits>
#include <stdexcept>
#include <string_view>

namespace fastlanes {

// ───────────────────────── constants ──────────────────────────
constexpr int64_t kMicrosPerSecond = 1'000'000;
constexpr int64_t kMicrosPerMinute = 60LL * kMicrosPerSecond;
constexpr int64_t kMicrosPerHour   = 60LL * kMicrosPerMinute;
constexpr int64_t kMicrosPerDay    = 24LL * kMicrosPerHour;

// ⌊INT64_MAX / 86 400 000 000⌋  ≈ 106 751 991
constexpr int64_t kMaxAbsDays = std::numeric_limits<int64_t>::max() / kMicrosPerDay;

constexpr int      kEpochYear  = 1970;
constexpr unsigned kEpochMonth = 1;
constexpr unsigned kEpochDay   = 1;

// ───────────────────────── helpers ────────────────────────────
template <typename INT>
[[nodiscard]] static INT to_int(std::string_view s, const char* field) {
	INT v {};
	auto [ptr, ec] = std::from_chars(s.data(), s.data() + s.size(), v);
	if (ec != std::errc {} || ptr != s.data() + s.size())
		throw std::invalid_argument(std::string("Invalid ") + field);
	return v;
}

// Days from 1970-01-01 using Howard Hinnant algorithm
static int64_t civil_to_days(int y, unsigned m, unsigned d) {
	if (m <= 2) {
		--y;
		m += 12;
	}
	const int64_t     era               = y / 400;
	const int64_t     yoe               = static_cast<int64_t>(y) - era * 400;   // [0,399]
	const int64_t     doy               = (153 * (m - 3) + 2) / 5 + d - 1;       // [0,365]
	const int64_t     doe               = yoe * 365 + yoe / 4 - yoe / 100 + doy; // [0,146096]
	constexpr int64_t days_0000_to_1970 = 719468;                                // 0000-03-01 → 1970-01-01
	return era * 146097 + doe - days_0000_to_1970;
}

// ─────────────────────── parse_timestamp ──────────────────────
int64_t parse_timestamp(std::string_view ts) {
	// split YYYY-MM-DD
	const std::size_t p1 = ts.find('-');
	const std::size_t p2 = (p1 == std::string_view::npos) ? std::string_view::npos : ts.find('-', p1 + 1);
	if (p1 == std::string_view::npos || p2 == std::string_view::npos)
		throw std::invalid_argument("Expected YYYY-MM-DDThh:mm:ss");

	const auto year_str  = ts.substr(0, p1);
	const auto month_str = ts.substr(p1 + 1, 2);
	const auto day_str   = ts.substr(p2 + 1, 2);

	const std::size_t posT = p2 + 3; // after DD
	if (posT >= ts.size() || ts[posT] != 'T')
		throw std::invalid_argument("Expected 'T' after date");

	// ensure hh:mm:ss present
	if (ts.size() < posT + 9 || ts[posT + 3] != ':' || ts[posT + 6] != ':')
		throw std::invalid_argument("Expected hh:mm:ss");

	const auto hour_str   = ts.substr(posT + 1, 2);
	const auto minute_str = ts.substr(posT + 4, 2);
	const auto second_str = ts.substr(posT + 7, 2);

	// numeric conversion
	const int      year   = to_int<int>(year_str, "year");
	const unsigned month  = to_int<unsigned>(month_str, "month");
	const unsigned day    = to_int<unsigned>(day_str, "day");
	const int      hour   = to_int<int>(hour_str, "hour");
	const int      minute = to_int<int>(minute_str, "minute");
	const int      second = to_int<int>(second_str, "second");

	if (!(1 <= month && month <= 12))
		throw std::invalid_argument("Month out of range");
	if (!(1 <= day && day <= 31))
		throw std::invalid_argument("Day out of range");
	if (!(0 <= hour && hour <= 23))
		throw std::invalid_argument("Hour out of range");
	if (!(0 <= minute && minute <= 59))
		throw std::invalid_argument("Minute out of range");
	if (!(0 <= second && second <= 59))
		throw std::invalid_argument("Second out of range");

	// fractional microseconds
	std::chrono::microseconds frac_us {0};
	const std::size_t         posFrac = posT + 9; // after hh:mm:ss
	if (posFrac < ts.size()) {
		if (ts[posFrac] != '.')
			throw std::invalid_argument("Expected '.' before fraction");
		const auto frac = ts.substr(posFrac + 1);
		if (frac.empty() || frac.size() > 6)
			throw std::invalid_argument("Fraction must have 1-6 digits");
		int64_t val = to_int<int64_t>(frac, "fractional seconds");
		for (std::size_t pad = 6 - frac.size(); pad; --pad)
			val *= 10; // right-pad
		frac_us = std::chrono::microseconds {val};
	}

	// days from epoch
	const int64_t days_from_epoch = civil_to_days(year, month, day) - civil_to_days(kEpochYear, kEpochMonth, kEpochDay);

	if (std::llabs(days_from_epoch) > kMaxAbsDays)
		throw std::out_of_range("Timestamp out of int64 range");

	// accumulate in 128-bit, clamp to 64
	__int128 total_us = static_cast<__int128>(days_from_epoch) * kMicrosPerDay +
	                    static_cast<__int128>(hour) * kMicrosPerHour +
	                    static_cast<__int128>(minute) * kMicrosPerMinute +
	                    static_cast<__int128>(second) * kMicrosPerSecond + static_cast<__int128>(frac_us.count());

	if (total_us > std::numeric_limits<int64_t>::max() || total_us < std::numeric_limits<int64_t>::min())
		throw std::out_of_range("Timestamp out of int64 range");

	return static_cast<int64_t>(total_us);
}

// ───────────────────── timestamp_formatter ────────────────────
std::string timestamp_formatter(int64_t micros_since_epoch) {
	// split into days + remainder
	int64_t days = micros_since_epoch / kMicrosPerDay;
	int64_t rem  = micros_since_epoch % kMicrosPerDay;
	if (rem < 0) {
		rem += kMicrosPerDay;
		--days;
	}

	// convert back to Y-M-D  (inverse of civil_to_days)
	int64_t        z      = days + civil_to_days(kEpochYear, kEpochMonth, kEpochDay) + 719468; // to 0000-03-01 origin
	const int64_t  era    = (z >= 0 ? z : z - 146096) / 146097;
	const unsigned doe    = static_cast<unsigned>(z - era * 146097);               // [0,146096]
	const unsigned yoe    = (doe - doe / 1460 + doe / 36524 - doe / 146096) / 365; // [0,399]
	const int64_t  y_full = yoe + era * 400;
	const unsigned doy    = doe - (365 * yoe + yoe / 4 - yoe / 100); // [0,365]
	const unsigned mp     = (5 * doy + 2) / 153;                     // [0,11]

	const int      m_signed = static_cast<int>(mp) + (mp < 10 ? 3 : -9); // 1-12
	const unsigned M        = static_cast<unsigned>(m_signed);
	const unsigned D        = doy - (153 * mp + 2) / 5 + 1; // 1-31

	// year adjustment: add 1 if month Jan/Feb (M<=2)
	int     Y_int;
	int64_t Y_calc = y_full + (M <= 2 ? 1 : 0);
	if (Y_calc > std::numeric_limits<int>::max() || Y_calc < std::numeric_limits<int>::min())
		throw std::runtime_error("Year out of int range");
	Y_int = static_cast<int>(Y_calc);

	// time-of-day
	const int hour = static_cast<int>(rem / kMicrosPerHour);
	rem %= kMicrosPerHour;
	const int minute = static_cast<int>(rem / kMicrosPerMinute);
	rem %= kMicrosPerMinute;
	const int second = static_cast<int>(rem / kMicrosPerSecond);
	const int micro  = static_cast<int>(rem % kMicrosPerSecond);

	std::string out = std::format("{:04d}-{:02d}-{:02d}T{:02d}:{:02d}:{:02d}",
	                              Y_int,
	                              static_cast<int>(M),
	                              static_cast<int>(D),
	                              hour,
	                              minute,
	                              second);

	if (micro != 0)
		out += std::format(".{:06d}", micro);
	return out;
}

} // namespace fastlanes
