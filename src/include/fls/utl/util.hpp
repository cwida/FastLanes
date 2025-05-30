#ifndef FLS_UTL_UTIL_HPP
#define FLS_UTL_UTIL_HPP

#include "fls/common/common.hpp"
#include <climits> // for CHAR_BIT
#include <cstdint> // for uint64_t, int64_t, uint8_t
#include <type_traits>

namespace fastlanes {
template <typename T>
auto valid_bit_width(T val) {
	if (val < 0x10000) {
		if (val < 0x100) {
			return 8;
		}
		return 16;
	}
	if (val < 0x100000000L) {
		return 32;
	}
	return 64;
}

/*---------------------------------------------------------------------------------------------------------------------\
 *  RANGE_BIT:
 *  return number of bits needed to represent the given range
\---------------------------------------------------------------------------------------------------------------------*/
template <typename T>
static uint8_t RANGE_BIT(T range) { // NOLINT
	if constexpr (std::is_same<T, bool>()) {
		FLS_ABORT("Not Supported")
	} else if constexpr (std::is_same<T, float>()) {
		FLS_ABORT("Not Supported")
	} else if constexpr (std::is_same<T, double>()) {
		FLS_ABORT("Not Supported")
	} else {
		if (range == 0) {
			return 0;
		}

		uint8_t bw = 0;
		do {
			range = range >> 1;
			++bw;
		} while (range > 0);
		return bw;
	}
	return uint8_t {0};
}

/*---------------------------------------------------------------------------------------------------------------------\
 *  TYPE_BIT:
 *  return number of bits needed to represent the given type
\---------------------------------------------------------------------------------------------------------------------*/
template <typename T>
struct TYPE_BIT { // NOLINT.
	enum : bw_t { VALUE = sizeof(T) * CHAR_BIT };
};

static_assert(TYPE_BIT<int64_t>::VALUE == 64);
static_assert(TYPE_BIT<uint8_t>::VALUE == 8);

template <typename T>
constexpr bw_t type_bit() {
	return sizeof(T) * CHAR_BIT;
}
static_assert(type_bit<int64_t>() == 64);
static_assert(type_bit<uint8_t>() == 8);
/*---------------------------------------------------------------------------------------------------------------------\
 *  count_types:
 *  VALUE shows number of args.
\---------------------------------------------------------------------------------------------------------------------*/
template <class... ARGS_T>
struct TYPE_C;

template <>
struct TYPE_C<> {
	static const n_t VALUE = 0;
};

template <class HEAD_T, class... TAIL_T>
struct TYPE_C<HEAD_T, TAIL_T...> {
	static const n_t VALUE = 1 + TYPE_C<TAIL_T...>::VALUE;
};

uint64_t MAX_BIT(uint64_t bw); // NOLINT
/*---------------------------------------------------------------------------------------------------------------------\
 *  SafeUpperBound:
 *  Finding the upper bound of a {base, bw} is risky as there could be an overflow.
 *  If so, the max needs to be returned.
\---------------------------------------------------------------------------------------------------------------------*/
template <typename T>
T SafeUpperBound(T base, n_t bw) {
	FLS_ASSERT(TYPE_BIT<T>::VALUE >= bw, "More bits than supported number of bits.", " ");

	// is it necessary?
	if (bw == 0) {
		return base;
	}
	/* Domain -> [x y] , range =  y - x. */
	const T range = static_cast<T>(MAX_BIT(bw));
	const T MAX   = std::numeric_limits<T>::max();

	if (base > 0 && range > MAX - base) {
		return MAX; // handle overflow
	} else if (base < 0) {
		return MAX; // handle underflow
	}

	return base + range;
}
} // namespace fastlanes
#endif // FLS_UTL_UTIL_HPP
