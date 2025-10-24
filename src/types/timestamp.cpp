// ────────────────────────────────────────────────────────
// |                      FastLanes                       |
// ────────────────────────────────────────────────────────
// src/types/timestamp.cpp
// ────────────────────────────────────────────────────────
// src/types/timestamp.cpp
#include "fls/types/timestamp.hpp"
#include "fls/std/string.hpp"
#include "fls/std/chrono.hpp"
#include <cctype>
#include <charconv>
#include <cstdint>
#include <cstdio>
#include <cstdlib> // for std::llabs
#include <limits>
#include <stdexcept>
#include <string_view>
#include <system_error> // for std::errc

namespace fastlanes {

// ───────────────────────── constants ──────────────────────────
constexpr int64_t K_MICROS_PER_SECOND = 1'000'000;
constexpr int64_t K_MICROS_PER_MINUTE = 60LL * K_MICROS_PER_SECOND;
constexpr int64_t K_MICROS_PER_HOUR   = 60LL * K_MICROS_PER_MINUTE;
constexpr int64_t K_MICROS_PER_DAY    = 24LL * K_MICROS_PER_HOUR;

// Hard guard: ⌊INT64_MAX / 86 400 000 000⌋
constexpr int64_t K_MAX_ABS_DAYS = std::numeric_limits<int64_t>::max() / K_MICROS_PER_DAY;

constexpr int      kEpochYear  = 1970;
constexpr unsigned kEpochMonth = 1;
constexpr unsigned kEpochDay   = 1;

// ───────────────────────── helpers ────────────────────────────
template <typename INT>
[[nodiscard]] INT to_int(string_view s, const char* field) {
	INT v {};
	auto [ptr, ec] = std::from_chars(s.data(), s.data() + s.size(), v);
	if (ec != std::errc {} || ptr != s.data() + s.size())
		throw std::invalid_argument(string("Invalid ") + field);
	return v;
}

// Howard Hinnant civil-to-days
static int64_t civil_to_days(int y, unsigned m, unsigned d) {
	if (m <= 2) {
		--y;
		m += 12;
	}
	const int64_t     era            = y / 400;
	const int64_t     yoe            = static_cast<int64_t>(y) - era * 400;   // [0,399]
	const int64_t     doy            = (153 * (m - 3) + 2) / 5 + d - 1;       // [0,365]
	const int64_t     doe            = yoe * 365 + yoe / 4 - yoe / 100 + doy; // [0,146096]
	constexpr int64_t DAYS_0000_1970 = 719468;
	return era * 146097 + doe - DAYS_0000_1970;
}

// Guard helper
static void guard_days_range(int y, unsigned m, unsigned d) {
	int64_t diff = civil_to_days(y, m, d) - civil_to_days(kEpochYear, kEpochMonth, kEpochDay);
	if (std::llabs(diff) > K_MAX_ABS_DAYS)
		throw std::out_of_range("Timestamp out of int64 range");
}

// ─────────────────────── parse_timestamp ──────────────────────
int64_t parse_timestamp(string_view ts) {
	// ── branch A: “MM/DD/YYYY hh:mm:ss AM/PM” ───────────────────
	if (ts.size() == 22 && ts[2] == '/' && ts[5] == '/' && ts[10] == ' ' && ts[13] == ':' && ts[16] == ':' &&
	    ts[19] == ' ' && ((ts[20] == 'A' && ts[21] == 'M') || (ts[20] == 'P' && ts[21] == 'M'))) {
		int  mon    = to_int<int>(ts.substr(0, 2), "month");
		int  day    = to_int<int>(ts.substr(3, 2), "day");
		int  year   = to_int<int>(ts.substr(6, 4), "year");
		int  hour   = to_int<int>(ts.substr(11, 2), "hour");
		int  minute = to_int<int>(ts.substr(14, 2), "minute");
		int  second = to_int<int>(ts.substr(17, 2), "second");
		bool is_pm  = (ts[20] == 'P');

		if (!(1 <= mon && mon <= 12) || !(1 <= day && day <= 31) || !(0 <= hour && hour <= 12) ||
		    !(0 <= minute && minute <= 59) || !(0 <= second && second <= 59)) {
			throw std::invalid_argument("Date-time component out of range");
		}

		// Convert 12-hour → 24-hour
		if (hour == 12) {
			hour = is_pm ? 12 : 0;
		} else if (is_pm) {
			hour += 12;
		}

		guard_days_range(year, static_cast<unsigned>(mon), static_cast<unsigned>(day));

		auto epoch = std::chrono::sys_days {std::chrono::year {kEpochYear} / std::chrono::month {kEpochMonth} /
		                                    std::chrono::day {kEpochDay}};
		std::chrono::year_month_day ymd {std::chrono::year {year} / std::chrono::month {static_cast<unsigned>(mon)} /
		                                 std::chrono::day {static_cast<unsigned>(day)}};
		auto tp = std::chrono::sys_days {ymd} + std::chrono::hours {hour} + std::chrono::minutes {minute} +
		          std::chrono::seconds {second};

		return std::chrono::duration_cast<std::chrono::microseconds>(tp - epoch).count();
	}

	// ── branch B: “MM/DD/YY hh:mm:ss[.ffffff][±HH[:MM]]” ───────
	if (ts.size() >= 17 && ts[2] == '/' && ts[5] == '/' && ts[8] == ' ' && ts[11] == ':' && ts[14] == ':') {
		int mon    = to_int<int>(ts.substr(0, 2), "month");
		int day    = to_int<int>(ts.substr(3, 2), "day");
		int year   = 2000 + to_int<int>(ts.substr(6, 2), "year");
		int hour   = to_int<int>(ts.substr(9, 2), "hour");
		int minute = to_int<int>(ts.substr(12, 2), "minute");
		int second = to_int<int>(ts.substr(15, 2), "second");

		if (!(1 <= mon && mon <= 12) || !(1 <= day && day <= 31) || !(0 <= hour && hour <= 23) ||
		    !(0 <= minute && minute <= 59) || !(0 <= second && second <= 59)) {
			throw std::invalid_argument("Date-time component out of range");
		}

		guard_days_range(year, static_cast<unsigned>(mon), static_cast<unsigned>(day));

		// fraction
		std::chrono::microseconds frac {0};
		std::size_t               idx = 17;
		if (idx < ts.size() && ts[idx] == '.') {
			std::size_t start = ++idx, end = start;
			while (end < ts.size() && std::isdigit(static_cast<unsigned char>(ts[end])) && (end - start) < 6) {
				++end;
			}
			if (end < ts.size() && std::isdigit(static_cast<unsigned char>(ts[end])))
				throw std::invalid_argument("Fraction must have 1-6 digits");
			if (start == end)
				throw std::invalid_argument("Fraction must have 1-6 digits");

			auto v = to_int<int64_t>(ts.substr(start, end - start), "fractional seconds");
			for (std::size_t pad = 6 - (end - start); pad; --pad) {
				v *= 10;
			}
			frac = std::chrono::microseconds {v};
			idx  = end;
		}

		// offset or 'Z'
		int sign = 0, off_h = 0, off_m = 0;
		if (idx < ts.size()) {
			if (ts[idx] == 'Z' && idx + 1 == ts.size()) {
				// Zulu (UTC), so offset = +00:00
			} else if (ts[idx] == '+' || ts[idx] == '-') {
				sign = (ts[idx++] == '+') ? +1 : -1;
				if (idx + 1 >= ts.size() || !std::isdigit(static_cast<unsigned char>(ts[idx])) ||
				    !std::isdigit(static_cast<unsigned char>(ts[idx + 1]))) {
					throw std::invalid_argument("Invalid timezone offset format");
				}
				off_h = (ts[idx] - '0') * 10 + (ts[idx + 1] - '0');
				if (!(0 <= off_h && off_h <= 23))
					throw std::invalid_argument("TZ hour out of range");
				idx += 2;

				if (idx == ts.size()) {
					// "+HH"
				} else if (ts[idx] == ':' && idx + 2 < ts.size() &&
				           std::isdigit(static_cast<unsigned char>(ts[idx + 1])) &&
				           std::isdigit(static_cast<unsigned char>(ts[idx + 2]))) {
					off_m = (ts[idx + 1] - '0') * 10 + (ts[idx + 2] - '0');
					if (!(0 <= off_m && off_m <= 59))
						throw std::invalid_argument("TZ minute out of range");
					idx += 3;
					if (idx != ts.size())
						throw std::invalid_argument("Invalid trailing characters in offset");
				} else {
					throw std::invalid_argument("Invalid timezone offset format");
				}
			} else {
				throw std::invalid_argument("Unexpected trailing characters");
			}
		}

		// chrono
		auto epoch = std::chrono::sys_days {std::chrono::year {kEpochYear} / std::chrono::month {kEpochMonth} /
		                                    std::chrono::day {kEpochDay}};
		std::chrono::year_month_day ymd {std::chrono::year {year} / std::chrono::month {static_cast<unsigned>(mon)} /
		                                 std::chrono::day {static_cast<unsigned>(day)}};
		auto tp = std::chrono::sys_days {ymd} + std::chrono::hours {hour} + std::chrono::minutes {minute} +
		          std::chrono::seconds {second} + frac - std::chrono::hours {sign * off_h} -
		          std::chrono::minutes {sign * off_m};

		return std::chrono::duration_cast<std::chrono::microseconds>(tp - epoch).count();
	}

	// ── branch C: “YYYY-MM-DD[T| ]hh:mm:ss[.ffffff][Z|±HH[:MM]]” ────
	const std::size_t p1 = ts.find('-');
	const std::size_t p2 = (p1 == string_view::npos) ? string_view::npos : ts.find('-', p1 + 1);
	if (p1 == string_view::npos || p2 == string_view::npos) {
		throw std::invalid_argument("Expected YYYY-MM-DDThh:mm:ss");
	}

	int  year  = to_int<int>(ts.substr(0, p1), "year");
	auto month = to_int<unsigned>(ts.substr(p1 + 1, 2), "month");
	auto day   = to_int<unsigned>(ts.substr(p2 + 1, 2), "day");

	std::size_t posT = p2 + 3;
	if (posT >= ts.size() || (ts[posT] != 'T' && ts[posT] != ' ')) {
		throw std::invalid_argument("Expected 'T' or ' ' after date");
	}
	if (ts.size() < posT + 9 || ts[posT + 3] != ':' || ts[posT + 6] != ':') {
		throw std::invalid_argument("Expected hh:mm:ss");
	}

	int hour   = to_int<int>(ts.substr(posT + 1, 2), "hour");
	int minute = to_int<int>(ts.substr(posT + 4, 2), "minute");
	int second = to_int<int>(ts.substr(posT + 7, 2), "second");

	if (!(1 <= month && month <= 12) || !(1 <= day && day <= 31) || !(0 <= hour && hour <= 23) ||
	    !(0 <= minute && minute <= 59) || !(0 <= second && second <= 59)) {
		throw std::invalid_argument("Date-time component out of range");
	}

	guard_days_range(year, month, day);

	// fraction
	std::size_t               idx = posT + 9;
	std::chrono::microseconds frac {0};
	if (idx < ts.size() && ts[idx] == '.') {
		std::size_t start = ++idx, end = start;
		while (end < ts.size() && std::isdigit(static_cast<unsigned char>(ts[end])) && (end - start) < 6) {
			++end;
		}
		if (end < ts.size() && std::isdigit(static_cast<unsigned char>(ts[end]))) {
			throw std::invalid_argument("Fraction must have 1-6 digits");
		}
		if (start == end) {
			throw std::invalid_argument("Fraction must have 1-6 digits");
		}
		auto v = to_int<int64_t>(ts.substr(start, end - start), "fractional seconds");
		for (std::size_t pad = 6 - (end - start); pad; --pad) {
			v *= 10;
		}
		frac = std::chrono::microseconds {v};
		idx  = end;
	}

	// offset or ‘Z’
	int sign = 0, off_h = 0, off_m = 0;
	if (idx < ts.size()) {
		if (ts[idx] == 'Z' && idx + 1 == ts.size()) {
		} else if (ts[idx] == '+' || ts[idx] == '-') {
			sign = (ts[idx++] == '+') ? +1 : -1;
			if (idx + 1 >= ts.size() || !std::isdigit(static_cast<unsigned char>(ts[idx])) ||
			    !std::isdigit(static_cast<unsigned char>(ts[idx + 1]))) {
				throw std::invalid_argument("Invalid timezone offset format");
			}
			off_h = (ts[idx] - '0') * 10 + (ts[idx + 1] - '0');
			if (!(0 <= off_h && off_h <= 23))
				throw std::invalid_argument("TZ hour out of range");
			idx += 2;

			if (idx == ts.size()) {
				// "+HH"
			} else if (ts[idx] == ':' && idx + 2 < ts.size() && std::isdigit(static_cast<unsigned char>(ts[idx + 1])) &&
			           std::isdigit(static_cast<unsigned char>(ts[idx + 2]))) {
				off_m = (ts[idx + 1] - '0') * 10 + (ts[idx + 2] - '0');
				if (!(0 <= off_m && off_m <= 59))
					throw std::invalid_argument("TZ minute out of range");
				idx += 3;
				if (idx != ts.size())
					throw std::invalid_argument("Invalid trailing characters in offset");
			} else {
				throw std::invalid_argument("Invalid timezone offset format");
			}
		} else {
			throw std::invalid_argument("Unexpected trailing characters");
		}
	}

	// chrono
	std::chrono::year_month_day ymd {std::chrono::year {year} / std::chrono::month {month} / std::chrono::day {day}};
	auto epoch = std::chrono::sys_days {std::chrono::year {kEpochYear} / std::chrono::month {kEpochMonth} /
	                                    std::chrono::day {kEpochDay}};
	auto tp    = std::chrono::sys_days {ymd} + std::chrono::hours {hour} + std::chrono::minutes {minute} +
	          std::chrono::seconds {second} + frac - std::chrono::hours {sign * off_h} -
	          std::chrono::minutes {sign * off_m};

	return std::chrono::duration_cast<std::chrono::microseconds>(tp - epoch).count();
}

// ───────────────────── timestamp_formatter ────────────────────
string timestamp_formatter(int64_t micros) {
	// Split micros into civil-date parts and time-of-day
	int64_t days = micros / K_MICROS_PER_DAY;
	int64_t rem  = micros % K_MICROS_PER_DAY;
	if (rem < 0) {
		rem += K_MICROS_PER_DAY;
		--days;
	}

	// Civil-from-days (inverse of civil_to_days)
	int64_t  z   = days + civil_to_days(kEpochYear, kEpochMonth, kEpochDay) + 719468;
	int64_t  era = (z >= 0 ? z : z - 146096) / 146097;
	auto     doe = static_cast<unsigned>(z - era * 146097);
	unsigned yoe = (doe - doe / 1460 + doe / 36524 - doe / 146096) / 365;
	int64_t  y   = yoe + era * 400;
	unsigned doy = doe - (365 * yoe + yoe / 4 - yoe / 100);
	unsigned mp  = (5 * doy + 2) / 153;

	int      m_s   = static_cast<int>(mp) + (mp < 10 ? 3 : -9); // 1-12
	auto     month = static_cast<unsigned>(m_s);
	unsigned day   = doy - (153 * mp + 2) / 5 + 1;
	int      year  = static_cast<int>(y + (month <= 2 ? 1 : 0));

	int hour = static_cast<int>(rem / K_MICROS_PER_HOUR);
	rem %= K_MICROS_PER_HOUR;
	int minute = static_cast<int>(rem / K_MICROS_PER_MINUTE);
	rem %= K_MICROS_PER_MINUTE;
	int second = static_cast<int>(rem / K_MICROS_PER_SECOND);
	int micro  = static_cast<int>(rem % K_MICROS_PER_SECOND);

	// Build ISO-8601 string
	char buf[32]; // enough
	int  len = std::snprintf(buf, sizeof(buf), "%04d-%02u-%02uT%02d:%02d:%02d", year, month, day, hour, minute, second);

	if (micro != 0) {
		std::size_t remaining = sizeof(buf) - static_cast<std::size_t>(len);
		std::snprintf(buf + len, remaining, ".%06d", micro);
	}
	return buf;
}

} // namespace fastlanes
