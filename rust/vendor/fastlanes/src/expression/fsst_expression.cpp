#include "fls/expression/fsst_expression.hpp"
#include "fls/common/assert.hpp"
#include "fls/common/string.hpp"
#include "fls/expression/decoding_operator.hpp"
#include "fls/expression/interpreter.hpp"
#include "fls/expression/physical_expression.hpp"
#include "fls/expression/rsum_operator.hpp"
#include "fls/expression/scan_operator.hpp"
#include "fls/primitive/fsst/fsst.hpp"
#include "fls/reader/column_view.hpp"
#include "fls/reader/segment.hpp"
#include "fls_gen/untranspose/untranspose.hpp"

namespace fastlanes {
/*--------------------------------------------------------------------------------------------------------------------*\
 * enc_fsst_opr
\*--------------------------------------------------------------------------------------------------------------------*/
enc_fsst_opr::enc_fsst_opr(const PhysicalExpr& expr,
                           const col_pt&       column,
                           ColumnDescriptorT&  column_descriptor,
                           InterpreterState&   state)
    : str_col_view(column)
    , fsst_encoder_p(fsst_helper::make_fsst(str_col_view)) {
	auto& [operator_tokens, operand_tokens] = *column_descriptor.encoding_rpn;

	fsst_bytes.resize(str_col_view.stats.maximum_n_bytes_p_value * CFG::VEC_SZ * 2);

	fsst_header_segment = make_unique<Segment>();
	fsst_header_segment->MakeBlockBased();
	fsst_bytes_segment  = make_unique<Segment>();
	fsst_offset_segment = make_unique<Segment>();

	operand_tokens.emplace_back(state.cur_operand++);
	operand_tokens.emplace_back(state.cur_operand++);
	operand_tokens.emplace_back(state.cur_operand++);
}

enc_fsst_opr::~enc_fsst_opr() {
	fsst_destroy(fsst_encoder_p);
}

void enc_fsst_opr::PointTo(const n_t vec_idx) {
	str_col_view.PointTo(vec_idx);
}

void enc_fsst_opr::Finalize() {
	const auto size = fsst_export(fsst_encoder_p, fsst_header);
	fsst_header_segment->Flush(fsst_header, size);
}

void enc_fsst_opr::Encode() {
	[[maybe_unused]] auto n_encoded_vals = fsst_helper::fsst_compress(fsst_encoder_p,
	                                                                  CFG::VEC_SZ,
	                                                                  str_col_view.FSSTLength(),
	                                                                  str_col_view.FsstString(),
	                                                                  fsst_bytes.capacity(),
	                                                                  fsst_bytes.data(),
	                                                                  fsst_encoded_offset_arr);

	FLS_ASSERT_E(n_encoded_vals, CFG::VEC_SZ)

	n_t encoded_size = fsst_encoded_offset_arr[CFG::VEC_SZ];
	FLS_ASSERT_LE(encoded_size, fsst_bytes.capacity())

	fsst_bytes_segment->Flush(fsst_bytes.data(), encoded_size);
	fsst_offset_segment->Flush(fsst_encoded_offset_arr + 1, sizeof(ofs_t) * CFG::VEC_SZ);
}

void enc_fsst_opr::MoveSegments(vector<up<Segment>>& segments) {
	segments.push_back(std::move(fsst_header_segment));
	segments.push_back(std::move(fsst_bytes_segment));
	segments.push_back(std::move(fsst_offset_segment));
}
/*--------------------------------------------------------------------------------------------------------------------*\
 * dec_fsst_opr
\*--------------------------------------------------------------------------------------------------------------------*/
struct FSSTExprVisitor {
	explicit FSSTExprVisitor(dec_fsst_opr& this_opr)
	    : this_opr(this_opr) {
	}

	void operator()(const sp<dec_scan_opr<ofs_t>>& opr) {
		this_opr.offset_arr = opr->data;
	}
	void operator()(const sp<dec_rsum_opr<ofs_t>>& opr) {
		this_opr.offset_arr = opr->idxs;
	}
	void operator()(std::monostate& arg) {
		FLS_UNREACHABLE_WITH_TYPE(arg);
	}
	void operator()(const auto& arg) {
		FLS_UNREACHABLE_WITH_TYPE(arg);
	}

	dec_fsst_opr& this_opr;
};

dec_fsst_opr::dec_fsst_opr(PhysicalExpr& physical_expr, const ColumnView& column_view, InterpreterState& state)
    : fsst_header_segment_view(column_view.GetSegment(0))
    , fsst_bytes_segment_view(column_view.GetSegment(1))
    , offset_arr(nullptr) {

	visit(FSSTExprVisitor {*this}, physical_expr.operators.back());
	FLS_ASSERT_NOT_NULL_POINTER(offset_arr)

	fsst_header_segment_view.PointTo(0);
	[[maybe_unused]] auto symbol_table_size =
	    fsst_import(&fsst_decoder, reinterpret_cast<uint8_t*>(fsst_header_segment_view.data));

	FLS_ASSERT_E(symbol_table_size, fsst_header_segment_view.data_span.size())

	tmp_string.resize(CFG::String::max_bytes_per_string);
}

void dec_fsst_opr::PointTo(const n_t vec_n) {
	fsst_bytes_segment_view.PointTo(vec_n);
}

void dec_fsst_opr::Decode(vector<uint8_t>& byte_arr_vec, vector<ofs_t>& length_vec) {
	auto* in_byte_arr = reinterpret_cast<uint8_t*>(fsst_bytes_segment_view.data);

	length_vec.resize(length_vec.size() + CFG::VEC_SZ);
	auto* length_pointer = &length_vec.back() + 1 - CFG::VEC_SZ;

	FLS_ASSERT_NOT_NULL_POINTER(length_pointer)

	for (auto i {0}; i < CFG::VEC_SZ; ++i) {
		generated::untranspose::fallback::scalar::untranspose_i(offset_arr, untrasposed_offset);

		len_t encoded_size {0};
		ofs_t offset {0};

		if (i == 0) {
			encoded_size = untrasposed_offset[0];
		} else {
			offset                 = untrasposed_offset[i - 1];
			const auto offset_next = untrasposed_offset[i];
			encoded_size           = offset_next - offset;
		}

		const auto decoded_size = static_cast<ofs_t>(fsst_decompress(
		    &fsst_decoder, encoded_size, in_byte_arr, CFG::String::max_bytes_per_string, tmp_string.data()));

		FLS_ASSERT_L(decoded_size, tmp_string.capacity())

		in_byte_arr += encoded_size;
		length_pointer[i] = decoded_size;
		if (byte_arr_vec.capacity() - byte_arr_vec.size() < CFG::String::max_bytes_per_string) {
			byte_arr_vec.reserve(byte_arr_vec.size() + 1024 * CFG::String::max_bytes_per_string);
		}
		byte_arr_vec.insert(byte_arr_vec.end(), tmp_string.begin(), tmp_string.begin() + decoded_size);
	}

	//
	FLS_ASSERT_NOT_NULL_POINTER(length_pointer)
}
} // namespace fastlanes
