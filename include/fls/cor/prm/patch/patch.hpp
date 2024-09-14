#ifndef FLS_COR_PRM_PATCH_PATCH_HPP
#define FLS_COR_PRM_PATCH_PATCH_HPP

#include "fls/common/common.hpp"
#include <vector>

namespace fastlanes {
/*--------------------------------------------------------------------------------------------------------------------*/
class Vec;
class CompressState;

/*--------------------------------------------------------------------------------------------------------------------*/

template <typename T>
class typed_patch {
public:
	static n_t  count_exceptions(const T                      lower_bound,
	                             const T                      upper_bound,
	                             const std::vector<T>&        val_vec,
	                             const std::vector<uint16_t>& rep_vec);
	static bool is_exception(T lower_bound, T upper_bound, T val);
	static void b_patch_decompress(T* in_p, uint64_t* bitmap, T* exc_p);
	static void l_patch_compress(T* in, T* exc, pos_t arr[], pos_t c, n_t max_range);
	static void l_patch_decompress(T* in, pos_t first, pos_t c);
};
class patch {
public:
	static void b_patch_compress(pos_t arr[], pos_t c, bitmap_t bitmap);
	static bool is_compulsory_exc(pos_t curr, pos_t next, uint64_t range);
};
} // namespace fastlanes
#endif // FLS_COR_PRM_PATCH_PATCH_HPP
