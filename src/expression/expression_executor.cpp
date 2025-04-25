#include "fls/expression/expression_executor.hpp"
#include "fls/expression/alp_expression.hpp"
#include "fls/expression/analyze_operator.hpp"
#include "fls/expression/decoding_operator.hpp"
#include "fls/expression/encoding_operator.hpp"
#include "fls/expression/frequency_operator.hpp"
#include "fls/expression/fsst12_expression.hpp"
#include "fls/expression/fsst_expression.hpp"
#include "fls/expression/null_operator.hpp"
#include "fls/expression/physical_expression.hpp"
#include "fls/expression/predicate_operator.hpp"
#include "fls/expression/rle_expression.hpp"
#include "fls/expression/rsum_operator.hpp"
#include "fls/expression/scan_operator.hpp"
#include "fls/expression/slpatch_operator.hpp"
#include "fls/expression/transpose_operator.hpp"

namespace fastlanes {

struct operator_visitor {
	operator_visitor(n_t& vec_idx)
	    : vec_idx(vec_idx) {
	}
	// predicate
	void operator()(sp<predicate_eq_vector_constant_i64>& opr) {
		opr->execute();
	}
	void operator()(sp<predicate_GT_i64>& opr) {
		opr->execute();
	}
	void operator()(sp<predicate_LE_i64>& opr) {
		opr->execute();
	}
	void operator()(sp<predicate_and_selection_ds>& opr) {
		opr->execute();
	}

	// encoding
	template <typename PT>
	void operator()(sp<enc_uncompressed_opr<PT>>& opr) {
		opr->Copy();
	}
	template <typename PT>
	void operator()(sp<enc_scan_opr<PT>>& opr) {
		opr->Copy();
	}

	void operator()(sp<enc_constant_opr>& op) {
	}
	void operator()(sp<enc_struct_opr>& op) {
		for (auto& expr_operator : op->internal_exprs) {
			ExprExecutor::execute(*expr_operator, vec_idx);
		}
	}
	void operator()(sp<enc_fls_str_uncompressed_op>& opr) {
		opr->Copy();
	}
	template <typename PT>
	void operator()(sp<enc_ffor_opr<PT>>& opr) {
		opr->ffor();
	}

	template <typename KEY_PT, typename INDEX_PT>
	void operator()(sp<enc_dict_map_opr<KEY_PT, INDEX_PT>>& opr) {
		opr->Map();
	}

	// decoding
	template <typename PT>
	void operator()(sp<dec_uncompressed_opr<PT>>& op) {};
	template <typename PT>
	void operator()(sp<dec_unffor_opr<PT>>& op) {
		op->Unffor(vec_idx);
	};
	template <typename PT>
	void operator()(sp<dec_constant_opr<PT>>& op) {
	}
	void operator()(sp<PhysicalExpr>& op) {
	}
	void operator()(sp<dec_struct_opr>& opr) {
		for (auto& expr_operator : opr->internal_exprs) {
			ExprExecutor::execute(*expr_operator, vec_idx);
		}
	}
	void operator()(sp<dec_fls_str_uncompressed_opr>& op) {};
	void operator()(sp<dec_constant_str_opr>& op) {
	}

	template <typename PT>
	void operator()(sp<dec_alp_opr<PT>>& opr) {
		opr->Decode(vec_idx);
	}

	template <typename PT>
	void operator()(sp<enc_alp_opr<PT>>& opr) {
		opr->Encode();
	}

	template <typename PT>
	void operator()(sp<dec_alp_rd_opr<PT>>& opr) {
		opr->Decode(vec_idx);
	}

	template <typename PT>
	void operator()(sp<enc_alp_rd_opr<PT>>& opr) {
		opr->Encode();
	}

