#ifndef FLS_EXPRESSION_ENCODING_OPERATOR_HPP
#define FLS_EXPRESSION_ENCODING_OPERATOR_HPP

#include "fls/table/chunk.hpp"

namespace fastlanes {

struct enc_constant_op {
	enc_constant_op() = default;
};

template <typename PT>
struct enc_zero_copy_op {
	explicit enc_zero_copy_op(const fls_vec& src);
};

} // namespace fastlanes

#endif // FLS_EXPRESSION_ENCODING_OPERATOR_HPP
