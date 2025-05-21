#include "fls/expression/rle_expression.hpp"
#include "fls/expression/interpreter.hpp"
#include "fls/expression/physical_expression.hpp"
#include "fls/expression/rsum_operator.hpp"
#include "fls/primitive/rle/rle.hpp"
#include "fls/reader/segment.hpp"
#include "fls_gen/transpose/transpose.hpp"
#include "fls_gen/untranspose/untranspose.hpp"

namespace fastlanes {
/*--------------------------------------------------------------------------------------------------------------------*\
 * enc_rle_map_opr
\*--------------------------------------------------------------------------------------------------------------------*/
template <typename KEY_PT, typename INDEX_PT>
enc_rle_map_opr<KEY_PT, INDEX_PT>::enc_rle_map_opr(const PhysicalExpr& expr,
                                                   const col_pt&       column,
                                                   ColumnDescriptorT&  column_descriptor,
                                                   InterpreterState&   state)
    : typed_column_view(column) {

	auto& [operator_tokens, operand_tokens] = *column_descriptor.encoding_rpn;
	operand_tokens.emplace_back(state.cur_operand++);
	rle_val_segment = make_unique<Segment>();
}

template <typename KEY_PT, typename INDEX_PT>
void enc_rle_map_opr<KEY_PT, INDEX_PT>::PointTo(n_t vec_idx) {
	typed_column_view.PointTo(vec_idx);
}

template <typename KEY_PT, typename INDEX_PT>
void enc_rle_map_opr<KEY_PT, INDEX_PT>::Map() {
	[[maybe_unused]] const auto* in_arr = typed_column_view.Data();

	auto n_rle_vals = RLE<KEY_PT, INDEX_PT>::encode(in_arr, rle_vals, rle_idxs);

	rle_val_segment->Flush(rle_vals, sizeof(KEY_PT) * n_rle_vals);
}

template <typename KEY_PT, typename INDEX_PT>
void enc_rle_map_opr<KEY_PT, INDEX_PT>::MoveSegments(vector<up<Segment>>& segments) {
	segments.push_back(std::move(rle_val_segment));
}

template struct enc_rle_map_opr<flt_pt, u16_pt>;
template struct enc_rle_map_opr<dbl_pt, u16_pt>;
template struct enc_rle_map_opr<i64_pt, u16_pt>;
template struct enc_rle_map_opr<i32_pt, u16_pt>;
template struct enc_rle_map_opr<i16_pt, u16_pt>;
template struct enc_rle_map_opr<i08_pt, u16_pt>;

template <typename INDEX_PT>
void enc_rle_map_opr<fls_string_t, INDEX_PT>::MoveSegments(vector<up<Segment>>& segments) {
	segments.push_back(std::move(rle_val_bytes_segment));
	segments.push_back(std::move(rle_val_offset_segment));
}

template <typename INDEX_PT>
enc_rle_map_opr<fls_string_t, INDEX_PT>::enc_rle_map_opr(const PhysicalExpr& expr,
                                                         const col_pt&       column,
                                                         ColumnDescriptorT&  column_descriptor,
                                                         InterpreterState&   state)
    : string_col(column) {
	auto& [operator_tokens, operand_tokens] = *column_descriptor.encoding_rpn;

	rle_val_bytes_segment  = make_unique<Segment>();
	rle_val_offset_segment = make_unique<Segment>();

	operand_tokens.emplace_back(state.cur_operand++);
	operand_tokens.emplace_back(state.cur_operand++);

	buf = make_unique<Buf>();
}

template <typename INDEX_PT>
void enc_rle_map_opr<fls_string_t, INDEX_PT>::PointTo(n_t vec_idx) {
	string_col.PointTo(vec_idx);
}

template <typename INDEX_PT>
void enc_rle_map_opr<fls_string_t, INDEX_PT>::Map() {
	const auto* vals = string_col.String();

	auto n_rle_vals = RLE<fls_string_t, INDEX_PT>::encode(vals, rle_vals, rle_idxs);

	len_t cur_offset {0};
	rle_val_offsets[0] = cur_offset;
	buf->Reset();

	for (n_t val_idx {0}; val_idx < n_rle_vals; val_idx++) {
		const fls_string_t& current_fls_string = rle_vals[val_idx];
		buf->Append(current_fls_string.p, current_fls_string.length);
		cur_offset                   = cur_offset + current_fls_string.length;
		rle_val_offsets[val_idx + 1] = cur_offset;
	}

	rle_val_bytes_segment->Flush(buf->data(), buf->Size());
	rle_val_offset_segment->Flush(rle_val_offsets, sizeof(ofs_t) * (n_rle_vals + 1));
}

template struct enc_rle_map_opr<fls_string_t, u16_pt>;
/*--------------------------------------------------------------------------------------------------------------------*\
 * dec_rle_map_opr
\*--------------------------------------------------------------------------------------------------------------------*/
template <typename PT>
struct RLEExprVisitor {
	explicit RLEExprVisitor(const PT*& idxs)
	    : idxs(idxs) {
	}

	const PT*& idxs;

