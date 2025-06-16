#ifndef FLS_COR_ENG_SAMPLER_HPP
#define FLS_COR_ENG_SAMPLER_HPP

#include "fls/common/common.hpp"
#include <string>
#include <vector>

namespace fastlanes {

class ColEncoder;

class SampleState {
public:
	explicit SampleState(); //
public:
	std::vector<std::string> str_vec;
};

template <typename PT>
class Sampler {
public:
	Sampler(); //
public:
	void Sample(const PT* data_p, n_t n, SampleState& sample_state);         //
	void AdaptiveSample(const PT* data_p, n_t n, SampleState& sample_state); //
};
} // namespace fastlanes
#endif // FLS_COR_ENG_SAMPLER_HPP
