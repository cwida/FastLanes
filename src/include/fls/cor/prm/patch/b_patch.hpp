#ifndef FLS_COR_PRM_PATCH_B_PATCH_HPP
#define FLS_COR_PRM_PATCH_B_PATCH_HPP

#include "fls/cfg/cfg.hpp"
#include "fls/common/assert.hpp"
#include "fls/cor/fun.hpp"
#include "fls/utl/util.hpp"

namespace fastlanes {
class b_patch {
public:
	template <typename T>
	static cmpr_fun_t ResolveCompressFunc();
	template <typename T>
	static de_cmpr_fun_t ResolveDecompressFunc();
};
} // namespace fastlanes
#endif // FLS_COR_PRM_PATCH_B_PATCH_HPP
