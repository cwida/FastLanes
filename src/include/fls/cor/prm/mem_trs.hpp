#ifndef FLS_COR_PRM_MEM_TRS_HPP
#define FLS_COR_PRM_MEM_TRS_HPP

#include "fls/cor/fun.hpp"

// clang-format off
namespace fastlanes {
class mem_trs {
public:
	template <typename T> static cmpr_fun_t ResolveCompressFunc();
	template <typename T> static de_cmpr_fun_t ResolveDecompressFunc();
};
} // namespace fastlanes
#endif // FLS_COR_PRM_MEM_TRS_HPP
