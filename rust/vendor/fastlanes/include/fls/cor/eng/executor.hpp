#ifndef FLS_COR_ENG_EXECUTOR_HPP
#define FLS_COR_ENG_EXECUTOR_HPP

#include "fls/common/common.hpp"
#include "fls/cor/fun.hpp"

namespace fastlanes {
class RPN;
class Vec;
template <typename T>
class TExp;

constexpr inline n_t N_FUNCTIONS = 5;

template <typename T>
class Exe {
public:
	Exe() = default; //
public:
	void ResCmpr(sp<TExp<T>>& exp);                                               //
	void ResDecmpr(sp<TExp<T>>& exp);                                             //
	void Execute(Vec& src_vec, Vec& des_vec, CompressState& compress_state);      //
	void Execute(PageParam pg_params, VecParam vec_params, DecompressState& stt); //
public:
	cmpr_fun_t    cmpr_fun_arr[N_FUNCTIONS];    //
	de_cmpr_fun_t de_cmpr_fun_arr[N_FUNCTIONS]; //
	const RPN*    rpn_p;                        //
};
} // namespace fastlanes
#endif // FLS_COR_ENG_EXECUTOR_HPP
