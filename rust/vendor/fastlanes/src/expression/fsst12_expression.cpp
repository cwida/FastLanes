#include "fls/expression/fsst12_expression.hpp"
#include "fls/common/assert.hpp"
#include "fls/common/string.hpp"
#include "fls/expression/decoding_operator.hpp"
#include "fls/expression/interpreter.hpp"
#include "fls/expression/physical_expression.hpp"
#include "fls/expression/rsum_operator.hpp"
#include "fls/expression/scan_operator.hpp"
#include "fls/primitive/fsst12/fsst12.hpp"
#include "fls/reader/column_view.hpp"
#include "fls/reader/segment.hpp"
#include "fls_gen/untranspose/untranspose.hpp"

namespace fastlanes {
/*--------------------------------------------------------------------------------------------------------------------*\
 * enc_fsst12_opr
\*--------------------------------------------------------------------------------------------------------------------*/
enc_fsst12_opr::enc_fsst12_opr(const PhysicalExpr& expr,
                               const col_pt&       column,
                               ColumnDescriptorT&  column_descriptor,
                               InterpreterState&   state)
    : str_col_view(column)
    , fsst12_encoder_p(fsst12_helper::make_fsst12(str_col_view)) {
	auto& [operator_tokens, operand_tokens] = *column_descriptor.encoding_rpn;

	fsst12_bytes.resize(str_col_view.stats.maximum_n_bytes_p_value * CFG::VEC_SZ * 4);

	fsst12_header_segment = make_unique<Segment>();
	fsst12_header_segment->MakeBlockBased();
	fsst12_bytes_segment  = make_unique<Segment>();
	fsst12_offset_segment = make_unique<Segment>();

	operand_tokens.emplace_back(state.cur_operand++);
	operand_tokens.emplace_back(state.cur_operand++);
	operand_tokens.emplace_back(state.cur_operand++);
}

enc_fsst12_opr::~enc_fsst12_opr() {
	fsst12_destroy(fsst12_encoder_p);
}

void enc_fsst12_opr::PointTo(const n_t vec_idx) {
	str_col_view.PointTo(vec_idx);
}

void enc_fsst12_opr::Finalize() {
	const auto size = fsst12_export(fsst12_encoder_p, fsst12_header);
	fsst12_header_segment->Flush(fsst12_header, size);
}

void enc_fsst12_opr::Encode() {
	[[maybe_unused]] auto n_encoded_vals = fsst12_helper::fsst12_compress(fsst12_encoder_p,
	                                                                      CFG::VEC_SZ,
	                                                                      str_col_view.FSSTLength(),
	                                                                      str_col_view.FsstString(),
	                                                                      fsst12_bytes.capacity(),
	                                                                      fsst12_bytes.data(),
	                                                                      fsst12_encoded_offset_arr);

	FLS_ASSERT_E(n_encoded_vals, CFG::VEC_SZ)

	n_t encoded_size = fsst12_encoded_offset_arr[CFG::VEC_SZ];
	FLS_ASSERT_LE(encoded_size, fsst12_bytes.capacity())

	fsst12_bytes_segment->Flush(fsst12_bytes.data(), encoded_size);
	fsst12_offset_segment->Flush(fsst12_encoded_offset_arr + 1, sizeof(ofs_t) * CFG::VEC_SZ);
}

void enc_fsst12_opr::MoveSegments(vector<up<Segment>>& segments) {
	segments.push_back(std::move(fsst12_header_segment));
	segments.push_back(std::move(fsst12_bytes_segment));
	segments.push_back(std::move(fsst12_offset_segment));
}
/*--------------------------------------------------------------------------------------------------------------------*\
 * dec_fsst12_opr
\*--------------------------------------------------------------------------------------------------------------------*/
struct FSST12ExprVisitor {
	explicit FSST12ExprVisitor(dec_fsst12_opr& this_opr)
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

	dec_fsst12_opr& this_opr;
};

dec_fsst12_opr::dec_fsst12_opr(PhysicalExpr& physical_expr, const ColumnView& column_view, InterpreterState& state)
    : fsst12_header_segment_view(column_view.GetSegment(0))
    , fsst12_bytes_segment_view(column_view.GetSegment(1))
    , offset_arr(nullptr) {

	visit(FSST12ExprVisitor {*this}, physical_expr.operators.back());
	FLS_ASSERT_NOT_NULL_POINTER(offset_arr)

	fsst12_header_segment_view.PointTo(0);
	[[maybe_unused]] auto symbol_table_size =
	    fsst12_import(&fsst12_decoder, reinterpret_cast<uint8_t*>(fsst12_header_segment_view.data));

	FLS_ASSERT_E(symbol_table_size, fsst12_header_segment_view.data_span.size())

	tmp_string.resize(CFG::String::max_bytes_per_string);
}

void dec_fsst12_opr::PointTo(const n_t vec_n) {
	fsst12_bytes_segment_view.PointTo(vec_n);
}

void dec_fsst12_opr::Decode(vector<uint8_t>& byte_arr_vec, vector<ofs_t>& length_vec) {
	auto* in_byte_arr = reinterpret_cast<uint8_t*>(fsst12_bytes_segment_view.data);

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

		const auto decoded_size = static_cast<ofs_t>(fsst12_decompress(
		    &fsst12_decoder, encoded_size, in_byte_arr, CFG::String::max_bytes_per_string, tmp_string.data()));

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
