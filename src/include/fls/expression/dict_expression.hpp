#ifndef FLS_EXPRESSION_DICT_EXPRESSION_HPP
#define FLS_EXPRESSION_DICT_EXPRESSION_HPP

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
class RowgroupReader;
/*--------------------------------------------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------------------------------------------*\
 * enc_dict_opr
\*--------------------------------------------------------------------------------------------------------------------*/
template <typename KEY_PT>
struct enc_dict_opr {
	explicit enc_dict_opr(const PhysicalExpr& expr,
	                      const col_pt&       column,
	                      ColumnDescriptorT&  column_descriptor,
	                      InterpreterState&   state);
	void Finalize();
	void MoveSegments(vector<up<Segment>>& segments);

	up<Segment>             key_segment;
	TypedColumnView<KEY_PT> typed_column_view;
};

template <>
struct enc_dict_opr<fls_string_t> {
	explicit enc_dict_opr(const PhysicalExpr& expr,
	                      const col_pt&       column,
	                      ColumnDescriptorT&  column_descriptor,
	                      InterpreterState&   state);

	void PointTo(n_t vec_idx);
	void Encode();
	void MoveSegments(vector<up<Segment>>& segments);
	void Finalize();

public:
	up<Segment> offset_segment;
	up<Segment> bytes_segment;

	FlsStrColumnView col_view;
};

/*--------------------------------------------------------------------------------------------------------------------*\
 * dec_dict_opr
\*--------------------------------------------------------------------------------------------------------------------*/
template <typename KEY_PT, typename INDEX_PT>
struct dec_dict_opr {
	explicit dec_dict_opr(const PhysicalExpr& physical_expr, const ColumnView& column_view, InterpreterState& state);
	KEY_PT*         Keys();
	const INDEX_PT* Index();

	SegmentView     key_segment_view;
	const INDEX_PT* index_arr;
};

template <typename INDEX_PT>
struct dec_dict_opr<fls_string_t, INDEX_PT> {
	explicit dec_dict_opr(const PhysicalExpr& physical_expr, const ColumnView& column_view, InterpreterState& state);

	const INDEX_PT* Index();
	const ofs_t*    Offsets();
	const uint8_t*  Bytes();
	void            Decode(vector<uint8_t>& byte_arr_vec, vector<ofs_t>& length_vec);

public:
	SegmentView     dict_offsets_segment;
	SegmentView     dict_bytes_segment;
	const INDEX_PT* index_arr;
};

} // namespace fastlanes

#endif