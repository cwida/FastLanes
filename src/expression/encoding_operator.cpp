#include "fls/expression/encoding_operator.hpp"

namespace fastlanes {
/*--------------------------------------------------------------------------------------------------------------------*\
 * encoding operator
\*--------------------------------------------------------------------------------------------------------------------*/
template <typename PT>
enc_zero_copy_op<PT>::enc_zero_copy_op(const fls_vec& src) {
	visit(overloaded {[&](const up<TypedVector<PT>>& typed_vector) { typed_vector->should_be_stored = true; },
	                  [&](auto&) {
		                  FLS_UNREACHABLE();
	                  }},
	      src);
}

template struct enc_zero_copy_op<i64_pt>;
template struct enc_zero_copy_op<str_pt>;

} // namespace fastlanes
