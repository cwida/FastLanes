#include "fls/expression/alp_expression.hpp"
#include "fls/common/string.hpp"
#include "fls/cor/lyt/buf.hpp"
#include "fls/expression/decoding_operator.hpp"
#include "fls/expression/physical_expression.hpp"
#include "fls/primitive/bitpack/bitpack.hpp"
#include "fls/reader/column_view.hpp"
#include "fls/reader/segment.hpp"
#include "fls/unffor.hpp"
#include <cstring>

namespace fastlanes {
/*--------------------------------------------------------------------------------------------------------------------*\
 * enc_alp_opr
\*--------------------------------------------------------------------------------------------------------------------*/
template <typename PT>
enc_alp_opr<PT>::enc_alp_opr(const PhysicalExpr& expr,
                             const col_pt&       column,
                             ColumnDescriptorT&  column_descriptor,
                             InterpreterState&   state)
    : typed_column_view(column)
    , pos_arr {} {
	alp::encoder<PT>::init(typed_column_view.Data(0), typed_column_view.TotalSize(), sample_arr, alp_state);

	ffor_segment      = make_unique<Segment>();
	base_segment      = make_unique<Segment>();
	bw_segment        = make_unique<Segment>();
	exception_segment = make_unique<Segment>();
	fac_segment       = make_unique<Segment>();
	exp_segment       = make_unique<Segment>();
	pos_segment       = make_unique<Segment>();
	n_exp_segment     = make_unique<Segment>();
}

template <typename PT>
void enc_alp_opr<PT>::PointTo(n_t vec_idx) {
	typed_column_view.PointTo(vec_idx);
}

template <typename PT>
n_t calculate_alp_exception_vector_size(const uint16_t n_exc) {
	//
	return n_exc * sizeof(PT);
}

n_t calculate_alp_pos_vector_size(const uint16_t n_exc) {
	//
	return n_exc * sizeof(uint16_t);
}

template <typename PT>
void enc_alp_opr<PT>::Encode() {

	const auto* cur_vec_p = typed_column_view.Data();

	typename alp::inner_t<PT>::st base;

	alp::encoder<PT, true>::encode(cur_vec_p, exc_arr, pos_arr, encoded_arr, alp_state, typed_column_view.NullMap());
	alp::encoder<PT>::analyze_ffor(encoded_arr, alp_state.bit_width, &base);
	ffor::ffor(encoded_arr, ffor_arr, alp_state.bit_width, &base);

	const n_t bytes        = calculate_bitpacked_vector_size(alp_state.bit_width);
	const n_t exc_arr_size = calculate_alp_exception_vector_size<PT>(alp_state.n_exceptions);
	const n_t pos_arr_size = calculate_alp_pos_vector_size(alp_state.n_exceptions);

	bw_segment->Flush(&alp_state.bit_width, sizeof(bw_t));
	base_segment->Flush(&base, sizeof(typename alp::inner_t<PT>::st));
	ffor_segment->Flush(ffor_arr, bytes);
	exception_segment->Flush(exc_arr, exc_arr_size);
	fac_segment->Flush(&alp_state.fac, sizeof(uint8_t));
	exp_segment->Flush(&alp_state.exp, sizeof(uint8_t));
	pos_segment->Flush(pos_arr, pos_arr_size);
	n_exp_segment->Flush(&alp_state.n_exceptions, sizeof(uint16_t));
}

template <typename PT>
void enc_alp_opr<PT>::MoveSegments(vector<up<Segment>>& segments) {

	segments.push_back(std::move(ffor_segment));
	segments.push_back(std::move(base_segment));
	segments.push_back(std::move(bw_segment));
	segments.push_back(std::move(exception_segment));
	segments.push_back(std::move(fac_segment));
	segments.push_back(std::move(exp_segment));
	segments.push_back(std::move(pos_segment));
	segments.push_back(std::move(n_exp_segment));
}

template struct enc_alp_opr<dbl_pt>;
template struct enc_alp_opr<flt_pt>;

/*--------------------------------------------------------------------------------------------------------------------*\
 * dec_alp_opr
\*--------------------------------------------------------------------------------------------------------------------*/
template <typename PT>
dec_alp_opr<PT>::dec_alp_opr(const ColumnView& column_view, InterpreterState& state) //
    : ffor_segment_view(column_view.GetSegment(0))
    , base_segment_view(column_view.GetSegment(1))
    , bitwidth_segment_view(column_view.GetSegment(2))
    , exception_segment_view(column_view.GetSegment(3))
    , fac_segment_view(column_view.GetSegment(4))
    , exp_segment_view(column_view.GetSegment(5))
    , pos_segment_view(column_view.GetSegment(6))
    , n_exp_segment_view(column_view.GetSegment(7)) {
}

template <typename PT>
void dec_alp_opr<PT>::PointTo(const n_t vec_n) {
	ffor_segment_view.PointTo(vec_n);
	base_segment_view.PointTo(vec_n);
	bitwidth_segment_view.PointTo(vec_n);
	exception_segment_view.PointTo(vec_n);
	fac_segment_view.PointTo(vec_n);
	exp_segment_view.PointTo(vec_n);
	pos_segment_view.PointTo(vec_n);
	n_exp_segment_view.PointTo(vec_n);
}

template <typename PT>
void dec_alp_opr<PT>::Decode(n_t vec_idx) {
	PointTo(vec_idx);

	const auto* ffor_arr   = reinterpret_cast<const typename alp::inner_t<PT>::st*>(ffor_segment_view.data);
	const auto* base_p     = reinterpret_cast<const typename alp::inner_t<PT>::st*>(base_segment_view.data);
	const auto* bw_p       = reinterpret_cast<const bw_t*>(bitwidth_segment_view.data);
	const auto* exc_arr_p  = reinterpret_cast<const PT*>(exception_segment_view.data);
	const auto* fac_p      = reinterpret_cast<const uint8_t*>(fac_segment_view.data);
	const auto* exp_p      = reinterpret_cast<const uint8_t*>(exp_segment_view.data);
	const auto* pos_arr    = reinterpret_cast<const uint16_t*>(pos_segment_view.data);
	const auto* n_exp_arr  = reinterpret_cast<const uint16_t*>(n_exp_segment_view.data);
	alp_state.n_exceptions = n_exp_arr[0];

	FLS_ASSERT_POINTER(ffor_arr);

	unffor::unffor(ffor_arr, unffor_arr, *bw_p, base_p);
	alp::decoder<PT>::decode(unffor_arr, *fac_p, *exp_p, decoded_arr);
	alp::decoder<PT>::patch_exceptions(decoded_arr, exc_arr_p, pos_arr, alp_state);
}

template struct dec_alp_opr<dbl_pt>;
template struct dec_alp_opr<flt_pt>;
/*--------------------------------------------------------------------------------------------------------------------*\
 * enc_alp_rd_opr
\*--------------------------------------------------------------------------------------------------------------------*/
template <typename PT>
enc_alp_rd_opr<PT>::enc_alp_rd_opr(const PhysicalExpr& expr,
                                   const col_pt&       column,
                                   ColumnDescriptorT&  column_descriptor,
                                   InterpreterState&   state)
    : typed_column_view(column)
    , rd_exc_arr {}
    , l_arr {}
    , l_ffor_arr {}
    , pos_arr {} {

	alp::rd_encoder<PT>::init(typed_column_view.Data(0), typed_column_view.TotalSize(), sample_arr, alp_state);

	l_ffor_segment       = make_unique<Segment>();
	l_bw_segment         = make_unique<Segment>();
	l_base_segment       = make_unique<Segment>();
	r_bw_segment         = make_unique<Segment>();
	r_base_segment       = make_unique<Segment>();
	r_ffor_segment       = make_unique<Segment>();
	rd_exception_segment = make_unique<Segment>();
	rd_pos_segment       = make_unique<Segment>();
	rd_n_exc_segment     = make_unique<Segment>();
	rd_dict_segment      = make_unique<Segment>();
	rd_dict_segment->MakeBlockBased();
}
template <typename PT>
void enc_alp_rd_opr<PT>::PointTo(n_t vec_idx) {
	typed_column_view.PointTo(vec_idx);
}

template <typename PT>
void enc_alp_rd_opr<PT>::Finalize() {
	rd_dict_segment->Flush(alp_state.left_parts_dict, sizeof(uint16_t) * alp::config::MAX_RD_DICTIONARY_SIZE);
}

template <typename PT>
void enc_alp_rd_opr<PT>::Encode() {
	const auto* cur_vec_p = typed_column_view.Data();

	alp::rd_encoder<PT>::encode(cur_vec_p, rd_exc_arr, pos_arr, r_arr, l_arr, alp_state);
	ffor::ffor(r_arr, r_ffor_arr, alp_state.right_bit_width, &alp_state.right_for_base);
	ffor::ffor(l_arr, l_ffor_arr, alp_state.left_bit_width, &alp_state.left_for_base);

	const n_t r_bytes      = calculate_bitpacked_vector_size(alp_state.right_bit_width);
	const n_t l_bytes      = calculate_bitpacked_vector_size(alp_state.left_bit_width);
	const n_t exc_arr_size = calculate_alp_exception_vector_size<uint16_t>(alp_state.n_exceptions);
	const n_t pos_arr_size = calculate_alp_pos_vector_size(alp_state.n_exceptions);

	// Flushing segments
	l_bw_segment->Flush(&alp_state.left_bit_width, sizeof(bw_t));
	l_base_segment->Flush(&alp_state.left_for_base, sizeof(uint16_t));
	l_ffor_segment->Flush(l_ffor_arr, l_bytes);

	r_bw_segment->Flush(&alp_state.right_bit_width, sizeof(bw_t));
	r_base_segment->Flush(&alp_state.right_for_base, sizeof(typename alp::inner_t<PT>::ut));
	r_ffor_segment->Flush(r_ffor_arr, r_bytes);

	rd_exception_segment->Flush(rd_exc_arr, exc_arr_size);
	rd_pos_segment->Flush(pos_arr, pos_arr_size);
	rd_n_exc_segment->Flush(&alp_state.n_exceptions, sizeof(uint16_t));
}

template <typename PT>
void enc_alp_rd_opr<PT>::MoveSegments(vector<up<Segment>>& segments) {
	segments.push_back(std::move(l_ffor_segment));
	segments.push_back(std::move(l_bw_segment));
	segments.push_back(std::move(l_base_segment));
	segments.push_back(std::move(r_ffor_segment));
	segments.push_back(std::move(r_bw_segment));
	segments.push_back(std::move(r_base_segment));
	segments.push_back(std::move(rd_exception_segment));
	segments.push_back(std::move(rd_pos_segment));
	segments.push_back(std::move(rd_n_exc_segment));
	segments.push_back(std::move(rd_dict_segment));
}

template struct enc_alp_rd_opr<dbl_pt>;
template struct enc_alp_rd_opr<flt_pt>;
/*--------------------------------------------------------------------------------------------------------------------*\
 * dec_alp_rd_opr
\*--------------------------------------------------------------------------------------------------------------------*/
template <typename PT>
dec_alp_rd_opr<PT>::dec_alp_rd_opr(const ColumnView& column_view, InterpreterState& state) //
    : l_ffor_segment_view(column_view.GetSegment(0))
    , l_bw_segment_view(column_view.GetSegment(1))
    , l_base_segment_view(column_view.GetSegment(2))
    , r_ffor_segment_view(column_view.GetSegment(3))
    , r_bw_segment_view(column_view.GetSegment(4))
    , r_base_segment_view(column_view.GetSegment(5))
    , rd_exception_segment_view(column_view.GetSegment(6))
    , rd_pos_segment_view(column_view.GetSegment(7))
    , rd_n_exc_segment_view(column_view.GetSegment(8))
    , rd_dict_segment_view(column_view.GetSegment(9))
    , unffor_left_arr {} {

	rd_dict_segment_view.PointTo(0);
	std::memcpy(alp_state.left_parts_dict, rd_dict_segment_view.data, 16);
}

template <typename PT>
void dec_alp_rd_opr<PT>::PointTo(const n_t vec_n) {
	l_ffor_segment_view.PointTo(vec_n);
	l_bw_segment_view.PointTo(vec_n);
	l_base_segment_view.PointTo(vec_n);
	r_bw_segment_view.PointTo(vec_n);
	r_base_segment_view.PointTo(vec_n);
	r_ffor_segment_view.PointTo(vec_n);
	rd_exception_segment_view.PointTo(vec_n);
	rd_pos_segment_view.PointTo(vec_n);
	rd_n_exc_segment_view.PointTo(vec_n);
}

template <typename PT>
void dec_alp_rd_opr<PT>::Decode(n_t vec_idx) {
	PointTo(vec_idx);

	const auto* l_ffor_arr = reinterpret_cast<const uint16_t*>(l_ffor_segment_view.data);
	const auto* l_bw_p     = reinterpret_cast<bw_t*>(l_bw_segment_view.data);
	const auto* l_base_p   = reinterpret_cast<uint16_t*>(l_base_segment_view.data);

	const auto* r_ffor_arr = reinterpret_cast<const typename alp::inner_t<PT>::ut*>(r_ffor_segment_view.data);
	auto*       r_bw_p     = reinterpret_cast<bw_t*>(r_bw_segment_view.data);
	auto*       r_base_p   = reinterpret_cast<typename alp::inner_t<PT>::ut*>(r_base_segment_view.data);

	auto* rd_exc_arr_p        = reinterpret_cast<uint16_t*>(rd_exception_segment_view.data);
	auto* rd_pos_arr_p        = reinterpret_cast<uint16_t*>(rd_pos_segment_view.data);
	auto* rd_n_exc_arr        = reinterpret_cast<uint16_t*>(rd_n_exc_segment_view.data);
	alp_state.n_exceptions    = rd_n_exc_arr[0];
	alp_state.left_bit_width  = *l_bw_p;
	alp_state.right_bit_width = *r_bw_p;

	FLS_ASSERT_POINTER(l_ffor_arr);
	FLS_ASSERT_POINTER(r_ffor_arr);

	unffor::unffor(r_ffor_arr, unffor_right_arr, *r_bw_p, r_base_p);
	unffor::unffor(l_ffor_arr, unffor_left_arr, *l_bw_p, l_base_p);
	alp::rd_encoder<PT>::decode(glue_arr, unffor_right_arr, unffor_left_arr, rd_exc_arr_p, rd_pos_arr_p, alp_state);
}

template struct dec_alp_rd_opr<dbl_pt>;
template struct dec_alp_rd_opr<flt_pt>;

} // namespace fastlanes
