#include "fls/expression/fsst12_dict_operator.hpp"
#include "fls/common/assert.hpp"
#include "fls/common/string.hpp"
#include "fls/expression/decoding_operator.hpp"
#include "fls/expression/interpreter.hpp"
#include "fls/expression/physical_expression.hpp"
#include "fls/primitive/fsst12/fsst12.hpp"
#include "fls/reader/column_view.hpp"
#include "fls/reader/segment.hpp"

namespace fastlanes {
template <typename INDEX_PT>
struct FSST12DictExprVisitor {
	explicit FSST12DictExprVisitor(const INDEX_PT*& index_arr)
	    : index_arr(index_arr) {
	}

	const INDEX_PT*& index_arr;

	void operator()(const sp<dec_unffor_opr<INDEX_PT>>& opr) {
		index_arr = opr->Data();
	}
	void operator()(const sp<PhysicalExpr>& expr) {
		visit(FSST12DictExprVisitor {index_arr}, expr->operators[0]);
	}
	void operator()(std::monostate&) {
		FLS_UNREACHABLE();
	}
	void operator()(const auto& arg) {
		FLS_UNREACHABLE_WITH_TYPE(arg);
	}
};

enc_fsst12_dict_opr::enc_fsst12_dict_opr(const PhysicalExpr& expr,
                                         const col_pt&       column,
                                         ColumnDescriptorT&  column_descriptor,
                                         InterpreterState&   state)
    : col_view {column} {

	fsst12_header_segment = make_unique<Segment>();
	fsst12_header_segment->MakeBlockBased();
	fsst12_bytes_segment = make_unique<Segment>();
	fsst12_bytes_segment->MakeBlockBased();
	fsst12_offset_segment = make_unique<Segment>();
	fsst12_offset_segment->MakeBlockBased();
	length_buf       = make_unique<Buf>();
	bytes_buf        = make_unique<Buf>();
	string_p_buf     = make_unique<Buf>();
	fsst12_bytes_buf = make_unique<Buf>();
	out_offset_buf   = make_unique<Buf>();

	auto& [operator_tokens, operand_tokens] = *column_descriptor.encoding_rpn;
	operand_tokens.emplace_back(state.cur_operand++);
	operand_tokens.emplace_back(state.cur_operand++);
	operand_tokens.emplace_back(state.cur_operand++);
	state.cur_operator++;
}

void enc_fsst12_dict_opr::PointTo(n_t vec_idx) {
}
void enc_fsst12_dict_opr::Encode() {
}

void enc_fsst12_dict_opr::MoveSegments(vector<up<Segment>>& segments) {
	segments.push_back(std::move(fsst12_header_segment));
	segments.push_back(std::move(fsst12_bytes_segment));
	segments.push_back(std::move(fsst12_offset_segment));
}

void enc_fsst12_dict_opr::Finalize() {
	// init
	[[maybe_unused]] const auto& bimap     = col_view.stats.bimap;
	[[maybe_unused]] const auto& string_ps = col_view.string_p;

	const auto n_dict_vals = bimap.size();

	FLS_ASSERT_FALSE(bimap.empty())

	for (n_t dict_value_idx {0}; dict_value_idx < bimap.size(); dict_value_idx++) {
		const fls_string_t& current_fls_string = bimap.get_key(dict_value_idx);
		bytes_buf->Append(current_fls_string.p, current_fls_string.length);
		length_buf->Append(&current_fls_string.length, sizeof(ofs_t));
		uint8_t* string_p = bytes_buf->end() - current_fls_string.length;
		string_p_buf->Append(&string_p, sizeof(uint8_t*));
	}

	// fsst12 header
	auto*      fsst12_encoder_p = fsst12_helper::make_fsst12(n_dict_vals, *length_buf, *string_p_buf);
	const auto size             = fsst12_export(fsst12_encoder_p, fsst12_header);
	fsst12_header_segment->Flush(fsst12_header, size);

	// encode
	const auto n_encoded_vals = fsst12_helper::fsst12_compress(fsst12_encoder_p,
	                                                           n_dict_vals,
	                                                           length_buf->mutable_data<len_t>(),
	                                                           string_p_buf->mutable_data<uint8_t*>(),
	                                                           fsst12_bytes_buf->Capacity(),
	                                                           fsst12_bytes_buf->mutable_data<uint8_t>(),
	                                                           out_offset_buf->mutable_data<ofs_t>());

	FLS_ASSERT_E(n_encoded_vals, n_dict_vals)

	const auto encoded_size = out_offset_buf->mutable_data<ofs_t>()[n_encoded_vals];
	fsst12_bytes_segment->Flush(fsst12_bytes_buf->data(), encoded_size);
	fsst12_offset_segment->Flush(out_offset_buf->data() + sizeof(len_t), sizeof(len_t) * (n_encoded_vals));

	fsst12_destroy(fsst12_encoder_p);
}

template <typename INDEX_PT>
dec_fsst12_dict_opr<INDEX_PT>::dec_fsst12_dict_opr(const PhysicalExpr& physical_expr,
                                                   const ColumnView&   column_view,
                                                   InterpreterState&   state)
    : fsst12_header_segment_view(
          column_view.GetSegment(column_view.column_descriptor.encoding_rpn->operand_tokens[state.cur_operand - 2]))
    , fsst12_bytes_segment_view(
          column_view.GetSegment(column_view.column_descriptor.encoding_rpn->operand_tokens[state.cur_operand - 1]))
    , fsst12_offset_segment_view(
          column_view.GetSegment(column_view.column_descriptor.encoding_rpn->operand_tokens[state.cur_operand - 0]))
    , index_arr(nullptr) {

	visit(FSST12DictExprVisitor<INDEX_PT> {index_arr}, physical_expr.operators[0]);
	tmp_string.resize(CFG::String::max_bytes_per_string);

	fsst12_header_segment_view.PointTo(0);
	fsst12_bytes_segment_view.PointTo(0);
	fsst12_offset_segment_view.PointTo(0);

	[[maybe_unused]] auto symbol_table_size =
	    fsst12_import(&fsst12_decoder, reinterpret_cast<uint8_t*>(fsst12_header_segment_view.data));

	FLS_ASSERT_E(symbol_table_size, fsst12_header_segment_view.data_span.size())
}

template <typename INDEX_PT>
const INDEX_PT* dec_fsst12_dict_opr<INDEX_PT>::Index() {
	FLS_ASSERT_NOT_NULL_POINTER(index_arr)
	return index_arr;
}

template <typename INDEX_PT>
const ofs_t* dec_fsst12_dict_opr<INDEX_PT>::Offsets() {
	return reinterpret_cast<ofs_t*>(fsst12_offset_segment_view.data_span.data());
}

template <typename INDEX_PT>
const uint8_t* dec_fsst12_dict_opr<INDEX_PT>::Bytes() {
	return reinterpret_cast<uint8_t*>(fsst12_bytes_segment_view.data_span.data());
};

template <typename INDEX_PT>
void dec_fsst12_dict_opr<INDEX_PT>::Decode(vector<uint8_t>& byte_arr_vec, vector<ofs_t>& length_vec) {
	length_vec.resize(length_vec.size() + CFG::VEC_SZ);
	auto* length_pointer = &length_vec.back() + 1 - CFG::VEC_SZ;
	auto* in_byte_arr    = reinterpret_cast<uint8_t*>(fsst12_bytes_segment_view.data);

	FLS_ASSERT_NOT_NULL_POINTER(in_byte_arr)
	FLS_ASSERT_NOT_NULL_POINTER(length_pointer)

	for (n_t idx {0}; idx < CFG::VEC_SZ; ++idx) {
		const auto index = Index()[idx];

		ofs_t offset = 0;
		len_t length = 0;

		if (index == 0) {
			offset = 0;
			length = Offsets()[index];
		} else {
			offset                 = Offsets()[index - 1];
			const auto offset_next = Offsets()[index];
			length                 = offset_next - offset;
		}

		const auto decoded_size = static_cast<ofs_t>(fsst12_decompress(
		    &fsst12_decoder, length, in_byte_arr + offset, CFG::String::max_bytes_per_string, tmp_string.data()));

		FLS_ASSERT_L(decoded_size, tmp_string.capacity())

		length_pointer[idx] = decoded_size;

		if (byte_arr_vec.capacity() - byte_arr_vec.size() < CFG::String::max_bytes_per_string) {
			byte_arr_vec.reserve(byte_arr_vec.size() + 1024 * CFG::String::max_bytes_per_string);
		}
		byte_arr_vec.insert(byte_arr_vec.end(), tmp_string.begin(), tmp_string.begin() + decoded_size);
	}
}

template struct dec_fsst12_dict_opr<u32_pt>;
template struct dec_fsst12_dict_opr<u16_pt>;
template struct dec_fsst12_dict_opr<u08_pt>;

} // namespace fastlanes