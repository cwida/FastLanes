#include "fls/common/decimal.hpp"
#include <cmath>
#include <format>
#include <regex>

namespace fastlanes {

// Function to filter out non-numeric characters (except `-` and `.`)
std::string clean_numeric_string(const std::string& input) {
	std::string cleaned;
	for (char ch : input) {
		if (std::isdigit(ch) || ch == '.' || (ch == '-' && cleaned.empty())) {
			cleaned += ch;
		}
	}
	return cleaned;
}

int64_t make_decimal(const std::string& value, n_t scale) {
	std::string cleaned_value = clean_numeric_string(value); // ✅ Remove unwanted characters

	// Ensure we still have a valid numeric string
	if (cleaned_value.empty() || cleaned_value == "-" || cleaned_value == ".") {
		throw std::invalid_argument("Invalid numeric input: " + value);
	}

	std::string abs_value   = cleaned_value;
	bool        is_negative = (cleaned_value[0] == '-'); // Track if the number is negative
	if (is_negative) {
		abs_value = cleaned_value.substr(1); // Remove the minus sign
	}

	const size_t dot_pos           = abs_value.find('.');
	const n_t    fractional_digits = (dot_pos == std::string::npos) ? 0 : abs_value.size() - dot_pos - 1;

	// ❌ If the input has more decimals than `scale`, throw an exception
	if (fractional_digits > scale) {
		throw std::invalid_argument("Input has more decimal places than allowed scale: " + cleaned_value);
	}

	// ✅ Use std::round() to avoid precision issues
	const auto scaled_value = static_cast<double>(std::stold(cleaned_value)) * std::pow(10, scale);
	const auto int_value    = static_cast<int64_t>(std::round(scaled_value)); // ✅ Fix: Round before conversion

	return int_value;
}

DecimalType::DecimalType() = default;

DecimalType::DecimalType(const n_t precision, const n_t scale)
    : precision(precision)
    , scale(scale) {
}

// ✅ Function to parse "decimal(precision, scale)" format
DecimalType make_decimal_t(const std::string& value) {
	std::regex  pattern(R"(decimal\s*\(\s*(\d+)\s*,\s*(\d+)\s*\))", std::regex::icase);
	std::smatch match;

	if (std::regex_match(value, match, pattern)) {
		return {static_cast<n_t>(std::stoul(match[1])), static_cast<n_t>(std::stoul(match[2]))};
	}

	throw std::invalid_argument(std::format("Invalid decimal format: {}", value));
}

} // namespace fastlanes