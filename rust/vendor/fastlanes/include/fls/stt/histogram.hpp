#ifndef FLS_STT_HISTOGRAM_HPP
#define FLS_STT_HISTOGRAM_HPP

#include "fls/common/common.hpp" // for size_t
#include "fls/stt/statistic.hpp" // for ISTT
#include <vector>

namespace fastlanes {
template <typename T>
class Histogram : public Statistic<T> {
public:
	Histogram() = default; //
public:
	static up<Histogram<T>> cal(uint8_t* data_p, n_t c = vec_n_tup());                   //
	void                    Cal(uint8_t* data_p, n_t start, n_t = vec_n_tup()) override; //
	void                    Reset() override;                                            //
public:
	std::vector<T>        val_vec; //
	std::vector<uint16_t> rep_vec; //
};
} // namespace fastlanes
#endif // FLS_STT_HISTOGRAM_HPP
