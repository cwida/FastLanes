// ────────────────────────────────────────────────────────
// |                      FastLanes                       |
// ────────────────────────────────────────────────────────
// src/expression/dec_transpose_operator.cpp
// ────────────────────────────────────────────────────────
#include "fls/cfg/cfg.hpp"
#include "fls/common/alias.hpp"
#include "fls/common/assert.hpp"
#include "fls/common/common.hpp"
#include "fls/expression/data_type.hpp"
#include "fls/expression/physical_expression.hpp"
#include "fls/expression/rsum_operator.hpp"
#include "fls/expression/transpose_operator.hpp"
#include "fls/table/rowgroup.hpp"
#include "fls_gen/untranspose/untranspose.hpp"
#include <variant>

namespace fastlanes {
/*--------------------------------------------------------------------------------------------------------------------*\
 * dec_transpose_opr
\*--------------------------------------------------------------------------------------------------------------------*/
template <typename PT>
struct TransposeExprVisitor {
	explicit TransposeExprVisitor(dec_transpose_opr<PT>& opr)
	    : trapose_opr(opr) {
	}

	void operator()(const sp<dec_rsum_opr<PT>>& opr) {
		trapose_opr.transposed_data = opr->idxs;
		FLS_ASSERT_NOT_NULL_POINTER(trapose_opr.transposed_data)
	}
	void operator()(std::monostate& arg) {
		FLS_UNREACHABLE_WITH_TYPE(arg);
	}
	void operator()(const auto& arg) {
		FLS_UNREACHABLE_WITH_TYPE(arg);
	}

	dec_transpose_opr<PT>& trapose_opr;
};

template <typename PT>
dec_transpose_opr<PT>::dec_transpose_opr(PhysicalExpr&     physical_expr,
                                         const ColumnView& column_view,
                                         InterpreterState& state)
    : transposed_data(nullptr) {

	visit_dec(TransposeExprVisitor<PT> {*this}, physical_expr.operators.back());
}

template <typename PT>
void dec_transpose_opr<PT>::Materialize(n_t vec_idx, TypedCol<PT>& typed_col) {
	typed_col.data.resize(typed_col.data.size() + CFG::VEC_SZ);
	PT* untrasposed_data_p = typed_col.data.data() + (CFG::VEC_SZ * vec_idx);
	generated::untranspose::fallback::scalar::untranspose_i(transposed_data, untrasposed_data_p);
}

template struct dec_transpose_opr<u08_pt>;
template struct dec_transpose_opr<u16_pt>;
template struct dec_transpose_opr<u32_pt>;
template struct dec_transpose_opr<u64_pt>;
template struct dec_transpose_opr<i08_pt>;
template struct dec_transpose_opr<i16_pt>;
template struct dec_transpose_opr<i32_pt>;
template struct dec_transpose_opr<i64_pt>;

} // namespace fastlanes
