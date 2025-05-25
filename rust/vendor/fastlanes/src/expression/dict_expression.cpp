#include "fls/expression/dict_expression.hpp"
#include "fls/common/assert.hpp"
#include "fls/common/string.hpp"
#include "fls/expression/decoding_operator.hpp"
#include "fls/expression/interpreter.hpp"
#include "fls/expression/physical_expression.hpp"
#include "fls/reader/column_view.hpp"
#include "fls/reader/segment.hpp"

namespace fastlanes {
/*--------------------------------------------------------------------------------------------------------------------*\
 * enc_dict_opr
\*--------------------------------------------------------------------------------------------------------------------*/
template <typename INDEX_PT>
struct DictExprVisitor {
	explicit DictExprVisitor(const INDEX_PT*& index_arr)
	    : index_arr(index_arr) {
	}

	const INDEX_PT*& index_arr;

	void operator()(const sp<dec_unffor_opr<INDEX_PT>>& opr) {
		index_arr = opr->Data();
	}
	void operator()(const sp<PhysicalExpr>& expr) {
		visit(DictExprVisitor {index_arr}, expr->operators[0]);
	}
	void operator()(std::monostate&) {
		FLS_UNREACHABLE();
	}
	void operator()(const auto& arg) {
		FLS_UNREACHABLE_WITH_TYPE(arg);
	}
};

template <typename VALUE_PT>
enc_dict_opr<VALUE_PT>::enc_dict_opr(const PhysicalExpr& expr,
                                     const col_pt&       column,
                                     ColumnDescriptorT&  column_descriptor,
                                     InterpreterState&   state)
    : typed_column_view(column) {
	auto& [operator_tokens, operand_tokens] = *column_descriptor.encoding_rpn;
	operand_tokens.emplace_back(state.cur_operand++);
	state.cur_operator++;
	key_segment = make_unique<Segment>();
	key_segment->MakeBlockBased();
}

template <typename KEY_P>
void enc_dict_opr<KEY_P>::Finalize() {
	// init
	[[maybe_unused]] const auto& bimap_frequency = typed_column_view.GetStats()->bimap_frequency;

	auto* key_p = key_segment->GetFixedSizeArray<KEY_P>(bimap_frequency.size());

	for (const auto& [key, idx] : bimap_frequency.value_to_key) {
		key_p[idx] = key;
	}
}

template <typename KEY_PT>
void enc_dict_opr<KEY_PT>::MoveSegments(vector<up<Segment>>& segments) {
	segments.push_back(std::move(key_segment));
}

template struct enc_dict_opr<i64_pt>;
template struct enc_dict_opr<i32_pt>;
template struct enc_dict_opr<i16_pt>;
template struct enc_dict_opr<i08_pt>;
template struct enc_dict_opr<dbl_pt>;
template struct enc_dict_opr<flt_pt>;

/*--------------------------------------------------------------------------------------------------------------------*\
 * enc_dict_opr
\*--------------------------------------------------------------------------------------------------------------------*/
enc_dict_opr<fls_string_t>::enc_dict_opr(const PhysicalExpr& expr,
                                         const col_pt&       column,
                                         ColumnDescriptorT&  column_descriptor,
                                         InterpreterState&   state)
    : col_view {column} {
	offset_segment = make_unique<Segment>();
	bytes_segment  = make_unique<Segment>();

	auto& [operator_tokens, operand_tokens] = *column_descriptor.encoding_rpn;
	operand_tokens.emplace_back(state.cur_operand++);
	operand_tokens.emplace_back(state.cur_operand++);
	state.cur_operator++;
}

void enc_dict_opr<fls_string_t>::PointTo(n_t vec_idx) {
}
void enc_dict_opr<fls_string_t>::Encode() {
}

void enc_dict_opr<fls_string_t>::MoveSegments(vector<up<Segment>>& segments) {
	segments.push_back(std::move(offset_segment));
	segments.push_back(std::move(bytes_segment));
}

void enc_dict_opr<fls_string_t>::Finalize() {
	auto length_buf = make_unique<Buf>();
	auto bytes_buf  = make_unique<Buf>();
	// init
	[[maybe_unused]] const auto& bimap     = col_view.stats.bimap;
	[[maybe_unused]] const auto& string_ps = col_view.string_p;

	FLS_ASSERT_FALSE(bimap.empty())
	FLS_ASSERT_FALSE(bimap.empty())

	len_t cur_offset {0};
	for (n_t dict_value_idx {0}; dict_value_idx < bimap.size(); dict_value_idx++) {
		const fls_string_t& current_fls_string = bimap.get_key(dict_value_idx);
		bytes_buf->Append(current_fls_string.p, current_fls_string.length);
		cur_offset = cur_offset + current_fls_string.length;
		length_buf->Append(&cur_offset, sizeof(ofs_t));
	}

	bytes_segment->Flush(bytes_buf->data(), bytes_buf->Size());
	offset_segment->Flush(length_buf->data(), length_buf->Size());
}

/*--------------------------------------------------------------------------------------------------------------------*\
 * dec_dict_opr
\*--------------------------------------------------------------------------------------------------------------------*/
template <typename KEY_PT, typename INDEX_PT>
dec_dict_opr<KEY_PT, INDEX_PT>::dec_dict_opr(const PhysicalExpr& physical_expr,
                                             const ColumnView&   column_view,
                                             InterpreterState&   state)
    : key_segment_view(
          column_view.GetSegment(column_view.column_descriptor.encoding_rpn->operand_tokens[state.cur_operand - 0]))
    , index_arr(nullptr) {

	state.cur_operand = state.cur_operand - 1;
	visit(DictExprVisitor<INDEX_PT> {index_arr}, physical_expr.operators[0]);
}

template <typename KEY_PT, typename INDEX_PT>
KEY_PT* dec_dict_opr<KEY_PT, INDEX_PT>::Keys() {
	return reinterpret_cast<KEY_PT*>(key_segment_view.data_span.data());
}

template <typename KEY_PT, typename INDEX_PT>
const INDEX_PT* dec_dict_opr<KEY_PT, INDEX_PT>::Index() {
	FLS_ASSERT_NOT_NULL_POINTER(index_arr)
	return index_arr;
}

template struct dec_dict_opr<i64_pt, u32_pt>;
template struct dec_dict_opr<i64_pt, u16_pt>;
template struct dec_dict_opr<i64_pt, u08_pt>;
template struct dec_dict_opr<i32_pt, u32_pt>;
template struct dec_dict_opr<i32_pt, u16_pt>;
template struct dec_dict_opr<i32_pt, u08_pt>;
template struct dec_dict_opr<i16_pt, u16_pt>;
template struct dec_dict_opr<i16_pt, u08_pt>;
template struct dec_dict_opr<i08_pt, u08_pt>;
template struct dec_dict_opr<dbl_pt, u32_pt>;
template struct dec_dict_opr<dbl_pt, u16_pt>;
template struct dec_dict_opr<dbl_pt, u08_pt>;
template struct dec_dict_opr<flt_pt, u32_pt>;
template struct dec_dict_opr<flt_pt, u16_pt>;
template struct dec_dict_opr<flt_pt, u08_pt>;
template <typename INDEX_PT>
dec_dict_opr<fls_string_t, INDEX_PT>::dec_dict_opr(const PhysicalExpr& physical_expr,
                                                   const ColumnView&   column_view,
                                                   InterpreterState&   state)
    : dict_offsets_segment(column_view.GetSegment(0))
    , dict_bytes_segment(column_view.GetSegment(1))
    , index_arr(nullptr) {

	state.cur_operand = state.cur_operand - 1;
	visit(DictExprVisitor<INDEX_PT> {index_arr}, physical_expr.operators[0]);
}

template <typename INDEX_PT>
const INDEX_PT* dec_dict_opr<fls_string_t, INDEX_PT>::Index() {
	FLS_ASSERT_NOT_NULL_POINTER(index_arr)
	return index_arr;
}

template <typename INDEX_PT>
const ofs_t* dec_dict_opr<fls_string_t, INDEX_PT>::Offsets() {
	return reinterpret_cast<ofs_t*>(dict_offsets_segment.data_span.data());
}

template <typename INDEX_PT>
const uint8_t* dec_dict_opr<fls_string_t, INDEX_PT>::Bytes() {
	return reinterpret_cast<uint8_t*>(dict_bytes_segment.data_span.data());
};

template <typename INDEX_PT>
void dec_dict_opr<fls_string_t, INDEX_PT>::Decode(vector<uint8_t>& byte_arr_vec, vector<ofs_t>& length_vec) {
	length_vec.resize(length_vec.size() + CFG::VEC_SZ);
	auto* length_pointer = &length_vec.back() + 1 - CFG::VEC_SZ;

	FLS_ASSERT_NOT_NULL_POINTER(index_arr)
	FLS_ASSERT_NOT_NULL_POINTER(Offsets())
	FLS_ASSERT_NOT_NULL_POINTER(Bytes())

	for (n_t idx {0}; idx < CFG::VEC_SZ; ++idx) {
		const auto index = Index()[idx];
		ofs_t      offset;

		if (index == 0) {
			offset = 0;
		} else {
			offset = Offsets()[index - 1];
		}
		const auto offset_next = Offsets()[index];
		const auto length      = offset_next - offset;
		length_pointer[idx]    = length;

		if (byte_arr_vec.capacity() - byte_arr_vec.size() < CFG::String::max_bytes_per_string) {
			byte_arr_vec.reserve(byte_arr_vec.size() + 1024 * CFG::String::max_bytes_per_string);
		}
		byte_arr_vec.insert(byte_arr_vec.end(), Bytes() + offset, Bytes() + offset_next);
	}
}

template struct dec_dict_opr<fls_string_t, u32_pt>;
template struct dec_dict_opr<fls_string_t, u16_pt>;
template struct dec_dict_opr<fls_string_t, u08_pt>;

} // namespace fastlanes