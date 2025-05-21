#ifndef FLS_EXPRESSION_FSST12_EXPRESSION_HPP
#define FLS_EXPRESSION_FSST12_EXPRESSION_HPP

#include "fls/cfg/cfg.hpp"
#include "fls/cor/prm/fsst12/fsst12.h"
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
 * enc_fsst12_opr
\*--------------------------------------------------------------------------------------------------------------------*/
struct enc_fsst12_opr {
	explicit enc_fsst12_opr(const PhysicalExpr& expr,
	                        const col_pt&       column,
	                        ColumnDescriptorT&  column_descriptor,
	                        InterpreterState&   state);
	~enc_fsst12_opr();

	void PointTo(n_t vec_idx);
	void Finalize();
	void Encode();
	void MoveSegments(vector<up<Segment>>& segments);

public:
	FlsStrColumnView  str_col_view;
	fsst12_encoder_t* fsst12_encoder_p;
	uint8_t           fsst12_header[FSST12_MAXHEADER];
	vector<uint8_t>   fsst12_bytes;
	ofs_t             fsst12_encoded_offset_arr[CFG::VEC_SZ + 1];
	uint8_t*          fsst12_str_p_arr[CFG::VEC_SZ];

	//
	up<Segment> fsst12_header_segment;
	up<Segment> fsst12_bytes_segment;
	up<Segment> fsst12_offset_segment;
};

/*--------------------------------------------------------------------------------------------------------------------*\
 * dec_fsst12_opr
\*--------------------------------------------------------------------------------------------------------------------*/
struct dec_fsst12_opr {
public:
	explicit dec_fsst12_opr(PhysicalExpr& physical_expr, const ColumnView& column_view, InterpreterState& state);

public:
	void PointTo(n_t vec_n);
	void Decode(vector<uint8_t>& out_byte_arr, vector<ofs_t>& out_length_arr);

public:
	SegmentView      fsst12_header_segment_view;
	SegmentView      fsst12_bytes_segment_view;
	fsst12_decoder_t fsst12_decoder;
	vector<uint8_t>  tmp_string;
	ofs_t*           offset_arr;
	ofs_t            untrasposed_offset[CFG::VEC_SZ];
};

} // namespace fastlanes

#endif // FLS_EXPRESSION_FSST12_EXPRESSION_HPP
