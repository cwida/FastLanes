// ────────────────────────────────────────────────────────
// |                      FastLanes                       |
// ────────────────────────────────────────────────────────
// src/include/fls/ffor_util.hpp
// ────────────────────────────────────────────────────────
#ifndef FLS_FFOR_UTIL_HPP
#define FLS_FFOR_UTIL_HPP

#include <cstdint>
#include <type_traits>

namespace fastlanes {

template <typename T>
concept integral = std::is_integral_v<T>;

template <integral PT>
uint8_t count_bits(PT max, PT min) {
	using UT       = std::conditional_t<std::is_signed_v<PT>, std::make_unsigned_t<PT>, PT>;
	const UT delta = static_cast<UT>(max) - static_cast<UT>(min);

	if (delta == 0)
		return 0;

	if constexpr (std::is_same_v<UT, uint64_t>) {
		return static_cast<uint8_t>(64 - __builtin_clzll(delta));
	} else if constexpr (std::is_same_v<UT, uint32_t>) {
		return static_cast<uint8_t>(32 - __builtin_clz(delta));
	} else if constexpr (std::is_same_v<UT, uint16_t>) {
		return static_cast<uint8_t>(16 - (__builtin_clz(static_cast<uint32_t>(delta)) - 16));
	} else if constexpr (std::is_same_v<UT, uint8_t>) {
		return static_cast<uint8_t>(8 - (__builtin_clz(static_cast<uint32_t>(delta)) - 24));
	}
	return 0;
}

} // namespace fastlanes

#endif // FLS_FFOR_UTIL_HPP
