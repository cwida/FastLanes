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
constexpr int64_t K_MICROS_PER_SECOND = 1'000'000;
constexpr int64_t K_MICROS_PER_MINUTE = 60LL * K_MICROS_PER_SECOND;
constexpr int64_t K_MICROS_PER_HOUR   = 60LL * K_MICROS_PER_MINUTE;
constexpr int64_t K_MICROS_PER_DAY    = 24LL * K_MICROS_PER_HOUR;

// ⌊INT64_MAX / 86 400 000 000⌋  ≈ 106 751 991
constexpr int64_t K_MAX_ABS_DAYS = std::numeric_limits<int64_t>::max() / K_MICROS_PER_DAY;

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
	// ── support "MM/DD/YY hh:mm:ss[.ffffff]" (two-digit year → 2000+YY) ──
	if (ts.size() >= 17 && ts[2] == '/' && ts[5] == '/' && ts[8] == ' ' && ts[11] == ':' && ts[14] == ':') {
		// parse month, day, two-digit year
		auto month_str = ts.substr(0, 2);
		auto day_str   = ts.substr(3, 2);
		auto year2_str = ts.substr(6, 2);
		int  mon       = to_int<int>(month_str, "month");
		int  day       = to_int<int>(day_str, "day");
		int  yr2       = to_int<int>(year2_str, "year");
		int  year      = 2000 + yr2;

		// parse hh:mm:ss
		auto hour_str   = ts.substr(9, 2);
		auto minute_str = ts.substr(12, 2);
		auto second_str = ts.substr(15, 2);
		int  hour       = to_int<int>(hour_str, "hour");
		int  minute     = to_int<int>(minute_str, "minute");
		int  second     = to_int<int>(second_str, "second");

		if (!(1 <= mon && mon <= 12))
			throw std::invalid_argument("Month out of range");
		if (!(1 <= day && day <= 31))
			throw std::invalid_argument("Day out of range");
		if (!(0 <= hour && hour <= 23))
			throw std::invalid_argument("Hour out of range");
		if (!(0 <= minute && minute <= 59))
			throw std::invalid_argument("Minute out of range");
		if (!(0 <= second && second <= 59))
			throw std::invalid_argument("Second out of range");

		// fractional microseconds (optional)
		std::chrono::microseconds frac_us {0};
		std::size_t               posFrac = 17; // index after "MM/DD/YY hh:mm:ss"
		if (posFrac < ts.size()) {
			if (ts[posFrac] == '.') {
				auto frac_part = ts.substr(posFrac + 1);
				if (frac_part.empty() || frac_part.size() > 6)
					throw std::invalid_argument("Fraction must have 1-6 digits");
				int64_t val = to_int<int64_t>(frac_part, "fractional seconds");
				for (std::size_t pad = 6 - frac_part.size(); pad; --pad)
					val *= 10;
				frac_us = std::chrono::microseconds {val};
			} else {
				throw std::invalid_argument("Expected '.' before fraction");
			}
		}

		// build chrono date
		const std::chrono::year           y {year};
		const std::chrono::month          m {static_cast<unsigned>(mon)};
		const std::chrono::day            d {static_cast<unsigned>(day)};
		const std::chrono::year_month_day ymd {y / m / d};
		if (!ymd.ok())
			throw std::invalid_argument("Date out of range in timestamp");
		auto date_days = std::chrono::sys_days {ymd};

		// compute microseconds difference
		auto td = date_days + std::chrono::hours {hour} + std::chrono::minutes {minute} +
		          std::chrono::seconds {second} + frac_us -
		          std::chrono::sys_days {std::chrono::year {kEpochYear} / std::chrono::month {kEpochMonth} /
		                                 std::chrono::day {kEpochDay}};

		int64_t count = td.count();
		if (td < std::chrono::microseconds {std::numeric_limits<int64_t>::min()} ||
		    td > std::chrono::microseconds {std::numeric_limits<int64_t>::max()})
			throw std::out_of_range("Timestamp out of int64 range");
		return count;
	}

	// 1) split YYYY-MM-DD
	const std::size_t p1 = ts.find('-');
	const std::size_t p2 = (p1 == std::string_view::npos) ? std::string_view::npos : ts.find('-', p1 + 1);
	if (p1 == std::string_view::npos || p2 == std::string_view::npos)
		throw std::invalid_argument("Expected YYYY-MM-DDThh:mm:ss or YYYY-MM-DD hh:mm:ss");

	const auto year_str  = ts.substr(0, p1);
	const auto month_str = ts.substr(p1 + 1, 2);
	const auto day_str   = ts.substr(p2 + 1, 2);

	const std::size_t posT = p2 + 3; // position of 'T' or ' ' after “YYYY-MM-DD”
	if (posT >= ts.size() || (ts[posT] != 'T' && ts[posT] != ' '))
		throw std::invalid_argument("Expected 'T' or ' ' after date");

	// 2) ensure hh:mm:ss follows
	if (ts.size() < posT + 9 || ts[posT + 3] != ':' || ts[posT + 6] != ':')
		throw std::invalid_argument("Expected hh:mm:ss");

	const auto hour_str   = ts.substr(posT + 1, 2);
	const auto minute_str = ts.substr(posT + 4, 2);
	const auto second_str = ts.substr(posT + 7, 2);

	// 3) numeric conversion & validation
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

	// 4) fractional microseconds (optional)
	std::chrono::microseconds frac_us {0};
	std::size_t               posFrac = posT + 9; // just after “hh:mm:ss”
	if (posFrac < ts.size() && ts[posFrac] == '.') {
		auto frac_part = ts.substr(posFrac + 1);
		if (frac_part.empty() || frac_part.size() > 6)
			throw std::invalid_argument("Fraction must have 1-6 digits");
		int64_t val = to_int<int64_t>(frac_part, "fractional seconds");
		for (std::size_t pad = 6 - frac_part.size(); pad; --pad)
			val *= 10; // right-pad to microseconds
		frac_us = std::chrono::microseconds {val};
		posFrac += 1 + frac_part.size(); // advance past '.' and digits
	}

	// 5) optional timezone offset [+/-HH:MM]
	int offset_sign = 0;
	int offset_h = 0, offset_m = 0;
	if (posFrac < ts.size() && (ts[posFrac] == '+' || ts[posFrac] == '-')) {
		offset_sign = (ts[posFrac] == '+') ? +1 : -1;
		// expect HH:MM after sign
		if (posFrac + 6 > ts.size() || ts[posFrac + 3] != ':')
			throw std::invalid_argument("Invalid timezone offset format");
		auto off_hour_str = ts.substr(posFrac + 1, 2);
		auto off_min_str  = ts.substr(posFrac + 4, 2);
		offset_h          = to_int<int>(off_hour_str, "tz hour");
		offset_m          = to_int<int>(off_min_str, "tz minute");
		if (!(0 <= offset_h && offset_h <= 23))
			throw std::invalid_argument("TZ hour out of range");
		if (!(0 <= offset_m && offset_m <= 59))
			throw std::invalid_argument("TZ minute out of range");
	}

	// 6) days from epoch
	const int64_t days_from_epoch = civil_to_days(year, month, day) - civil_to_days(kEpochYear, kEpochMonth, kEpochDay);
	if (std::llabs(days_from_epoch) > K_MAX_ABS_DAYS)
		throw std::out_of_range("Timestamp out of int64 range");

	// 7) accumulate in 128-bit, clamp to 64-bit
	__int128 total_us = static_cast<__int128>(days_from_epoch) * K_MICROS_PER_DAY +
	                    static_cast<__int128>(hour) * K_MICROS_PER_HOUR +
	                    static_cast<__int128>(minute) * K_MICROS_PER_MINUTE +
	                    static_cast<__int128>(second) * K_MICROS_PER_SECOND + static_cast<__int128>(frac_us.count());

	// apply timezone adjustment (to UTC): if offset_sign = +1, local = UTC+offset → subtract
	if (offset_sign != 0) {
		int64_t tz_us = static_cast<int64_t>(offset_h) * 3600'000'000LL + static_cast<int64_t>(offset_m) * 60'000'000LL;
		total_us -= static_cast<__int128>(offset_sign) * tz_us;
	}

	if (total_us > std::numeric_limits<int64_t>::max() || total_us < std::numeric_limits<int64_t>::min())
		throw std::out_of_range("Timestamp out of int64 range");

	return static_cast<int64_t>(total_us);
}

