#include "fls/encoder/verifier.hpp"

namespace fastlanes {

template <typename PT>
void Verifier::decode_verify_print_save(
    TColDecoder<PT>& col_decoder, const PT* data, n_t n_vec, assert_fun_t<PT> assert_func, ExpT exp) {
	for (idx_t vec_idx {0}; vec_idx < n_vec; ++vec_idx) {
		Vec* res_fls_vec;
		res_fls_vec = col_decoder.Decompress();
		assert_func(res_fls_vec, data, vec_idx * CFG::VEC_SZ, exp);
	}
}

template void Verifier::decode_verify_print_save<i64_pt>(
    TColDecoder<i64_pt>& col_chunk, const i64_pt* vec, n_t n_vec, assert_fun_t<i64_pt> assert_func, ExpT exp);

template void Verifier::decode_verify_print_save<str_pt>(
    TColDecoder<str_pt>& col_chunk, const str_pt* vec, n_t n_vec, assert_fun_t<str_pt> assert_func, ExpT exp);

template void Verifier::decode_verify_print_save<dbl_pt>(
    TColDecoder<dbl_pt>& col_chunk, const dbl_pt* vec, n_t n_vec, assert_fun_t<dbl_pt> assert_func, ExpT exp);
} // namespace fastlanes