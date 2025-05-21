#ifndef FLS_EXPRESSION_FSST_DICT_OPERATOR_HPP
#define FLS_EXPRESSION_FSST_DICT_OPERATOR_HPP

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
struct enc_fsst_dict_opr {
	explicit enc_fsst_dict_opr(const PhysicalExpr& expr,
	                           const col_pt&       column,
	                           ColumnDescriptorT&  column_descriptor,
	                           InterpreterState&   state);
	~enc_fsst_dict_opr() = default;

	void PointTo(n_t vec_idx);
	void Encode();
	void MoveSegments(vector<up<Segment>>& segments);
	void Finalize();

public:
	up<Buf>          length_buf;
	up<Buf>          bytes_buf;
	up<Buf>          string_p_buf;
	up<Buf>          fsst_bytes_buf;
	up<Buf>          out_offset_buf;
	up<Segment>      fsst_header_segment;
	up<Segment>      fsst_bytes_segment;
	up<Segment>      fsst_offset_segment;
	uint8_t          fsst_header[CFG::FSST::MAX_HEADER_SIZE];
	FlsStrColumnView col_view;
};

template <typename INDEX_PT>
struct dec_fsst_dict_opr {
	explicit dec_fsst_dict_opr(const PhysicalExpr& physical_expr,
	                           const ColumnView&   column_view,
	                           InterpreterState&   state);

	const INDEX_PT* Index();
	const ofs_t*    Offsets();
	const uint8_t*  Bytes();
	void            Decode(vector<uint8_t>& byte_arr_vec, vector<ofs_t>& length_vec);

public:
	SegmentView     fsst_header_segment_view;
	SegmentView     fsst_bytes_segment_view;
	SegmentView     fsst_offset_segment_view;
	const INDEX_PT* index_arr;
	vector<uint8_t> tmp_string;
	fsst_decoder_t  fsst_decoder;
};

} // namespace fastlanes

#endif