#ifndef FLS_EXPRESSION_EXPRESSION_EXECUTOR_HPP
#define FLS_EXPRESSION_EXPRESSION_EXECUTOR_HPP

namespace fastlanes {
/*--------------------------------------------------------------------------------------------------------------------*/
class PhysicalExpr;
/*--------------------------------------------------------------------------------------------------------------------*/
class ExprExecutor {
public:
	static void execute(PhysicalExpr& expr);
};
} // namespace fastlanes

#endif // FLS_EXPRESSION_EXPRESSION_EXECUTOR_HPP
