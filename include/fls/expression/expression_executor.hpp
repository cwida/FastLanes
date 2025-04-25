#ifndef FLS_EXPRESSION_EXPRESSION_EXECUTOR_HPP
#define FLS_EXPRESSION_EXPRESSION_EXECUTOR_HPP

#include "fls/common/alias.hpp"

namespace fastlanes {
/*--------------------------------------------------------------------------------------------------------------------*/
class PhysicalExpr;
/*--------------------------------------------------------------------------------------------------------------------*/
class ExprExecutor {
public:
	//
	static void CountOperator(PhysicalExpr& expr);
	//
	static void execute(PhysicalExpr& expr, n_t vec_idx);
	//
	static void smart_execute(PhysicalExpr& expr, n_t vec_idx);
	//
	ExprExecutor() = default;
};
} // namespace fastlanes

#endif // FLS_EXPRESSION_EXPRESSION_EXECUTOR_HPP
