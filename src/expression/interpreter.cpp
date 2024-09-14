#include "fls/expression/interpreter.hpp"
#include "fls/common/common.hpp"
#include "fls/expression/physical_expression.hpp"
#include <fls/expression/new_rpn.hpp>
#include <fls/table/rowgroup.hpp>

namespace fastlanes {

template <typename PT>
void add_zero_copy_opr(PhysicalExpr&   physical_expr,
                       const Rowgroup& rowgroup,
                       const Operator& opr,
                       const Operand&  operand) {

	// add operand
	physical_expr.operands.emplace_back(make_unique<TypedVector<PT>>(rowgroup.internal_rowgroup[operand.col_idx]));
	// add operator
	physical_expr.operators.emplace_back(make_unique<enc_zero_copy_op<PT>>(physical_expr.operands.back()));
}

void add_zero_copy_expr(PhysicalExpr&   physical_expr,
                        const Rowgroup& rowgroup,
                        const Operator& opr,
                        const Operand&  operand) {
	switch (opr.data_type) {
	case DataType::INT64: {
		add_zero_copy_opr<i64_pt>(physical_expr, rowgroup, opr, operand);
		break;
	}
	case DataType::STR: {
		// add_zero_copy_opr<str_pt>(physical_expr, rowgroup, opr, operand);
		break;
	}
	default:
		FLS_UNREACHABLE()
	}
}

up<PhysicalExpr> Interpreter::Encoding::Interpret(const NewRPN& rpn, const Rowgroup& rowgroup) {
	// return
	auto physical_expr = make_unique<PhysicalExpr>();

	for (const auto& opr : rpn.operators) {
		switch (opr.operator_type) {
		case OperatorType::ZERO_COPY: {
			add_zero_copy_expr(*physical_expr, rowgroup, opr, rpn.operands[0]);
			break;
		}
		case OperatorType::CONSTANT: {
			physical_expr->operators.emplace_back(make_unique<enc_constant_op>());
			break;
		}
		case OperatorType::EQUAL: {
			// FLS_IMPLEMENT_THIS();
			break;
		}
		case OperatorType::DICT: {
			// FLS_IMPLEMENT_THIS();
			break;
		}
		case OperatorType::SUB_EXPRESSION: {
			// FLS_IMPLEMENT_THIS();
			break;
		}
		case OperatorType::FIXME: {
			// FLS_IMPLEMENT_THIS();
			break;
		}

		default:
			FLS_UNREACHABLE();
		}
	}

	return physical_expr;
}

template <typename PT>
void add_zero_copy_decoding_opr(PhysicalExpr& physical_expr, const Operator& opr) {

	// add operand
	// physical_expr.operands.emplace_back(make_unique<TypedVector<PT>>(rowgroup.internal_rowgroup[operand.col_idx]));
	// add operator
	physical_expr.operators.emplace_back(make_unique<enc_zero_copy_op<PT>>(physical_expr.operands.back()));
}

void add_zero_copy_decoding_expr(PhysicalExpr& physical_expr, const Operator& opr, Interpreter::State state) {
	switch (opr.data_type) {
	case DataType::INT64: {
		add_zero_copy_decoding_opr<i64_pt>(physical_expr, opr);
		break;
	}
	case DataType::STR: {
		// add_zero_copy_opr<str_pt>(physical_expr, rowgroup, opr, operand);
		break;
	}
	default:
		FLS_UNREACHABLE()
	}

	//
	state.cur_opr = state.cur_opr + 1;
}

void Interpreter::Decoding::Interpret(const NewRPN& rpn, PhysicalExpr& physical_expr, State state) {

	for (const auto& opr : rpn.operators) {
		switch (opr.operator_type) {
		case OperatorType::ZERO_COPY: {
			add_zero_copy_decoding_expr(physical_expr, opr, state);
			break;
		}
		case OperatorType::CONSTANT: {
			break;
		}
		case OperatorType::EQUAL: {
			// FLS_IMPLEMENT_THIS();
			break;
		}
		case OperatorType::DICT: {
			// FLS_IMPLEMENT_THIS();
			break;
		}
		case OperatorType::SUB_EXPRESSION: {
			// FLS_IMPLEMENT_THIS();
			break;
		}
		case OperatorType::FIXME: {
			// FLS_IMPLEMENT_THIS();
			break;
		}

		default:
			FLS_UNREACHABLE();
		}
	}
};
} // namespace fastlanes