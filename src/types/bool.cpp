// ────────────────────────────────────────────────────────
// |                      FastLanes                       |
// ────────────────────────────────────────────────────────
// src/types/bool.cpp
// ────────────────────────────────────────────────────────
#include "fls/types/bool.hpp"
#include <algorithm>
#include <cctype>
#include <cstdint>
#include <stdexcept>

namespace fastlanes {

namespace {

// Trim leading and trailing ASCII whitespace from a string_view (in-place)
inline void trim(string_view& sv) {
	while (!sv.empty() && std::isspace(static_cast<unsigned char>(sv.front()))) {
		sv.remove_prefix(1);
	}
	while (!sv.empty() && std::isspace(static_cast<unsigned char>(sv.back()))) {
		sv.remove_suffix(1);
	}
}

// Case-insensitive equality (ASCII only, avoids allocation)
inline bool iequals(string_view a, string_view b) {
	if (a.size() != b.size()) {
		return false;
	};
	for (std::size_t i = 0; i < a.size(); ++i) {
		unsigned char c1 = static_cast<unsigned char>(a[i]);
		unsigned char c2 = static_cast<unsigned char>(b[i]);
		if (std::tolower(c1) != std::tolower(c2)) {
			return false;
		};
	}
	return true;
}

} // anonymous namespace

uint8_t parse_bool(string_view val_str) {
	trim(val_str);
	if (val_str.empty()) {
		throw std::invalid_argument("Boolean literal is empty");
	};

	// Fast path: single-character literals
	if (val_str.size() == 1) {
		char c = static_cast<char>(std::tolower(static_cast<unsigned char>(val_str[0])));
		switch (c) {
		case '1':
		case 't':
		case 'y': {
			return 1;
		};
		case '0':
		case 'f':
		case 'n': {
			return 0;
		};
		default: {
			throw std::invalid_argument("Unrecognised boolean literal");
		};
		}
	}

	// Multi-character literals
	if (iequals(val_str, "true") || iequals(val_str, "yes")) {
		return 1;
	};
	if (iequals(val_str, "false") || iequals(val_str, "no")) {
		return 0;
	};

	throw std::invalid_argument("Unrecognised boolean literal");
}

std::string bool_formatter(uint8_t value) {
	return value == 0 ? "false" : "true";
}

} // namespace fastlanes