// ───────────────────── timestamp_formatter ────────────────────
std::string timestamp_formatter(int64_t micros_since_epoch) {
	// split into days + remainder
	int64_t days = micros_since_epoch / K_MICROS_PER_DAY;
	int64_t rem  = micros_since_epoch % K_MICROS_PER_DAY;
	if (rem < 0) {
		rem += K_MICROS_PER_DAY;
		--days;
	}

	// convert back to Y-M-D (inverse of civil_to_days)
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

	// year adjustment: add 1 if month Jan/Feb (M <= 2)
	int     Y_int;
	int64_t Y_calc = y_full + (M <= 2 ? 1 : 0);
	if (Y_calc > std::numeric_limits<int>::max() || Y_calc < std::numeric_limits<int>::min())
		throw std::runtime_error("Year out of int range");
	Y_int = static_cast<int>(Y_calc);

	// time-of-day
	const int hour = static_cast<int>(rem / K_MICROS_PER_HOUR);
	rem %= K_MICROS_PER_HOUR;
	const int minute = static_cast<int>(rem / K_MICROS_PER_MINUTE);
	rem %= K_MICROS_PER_MINUTE;
	const int second = static_cast<int>(rem / K_MICROS_PER_SECOND);
	const int micro  = static_cast<int>(rem % K_MICROS_PER_SECOND);

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
