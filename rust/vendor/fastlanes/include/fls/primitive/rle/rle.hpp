#ifndef FLS_PRIMITIVE_RLE_RLE_HPP
#define FLS_PRIMITIVE_RLE_RLE_HPP

#include "fls/common/common.hpp"

namespace fastlanes {
template <typename KEY_PT, typename INDEX_PT>
class RLE {
public:
	static n_t encode(const KEY_PT* __restrict in, KEY_PT* __restrict rle_vals, INDEX_PT* __restrict rle_idxs);
};
} // namespace fastlanes

#endif // FLS_PRIMITIVE_RLE_RLE_HPP
