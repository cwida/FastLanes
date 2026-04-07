// ────────────────────────────────────────────────────────
// |                      FastLanes                       |
// ────────────────────────────────────────────────────────
// src/expression/enc_rsum_operator.cpp
// ────────────────────────────────────────────────────────
#include "fls/cfg/cfg.hpp"
#include "fls/common/alias.hpp"
#include "fls/common/common.hpp"
#include "fls/expression/encoding_operator.hpp"
#include "fls/expression/interpreter.hpp"
#include "fls/expression/physical_expression.hpp"
#include "fls/expression/rsum_operator.hpp"
#include "fls/expression/transpose_operator.hpp"
#include "fls/reader/segment.hpp"
#include "fls/std/variant.hpp"
#include "fls/table/rowgroup.hpp"
#include "fls_gen/unrsum/unrsum.hpp"
#include <utility>
#include <variant>

namespace fastlanes {
/*--------------------------------------------------------------------------------------------------------------------*\
 * enc rsum opr
\*--------------------------------------------------------------------------------------------------------------------*/
template <typename PT>
enc_rsum_opr<PT>::enc_rsum_opr(const PhysicalExpr& expr,
                               const col_pt&       col,
                               ColumnDescriptorT&  column_descriptor,
                               InterpreterState&   state) {

	visit_enc(overloaded {
	              [&](const sp<enc_scan_opr<PT>>& opr) { data = opr->data; },
	              [&](const sp<enc_transpose_opr<PT>>& opr) { data = opr->transposed_data; },
	              [&](std::monostate&) { FLS_UNREACHABLE(); },
	              [&](auto& arg) { FLS_UNREACHABLE_WITH_TYPE(arg); },
	          },
	          expr.operators[state.cur_operator++]);

	auto& [operator_tokens, operand_tokens] = *column_descriptor.encoding_rpn;
	operand_tokens.emplace_back(state.cur_operand++);

	bases_segment = make_unique<Segment>();
}

template <typename PT>
void enc_rsum_opr<PT>::Rsum() {
	::generated::unrsum::fallback::scalar::unrsum(data, deltas);

	bases_segment->Flush(data, CFG::UNIFIED_TRANSPOSED::BASES_SIZE);
};

template <typename PT>
void enc_rsum_opr<PT>::MoveSegments(vector<up<Segment>>& segments) {
	segments.push_back(std::move(bases_segment));
}

template struct enc_rsum_opr<u08_pt>;
template struct enc_rsum_opr<u16_pt>;
template struct enc_rsum_opr<u32_pt>;
template struct enc_rsum_opr<u64_pt>;
template struct enc_rsum_opr<i08_pt>;
template struct enc_rsum_opr<i16_pt>;
template struct enc_rsum_opr<i32_pt>;
template struct enc_rsum_opr<i64_pt>;

} // namespace fastlanes
