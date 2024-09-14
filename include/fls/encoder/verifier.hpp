#ifndef FLS_ENCODER_VERIFIER_HPP
#define FLS_ENCODER_VERIFIER_HPP

#include "fls/common/alias.hpp"
#include "fls/encoder/assert_eq.hpp"

namespace fastlanes {
template <typename PT>
class TColDecoder;

class Verifier {
public:
	template <typename PT>
	static void decode_verify_print_save(
	    TColDecoder<PT>& col_decoder, const PT* data_p, n_t n_vec, assert_fun_t<PT> assert_func, ExpT exp);
};
} // namespace fastlanes

#endif // FLS_ENCODER_VERIFIER_HPP
