#include "fls/primitive/rle/rle.hpp"
#include "fls/cfg/cfg.hpp"
#include "fls/common/string.hpp"

namespace fastlanes {

template <typename KEY_PT, typename INDEX_PT>
n_t RLE<KEY_PT, INDEX_PT>::encode(const KEY_PT* __restrict in_arr,
                                  KEY_PT* __restrict rle_vals,
                                  INDEX_PT* __restrict rle_idxs) {

	rle_idx_t pos_val       = 0;
	n_t       rle_val_idx   = 0;
	auto      prev_val      = in_arr[0];
	rle_vals[rle_val_idx++] = prev_val;
	rle_idxs[0]             = pos_val;

	for (n_t i = 1; i < CFG::VEC_SZ; ++i) {
		auto cur_val = in_arr[i];
		if (cur_val != prev_val) {
			FLS_ASSERT_L(rle_val_idx, CFG::VEC_SZ)
			rle_vals[rle_val_idx++] = cur_val;
			++pos_val;
			prev_val = cur_val;
		}
		rle_idxs[i] = pos_val;
	}

	FLS_ASSERT_LE(rle_val_idx, CFG::VEC_SZ)
	return rle_val_idx;
};

template class RLE<i64_pt, u16_pt>;
template class RLE<i32_pt, u16_pt>;
template class RLE<i16_pt, u16_pt>;
template class RLE<i08_pt, u16_pt>;
template class RLE<dbl_pt, u16_pt>;
template class RLE<flt_pt, u16_pt>;
template class RLE<fls_string_t, u16_pt>;

} // namespace fastlanes