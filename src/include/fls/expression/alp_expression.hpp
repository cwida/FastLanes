#ifndef FLS_EXPRESSION_ALP_EXPRESSION_HPP
#define FLS_EXPRESSION_ALP_EXPRESSION_HPP

#include "alp.hpp"
#include "fls/cfg/cfg.hpp"
#include "fls/reader/segment.hpp"
#include "fls/table/chunk.hpp"
#include "fls/table/rowgroup.hpp"

namespace fastlanes {
/*--------------------------------------------------------------------------------------------------------------------*/
class Segment;
struct ColumnDescriptorT;
class PhysicalExpr;
struct InterpreterState;
class ColumnView;
struct InterpreterState;
/*--------------------------------------------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------------------------------------------*\
 * enc_alp_opr
\*--------------------------------------------------------------------------------------------------------------------*/
template <typename PT>
struct enc_alp_opr {
	explicit enc_alp_opr(const PhysicalExpr& expr,
	                     const col_pt&       column,
	                     ColumnDescriptorT&  column_descriptor,
	                     InterpreterState&   state);

	void PointTo(n_t vec_idx);
	void Encode();
	void MoveSegments(vector<up<Segment>>& segments);

public:
	TypedColumnView<PT> typed_column_view;
	alp::state<PT>      alp_state;

	// arrays
	alignas(64) PT sample_arr[CFG::VEC_SZ];
	alignas(64) typename alp::inner_t<PT>::st ffor_arr[CFG::VEC_SZ];
	alignas(64) typename alp::inner_t<PT>::st encoded_arr[CFG::VEC_SZ];
	alignas(64) uint16_t pos_arr[CFG::VEC_SZ];
	alignas(64) PT exc_arr[CFG::VEC_SZ];

	up<Segment> ffor_segment;
	up<Segment> base_segment;
	up<Segment> bw_segment;
	up<Segment> exception_segment;
	up<Segment> fac_segment;
	up<Segment> exp_segment;
	up<Segment> pos_segment;
	up<Segment> n_exp_segment;
};

/*--------------------------------------------------------------------------------------------------------------------*\
 * dec_alp_opr
\*--------------------------------------------------------------------------------------------------------------------*/
template <typename PT>
struct dec_alp_opr {
public:
	explicit dec_alp_opr(const ColumnView& column_view, InterpreterState& state);

public:
	void PointTo(n_t vec_n);
	void Decode(n_t vec_idx);

public:
	//
	alp::state<PT> alp_state;
	SegmentView    ffor_segment_view;
	SegmentView    base_segment_view;
	SegmentView    bitwidth_segment_view;
	SegmentView    exception_segment_view;
	SegmentView    fac_segment_view;
	SegmentView    exp_segment_view;
	SegmentView    pos_segment_view;
	SegmentView    n_exp_segment_view;
	alignas(64) typename alp::inner_t<PT>::st unffor_arr[CFG::VEC_SZ];
	alignas(64) PT decoded_arr[CFG::VEC_SZ];
};

/*--------------------------------------------------------------------------------------------------------------------*\
 * enc_alp_rd_opr
\*--------------------------------------------------------------------------------------------------------------------*/
template <typename PT>
struct enc_alp_rd_opr {
	explicit enc_alp_rd_opr(const PhysicalExpr& expr,
	                        const col_pt&       column,
	                        ColumnDescriptorT&  column_descriptor,
	                        InterpreterState&   state);

	void PointTo(n_t vec_idx);
	void Finalize();
	void Encode();
	void MoveSegments(vector<up<Segment>>& segments);

public:
	TypedColumnView<PT> typed_column_view;
	alp::state<PT>      alp_state;

	// arrays
	alignas(64) uint16_t rd_exc_arr[CFG::VEC_SZ];
	alignas(64) typename alp::inner_t<PT>::ut r_arr[CFG::VEC_SZ];
	alignas(64) typename alp::inner_t<PT>::ut r_ffor_arr[CFG::VEC_SZ];
	alignas(64) uint16_t l_arr[CFG::VEC_SZ];
	alignas(64) uint16_t l_ffor_arr[CFG::VEC_SZ];
	alignas(64) PT sample_arr[CFG::VEC_SZ];
	alignas(64) uint16_t pos_arr[CFG::VEC_SZ];

	// ALP_RD
	up<Segment> l_ffor_segment;
	up<Segment> l_bw_segment;
	up<Segment> l_base_segment;
	up<Segment> r_bw_segment;
	up<Segment> r_base_segment;
	up<Segment> r_ffor_segment;
	up<Segment> rd_exception_segment;
	up<Segment> rd_pos_segment;
	up<Segment> rd_n_exc_segment;
	up<Segment> rd_dict_segment;
};

/*--------------------------------------------------------------------------------------------------------------------*\
 * dec_alp_rd_opr
\*--------------------------------------------------------------------------------------------------------------------*/
template <typename PT>
struct dec_alp_rd_opr {
public:
	explicit dec_alp_rd_opr(const ColumnView& column_view, InterpreterState& state);

public:
	void PointTo(n_t vec_n);
	void Decode(n_t vec_idx);

public:
	// Segment views
	SegmentView l_ffor_segment_view;       // Left FFOR segment view
	SegmentView l_bw_segment_view;         // Left bitwidth segment view
	SegmentView l_base_segment_view;       // Left base segment view
	SegmentView r_ffor_segment_view;       // Right FFOR segment view
	SegmentView r_bw_segment_view;         // Right bitwidth segment view
	SegmentView r_base_segment_view;       // Right base segment view
	SegmentView rd_exception_segment_view; // RD exception values
	SegmentView rd_pos_segment_view;       // Exception positions
	SegmentView rd_n_exc_segment_view;     // Number of exceptions
	SegmentView rd_dict_segment_view;      // Number of exceptions

	//
	alp::state<PT> alp_state;
	alignas(64) typename alp::inner_t<PT>::ut unffor_right_arr[CFG::VEC_SZ];
	alignas(64) uint16_t unffor_left_arr[CFG::VEC_SZ];
	alignas(64) PT glue_arr[CFG::VEC_SZ];
};

} // namespace fastlanes

#endif // FLS_EXPRESSION_ALP_EXPRESSION_HPP
