#ifndef FLS_EXPRESSION_FSST_EXPRESSION_HPP
#define FLS_EXPRESSION_FSST_EXPRESSION_HPP

#include "fls/cfg/cfg.hpp"
#include "fls/cor/prm/fsst/fsst.h"
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
class RowgroupReader;
/*--------------------------------------------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------------------------------------------*\
 * enc_fsst_opr
\*--------------------------------------------------------------------------------------------------------------------*/
struct enc_fsst_opr {
	explicit enc_fsst_opr(const PhysicalExpr& expr,
	                      const col_pt&       column,
	                      ColumnDescriptorT&  column_descriptor,
	                      InterpreterState&   state);
	~enc_fsst_opr();

	void PointTo(n_t vec_idx);
	void Finalize();
	void Encode();
	void MoveSegments(vector<up<Segment>>& segments);

public:
	FlsStrColumnView str_col_view;
	fsst_encoder_t*  fsst_encoder_p;
	uint8_t          fsst_header[FSST_MAXHEADER];
	vector<uint8_t>  fsst_bytes;
	ofs_t            fsst_encoded_offset_arr[CFG::VEC_SZ + 1];
	uint8_t*         fsst_str_p_arr[CFG::VEC_SZ];

	//
	up<Segment> fsst_header_segment;
	up<Segment> fsst_bytes_segment;
	up<Segment> fsst_offset_segment;
};

/*--------------------------------------------------------------------------------------------------------------------*\
 * dec_fsst_opr
\*--------------------------------------------------------------------------------------------------------------------*/
struct dec_fsst_opr {
public:
	explicit dec_fsst_opr(PhysicalExpr& physical_expr, const ColumnView& column_view, InterpreterState& state);

public:
	void PointTo(n_t vec_n);
	void Decode(vector<uint8_t>& out_byte_arr, vector<ofs_t>& out_length_arr);

public:
	SegmentView     fsst_header_segment_view;
	SegmentView     fsst_bytes_segment_view;
	fsst_decoder_t  fsst_decoder;
	vector<uint8_t> tmp_string;
	ofs_t*          offset_arr;
	ofs_t           untrasposed_offset[CFG::VEC_SZ];
};

} // namespace fastlanes

#endif // FLS_EXPRESSION_FSST_EXPRESSION_HPP
