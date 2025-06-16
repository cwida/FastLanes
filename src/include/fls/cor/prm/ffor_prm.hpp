#ifndef FLS_COR_PRM_FFOR_PRM_HPP
#define FLS_COR_PRM_FFOR_PRM_HPP

#include "fls/common/common.hpp"
#include "fls/cor/fun.hpp"
#include <climits>

namespace fastlanes {
/*--------------------------------------------------------------------------------------------------------------------*/
template <typename T>
class Histogram;

/*--------------------------------------------------------------------------------------------------------------------*/

template <typename T>
class Params {
public:
	n_t size() {
		return (1024 * bw / CHAR_BIT) + exc_c * sizeof(T);
	} //
public:
	bw_t      bw;    //
	T         base;  //
	vec_idx_t exc_c; //
};

template <typename T>
class ffor_prm {
public:
	static cmpr_fun_t    ResolveCompressFunc();
	static de_cmpr_fun_t ResolveDecompressFunc();
	static cmpr_fun_t    ResolveAnalyzeFunc();
	static cmpr_fun_t    ResolvePatchAnalyzeFunc();
	static n_t           vec_sz(uint8_t bw);
	static bool          is_exception(Params<T> params, T val);
	static Params<T>     find_best_params(Histogram<T>& histogram, n_t idx);
};
} // namespace fastlanes
#endif // FLS_COR_PRM_FFOR_PRM_HPP
