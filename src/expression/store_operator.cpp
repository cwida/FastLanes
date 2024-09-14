#include "fls/expression/store_operator.hpp"
#include "fls/expression/physical_expression.hpp"

namespace fastlanes {
/*--------------------------------------------------------------------------------------------------------------------*\
 * store_vectorized_store_op
\*--------------------------------------------------------------------------------------------------------------------*/
store_vectorized_store_op::store_vectorized_store_op(PhysicalExpr& physical_expression, Buf& buf)
    : buf(buf) {
	for (auto& operand : physical_expression.operands) {
		visit(overloaded {[&]<typename PT>(up<TypedVector<PT>>& typed_vector) {
			                  if (typed_vector->should_be_stored) { vecs.push_back(std::ref(operand)); };
		                  },
		                  [&](auto&) {
			                  FLS_UNREACHABLE()
		                  }},
		      operand);
	}
}

/*--------------------------------------------------------------------------------------------------------------------*\
 * store
\*--------------------------------------------------------------------------------------------------------------------*/
void store_vectorized_store_op::store() {
	for (auto& persistant_vec : vecs) {
		visit(overloaded {//
		                  [&]<typename PT>(up<TypedVector<PT>>& typed_vector) {
			                  buf.Append(typed_vector->m_data, typed_vector->Size());
		                  },
		                  [&](auto&) {
			                  FLS_UNREACHABLE()
		                  }},
		      persistant_vec.get());
	}
}
} // namespace fastlanes