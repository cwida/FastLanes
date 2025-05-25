#include "fls/common/double.hpp"
#include <cmath>

namespace fastlanes {

// Function to be tested
bool Double::is_safely_castable_to_int64(dbl_pt value) {
	constexpr double SAFE_INT_MIN = -9007199254740992.0; // -2^53
	constexpr double SAFE_INT_MAX = 9007199254740992.0;  //  2^53

	// Check if value is within safe range
	if (value <= SAFE_INT_MIN || value >= SAFE_INT_MAX) {
		return false;
	}

	// Extract the integer and fractional parts
	double       int_part;
	const double frac_part = std::modf(value, &int_part);

	// Ensure there is NO fractional component (fraction must be exactly 0.0)
	if (frac_part != 0.0) {
		return false;
	}

	// Convert to int64_t and back to double
	const auto int_value       = static_cast<int64_t>(value);
	const auto recovered_value = static_cast<double>(int_value);

	// If conversion does not alter the value, it's safely castable
	return (value == recovered_value);
}

} // namespace fastlanes