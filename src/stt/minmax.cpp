#include "fls/stt/minmax.hpp"
#include <limits>

namespace fastlanes {
template <typename T>
MinMax<T>::MinMax()
    : min {std::numeric_limits<T>::max()}
    , max {std::numeric_limits<T>::min()} {
}

template <typename T>
void MinMax<T>::Reset() {
	if constexpr (std::is_same<T, bool>()) {
		return;
	} else {

		min = std::numeric_limits<T>::max();
		max = std::numeric_limits<T>::min();
	}
}

template <>
void MinMax<bool>::Reset() {
}

template <typename T>
void MinMax<T>::Cal(uint8_t* data_p, n_t start, n_t c) {
	if constexpr (std::is_same<T, bool>()) {
		return;
	} else {
		for (n_t i = 0; i < c; ++i) {
			min = std::min(min, reinterpret_cast<T*>(data_p)[start + i]);
			max = std::max(max, reinterpret_cast<T*>(data_p)[start + i]);
		}
	}
}
template <typename T>
up<MinMax<T>> MinMax<T>::cal(uint8_t* data_p, const n_t c) {
	MinMax<T> mm;
	mm.Cal(data_p, 0, c);
	return std::make_unique<MinMax<T>>(mm);
}

/*---------------------------------------------------------------------------------------------------------------------\
 * Specialization
\---------------------------------------------------------------------------------------------------------------------*/
FLS_ALL_CTS(MinMax)

} // namespace fastlanes