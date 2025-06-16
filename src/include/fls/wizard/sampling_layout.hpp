#ifndef SAMPLING_LAYOUT_HPP
#define SAMPLING_LAYOUT_HPP

#include "fls/common/alias.hpp" // for n_t
#include "fls/std/array.hpp"
#include "fls/std/vector.hpp"

// ─────────────────────────────────────────────────────────────────────────────────────────────────────────────
// Compile-time and run-time “sampling layout” mappings (see FastLanes VLDB 2025 for background).
// ─────────────────────────────────────────────────────────────────────────────────────────────────────────────
namespace fastlanes {

// -----------------------------------------------------------------------------------------------------------
// Compile-time mapping
// -----------------------------------------------------------------------------------------------------------
template <n_t N>
constexpr array<n_t, N> sampling_layout() {
	array<n_t, N> arr {};

	if constexpr (N == 64) {
		// Mapping for 64 elements.
		arr[0] = 0;
		arr[1] = 63;
		// Fill indices 2 … 61 with 30 pairs.
		for (n_t i = 0; i < 30; ++i) {
			arr[2 + 2 * i]     = 32 - i;
			arr[2 + 2 * i + 1] = 33 + i;
		}
		// Missing {1, 2} go at the end.
		arr[62] = 1;
		arr[63] = 2;
	} else if constexpr (N == 32) {
		// Mapping for 32 elements.
		arr[0] = 0;
		arr[1] = 31;
		// Fill indices 2 … 29 with 14 pairs.
		for (n_t i = 0; i < 14; ++i) {
			arr[2 + 2 * i]     = 16 - i;
			arr[2 + 2 * i + 1] = 17 + i;
		}
		// Missing {1, 2} go at the end.
		arr[30] = 1;
		arr[31] = 2;
	} else if constexpr (N == 2) {
		arr[0] = 0;
		arr[1] = 1;
	} else if constexpr (N == 1) {
		arr[0] = 0;
	} else {
		static_assert(N == 64 || N == 32 || N == 2 || N == 1,
		              "fastlanes::sampling_layout is defined only for N ∈ {1, 2, 32, 64}");
	}

	return arr;
}

// Convenience aliases explicitly instantiated once.
inline constexpr auto sampling_layout_1  = sampling_layout<1>();
inline constexpr auto sampling_layout_2  = sampling_layout<2>();
inline constexpr auto sampling_layout_32 = sampling_layout<32>();
inline constexpr auto sampling_layout_64 = sampling_layout<64>();

// -----------------------------------------------------------------------------------------------------------
// Run-time mapping
// -----------------------------------------------------------------------------------------------------------
vector<n_t> sampling_layout_dynamic(n_t rowgroup_size);

} // namespace fastlanes

#endif // SAMPLING_LAYOUT_HPP
