#include "fls/cor/prm/fsst/fsst_prm.hpp"
#include "fls/cfg/cfg.hpp"
#include "fls/common/assert.hpp"

namespace fastlanes {
fsst_encoder_t* fsst_wrapper::build_fsst_encoder(const n_t n_values, uint32_t offset_arr[], uint8_t* str_p) {
	const auto pointer_vec_up = offset_to_pointer(n_values, offset_arr, str_p);
	const auto length_vec_up  = offset_to_length(n_values, offset_arr);
	return fsst_create(n_values, length_vec_up->data(), pointer_vec_up->data(), CFG::FSST::NULL_TERMINATED);
}

up<vector<uint8_t*>> fsst_wrapper::offset_to_pointer(const n_t n_values, const uint32_t* offset_arr, uint8_t* str_arr) {
	auto tmp = std::make_unique<std::vector<uint8_t*>>();

	for (n_t i {0}; i < n_values; ++i) {
		tmp->push_back(&str_arr[offset_arr[i]]);
	}
	return tmp;
}

void fsst_wrapper::offset_to_pointer(uint8_t in_byte_arr[], const ofs_t in_offset_arr[], uint8_t* output_str_arr[]) {

	for (n_t val_idx {0}; val_idx < CFG::VEC_SZ; ++val_idx) {
		const auto cur_offset   = in_offset_arr[val_idx];
		output_str_arr[val_idx] = &in_byte_arr[cur_offset];
	}
}

/* Converts arrow offset to the length arr
 * important: in arrow representation, offset_len[1024] could be used a length value*/
up<vector<uint32_t>> fsst_wrapper::offset_to_length(n_t n, const uint32_t* offset_arr) {
	auto cur_vec = std::make_unique<std::vector<uint32_t>>();

	uint32_t start {0};
	for (n_t i {0}; i < n; ++i) {
		auto cur_len = offset_arr[i] - start;
		FLS_ASSERT_GE(offset_arr[i], start)
		cur_vec->push_back(cur_len);
		start = offset_arr[i];
	}
	return cur_vec;
}
} // namespace fastlanes