// ────────────────────────────────────────────────────────
// |                      FastLanes                       |
// ────────────────────────────────────────────────────────
// src/types/integer.cpp
// ────────────────────────────────────────────────────────
#include "fls/types/integer.hpp"
#include "fls/std/string.hpp"
#include <cctype> // for std::isdigit
#include <cstdint>
#include <cstdlib> // for std::stoull / std::stoll
#include <limits>
#include <stdexcept>

namespace fastlanes {

template <typename INTEGER_T>
INTEGER_T parse_integer(const string& val_str) {
	static_assert(std::is_integral_v<INTEGER_T> && !std::is_same_v<INTEGER_T, bool>,
	              "parse_integer requires a signed or unsigned integer type (not bool)");

	if (val_str.empty()) {
		throw std::invalid_argument("Empty string");
	}

	// Unsigned integer path
	if constexpr (std::is_unsigned_v<INTEGER_T>) {
		// Every character must be '0'..'9'; no whitespace or signs allowed
		for (const char c : val_str) {
			if (!std::isdigit(static_cast<unsigned char>(c))) {
				throw std::invalid_argument("Invalid character in unsigned integer");
			}
		}
		uint64_t v = 0;
		try {
			v = std::stoull(val_str);
		} catch (const std::invalid_argument&) {
			throw; // shouldn't reach here, since we've already validated digits
		} catch (const std::out_of_range&) {
			throw; // too large even for uint64_t
		}
		if (v > static_cast<uint64_t>(std::numeric_limits<INTEGER_T>::max())) {
			throw std::out_of_range("Value exceeds range of unsigned type");
		}
		return static_cast<INTEGER_T>(v);
	}
	// Signed integer path
	else {
		// First character may be '+' or '-', but if so, there must be at least one digit afterward
		std::size_t start = 0;
		if (val_str[0] == '+' || val_str[0] == '-') {
			if (val_str.size() == 1) {
				throw std::invalid_argument("Sign with no digits");
			}
			start = 1;
		}
		// All remaining characters must be '0'..'9'
		for (std::size_t i = start; i < val_str.size(); ++i) {
			if (!std::isdigit(static_cast<unsigned char>(val_str[i]))) {
				throw std::invalid_argument("Invalid character in signed integer");
			}
		}
		// Convert to long long, then range-check
		long long v = 0;
		try {
			v = std::stoll(val_str);
		} catch (const std::invalid_argument&) {
			throw; // shouldn't reach here, since we've already validated characters
		} catch (const std::out_of_range&) {
			throw; // outside of long long
		}
		if (v < static_cast<long long>(std::numeric_limits<INTEGER_T>::min()) ||
		    v > static_cast<long long>(std::numeric_limits<INTEGER_T>::max())) {
			throw std::out_of_range("Value out of range for signed type");
		}
		return static_cast<INTEGER_T>(v);
	}
}

template uint8_t  parse_integer<uint8_t>(const string&);
template uint16_t parse_integer<uint16_t>(const string&);
template uint32_t parse_integer<uint32_t>(const string&);
template uint64_t parse_integer<uint64_t>(const string&);
template int8_t   parse_integer<int8_t>(const string&);
template int16_t  parse_integer<int16_t>(const string&);
template int32_t  parse_integer<int32_t>(const string&);
template int64_t  parse_integer<int64_t>(const string&);

} // namespace fastlanes
