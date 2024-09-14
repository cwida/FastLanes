#include "fls/expression/expression_executor.hpp"
#include "fls/expression/physical_expression.hpp"
#include "iostream"

namespace fastlanes {

struct operator_visitor {
	void operator()(std::monostate&) { FLS_UNREACHABLE(); }
	void operator()(up<predicate_eq_vector_constant_i64>& opr) { opr->execute(); }
	void operator()(up<predicate_GT_i64>& opr) { opr->execute(); }
	void operator()(up<predicate_LE_i64>& opr) { opr->execute(); }
	void operator()(up<predicate_and_selection_ds>& opr) { opr->execute(); }
	// encoding
	template <typename PT>
	void operator()(up<enc_zero_copy_op<PT>>& eq_opr) {}
	void operator()(up<enc_constant_op>& op) {}
	void operator()(up<store_vectorized_store_op>& op) { op->store(); };
	void operator()(auto&) { FLS_IMPLEMENT_THIS(); }
};

void ExprExecutor::execute(PhysicalExpr& expr) {
	for (auto& expr_operator : expr.operators) {
		visit(operator_visitor {}, expr_operator);
	}
}
} // namespace fastlanes