	// FSST
	void operator()(sp<enc_fsst_opr>& opr) {
		opr->Encode();
	}
	void operator()(sp<dec_fsst_opr>& opr) {
	}
	void operator()(sp<enc_fsst12_opr>& opr) {
		opr->Encode();
	}
	void operator()(sp<dec_fsst12_opr>& opr) {
	}

	// DICT
	template <typename KEY_PT>
	void operator()(sp<enc_dict_opr<KEY_PT>>& opr) {
	}
	template <typename KEY_PT, typename INDEX_PT>
	void operator()(sp<dec_dict_opr<KEY_PT, INDEX_PT>>& opr) {
	}

	// DICT
	void operator()(sp<enc_fsst_dict_opr>& opr) {
	}
	void operator()(sp<enc_fsst12_dict_opr>& opr) {
	}
	template <typename INDEX_PT>
	void operator()(sp<dec_fsst_dict_opr<INDEX_PT>>& opr) {
	}
	template <typename INDEX_PT>
	void operator()(sp<dec_fsst12_dict_opr<INDEX_PT>>& opr) {
	}

	// RLE
	template <typename KEY_PT, typename INDEX_PT>
	void operator()(sp<enc_rle_map_opr<KEY_PT, INDEX_PT>>& opr) {
		opr->Map();
	}
	template <typename KEY_PT, typename INDEX_PT>
	void operator()(sp<dec_rle_map_opr<KEY_PT, INDEX_PT>>& opr) {
	}

	template <typename PT>
	void operator()(sp<enc_transpose_opr<PT>>& opr) {
		opr->Transpose();
	}

	//
	template <typename PT>
	void operator()(sp<enc_rsum_opr<PT>>& opr) {
		opr->Rsum();
	}
	template <typename PT>
	void operator()(sp<dec_rsum_opr<PT>>& opr) {
		opr->Unrsum(vec_idx);
	}
	// scan
	template <typename PT>
	void operator()(sp<dec_scan_opr<PT>>& opr) {
		opr->Scan(vec_idx);
	}
	//
	template <typename PT>
	void operator()(sp<dec_transpose_opr<PT>>& opr) {
	}
	//
	template <typename PT>
	void operator()(sp<enc_slpatch_opr<PT>>& opr) {
		opr->Store();
	}
	template <typename PT>
	void operator()(sp<dec_slpatch_opr<PT>>& opr) {
		opr->Patch(vec_idx);
	}
	template <typename PT>
	void operator()(sp<enc_null_opr<PT>>& opr) {
		opr->Store();
	}
	template <typename PT>
	void operator()(sp<dec_null_opr<PT>>& opr) {
	}
	//
	template <typename PT, bool USE_PATCHING>
	void operator()(sp<enc_analyze_opr<PT, USE_PATCHING>>& opr) {
		opr->Analyze();
	}
	//
	template <typename PT>
	void operator()(sp<dec_frequency_opr<PT>>& opr) {
		opr->Decode(vec_idx);
	}
	template <typename PT>
	void operator()(sp<enc_frequency_opr<PT>>& opr) {
		opr->Encode();
	}
	void operator()(sp<dec_frequency_str_opr>& opr) {
		opr->Decode();
	}
	void operator()(sp<enc_frequency_str_opr>& opr) {
		opr->Encode();
	}
	//
	template <typename PT>
	void operator()(sp<enc_cross_rle_opr<PT>>& opr) {
	}
	template <typename PT>
	void operator()(sp<dec_cross_rle_opr<PT>>& opr) {
	}
	//
	void operator()(std::monostate&) {
		FLS_UNREACHABLE();
	}
	void operator()(auto& arg) {
		FLS_UNREACHABLE_WITH_TYPE(arg);
	}

