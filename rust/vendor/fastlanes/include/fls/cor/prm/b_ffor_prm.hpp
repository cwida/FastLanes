#ifndef FLS_COR_PRM_B_FFOR_PRM_HPP
#define FLS_COR_PRM_B_FFOR_PRM_HPP

#include "fls/cor/fun.hpp"

// clang-format off
namespace fastlanes {
class b_ffor_prm {
public:
	template <typename T> static cmpr_fun_t ResolveCompressFunc(); //
	template <typename T> static de_cmpr_fun_t ResolveDecompressFunc();//
};
} // namespace fastlanes
#endif // FLS_COR_PRM_B_FFOR_PRM_HPP
