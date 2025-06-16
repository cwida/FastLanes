#include "fls/expression/frequency_operator.hpp"
#include "fls/cfg/cfg.hpp"
#include "fls/cor/lyt/buf.hpp"
#include "fls/expression/analyze_operator.hpp"
#include "fls/expression/interpreter.hpp"
#include "fls/expression/physical_expression.hpp"
#include "fls/primitive/copy/fls_copy.hpp"
#include "fls/primitive/fls_memset/fls_memset.hpp"
#include "fls/reader/column_view.hpp"
#include "fls/reader/segment.hpp"

namespace fastlanes {
/*--------------------------------------------------------------------------------------------------------------------*\
* enc frequency opr
\*--------------------------------------------------------------------------------------------------------------------*/
template <typename PT>
enc_frequency_opr<PT>::enc_frequency_opr(const PhysicalExpr& expr,
                                         const col_pt&       col,
                                         ColumnDescriptorT&  column_descriptor,
                                         InterpreterState&   state)
    : col_viewer(col) {

	frequent_val = col_viewer.GetStats()->bimap_frequency.get_most_frequent_value();

	frequent_value_seg = make_unique<Segment>();
	frequent_value_seg->MakeBlockBased();
	n_exceptions_seg        = make_unique<Segment>();
	exception_positions_seg = make_unique<Segment>();
	exception_values_seg    = make_unique<Segment>();

	auto& [operator_tokens, operand_tokens] = *column_descriptor.encoding_rpn;
	operand_tokens.emplace_back(state.cur_operand++);
	operand_tokens.emplace_back(state.cur_operand++);
	operand_tokens.emplace_back(state.cur_operand++);
	operand_tokens.emplace_back(state.cur_operand++);
}

template <typename PT>
void enc_frequency_opr<PT>::Encode() {
	const auto* null_map = col_viewer.NullMap();
	const auto* data     = col_viewer.Data();
	vec_idx_t   n_exceptions {0};

	for (vec_idx_t val_idx {0}; val_idx < CFG::VEC_SZ; ++val_idx) {
		if (data[val_idx] != frequent_val && !null_map[val_idx]) {
			exception_vals[n_exceptions]      = data[val_idx];
			exception_positions[n_exceptions] = val_idx;
			n_exceptions++;
		}
	}

	n_exceptions_seg->Flush(&n_exceptions, sizeof(vec_idx_t));
	exception_positions_seg->Flush(exception_positions, sizeof(vec_idx_t) * n_exceptions);
	exception_values_seg->Flush(exception_vals, sizeof(PT) * n_exceptions);
}
template <typename PT>
void enc_frequency_opr<PT>::PointTo(n_t vec_idx) {
	col_viewer.PointTo(vec_idx);
}

template <typename PT>
void enc_frequency_opr<PT>::Finalize() {
	frequent_value_seg->Flush(&frequent_val, sizeof(PT));
}

template <typename PT>
void enc_frequency_opr<PT>::MoveSegments(vector<up<Segment>>& segments) {
	segments.push_back(std::move(frequent_value_seg));
	segments.push_back(std::move(exception_values_seg));
	segments.push_back(std::move(exception_positions_seg));
	segments.push_back(std::move(n_exceptions_seg));
}

template struct enc_frequency_opr<dbl_pt>;
template struct enc_frequency_opr<flt_pt>;
template struct enc_frequency_opr<i08_pt>;
template struct enc_frequency_opr<i16_pt>;
template struct enc_frequency_opr<i32_pt>;
template struct enc_frequency_opr<i64_pt>;

enc_frequency_str_opr::enc_frequency_str_opr(const PhysicalExpr& expr,
                                             const col_pt&       col,
                                             ColumnDescriptorT&  column_descriptor,
                                             InterpreterState&   state)
    : col_viewer(col) {

	frequent_val = col_viewer.stats.bimap.get_most_frequent_key();

	length_buf = make_unique<Buf>();
	bytes_buf  = make_unique<Buf>();

	frequent_value_bytes_seg = make_unique<Segment>();
	frequent_value_bytes_seg->MakeBlockBased();
	frequent_value_size_seg = make_unique<Segment>();
	frequent_value_size_seg->MakeBlockBased();
	n_exceptions_seg            = make_unique<Segment>();
	exception_positions_seg     = make_unique<Segment>();
	exception_values_bytes_seg  = make_unique<Segment>();
	exception_values_offset_seg = make_unique<Segment>();

	auto& [operator_tokens, operand_tokens] = *column_descriptor.encoding_rpn;
	operand_tokens.emplace_back(state.cur_operand++);
	operand_tokens.emplace_back(state.cur_operand++);
	operand_tokens.emplace_back(state.cur_operand++);
	operand_tokens.emplace_back(state.cur_operand++);
	operand_tokens.emplace_back(state.cur_operand++);
	operand_tokens.emplace_back(state.cur_operand++);
}

void enc_frequency_str_opr::Encode() {
	bytes_buf->Reset();
	length_buf->Reset();

	const auto* fls_string = col_viewer.String();
	vec_idx_t   n_exceptions {0};

	ofs_t cur_offset {0};
	for (vec_idx_t val_idx {0}; val_idx < CFG::VEC_SZ; ++val_idx) {
		const auto current_val = fls_string[val_idx];
		if (current_val != frequent_val) {
			bytes_buf->Append(current_val.p, current_val.length);
			cur_offset += current_val.length;
			length_buf->Append(&cur_offset, sizeof(len_t));
			exception_positions[n_exceptions] = val_idx;
			n_exceptions++;
		}
	}

	exception_values_bytes_seg->Flush(bytes_buf->data(), bytes_buf->Size());
	exception_values_offset_seg->Flush(length_buf->data(), length_buf->Size());
	n_exceptions_seg->Flush(&n_exceptions, sizeof(vec_idx_t));
	exception_positions_seg->Flush(exception_positions, sizeof(vec_idx_t) * n_exceptions);
}

void enc_frequency_str_opr::PointTo(n_t vec_idx) {
	col_viewer.PointTo(vec_idx);
}

void enc_frequency_str_opr::Finalize() {
	frequent_value_bytes_seg->Flush(frequent_val.p, frequent_val.length);
	frequent_value_size_seg->Flush(&frequent_val.length, sizeof(len_t));
}

void enc_frequency_str_opr::MoveSegments(vector<up<Segment>>& segments) {
	segments.push_back(std::move(frequent_value_bytes_seg));
	segments.push_back(std::move(frequent_value_size_seg));
	segments.push_back(std::move(n_exceptions_seg));
	segments.push_back(std::move(exception_positions_seg));
	segments.push_back(std::move(exception_values_bytes_seg));
	segments.push_back(std::move(exception_values_offset_seg));
}

/*--------------------------------------------------------------------------------------------------------------------*\
 * dec_frequency_opr
\*--------------------------------------------------------------------------------------------------------------------*/
template <typename PT>
dec_frequency_opr<PT>::dec_frequency_opr(PhysicalExpr&     physical_expr,
                                         const ColumnView& column_view,
                                         InterpreterState& state)
    : frequent_value_seg(
          column_view.GetSegment(column_view.column_descriptor.encoding_rpn->operand_tokens[state.cur_operand - 3]))
    , exceptions_segment(
          column_view.GetSegment(column_view.column_descriptor.encoding_rpn->operand_tokens[state.cur_operand - 2]))
    , exceptions_position_segment(
          column_view.GetSegment(column_view.column_descriptor.encoding_rpn->operand_tokens[state.cur_operand - 1]))
    , n_exceptions_segment(
          column_view.GetSegment(column_view.column_descriptor.encoding_rpn->operand_tokens[state.cur_operand - 0])) {
	state.cur_operand = state.cur_operand - 4;

	frequent_value_seg.PointTo(0);
	frequent_val = *reinterpret_cast<PT*>(frequent_value_seg.data);
}

template <typename PT>
void dec_frequency_opr<PT>::PointTo(const n_t vec_idx) {
	exceptions_segment.PointTo(vec_idx);
	exceptions_position_segment.PointTo(vec_idx);
	n_exceptions_segment.PointTo(vec_idx);
}

template <typename PT>
void dec_frequency_opr<PT>::Decode(n_t vec_idx) {
	PointTo(vec_idx);

	fls_memset(&frequent_val, data);

	auto* exc_arr      = reinterpret_cast<PT*>(exceptions_segment.data);
	auto* exc_pos_arr  = reinterpret_cast<uint16_t*>(exceptions_position_segment.data);
	auto  n_exceptions = *reinterpret_cast<uint16_t*>(n_exceptions_segment.data);

	FLS_ASSERT_CORRECT_POS(n_exceptions)

	for (auto val_idx {0}; val_idx < n_exceptions; ++val_idx) {
		auto next_pos  = exc_pos_arr[val_idx];
		auto val       = exc_arr[val_idx];
		data[next_pos] = val;
	}
}

template <typename PT>
void dec_frequency_opr<PT>::Materialize(n_t vec_idx, TypedCol<PT>& typed_col) {
	typed_col.data.resize(typed_col.data.size() + CFG::VEC_SZ);
	PT* materialized_data_p = typed_col.data.data() + (CFG::VEC_SZ * vec_idx);

	copy(data, materialized_data_p);
}

template struct dec_frequency_opr<dbl_pt>;
template struct dec_frequency_opr<flt_pt>;
template struct dec_frequency_opr<i08_pt>;
template struct dec_frequency_opr<i16_pt>;
template struct dec_frequency_opr<i32_pt>;
template struct dec_frequency_opr<i64_pt>;

dec_frequency_str_opr::dec_frequency_str_opr(PhysicalExpr&     physical_expr,
                                             const ColumnView& column_view,
                                             InterpreterState& state)
    : frequent_value_bytes_seg(
          column_view.GetSegment(column_view.column_descriptor.encoding_rpn->operand_tokens[state.cur_operand - 5]))
    , frequent_value_size_seg(
          column_view.GetSegment(column_view.column_descriptor.encoding_rpn->operand_tokens[state.cur_operand - 4]))
    , n_exceptions_seg(
          column_view.GetSegment(column_view.column_descriptor.encoding_rpn->operand_tokens[state.cur_operand - 3]))
    , exception_positions_seg(
          column_view.GetSegment(column_view.column_descriptor.encoding_rpn->operand_tokens[state.cur_operand - 2]))
    , exception_values_bytes_seg(
          column_view.GetSegment(column_view.column_descriptor.encoding_rpn->operand_tokens[state.cur_operand - 1]))
    , exception_values_offset_seg(
          column_view.GetSegment(column_view.column_descriptor.encoding_rpn->operand_tokens[state.cur_operand - 0])) {
	state.cur_operand = state.cur_operand - 6;

	frequent_value_bytes_seg.PointTo(0);
	frequent_value_size_seg.PointTo(0);
	frequent_val = fls_string_t(reinterpret_cast<uint8_t*>(frequent_value_bytes_seg.data),
	                            *reinterpret_cast<len_t*>(frequent_value_size_seg.data));
}

void dec_frequency_str_opr::PointTo(n_t vec_idx) {
	n_exceptions_seg.PointTo(vec_idx);
	exception_positions_seg.PointTo(vec_idx);
	exception_values_bytes_seg.PointTo(vec_idx);
	exception_values_offset_seg.PointTo(vec_idx);
}

void dec_frequency_str_opr::Decode() {
}

void dec_frequency_str_opr::Materialize(n_t vec_idx, FLSStrColumn& typed_col) {
	auto& length_vec   = typed_col.length_arr;
	auto& byte_arr_vec = typed_col.byte_arr;
	length_vec.resize(length_vec.size() + CFG::VEC_SZ);
	auto* length_pointer = &length_vec.back() + 1 - CFG::VEC_SZ;

	auto* exception_positions     = reinterpret_cast<vec_idx_t*>(exception_positions_seg.data);
	auto* exception_values_bytes  = reinterpret_cast<uint8_t*>(exception_values_bytes_seg.data);
	auto* exception_values_offset = reinterpret_cast<ofs_t*>(exception_values_offset_seg.data);
	auto* n_exceptions_p          = reinterpret_cast<vec_idx_t*>(n_exceptions_seg.data);
	auto  n_exceptions            = n_exceptions_p[0];

	vec_idx_t exception_idx {0};
	vec_idx_t exception_position {0};
	for (n_t idx {0}; idx < CFG::VEC_SZ; ++idx) {
		if (byte_arr_vec.capacity() - byte_arr_vec.size() < CFG::String::max_bytes_per_string) {
			byte_arr_vec.reserve(byte_arr_vec.size() + 1024 * CFG::String::max_bytes_per_string);
		}

		exception_position = exception_positions[exception_idx];
		if (exception_position == idx && exception_idx < n_exceptions) {
			ofs_t cur_ofs;
			ofs_t next_ofs = exception_values_offset[exception_idx];
			if (exception_idx == 0) {
				cur_ofs = 0;
			} else {
				cur_ofs = exception_values_offset[exception_idx - 1];
			}
			byte_arr_vec.insert(
			    byte_arr_vec.end(), exception_values_bytes + cur_ofs, exception_values_bytes + next_ofs);
			length_pointer[idx] = next_ofs - cur_ofs;

			exception_idx++;
		} else {
			byte_arr_vec.insert(byte_arr_vec.end(), frequent_val.p, frequent_val.p + frequent_val.length);
			length_pointer[idx] = frequent_val.length;
		}
	}
}

} // namespace fastlanes
