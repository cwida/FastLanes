#ifndef FLS_STT_STATISTIC_HPP
#define FLS_STT_STATISTIC_HPP

#include "fls/common/common.hpp"

namespace fastlanes {
template <typename T>
class Statistic {
public:
	virtual ~Statistic() = default; //
public:
	virtual void Reset()                                              = 0; //
	virtual void Cal(uint8_t* data_p, n_t start, n_t c = vec_n_tup()) = 0; //
public:
};
} // namespace fastlanes
#endif // FLS_STT_STATISTIC_HPP
