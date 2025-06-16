#include "fls/expression/slpatch_operator.hpp"
#include "fls/cfg/cfg.hpp"
#include "fls/cor/lyt/buf.hpp"
#include "fls/expression/analyze_operator.hpp"
#include "fls/expression/decoding_operator.hpp"
#include "fls/expression/encoding_operator.hpp"
#include "fls/expression/interpreter.hpp"
#include "fls/expression/physical_expression.hpp"
#include "fls/expression/slpatch_operator.hpp"
#include "fls/primitive/copy/fls_copy.hpp"
#include "fls/reader/column_view.hpp"
#include "fls/reader/segment.hpp"
#include "fls/std/type_traits.hpp"

namespace fastlanes {
/*--------------------------------------------------------------------------------------------------------------------*\
* enc slpatch opr
\*--------------------------------------------------------------------------------------------------------------------*/
template <typename PT>
enc_slpatch_opr<PT>::enc_slpatch_opr(const PhysicalExpr& expr,
                                     const col_pt&       col,
                                     ColumnDescriptorT&  column_descriptor,
                                     InterpreterState&   state) {

	visit(overloaded {
	          [&](const sp<enc_analyze_opr<PT, true>>& opr) {
		          n_exceptions_p    = &opr->n_exceptions;
		          exceptions        = opr->exceptions;
		          exception_pos_arr = opr->exception_pos_arr;
	          },
	          [&](std::monostate&) { FLS_UNREACHABLE(); },
	          [&](auto& arg) { FLS_UNREACHABLE_WITH_TYPE(arg); },
	      },
	      expr.operators.back());

	n_exceptions_segment        = make_unique<Segment>();
	exceptions_position_segment = make_unique<Segment>();
	exceptions_segment          = make_unique<Segment>();

	auto& [operator_tokens, operand_tokens] = *column_descriptor.encoding_rpn;

	operand_tokens.emplace_back(state.cur_operand++);
	operand_tokens.emplace_back(state.cur_operand++);
	operand_tokens.emplace_back(state.cur_operand++);
}

template <typename PT>
void enc_slpatch_opr<PT>::Store() {
	FLS_ASSERT_NOT_NULL_POINTER(n_exceptions_p)
	FLS_ASSERT_NOT_NULL_POINTER(exception_pos_arr)
	FLS_ASSERT_NOT_NULL_POINTER(exceptions)

	const auto n_exceptions = *n_exceptions_p;

	n_exceptions_segment->Flush(n_exceptions_p, sizeof(vec_idx_t));
	exceptions_position_segment->Flush(exception_pos_arr, sizeof(vec_idx_t) * n_exceptions);
	exceptions_segment->Flush(exceptions, sizeof(PT) * n_exceptions);
}
template <typename PT>
void enc_slpatch_opr<PT>::MoveSegments(vector<up<Segment>>& segments) {
	segments.push_back(std::move(exceptions_segment));
	segments.push_back(std::move(exceptions_position_segment));
	segments.push_back(std::move(n_exceptions_segment));
}

template struct enc_slpatch_opr<u64_pt>;
template struct enc_slpatch_opr<u32_pt>;
template struct enc_slpatch_opr<u16_pt>;
template struct enc_slpatch_opr<u08_pt>;
template struct enc_slpatch_opr<i64_pt>;
template struct enc_slpatch_opr<i32_pt>;
template struct enc_slpatch_opr<i16_pt>;
template struct enc_slpatch_opr<i08_pt>;
/*--------------------------------------------------------------------------------------------------------------------*\
 * dec slpatch opr
\*--------------------------------------------------------------------------------------------------------------------*/
template <typename PT>
struct SLPatchExprVisitor {
	explicit SLPatchExprVisitor(dec_slpatch_opr<PT>& this_opr)
	    : this_opr(this_opr) {
	}

	void operator()(const sp<dec_unffor_opr<PT>>& opr) {
		this_opr.data = opr->unffored_data;
	}
	template <typename T = PT>
	requires(!std::is_same_v<T, std::make_unsigned_t<T>>) void
	operator()(const sp<dec_unffor_opr<std::make_unsigned_t<PT>>>& opr) {
		this_opr.data = reinterpret_cast<PT*>(opr->unffored_data);
	}
	void operator()(std::monostate& arg) {
		FLS_UNREACHABLE_WITH_TYPE(arg);
	}
	void operator()(const auto& arg) {
		FLS_UNREACHABLE_WITH_TYPE(arg);
	}

	dec_slpatch_opr<PT>& this_opr;
};

template <typename PT>
dec_slpatch_opr<PT>::dec_slpatch_opr(PhysicalExpr&     physical_expr,
                                     const ColumnView& column_view,
                                     InterpreterState& state)
    : exceptions_segment(
          column_view.GetSegment(column_view.column_descriptor.encoding_rpn->operand_tokens[state.cur_operand - 2]))
    , exceptions_position_segment(
          column_view.GetSegment(column_view.column_descriptor.encoding_rpn->operand_tokens[state.cur_operand - 1]))
    , n_exceptions_segment(
          column_view.GetSegment(column_view.column_descriptor.encoding_rpn->operand_tokens[state.cur_operand - 0])) {
	state.cur_operand = state.cur_operand - 3;

	visit(SLPatchExprVisitor {*this}, physical_expr.operators.back());
}

template <typename PT>
void dec_slpatch_opr<PT>::PointTo(const n_t vec_n) {
	exceptions_segment.PointTo(vec_n);
	exceptions_position_segment.PointTo(vec_n);
	n_exceptions_segment.PointTo(vec_n);
}

template <typename PT>
void dec_slpatch_opr<PT>::Patch(n_t vec_idx) {
	PointTo(vec_idx);

	auto* exc_arr      = reinterpret_cast<PT*>(exceptions_segment.data);
	auto* exc_pos_arr  = reinterpret_cast<uint16_t*>(exceptions_position_segment.data);
	auto  n_exceptions = *reinterpret_cast<uint16_t*>(n_exceptions_segment.data);

	FLS_ASSERT_CORRECT_POS(n_exceptions)

	for (auto val_idx {0}; val_idx < n_exceptions; ++val_idx) {
		auto next_pos  = exc_pos_arr[val_idx];
		data[next_pos] = exc_arr[val_idx];
	}
}

template <typename PT>
void dec_slpatch_opr<PT>::Materialize(n_t vec_idx, TypedCol<PT>& typed_col) {
	typed_col.data.resize(typed_col.data.size() + CFG::VEC_SZ);
	PT* materialized_data_p = typed_col.data.data() + (CFG::VEC_SZ * vec_idx);
	copy(data, materialized_data_p);
}

template struct dec_slpatch_opr<u64_pt>;
template struct dec_slpatch_opr<u32_pt>;
template struct dec_slpatch_opr<u16_pt>;
template struct dec_slpatch_opr<u08_pt>;
template struct dec_slpatch_opr<i64_pt>;
template struct dec_slpatch_opr<i32_pt>;
template struct dec_slpatch_opr<i16_pt>;
template struct dec_slpatch_opr<i08_pt>;
} // namespace fastlanes
