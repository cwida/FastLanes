#ifndef FLS_EXPRESSION_PHYSICAL_EXPRESSION_HPP
#define FLS_EXPRESSION_PHYSICAL_EXPRESSION_HPP

#include "fls/expression/encoding_operator.hpp"
#include "fls/expression/predicate_operator.hpp"
#include "fls/expression/store_operator.hpp"

namespace fastlanes {
/*--------------------------------------------------------------------------------------------------------------------*/
class Buf;
/*--------------------------------------------------------------------------------------------------------------------*/

using physical_operator = variant<std::monostate,
                                  // predication
                                  up<predicate_eq_vector_constant_i64>,
                                  up<predicate_GT_i64>,
                                  up<predicate_LE_i64>,
                                  up<predicate_and_selection_ds>,
                                  // decoding
                                  // encoding
                                  up<enc_constant_op>,
                                  up<enc_zero_copy_op<i64_pt>>,
                                  // store
                                  up<store_vectorized_store_op>>;

using physical_operators = vector<physical_operator>;
using physical_operands  = vector<fls_vec>;

class PhysicalExpr {
public:
	physical_operators operators;
	physical_operands  operands;

public:
	void PointTo(n_t vec_n);
	void EnableVectorizedStore(Buf& buf);
};

} // namespace fastlanes

#endif // FLS_EXPRESSION_PHYSICAL_EXPRESSION_HPP
