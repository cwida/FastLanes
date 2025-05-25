#include "fls/expression/null_operator.hpp"
#include "fls/cfg/cfg.hpp"
#include "fls/cor/lyt/buf.hpp"
#include "fls/expression/analyze_operator.hpp"
#include "fls/expression/interpreter.hpp"
#include "fls/expression/physical_expression.hpp"
#include "fls/primitive/copy/fls_copy.hpp"
#include "fls/reader/column_view.hpp"
#include "fls/reader/segment.hpp"

namespace fastlanes {
/*--------------------------------------------------------------------------------------------------------------------*\
* enc null opr
\*--------------------------------------------------------------------------------------------------------------------*/
template <typename PT>
enc_null_opr<PT>::enc_null_opr(const PhysicalExpr& expr,
                               const col_pt&       col,
                               ColumnDescriptorT&  column_descriptor,
                               InterpreterState&   state)
    : type_col_data(col) {

	n_vals_segment        = make_unique<Segment>();
	vals_position_segment = make_unique<Segment>();
	vals_segment          = make_unique<Segment>();

	auto& [operator_tokens, operand_tokens] = *column_descriptor.encoding_rpn;

	operand_tokens.emplace_back(state.cur_operand++);
	operand_tokens.emplace_back(state.cur_operand++);
	operand_tokens.emplace_back(state.cur_operand++);
}

template <typename PT>
void enc_null_opr<PT>::Store() {
	const auto* null_arr = type_col_data.NullMap();
	const auto* data     = type_col_data.Data();
	vec_idx_t   n_vals {0};

	for (vec_idx_t i {0}; i < CFG::VEC_SZ; ++i) {
		if (!null_arr[i]) {
			vals[n_vals]          = data[i];
			vals_position[n_vals] = i;
			n_vals++;
		}
	}

	n_vals_segment->Flush(&n_vals, sizeof(vec_idx_t));
	vals_position_segment->Flush(vals_position, sizeof(vec_idx_t) * n_vals);
	vals_segment->Flush(vals, sizeof(PT) * n_vals);
}
template <typename PT>
void enc_null_opr<PT>::PointTo(n_t vec_idx) {
	type_col_data.PointTo(vec_idx);
}
template <typename PT>
void enc_null_opr<PT>::MoveSegments(vector<up<Segment>>& segments) {
	segments.push_back(std::move(vals_segment));
	segments.push_back(std::move(vals_position_segment));
	segments.push_back(std::move(n_vals_segment));
}

template struct enc_null_opr<flt_pt>;
template struct enc_null_opr<dbl_pt>;
template struct enc_null_opr<i16_pt>;
template struct enc_null_opr<i32_pt>;

/*--------------------------------------------------------------------------------------------------------------------*\
 * dec slpatch opr
\*--------------------------------------------------------------------------------------------------------------------*/
template <typename PT>
dec_null_opr<PT>::dec_null_opr(PhysicalExpr& physical_expr, const ColumnView& column_view, InterpreterState& state)
    : vals_segment(
          column_view.GetSegment(column_view.column_descriptor.encoding_rpn->operand_tokens[state.cur_operand - 2]))
    , vals_position_segment(
          column_view.GetSegment(column_view.column_descriptor.encoding_rpn->operand_tokens[state.cur_operand - 1]))
    , n_vals_segment(
          column_view.GetSegment(column_view.column_descriptor.encoding_rpn->operand_tokens[state.cur_operand - 0])) {
	state.cur_operand = state.cur_operand - 3;
}

template <typename PT>
void dec_null_opr<PT>::PointTo(const n_t vec_n) {
	vals_segment.PointTo(vec_n);
	vals_position_segment.PointTo(vec_n);
	n_vals_segment.PointTo(vec_n);
}

template <typename PT>
void dec_null_opr<PT>::Materialize(n_t vec_idx, TypedCol<PT>& typed_col) {
	typed_col.data.resize(typed_col.data.size() + CFG::VEC_SZ);
	PT* materialized_data_p = typed_col.data.data() + (CFG::VEC_SZ * vec_idx);

	auto* exc_arr      = reinterpret_cast<PT*>(vals_segment.data);
	auto* exc_pos_arr  = reinterpret_cast<uint16_t*>(vals_position_segment.data);
	auto  n_exceptions = *reinterpret_cast<uint16_t*>(n_vals_segment.data);

	FLS_ASSERT_CORRECT_POS(n_exceptions)

	for (auto val_idx {0}; val_idx < n_exceptions; ++val_idx) {
		auto next_pos                 = exc_pos_arr[val_idx];
		auto val                      = exc_arr[val_idx];
		materialized_data_p[next_pos] = val;
	}
}

template struct dec_null_opr<flt_pt>;
template struct dec_null_opr<dbl_pt>;
template struct dec_null_opr<i16_pt>;
template struct dec_null_opr<i32_pt>;

} // namespace fastlanes
