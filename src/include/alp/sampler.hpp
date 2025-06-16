#ifndef ALP_SAMPLER_HPP
#define ALP_SAMPLER_HPP

#include "alp/config.hpp"
#include <cmath>

namespace alp::sampler {

template <class PT>
uint64_t first_level_sample(const PT* data_p, const uint64_t n_values, PT* sample_arr_p) {
	const uint64_t rowgroup_size = std::min(config::ROWGROUP_SIZE, n_values);
	const uint64_t n_vectors     = (rowgroup_size + config::VECTOR_SIZE - 1) / config::VECTOR_SIZE;
	uint64_t       sample_idx    = 0;
	uint64_t       data_idx      = 0;

	for (uint64_t vector_idx = 0; vector_idx < n_vectors; vector_idx++) {
		constexpr uint64_t n_sampled_increments = 32;
		//! We sample equidistant vectors; to do this we skip a fixed values of vectors
		//! If we are not in the correct jump, we do not take sample from this vector
		if (const bool must_select_rowgroup_sample = (vector_idx % config::ROWGROUP_SAMPLES_JUMP) == 0;
		    !must_select_rowgroup_sample) {
			data_idx += config::VECTOR_SIZE;
			continue;
		}

		// Storing the sample of that vector
		for (uint64_t i = 0; i < config::VECTOR_SIZE; i += n_sampled_increments) {
			sample_arr_p[sample_idx] = data_p[data_idx + i];
			sample_idx++;
		}
		data_idx += config::VECTOR_SIZE;
	}
	return sample_idx;
}

} // namespace alp::sampler

#endif
