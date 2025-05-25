#include "fls/utl/random.hpp"
#include <random>

namespace fastlanes {
n_t random::next_vec_num(n_t sample_c, vector<bool> is_sampled_arr) {
	std::random_device dev;
	std::mt19937       engine(dev());

	auto random_num = engine() % sample_c;
	while (is_sampled_arr[random_num]) {
		random_num = engine() % sample_c;
	}

	is_sampled_arr[random_num] = true;
	return random_num;
}
template <typename T>
T random::rand(T lowerbound, T upperbound) {
	std::random_device               rd;
	std::mt19937                     mt(rd());
	std::uniform_int_distribution<T> dist(lowerbound, upperbound);
	T                                result {dist(mt)};
	result = dist(mt);
	return result;
}

template <typename T>
void random::rand(n_t n, T lowerbound, T upperbound, std::vector<T>& vec) {

	for (idx_t tup_idx {0}; tup_idx < n; ++tup_idx) {
		vec.push_back(rand(lowerbound, upperbound));
	}
}

template int64_t random::rand<i64_pt>(i64_pt lowerbound, i64_pt upperbound);
template void    random::rand<i64_pt>(n_t n, i64_pt lowerbound, i64_pt upperbound, std::vector<i64_pt>& vec);
} // namespace fastlanes