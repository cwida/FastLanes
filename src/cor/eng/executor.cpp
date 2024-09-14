#include "fls/cor/eng/executor.hpp"
#include "fls/cor/eng/compressor.hpp"
#include "fls/cor/eng/decompressor.hpp"
#include "fls/cor/eng/resolver.hpp"
#include "fls/cor/exp/rpn.hpp"
#include "fls/cor/lyt/vec.hpp"

namespace fastlanes {
template <typename T>
void Exe<T>::Execute(Vec& src_vec, Vec& des_vec, CompressState& compress_state) {
	compress_state.cur_src_buff = 0;
	compress_state.cur_des_buff = 0;

	for (size_t i = 0; i < rpn_p->prm_c; ++i) {
		// FLS_ASSERT_NOT_NULL_POINTER(cmpr_fun_arr[i]) //fixme

		cmpr_fun_arr[i](src_vec, des_vec, compress_state);
	}
}

// [fixme] static
template <typename T>
void Exe<T>::ResCmpr(sp<TExp<T>> exp) {
	rpn_p = exp->cmpr_rpn();

	for (size_t i = 0; i < rpn_p->prm_c; ++i) {
		cmpr_fun_arr[i] = resolver<T>::resolve_cmpr(rpn_p->prm_arr[i], rpn_p->typ_arr[i], exp);

		// FLS_ASSERT_NOT_NULL_POINTER(cmpr_fun_arr[i]) //fixme
	}
}

template <typename T>
void Exe<T>::ResDecmpr(sp<TExp<T>> exp) {
	rpn_p = exp->decmpr_rpn();
	for (size_t i = 0; i < rpn_p->prm_c; ++i) {
		de_cmpr_fun_arr[i] = resolver<T>::resolve_de_cmpr(rpn_p->prm_arr[i], rpn_p->typ_arr[i], exp);

		// FLS_ASSERT_NOT_NULL_POINTER(de_cmpr_fun_arr[i])
	}
}

template <typename T>
void Exe<T>::Execute(PageParam pg_params, VecParam vec_params, DecompressState& stt) {
	stt.cur_src_arr = rpn_p->src_buf_c - 1;
	stt.cur_des_arr = rpn_p->des_buf_c - 1;

	for (size_t i = rpn_p->prm_c; i > 0; --i) {
		// FLS_ASSERT_NOT_NULL_POINTER(de_cmpr_fun_arr[i - 1])

		de_cmpr_fun_arr[i - 1](pg_params, vec_params, stt);
	}
}

/*--------------------------------------------------------------------------------------------------------------------*\
+ Specialization
\*--------------------------------------------------------------------------------------------------------------------*/
FLS_ALL_CTS(Exe)
// CHECK
//{
// template class Exe<parquet::FixedLenByteArray>;
// template class Exe<parquet::Int96>;
// template class Exe<parquet::ByteArray>;
// }
} // namespace fastlanes