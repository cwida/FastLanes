#ifndef FLS_UTL_RANDOM_HPP
#define FLS_UTL_RANDOM_HPP

#include "fls/common/common.hpp"
#include "fls/std/vector.hpp"

namespace fastlanes {
class random { // NOLINT
public:
	random() = delete; //
public:
	static n_t next_vec_num(n_t sample_c, vector<bool> is_sampled_arr);
	template <typename T>
	static void rand(n_t n, T lowerbound, T upperbound, vector<T>& vec);
	template <typename T>
	static T rand(T lowerbound, T upperbound);
};
} // namespace fastlanes
#endif // FLS_UTL_RANDOM_HPP
