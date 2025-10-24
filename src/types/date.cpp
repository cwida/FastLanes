// ────────────────────────────────────────────────────────
// |                      FastLanes                       |
// ────────────────────────────────────────────────────────
// src/types/date.cpp
// ────────────────────────────────────────────────────────
#include "fls/types/date.hpp"
#include "fls/std/string.hpp"
#include "fls/std/chrono.hpp"
#include <charconv>
#include <cstdint>
#include <cstdio> // for std::snprintf
#include <stdexcept>
#include <string_view>
#include <system_error> // for std::errc

namespace fastlanes {

// Define the epoch as 1970-01-01 in sys_days
constexpr std::chrono::sys_days EPOCH_DAYS {std::chrono::year {1970} / std::chrono::January / 1};

template <typename INTEGER_TYPE>
[[nodiscard]] static INTEGER_TYPE to_uint(string_view sv, const char* field_name) {
	INTEGER_TYPE value {};
	auto [ptr, ec] = std::from_chars(sv.data(), sv.data() + sv.size(), value);
	if (ec != std::errc {} || ptr != sv.data() + sv.size()) {
		throw std::invalid_argument(string("Invalid ") + field_name);
	}
	return value;
}

int32_t parse_date(string_view val_str) {
	std::chrono::year  year_val;
	std::chrono::month month_val;
	std::chrono::day   day_val;

	// 1) ISO-8601 fast path: "YYYY-MM-DD" (exactly 10 chars)
	if (val_str.size() == 10 && val_str[4] == '-' && val_str[7] == '-') {
		year_val  = std::chrono::year {to_uint<int>(val_str.substr(0, 4), "year")};
		month_val = std::chrono::month {to_uint<unsigned>(val_str.substr(5, 2), "month")};
		day_val   = std::chrono::day {to_uint<unsigned>(val_str.substr(8, 2), "day")};
	}
	// 2) Flexible US path: "M/D/YYYY" or "MM/DD/YYYY"
	else {
		const auto first_slash  = val_str.find('/');
		const auto second_slash = val_str.find('/', first_slash + 1);
		if (first_slash == string_view::npos || second_slash == string_view::npos) {
			throw std::invalid_argument("Expected format YYYY-MM-DD or MM/DD/YYYY");
		}

		month_val = std::chrono::month {to_uint<unsigned>(val_str.substr(0, first_slash), "month")};
		day_val   = std::chrono::day {
            to_uint<unsigned>(val_str.substr(first_slash + 1, second_slash - first_slash - 1), "day")};

		const auto year_str = val_str.substr(second_slash + 1);
		if (year_str.size() != 4) {
			throw std::invalid_argument("Year must be 4 digits");
		}
		year_val = std::chrono::year {to_uint<int>(year_str, "year")};
	}

	// 3) Validate calendar date via chrono::year_month_day
	const std::chrono::year_month_day ymd {year_val / month_val / day_val};
	if (!ymd.ok()) {
		throw std::invalid_argument("Date out of range");
	}

	// 4) Convert to “days since 1970-01-01”
	const std::chrono::sys_days sys_days_val {ymd};
	return static_cast<int32_t>((sys_days_val - EPOCH_DAYS).count());
}

string date_formatter(const int32_t days_since_epoch) {
	const std::chrono::sys_days sys_days_val {EPOCH_DAYS + std::chrono::days {days_since_epoch}};
	std::chrono::year_month_day ymd {sys_days_val};
	if (!ymd.ok()) {
		throw std::runtime_error("days_since_epoch out of range");
	}

	int      y = static_cast<int>(ymd.year());
	unsigned m = static_cast<unsigned>(ymd.month());
	unsigned d = static_cast<unsigned>(ymd.day());

	char buf[11]; // "YYYY-MM-DD" + '\0'
	std::snprintf(buf, sizeof(buf), "%04d-%02u-%02u", y, m, d);
	return buf;
}

} // namespace fastlanes