	n_t& vec_idx;
};

void ExprExecutor::execute(PhysicalExpr& expr, n_t vec_idx) {
	for (auto& expr_operator : expr.operators) {
		visit(operator_visitor {vec_idx}, expr_operator);
	}
}

void ExprExecutor::smart_execute(PhysicalExpr& expr, n_t vec_idx) {
	const auto n_operators = expr.n_active_operators;
	FLS_ASSERT_LE(n_operators, expr.operators.size());

	for (n_t operator_idx {0}; operator_idx < n_operators; operator_idx++) {
		visit(operator_visitor {vec_idx}, expr.operators[operator_idx]);
	}
}

/*--------------------------------------------------------------------------------------------------------------------*\
 * CountOperator
\*--------------------------------------------------------------------------------------------------------------------*/
struct operator_counter_visitor {
	operator_counter_visitor(PhysicalExpr& physical_expression)
	    : physical_expr(physical_expression) {
	}
	// predicate
	void operator()(sp<predicate_eq_vector_constant_i64>& opr) {
		physical_expr.n_active_operators++;
	}
	void operator()(sp<predicate_GT_i64>& opr) {
		physical_expr.n_active_operators++;
	}
	void operator()(sp<predicate_LE_i64>& opr) {
		physical_expr.n_active_operators++;
	}
	void operator()(sp<predicate_and_selection_ds>& opr) {
		physical_expr.n_active_operators++;
	}

	// encoding
	template <typename PT>
	void operator()(sp<enc_uncompressed_opr<PT>>& opr) {
		physical_expr.n_active_operators++;
	}
	template <typename PT>
	void operator()(sp<enc_scan_opr<PT>>& opr) {
		physical_expr.n_active_operators++;
	}
	void operator()(sp<enc_constant_opr>& op) {
	}

	void operator()(sp<enc_struct_opr>& op) {
		for (auto& expr_operator : op->internal_exprs) {
			ExprExecutor::CountOperator(*expr_operator);
		}

		physical_expr.n_active_operators = 1;
	}
	void operator()(sp<enc_fls_str_uncompressed_op>& opr) {
		physical_expr.n_active_operators++;
	}
	template <typename PT>
	void operator()(sp<enc_ffor_opr<PT>>& opr) {
		physical_expr.n_active_operators++;
	}

	template <typename KEY_PT, typename INDEX_PT>
	void operator()(sp<enc_dict_map_opr<KEY_PT, INDEX_PT>>& opr) {
		physical_expr.n_active_operators++;
	}

	// decoding
	template <typename PT>
	void operator()(sp<dec_uncompressed_opr<PT>>& op) {};
	template <typename PT>
	void operator()(sp<dec_unffor_opr<PT>>& op) {
		physical_expr.n_active_operators++;
	};
	template <typename PT>
	void operator()(sp<dec_constant_opr<PT>>& op) {
	}
	void operator()(sp<PhysicalExpr>& op) {
	}
	void operator()(sp<dec_struct_opr>& opr) {
		for (auto& expr_operator : opr->internal_exprs) {
			ExprExecutor::CountOperator(*expr_operator);
		}

		physical_expr.n_active_operators = 1;
	}
	void operator()(sp<dec_fls_str_uncompressed_opr>& op) {};
	void operator()(sp<dec_constant_str_opr>& op) {
	}

	template <typename PT>
	void operator()(sp<dec_alp_opr<PT>>& opr) {
		physical_expr.n_active_operators++;
	}

	template <typename PT>
	void operator()(sp<enc_alp_opr<PT>>& opr) {
		physical_expr.n_active_operators++;
	}

	template <typename PT>
	void operator()(sp<dec_alp_rd_opr<PT>>& opr) {
		physical_expr.n_active_operators++;
	}

	template <typename PT>
	void operator()(sp<enc_alp_rd_opr<PT>>& opr) {
		physical_expr.n_active_operators++;
	}

	// FSST
	void operator()(sp<enc_fsst_opr>& opr) {
		physical_expr.n_active_operators++;
	}
	void operator()(sp<dec_fsst_opr>& opr) {
	}
	void operator()(sp<enc_fsst12_opr>& opr) {
		physical_expr.n_active_operators++;
	}
	void operator()(sp<dec_fsst12_opr>& opr) {
	}

