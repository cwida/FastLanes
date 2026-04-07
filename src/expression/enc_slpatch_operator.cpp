// ────────────────────────────────────────────────────────
// |                      FastLanes                       |
// ────────────────────────────────────────────────────────
// src/expression/enc_slpatch_operator.cpp
// ────────────────────────────────────────────────────────
#include "fls/cfg/cfg.hpp"
#include "fls/common/alias.hpp"
#include "fls/common/assert.hpp"
#include "fls/common/common.hpp"
#include "fls/expression/analyze_operator.hpp"
#include "fls/expression/interpreter.hpp"
#include "fls/expression/physical_expression.hpp"
#include "fls/expression/slpatch_operator.hpp"
#include "fls/reader/segment.hpp"
#include "fls/std/variant.hpp"
#include "fls/std/vector.hpp"
#include <utility>
#include <variant>

namespace fastlanes {
/*--------------------------------------------------------------------------------------------------------------------*\
* enc slpatch opr
\*--------------------------------------------------------------------------------------------------------------------*/
template <typename PT>
enc_slpatch_opr<PT>::enc_slpatch_opr(const PhysicalExpr& expr,
                                     const col_pt&       col,
                                     ColumnDescriptorT&  column_descriptor,
                                     InterpreterState&   state) {

	visit_enc(overloaded {
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

} // namespace fastlanes
