#include "fls/common/str.hpp"
#include "fls/cfg/cfg.hpp"
#include "fls/common/assert.hpp" // for FLS_ASSERT_CORRECT_SZ, FLS_ASSERT_N...
#include <memory>                // for make_unique, unique_ptr
#include <vector>                // for vector

namespace fastlanes {

decoupled_str_vec Str::decouple(const std::vector<str_pt>& str_vec) {
	FLS_ABORT("IMPLEMENT IT")
	decoupled_str_vec result;
	// auto&             len_vec = result.first;
	// auto&             ptr_vec = result.second;

	return result;
}

decoupled_str_vec Str::decouple(n_t n, std::string* str_arr) {
	decoupled_str_vec result;
	auto&             len_vec = result.first;
	auto&             ptr_vec = result.second;

	for (n_t idx {0}; idx < n; ++idx) {

		auto& cur_str = str_arr[idx];

		FLS_ASSERT_LESS(cur_str.size(), CFG::String::MAX_SIZE)
		len_vec.push_back(static_cast<len_t>(cur_str.size()));
		ptr_vec.push_back(reinterpret_cast<uint8_t*>(cur_str.data()));
	}

	return result;
}

up<bsz_vec_t> Str::get_bsz_vec(const ofs_t* ofs_arr, sz_t size) {
	FLS_ASSERT_NOT_NULL_POINTER(ofs_arr)
	FLS_ASSERT_CORRECT_SZ(size)

	auto bsz_res_vec = std::make_unique<bsz_vec_t>();

	for (idx_t idx {0}, start {0}, end {0}; idx < size; ++idx) {
		end = ofs_arr[idx] - start;
		bsz_res_vec->push_back(end);
		start = ofs_arr[idx];
	}
	return bsz_res_vec;
}

up<ofs_vec_t> Str::to_normal_offset(const ofs_t* ofs_arr, sz_t size) {
	FLS_ASSERT_NOT_NULL_POINTER(ofs_arr)
	FLS_ASSERT_CORRECT_SZ(size)

	auto bsz_res_vec = std::make_unique<ofs_vec_t>();

	for (idx_t idx {0}, start {0}; idx < size; ++idx) {
		bsz_res_vec->push_back(start);
		start = ofs_arr[idx];
	}
	return bsz_res_vec;
}

up<std::vector<uint8_t*>> Str::smart_offset_to_pointer(n_t c, ofs_t offset_arr[], uint8_t str_arr[]) {

	auto tmp = std::make_unique<std::vector<uint8_t*>>();

	for (n_t i {0}, cur_ofs {0}; i < c; ++i) {
		tmp->push_back(&str_arr[cur_ofs]);
		cur_ofs = offset_arr[i];
	}
	return tmp;
}

} // namespace fastlanes