#include "fls/expression/decoding_operator.hpp"
#include "fls/expression/interpreter.hpp"
#include "fls/expression/physical_expression.hpp"
#include "fls/reader/column_view.hpp"
#include "fls/unffor.hpp"
#include <cstring>

namespace fastlanes {
/*--------------------------------------------------------------------------------------------------------------------*\
 * dec_unffor_opr
\*--------------------------------------------------------------------------------------------------------------------*/
template <typename PT>
dec_unffor_opr<PT>::dec_unffor_opr(const ColumnView& column_view, InterpreterState& state)
    : bitpacked_segment_view(
          column_view.GetSegment(column_view.column_descriptor.encoding_rpn->operand_tokens[state.cur_operand - 2]))
    , bw_segment_view(
          column_view.GetSegment(column_view.column_descriptor.encoding_rpn->operand_tokens[state.cur_operand - 1]))
    , base_segment_view(
          column_view.GetSegment(column_view.column_descriptor.encoding_rpn->operand_tokens[state.cur_operand - 0])) {
	state.cur_operand = state.cur_operand - 3;
}

template <typename PT>
void dec_unffor_opr<PT>::PointTo(n_t vec_idx) {
	bitpacked_segment_view.PointTo(vec_idx);
	base_segment_view.PointTo(vec_idx);
	bw_segment_view.PointTo(vec_idx);
}

template <typename PT>
void dec_unffor_opr<PT>::Unffor(n_t vec_idx) {
	PointTo(vec_idx);

	uint8_t     bw     = *reinterpret_cast<const bw_t*>(bw_segment_view.data);
	const auto* base_p = reinterpret_cast<const PT*>(base_segment_view.data);
	const auto* in_p   = reinterpret_cast<const PT*>(bitpacked_segment_view.data);

	generated::unffor::fallback::scalar::unffor(in_p, unffored_data, bw, base_p);
}

template <typename PT>
const PT* dec_unffor_opr<PT>::Data() {
	return unffored_data;
}

template struct dec_unffor_opr<u64_pt>;
template struct dec_unffor_opr<u32_pt>;
template struct dec_unffor_opr<u16_pt>;
template struct dec_unffor_opr<u08_pt>;

/*--------------------------------------------------------------------------------------------------------------------*\
 * dec_uncompressed_opr
\*--------------------------------------------------------------------------------------------------------------------*/
template <typename PT>
dec_uncompressed_opr<PT>::dec_uncompressed_opr(const ColumnView& column_view, const n_t segment_idx)
    : data_segment(column_view.GetSegment(segment_idx)) {
}

template <typename PT>
void dec_uncompressed_opr<PT>::PointTo(const n_t vec_n) {
	data_segment.PointTo(vec_n);
}

template <typename PT>
PT* dec_uncompressed_opr<PT>::Data() {
	return reinterpret_cast<PT*>(data_segment.data);
}

template struct dec_uncompressed_opr<i64_pt>;
template struct dec_uncompressed_opr<i32_pt>;
template struct dec_uncompressed_opr<i16_pt>;
template struct dec_uncompressed_opr<i08_pt>;
template struct dec_uncompressed_opr<u64_pt>;
template struct dec_uncompressed_opr<u32_pt>;
template struct dec_uncompressed_opr<u16_pt>;
template struct dec_uncompressed_opr<u08_pt>;
template struct dec_uncompressed_opr<dbl_pt>;
template struct dec_uncompressed_opr<flt_pt>;
template struct dec_uncompressed_opr<str_pt>;

/*--------------------------------------------------------------------------------------------------------------------*\
 * dec_constant_opr
\*--------------------------------------------------------------------------------------------------------------------*/
template <typename PT>
dec_constant_opr<PT>::dec_constant_opr(const ColumnView& column_view) {
	FLS_ASSERT_E(column_view.column_descriptor.max->binary_data.size(), sizeof(PT));
	value = *reinterpret_cast<const PT*>(column_view.column_descriptor.max->binary_data.data());
}

dec_constant_str_opr::dec_constant_str_opr(const ColumnView& column_view) {
	bytes.resize(column_view.column_descriptor.max->binary_data.size());
	memcpy(bytes.data(),
	       column_view.column_descriptor.max->binary_data.data(),
	       column_view.column_descriptor.max->binary_data.size());
};

template struct dec_constant_opr<i64_pt>;
template struct dec_constant_opr<i32_pt>;
template struct dec_constant_opr<i16_pt>;
template struct dec_constant_opr<i08_pt>;
template struct dec_constant_opr<u64_pt>;
template struct dec_constant_opr<u32_pt>;
template struct dec_constant_opr<u16_pt>;
template struct dec_constant_opr<u08_pt>;
template struct dec_constant_opr<dbl_pt>;
template struct dec_constant_opr<flt_pt>;
template struct dec_constant_opr<str_pt>;
/*--------------------------------------------------------------------------------------------------------------------*\
 * dec_fls_str_uncompressed_opr
\*--------------------------------------------------------------------------------------------------------------------*/
dec_fls_str_uncompressed_opr::dec_fls_str_uncompressed_opr(const ColumnView& column_view, const RPNT& rpn)
    : byte_arr_segment(column_view.GetSegment(rpn.operand_tokens[0]))
    , length_segment(column_view.GetSegment(rpn.operand_tokens[1])) {
	FLS_ASSERT_EQUALITY(rpn.operand_tokens.size(), 2);
}

void dec_fls_str_uncompressed_opr::PointTo(n_t vec_idx) {
	byte_arr_segment.PointTo(vec_idx);
	length_segment.PointTo(vec_idx);
}

std::byte* dec_fls_str_uncompressed_opr::Data() const {
	return byte_arr_segment.data;
}

len_t* dec_fls_str_uncompressed_opr::Length() const {
	return reinterpret_cast<len_t*>(length_segment.data);
}

/*--------------------------------------------------------------------------------------------------------------------*\
 * dec_struct_opr
\*--------------------------------------------------------------------------------------------------------------------*/
dec_struct_opr::dec_struct_opr(const ColumnDescriptorT& column_descriptor,
                               const ColumnView&        column_view,
                               InterpreterState&,
                               RowgroupReader& reader) {
	auto& children = column_descriptor.children;

	for (n_t children_idx {0}; children_idx < children.size(); ++children_idx) {
		auto& child_column_descriptor = children[children_idx];

		InterpreterState state;
		auto             child_physical_expr =
		    make_decoding_expression(*child_column_descriptor, column_view.children[children_idx], reader, state);

		internal_exprs.push_back(child_physical_expr);
	}

	//
};
} // namespace fastlanes