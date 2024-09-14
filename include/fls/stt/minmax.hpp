#ifndef FLS_STT_MINMAX_HPP
#define FLS_STT_MINMAX_HPP

#include "fls/stt/statistic.hpp"
#include <cstdint>
#include <vector>

namespace fastlanes {
template <typename T>
class MinMax : public Statistic<T> {
public:
	MinMax(); //
public:
	static up<MinMax<T>> cal(uint8_t* data_p, n_t c = vec_n_tup());                     //
	void                 Reset() override;                                              //
	void                 Cal(uint8_t* data_p, n_t start, n_t c = vec_n_tup()) override; //
public:
	T min; //
	T max; //
};
} // namespace fastlanes
#endif // FLS_STT_MINMAX_HPP
