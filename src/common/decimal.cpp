// ────────────────────────────────────────────────────────
// |                      FastLanes                       |
// ────────────────────────────────────────────────────────
// src/common/decimal.cpp
// ────────────────────────────────────────────────────────
#include "fls/common/decimal.hpp"
#include "fls/common/alias.hpp" // for up<>, make_unique<>, n_t
#include "fls/footer/decimal_type_generated.h"
#include "fls/std/string.hpp"
#include <cctype> // for std::isdigit
#include <cmath>
#include <cstddef> // for size_t
#include <cstdint> // for int64_t
#include <regex>
#include <stdexcept> // for std::invalid_argument
#include <string>    // for std::string, std::stold, std::stoull

namespace fastlanes {

// Function to filter out non-numeric characters (except `-` and `.`)
string clean_numeric_string(const string& input) {
	string cleaned;
	for (char ch : input) {
		if (std::isdigit(ch) || ch == '.' || (ch == '-' && cleaned.empty())) {
			cleaned += ch;
		}
	}
	return cleaned;
}

int64_t make_decimal(const string& value, n_t scale) {
	string cleaned_value = clean_numeric_string(value); // Remove unwanted characters

	// Ensure we still have a valid numeric string
	if (cleaned_value.empty() || cleaned_value == "-" || cleaned_value == ".") {
		throw std::invalid_argument("Invalid numeric input: " + value);
	}

	string abs_value   = cleaned_value;
	bool   is_negative = (cleaned_value[0] == '-'); // Track if the number is negative
	if (is_negative) {
		abs_value = cleaned_value.substr(1); // Remove the minus sign
	}

	const size_t dot_pos           = abs_value.find('.');
	const n_t    fractional_digits = (dot_pos == string::npos) ? 0 : abs_value.size() - dot_pos - 1;

	// If the input has more decimals than `scale`, throw an exception
	if (fractional_digits > scale) {
		throw std::invalid_argument("Input has more decimal places than allowed scale: " + cleaned_value);
	}

	// Use std::round() to avoid precision issues
	const auto scaled_value = static_cast<double>(std::stold(cleaned_value)) * std::pow(10, scale);
	const auto int_value    = static_cast<int64_t>(std::round(scaled_value)); // Round before conversion

	return int_value;
}

up<DecimalTypeT> make_decimal_t(const string& value) {
	static const std::regex pattern {R"(decimal\s*\(\s*(\d+)\s*,\s*(\d+)\s*\))", std::regex::icase};
	std::smatch             match;
	if (std::regex_match(value, match, pattern)) {
		n_t  precision = std::stoull(match.str(1));
		n_t  scale     = std::stoull(match.str(2));
		auto dt        = make_unique<DecimalTypeT>();
		dt->precision  = precision;
		dt->scale      = scale;
		return dt;
	}
	throw std::invalid_argument("Invalid decimal format: " + value);
}

} // namespace fastlanes
