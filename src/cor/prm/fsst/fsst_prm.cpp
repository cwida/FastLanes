#include "fls/cor/prm/fsst/fsst_prm.hpp"
#include "fls/cfg/cfg.hpp"
#include <vector>

namespace fastlanes {
fsst_encoder_t* fsst::build_fsst_encoder(n_t c, uint32_t off_arr[], uint8_t* str_p) {
	auto pointer_vec_up = offset_to_pointer(c, off_arr, str_p);
	auto length_vec_up  = offset_to_length(c, off_arr);
	return ::fsst_create(c, length_vec_up->data(), pointer_vec_up->data(), CFG::FSST::NULL_TERMINATED);
}

up<std::vector<uint8_t*>> fsst::offset_to_pointer(n_t c, uint32_t* offset_arr, uint8_t* str_arr) {
	auto tmp = std::make_unique<std::vector<uint8_t*>>();

	for (n_t i {0}; i < c; ++i) {
		tmp->push_back(&str_arr[offset_arr[i]]);
	}
	return tmp;
}

/* Converts arrow offset to the length arr
 * important: in arrow representation, offset_len[1024] could be used a length value*/
up<std::vector<uint32_t>> fsst::offset_to_length(n_t n, uint32_t* offset_arr) {
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