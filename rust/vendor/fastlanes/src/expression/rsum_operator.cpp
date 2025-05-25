#include "fls/expression/rsum_operator.hpp"
#include "fls/cfg/cfg.hpp"
#include "fls/cor/lyt/buf.hpp"
#include "fls/expression/encoding_operator.hpp"
#include "fls/expression/interpreter.hpp"
#include "fls/expression/physical_expression.hpp"
#include "fls/expression/slpatch_operator.hpp"
#include "fls/expression/transpose_operator.hpp"
#include "fls/reader/column_view.hpp"
#include "fls/reader/segment.hpp"
#include "fls/std/type_traits.hpp"
#include "fls_gen/rsum/rsum.hpp"
#include "fls_gen/unrsum/unrsum.hpp"

namespace fastlanes {
/*--------------------------------------------------------------------------------------------------------------------*\
 * enc rsum opr
\*--------------------------------------------------------------------------------------------------------------------*/
template <typename PT>
enc_rsum_opr<PT>::enc_rsum_opr(const PhysicalExpr& expr,
                               const col_pt&       col,
                               ColumnDescriptorT&  column_descriptor,
                               InterpreterState&   state) {

	visit(overloaded {
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

template struct enc_rsum_opr<u16_pt>;
template struct enc_rsum_opr<u32_pt>;
template struct enc_rsum_opr<i08_pt>;
template struct enc_rsum_opr<i16_pt>;
template struct enc_rsum_opr<i32_pt>;
template struct enc_rsum_opr<i64_pt>;

/*--------------------------------------------------------------------------------------------------------------------*\
 * dec_rsum_opr
\*--------------------------------------------------------------------------------------------------------------------*/
template <typename PT>
struct RsumExprVisitor {
	explicit RsumExprVisitor(const PT*& idxs)
	    : idxs(idxs) {
	}

	const PT*& idxs;

	void operator()(const sp<dec_unffor_opr<make_unsigned_t<PT>>>& opr) {
		idxs = reinterpret_cast<const PT*>(opr->Data());
	}
	void operator()(const sp<dec_slpatch_opr<make_unsigned_t<PT>>>& opr) {
		idxs = reinterpret_cast<const PT*>(opr->data);
	}
	void operator()(const sp<PhysicalExpr>& expr) {
		visit(RsumExprVisitor {idxs}, expr->operators[0]);
	}
	void operator()(std::monostate& arg) {
		FLS_UNREACHABLE_WITH_TYPE(arg);
	}
	void operator()(const auto& arg) {
		FLS_UNREACHABLE_WITH_TYPE(arg);
	}
};

template <typename PT>
dec_rsum_opr<PT>::dec_rsum_opr(PhysicalExpr& physical_expr, const ColumnView& column_view, InterpreterState& state)
    : bases_segment_view(column_view.GetSegment(state.cur_operand))
    , deltas(nullptr) {

	visit(RsumExprVisitor<PT> {deltas}, physical_expr.operators.back());
	state.cur_operand = state.cur_operand - 1;
	state.cur_operator++;
}
template <typename PT>
void dec_rsum_opr<PT>::PointTo(n_t vec_n) {
	bases_segment_view.PointTo(vec_n);
}
template <typename PT>
void dec_rsum_opr<PT>::Unrsum(n_t vec_idx) {
	PointTo(vec_idx);

	auto* bases = reinterpret_cast<PT*>(bases_segment_view.data);
	::generated::rsum::fallback::scalar::rsum(deltas, idxs, bases);
}

template struct dec_rsum_opr<u16_pt>;
template struct dec_rsum_opr<u32_pt>;
template struct dec_rsum_opr<i08_pt>;
template struct dec_rsum_opr<i16_pt>;
template struct dec_rsum_opr<i32_pt>;
template struct dec_rsum_opr<i64_pt>;

} // namespace fastlanes
