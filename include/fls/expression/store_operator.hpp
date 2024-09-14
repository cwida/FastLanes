#ifndef FLS_EXPRESSION_STORE_OPERATOR_HPP
#define FLS_EXPRESSION_STORE_OPERATOR_HPP

#include "fls/cor/lyt/buf.hpp"
#include "fls/table/chunk.hpp"

namespace fastlanes {
/*--------------------------------------------------------------------------------------------------------------------*/
class Buf;
class PhysicalExpr;
/*--------------------------------------------------------------------------------------------------------------------*/

struct store_vectorized_store_op {
	explicit store_vectorized_store_op(PhysicalExpr& physical_expr, Buf& buf);
	void store();

	Buf&                                    buf;
	vector<std::reference_wrapper<fls_vec>> vecs;
};

} // namespace fastlanes

#endif // FLS_EXPRESSION_STORE_OPERATOR_HPP
