#include "fls/detail/parse_fp.hpp"
#include <cerrno>    // for errno, ERANGE
#include <charconv>  // for std::from_chars
#include <cstdlib>   // for strtof / strtod
#include <limits>    // for numeric_limits
#include <locale>    // for classic locale
#include <sstream>   // for fallback parsing
#include <stdexcept> // for exceptions

namespace fastlanes { namespace detail {

template <typename FloatT>
FloatT parse_fp(const std::string& s) {
#if FASTLANES_HAS_FP_FROM_CHARS
	// Fast path: C++20 from_chars for floats
	FloatT value {};
	auto   rc = std::from_chars(s.data(), s.data() + s.size(), value, std::chars_format::general);
	if (rc.ec == std::errc::invalid_argument)
		throw std::invalid_argument("invalid floating-point literal: " + s);
	if (rc.ec == std::errc::result_out_of_range)
		throw std::out_of_range("floating-point out of representable range: " + s);
	return value;
#else
	// Fallback: use strtof/strtod which handle subnormals correctly
	errno      = 0;
	char*  end = nullptr;
	FloatT value {};
	if constexpr (std::is_same_v<FloatT, float>) {
		value = strtof(s.c_str(), &end);
	} else {
		value = strtod(s.c_str(), &end);
	}

	// Syntax check: all characters consumed?
	if (end != s.c_str() + s.size()) {
		throw std::invalid_argument("invalid floating-point literal: " + s);
	}
	// Overflow check: strto* sets errno==ERANGE only on true overflow
	if (errno == ERANGE && (value == static_cast<FloatT>(HUGE_VAL) || value == static_cast<FloatT>(-HUGE_VAL))) {
		throw std::out_of_range("floating-point out of representable range: " + s);
	}
	return value;
#endif
}

// Explicit instantiations for float and double:
template float  parse_fp<float>(const string&);
template double parse_fp<double>(const string&);

}} // namespace fastlanes::detail
