#ifndef FLS_COR_PRM_ALP_PRM_HPP
#define FLS_COR_PRM_ALP_PRM_HPP

#include "fls/cor/fun.hpp"

// clang-format off
namespace fastlanes {
class alp_prm {
public:
	template <typename T> static cmpr_fun_t ResolveCompressFunc(); //
	template <typename T> static de_cmpr_fun_t ResolveDecompressFunc();//
};

struct alp_mtd_t{
uint8_t bw;
uint8_t exp;
uint8_t fac;
};
static_assert(sizeof(alp_mtd_t) == 3);

} // namespace fastlanes
#endif // FLS_COR_PRM_ALP_PRM_HPP