	// DICT
	template <typename KEY_PT>
	void operator()(sp<enc_dict_opr<KEY_PT>>& opr) {
	}
	template <typename KEY_PT, typename INDEX_PT>
	void operator()(sp<dec_dict_opr<KEY_PT, INDEX_PT>>& opr) {
	}

	// DICT
	void operator()(sp<enc_fsst_dict_opr>& opr) {
	}
	void operator()(sp<enc_fsst12_dict_opr>& opr) {
	}
	template <typename INDEX_PT>
	void operator()(sp<dec_fsst_dict_opr<INDEX_PT>>& opr) {
	}
	template <typename INDEX_PT>
	void operator()(sp<dec_fsst12_dict_opr<INDEX_PT>>& opr) {
	}

	// RLE
	template <typename KEY_PT, typename INDEX_PT>
	void operator()(sp<enc_rle_map_opr<KEY_PT, INDEX_PT>>& opr) {
		physical_expr.n_active_operators++;
	}
	template <typename KEY_PT, typename INDEX_PT>
	void operator()(sp<dec_rle_map_opr<KEY_PT, INDEX_PT>>& opr) {
	}

	template <typename PT>
	void operator()(sp<enc_transpose_opr<PT>>& opr) {
		physical_expr.n_active_operators++;
	}

	//
	template <typename PT>
	void operator()(sp<enc_rsum_opr<PT>>& opr) {
		physical_expr.n_active_operators++;
	}
	template <typename PT>
	void operator()(sp<dec_rsum_opr<PT>>& opr) {
		physical_expr.n_active_operators++;
	}
	// scan
	template <typename PT>
	void operator()(sp<dec_scan_opr<PT>>& opr) {
		physical_expr.n_active_operators++;
	}
	//
	template <typename PT>
	void operator()(sp<dec_transpose_opr<PT>>& opr) {
	}
	//
	template <typename PT>
	void operator()(sp<enc_slpatch_opr<PT>>& opr) {
		physical_expr.n_active_operators++;
	}
	template <typename PT>
	void operator()(sp<dec_slpatch_opr<PT>>& opr) {
		physical_expr.n_active_operators++;
	}
	template <typename PT>
	void operator()(sp<enc_null_opr<PT>>& opr) {
		physical_expr.n_active_operators++;
	}
	template <typename PT>
	void operator()(sp<dec_null_opr<PT>>& opr) {
	}
	//
	template <typename PT, bool USE_PATCHING>
	void operator()(sp<enc_analyze_opr<PT, USE_PATCHING>>& opr) {
		physical_expr.n_active_operators++;
	}
	//
	template <typename PT>
	void operator()(sp<dec_frequency_opr<PT>>& opr) {
		physical_expr.n_active_operators++;
	}
	template <typename PT>
	void operator()(sp<enc_frequency_opr<PT>>& opr) {
		physical_expr.n_active_operators++;
	}
	void operator()(sp<dec_frequency_str_opr>& opr) {
		physical_expr.n_active_operators++;
	}
	void operator()(sp<enc_frequency_str_opr>& opr) {
		physical_expr.n_active_operators++;
	}
	//
	template <typename PT>
	void operator()(sp<enc_cross_rle_opr<PT>>& opr) {
	}
	template <typename PT>
	void operator()(sp<dec_cross_rle_opr<PT>>& opr) {
	}
	//
	void operator()(std::monostate&) {
		FLS_UNREACHABLE();
	}
	void operator()(auto& arg) {
		FLS_UNREACHABLE_WITH_TYPE(arg);
	}

	PhysicalExpr& physical_expr;
};

void ExprExecutor::CountOperator(PhysicalExpr& expr) {
	for (auto& expr_operator : expr.operators) {
		visit(operator_counter_visitor {expr}, expr_operator);
	}
}

} // namespace fastlanes