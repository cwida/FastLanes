#include "fls/stt/stt_fac.hpp"
#include "fls/stt/histogram.hpp"
#include "fls/stt/minmax.hpp"

namespace fastlanes {
template <typename T>
up<Statistic<T>> stt_fac<T>::Create(uint8_t* data_p, const n_t c, SttT type) {
	switch (type) {
	case SttT::MINMAX:
		return MinMax<T>::cal(data_p, c);
	case SttT::HISTOGRAM:
		return Histogram<T>::cal(data_p, c);
	}

	return nullptr;
}

/*--------------------------------------------------------------------------------------------------------------------*\
 * Specialization
\*--------------------------------------------------------------------------------------------------------------------*/
FLS_ALL_CTS(stt_fac)

} // namespace fastlanes