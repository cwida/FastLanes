#include "fls/stt/histogram.hpp"
#include "fls/std/string.hpp"
#include <algorithm>

namespace fastlanes {
template <typename T>
void Histogram<T>::Reset() {
	val_vec.clear();
	rep_vec.clear();
}

template <typename T>
void Histogram<T>::Cal(uint8_t* data_p, n_t start, n_t c) {
	if constexpr (std::is_same<T, bool>()) {
		return;
	} else {
		FLS_ASSERT_NOT_NULL_POINTER(data_p)
		FLS_ASSERT_CORRECT_SZ(c)

		val_vec.clear();
		rep_vec.clear();

		T* typed_data_p = reinterpret_cast<T*>(data_p) + start;

		/* Sort. */
		std::sort(typed_data_p, typed_data_p + c);

		/* Push the first one. */
		val_vec.push_back(typed_data_p[0]);
		rep_vec.push_back(1);

		/* Make the histogram. */
		for (n_t i = 1; i < c; ++i) {
			/* Same value. Increase the rep*/
			if (typed_data_p[i] == typed_data_p[i - 1]) {
				rep_vec.back() += 1;
			}
			/* New seq. add it to vec. Set the rep to one. */
			else {
				val_vec.push_back(typed_data_p[i]);
				rep_vec.push_back(1);
			}
		}
	}
}

template <typename T>
up<Histogram<T>> Histogram<T>::cal(uint8_t* data_p, n_t c) {
	Histogram<T> his;
	his.Cal(data_p, 0, c);
	return std::make_unique<Histogram<T>>(his);
}

/*---------------------------------------------------------------------------------------------------------------------\
 * Specialization
\---------------------------------------------------------------------------------------------------------------------*/
FLS_ALL_CTS(Histogram)

} // namespace fastlanes