	void operator()(const sp<dec_rsum_opr<PT>>& opr) {
		idxs = opr->idxs;
	}
	void operator()(const sp<PhysicalExpr>& expr) {
		visit(RLEExprVisitor {idxs}, expr->operators[0]);
	}
	void operator()(std::monostate& arg) {
		FLS_UNREACHABLE_WITH_TYPE(arg);
	}
	void operator()(const auto& arg) {
		FLS_UNREACHABLE_WITH_TYPE(arg);
	}
};

template <typename KEY_PT, typename INDEX_PT>
dec_rle_map_opr<KEY_PT, INDEX_PT>::dec_rle_map_opr(PhysicalExpr&     physical_expr,
                                                   const ColumnView& column_view,
                                                   InterpreterState& state)
    : rle_vals_segment_view(
          column_view.GetSegment(column_view.column_descriptor.encoding_rpn->operand_tokens[state.cur_operand])) {
	visit(RLEExprVisitor<INDEX_PT> {idxs}, physical_expr.operators.back());
	state.cur_operand = state.cur_operand - 1;
}

template <typename KEY_PT, typename INDEX_PT>

void dec_rle_map_opr<KEY_PT, INDEX_PT>::PointTo(const n_t vec_n) {
	rle_vals_segment_view.PointTo(vec_n);
}

template <typename KEY_PT, typename INDEX_PT>
void dec_rle_map_opr<KEY_PT, INDEX_PT>::Decode(const n_t vec_idx, vector<KEY_PT>& data) {
	static_assert(!std::is_same_v<KEY_PT, fls_string_t>, "Generic Decode logic cannot handle fls_string_t!");

	auto* rle_vals = reinterpret_cast<KEY_PT*>(rle_vals_segment_view.data);

	for (auto val_idx {0}; val_idx < CFG::VEC_SZ; val_idx++) {
		temporary_tranposed_arr[val_idx] = rle_vals[idxs[val_idx]];
	}

	data.resize(data.size() + CFG::VEC_SZ);
	generated::untranspose::fallback::scalar::untranspose_i(temporary_tranposed_arr,
	                                                        data.data() + vec_idx * CFG::VEC_SZ);
}

template <typename INDEX_PT>
dec_rle_map_opr<FlsString, INDEX_PT>::dec_rle_map_opr(PhysicalExpr&     physical_expr,
                                                      const ColumnView& column_view,
                                                      InterpreterState& state)
    : rle_vals_segment_view(
          column_view.GetSegment(column_view.column_descriptor.encoding_rpn->operand_tokens[state.cur_operand - 1]))
    , rle_offset_segment_view(
          column_view.GetSegment(column_view.column_descriptor.encoding_rpn->operand_tokens[state.cur_operand - 0])) {
	visit(RLEExprVisitor<INDEX_PT> {idxs}, physical_expr.operators.back());
	state.cur_operand = state.cur_operand - 2;
}
template <typename INDEX_PT>
void dec_rle_map_opr<FlsString, INDEX_PT>::PointTo(n_t vec_n) {
	rle_vals_segment_view.PointTo(vec_n);
	rle_offset_segment_view.PointTo(vec_n);
}

template <typename INDEX_PT>
void dec_rle_map_opr<FlsString, INDEX_PT>::Decode(n_t              vec_idx,
                                                  vector<uint8_t>& byte_arr_vec,
                                                  vector<ofs_t>&   length_vec) {
	const auto* bytes   = reinterpret_cast<uint8_t*>(rle_vals_segment_view.data);
	const auto* offsets = reinterpret_cast<ofs_t*>(rle_offset_segment_view.data);

	generated::untranspose::fallback::scalar::untranspose_i(idxs, temporary_idxs);

	length_vec.resize(length_vec.size() + CFG::VEC_SZ);
	auto* length_pointer = length_vec.data() + vec_idx * CFG::VEC_SZ;

	for (n_t val_idx {0}; val_idx < CFG::VEC_SZ; ++val_idx) {
		const auto cur_idx      = temporary_idxs[val_idx];
		const auto cur_ofs      = offsets[cur_idx];
		const auto next_offset  = offsets[cur_idx + 1];
		length_pointer[val_idx] = next_offset - cur_ofs;

		if (byte_arr_vec.capacity() - byte_arr_vec.size() < CFG::String::max_bytes_per_string) {
			byte_arr_vec.reserve(byte_arr_vec.size() + 1024 * CFG::String::max_bytes_per_string);
		}
		byte_arr_vec.insert(byte_arr_vec.end(), bytes + cur_ofs, bytes + next_offset);
	}
}

template struct dec_rle_map_opr<flt_pt, u16_pt>;
template struct dec_rle_map_opr<dbl_pt, u16_pt>;
template struct dec_rle_map_opr<i64_pt, u16_pt>;
template struct dec_rle_map_opr<i32_pt, u16_pt>;
template struct dec_rle_map_opr<i16_pt, u16_pt>;
template struct dec_rle_map_opr<i08_pt, u16_pt>;

template struct dec_rle_map_opr<fls_string_t, u16_pt>;

} // namespace fastlanes
