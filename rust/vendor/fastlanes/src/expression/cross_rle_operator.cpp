#include "fls/expression/cross_rle_operator.hpp"
#include "fls/cfg/cfg.hpp"
#include "fls/cor/lyt/buf.hpp"
#include "fls/expression/analyze_operator.hpp"
#include "fls/expression/interpreter.hpp"
#include "fls/expression/physical_expression.hpp"
#include "fls/primitive/fls_memset/fls_memset.hpp"
#include "fls/reader/column_view.hpp"
#include "fls/reader/segment.hpp"

namespace fastlanes {
/*--------------------------------------------------------------------------------------------------------------------*\
* enc cross_rle opr
\*--------------------------------------------------------------------------------------------------------------------*/
template <typename PT>
enc_cross_rle_opr<PT>::enc_cross_rle_opr(const PhysicalExpr& expr,
                                         const col_pt&       col,
                                         ColumnDescriptorT&  column_descriptor,
                                         InterpreterState&   state)
    : col_viewer(col) {

	values_seg = make_unique<Segment>();
	values_seg->MakeBlockBased();
	lengths_seg = make_unique<Segment>();
	lengths_seg->MakeBlockBased();
	values  = make_unique<Buf>();
	lengths = make_unique<Buf>();

	auto& [operator_tokens, operand_tokens] = *column_descriptor.encoding_rpn;
	operand_tokens.emplace_back(state.cur_operand++);
	operand_tokens.emplace_back(state.cur_operand++);
}

template <typename PT>
void enc_cross_rle_opr<PT>::Finalize() {
	col_viewer.PointTo(0);

	const auto* data = col_viewer.Data();
	len_t       prev_legnth {1};
	PT          prev_val = data[0];
	for (n_t row_idx {1}; row_idx < col_viewer.GetNTuples(); row_idx++) {
		PT cur_val = data[row_idx];
		if (prev_val != cur_val) {
			values->Append(&prev_val, sizeof(PT));
			lengths->Append(&prev_legnth, sizeof(len_t));
			prev_legnth = 1;
			prev_val    = cur_val;
		} else {
			prev_legnth += 1;
		}
	}
	values->Append(&prev_val, sizeof(PT));
	lengths->Append(&prev_legnth, sizeof(len_t));

	values_seg->Flush(values->data(), values->Size());
	lengths_seg->Flush(lengths->data(), lengths->Size());
}

template <typename PT>
void enc_cross_rle_opr<PT>::MoveSegments(vector<up<Segment>>& segments) {
	segments.push_back(std::move(values_seg));
	segments.push_back(std::move(lengths_seg));
}

template struct enc_cross_rle_opr<dbl_pt>;
template struct enc_cross_rle_opr<flt_pt>;
template struct enc_cross_rle_opr<i08_pt>;
template struct enc_cross_rle_opr<i16_pt>;
template struct enc_cross_rle_opr<i32_pt>;
template struct enc_cross_rle_opr<i64_pt>;

enc_cross_rle_opr<fls_string_t>::enc_cross_rle_opr(const PhysicalExpr& expr,
                                                   const col_pt&       col,
                                                   ColumnDescriptorT&  column_descriptor,
                                                   InterpreterState&   state)
    : col_viewer(col) {

	lengths_buf       = make_unique<Buf>();
	values_bytes_buf  = make_unique<Buf>();
	values_offset_buf = make_unique<Buf>();

	values_bytes_seg = make_unique<Segment>();
	values_bytes_seg->MakeBlockBased();
	values_offset_seg = make_unique<Segment>();
	values_offset_seg->MakeBlockBased();
	lengths_seg = make_unique<Segment>();
	lengths_seg->MakeBlockBased();

	auto& [operator_tokens, operand_tokens] = *column_descriptor.encoding_rpn;
	operand_tokens.emplace_back(state.cur_operand++);
	operand_tokens.emplace_back(state.cur_operand++);
	operand_tokens.emplace_back(state.cur_operand++);
}

void enc_cross_rle_opr<fls_string_t>::Finalize() {
	col_viewer.PointTo(0);
	const auto* data = col_viewer.String();
	len_t       prev_legnth {1};
	auto        prev_val = data[0];
	len_t       ofs {0};
	for (n_t row_idx {1}; row_idx < col_viewer.GetNTuples(); row_idx++) {
		auto cur_val = data[row_idx];
		if (prev_val != cur_val) {
			values_bytes_buf->Append(prev_val.p, prev_val.length);
			ofs += prev_val.length;
			values_offset_buf->TypedAppend<len_t>(&ofs);
			lengths_buf->Append(&prev_legnth, sizeof(len_t));

			prev_legnth = 1;
			prev_val    = cur_val;
		} else {
			prev_legnth += 1;
		}
	}
	values_bytes_buf->Append(prev_val.p, prev_val.length);
	ofs += prev_val.length;
	values_offset_buf->TypedAppend<len_t>(&ofs);
	lengths_buf->Append(&prev_legnth, sizeof(len_t));

	values_bytes_seg->Flush(values_bytes_buf->data(), values_bytes_buf->Size());
	values_offset_seg->Flush(values_offset_buf->data(), values_offset_buf->Size());
	lengths_seg->Flush(lengths_buf->data(), lengths_buf->Size());
}

void enc_cross_rle_opr<fls_string_t>::MoveSegments(vector<up<Segment>>& segments) {
	segments.push_back(std::move(values_bytes_seg));
	segments.push_back(std::move(values_offset_seg));
	segments.push_back(std::move(lengths_seg));
}

/*--------------------------------------------------------------------------------------------------------------------*\
 * dec_cross_rle_opr
\*--------------------------------------------------------------------------------------------------------------------*/
template <typename PT>
dec_cross_rle_opr<PT>::dec_cross_rle_opr(PhysicalExpr&     physical_expr,
                                         const ColumnView& column_view,
                                         InterpreterState& state)
    : values_segment(
          column_view.GetSegment(column_view.column_descriptor.encoding_rpn->operand_tokens[state.cur_operand - 1]))
    , lengths_segment(
          column_view.GetSegment(column_view.column_descriptor.encoding_rpn->operand_tokens[state.cur_operand - 0])) {
	state.cur_operand = state.cur_operand - 2;

	values_segment.PointTo(0);
	lengths_segment.PointTo(0);
}

n_t find_rle_segment(const len_t* rle_lengths, n_t size, n_t range_index) {
	n_t target_start = range_index * 1024;
	n_t current_pos  = 0;

	for (n_t i = 0; i < size; ++i) {
		if (current_pos + rle_lengths[i] > target_start) {
			return i;
		}
		current_pos += rle_lengths[i];
	}

	// If out of bounds, return last valid index or a sentinel value (-1)
	return size - 1;
}

template <typename PT>
void decode_rle_range(const len_t* rle_lengths, const PT* rle_values, n_t size, n_t range_index, PT* decoded_arr) {
	n_t start_rle_index = find_rle_segment(rle_lengths, size, range_index);

	n_t needed        = 1024;
	n_t current_index = start_rle_index;
	n_t current_pos   = 0;

	for (n_t i = 0; i < start_rle_index; ++i)
		current_pos += rle_lengths[i];

	n_t offset      = range_index * 1024 - current_pos;
	n_t decoded_pos = 0; // Track the correct position in decoded_arr

	while (needed > 0 && current_index < size) {
		n_t available = rle_lengths[current_index] - offset;
		n_t to_copy   = std::min(available, needed);

		for (n_t i = 0; i < to_copy; ++i) {
			decoded_arr[decoded_pos++] = rle_values[current_index];
		}

		needed -= to_copy;
		offset = 0;
		++current_index;
	}
}

template <typename PT>
void dec_cross_rle_opr<PT>::Materialize(n_t vec_idx, TypedCol<PT>& typed_col) {
	typed_col.data.resize(typed_col.data.size() + CFG::VEC_SZ);
	PT* materialized_data_p = typed_col.data.data() + (CFG::VEC_SZ * vec_idx);

	const auto* length = reinterpret_cast<const len_t*>(lengths_segment.data);
	const auto* values = reinterpret_cast<const PT*>(values_segment.data);

	const auto size = lengths_segment.data_span.size() / sizeof(len_t);

	decode_rle_range(length, values, size, vec_idx, materialized_data_p);
}

template struct dec_cross_rle_opr<dbl_pt>;
template struct dec_cross_rle_opr<flt_pt>;
template struct dec_cross_rle_opr<i08_pt>;
template struct dec_cross_rle_opr<i16_pt>;
template struct dec_cross_rle_opr<i32_pt>;
template struct dec_cross_rle_opr<i64_pt>;

dec_cross_rle_opr<fls_string_t>::dec_cross_rle_opr(PhysicalExpr&     physical_expr,
                                                   const ColumnView& column_view,
                                                   InterpreterState& state)
    : values_bytes_seg(
          column_view.GetSegment(column_view.column_descriptor.encoding_rpn->operand_tokens[state.cur_operand - 2]))
    , values_offset_seg(
          column_view.GetSegment(column_view.column_descriptor.encoding_rpn->operand_tokens[state.cur_operand - 1]))
    , lengths_segment(
          column_view.GetSegment(column_view.column_descriptor.encoding_rpn->operand_tokens[state.cur_operand - 0])) {
	state.cur_operand = state.cur_operand - 3;

	values_bytes_seg.PointTo(0);
	values_offset_seg.PointTo(0);
	lengths_segment.PointTo(0);
}

void decode_rle_range(const len_t*     rle_lengths,
                      const uint8_t*   rle_value_bytes,
                      const ofs_t*     rle_value_offsets,
                      n_t              size,
                      n_t              range_index,
                      vector<uint8_t>& byte_arr_vec,
                      len_t*           out_lengths) {

	n_t start_rle_index = find_rle_segment(rle_lengths, size, range_index);

	n_t needed        = 1024;
	n_t current_index = start_rle_index;
	n_t current_pos   = 0;
	n_t decoded_pos   = 0; // Track the correct position in decoded_arr

	for (n_t i = 0; i < start_rle_index; ++i)
		current_pos += rle_lengths[i];

	n_t offset = range_index * 1024 - current_pos;

	while (needed > 0 && current_index < size) {
		ofs_t prev_offset = 0;
		if (current_index == 0) {
			prev_offset = 0;
		} else {
			prev_offset = rle_value_offsets[current_index - 1];
		}
		ofs_t cur_offset = rle_value_offsets[current_index];
		auto  length     = cur_offset - prev_offset;
		n_t   available  = rle_lengths[current_index] - offset;
		n_t   to_copy    = std::min(available, needed);

		for (n_t i = 0; i < to_copy; ++i) {
			if (byte_arr_vec.capacity() - byte_arr_vec.size() < CFG::String::max_bytes_per_string) {
				byte_arr_vec.reserve(byte_arr_vec.size() + 1024 * CFG::String::max_bytes_per_string);
			}
			byte_arr_vec.insert(byte_arr_vec.end(), rle_value_bytes + prev_offset, rle_value_bytes + cur_offset);
			out_lengths[decoded_pos++] = length;
		}

		needed -= to_copy;
		offset = 0;
		++current_index;
	}
}

void dec_cross_rle_opr<fls_string_t>::Materialize(n_t vec_idx, FLSStrColumn& str_col) {
	str_col.length_arr.resize(str_col.length_arr.size() + CFG::VEC_SZ);
	auto* length_pointer = str_col.length_arr.data() + CFG::VEC_SZ * vec_idx;

	const auto* length       = reinterpret_cast<const len_t*>(lengths_segment.data);
	const auto* values_bytes = reinterpret_cast<const uint8_t*>(values_bytes_seg.data);
	const auto* offsets      = reinterpret_cast<const ofs_t*>(values_offset_seg.data);

	const auto size = lengths_segment.data_span.size() / sizeof(len_t);

	decode_rle_range(length, values_bytes, offsets, size, vec_idx, str_col.byte_arr, length_pointer);
}

} // namespace fastlanes
