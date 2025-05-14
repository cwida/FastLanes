#ifndef FLS_EXPRESSION_RLE_EXPRESSION_HPP
#define FLS_EXPRESSION_RLE_EXPRESSION_HPP

#include "fls/cfg/cfg.hpp"
#include "fls/reader/segment.hpp"
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
 * enc_rle_opr
\*--------------------------------------------------------------------------------------------------------------------*/
template <typename KEY_PT, typename INDEX_PT>
struct enc_rle_map_opr {
	explicit enc_rle_map_opr(const PhysicalExpr& expr,
	                         const col_pt&       column,
	                         ColumnDescriptorT&  column_descriptor,
	                         InterpreterState&   state);

	void PointTo(n_t vec_idx);
	void Map();
	void MoveSegments(vector<up<Segment>>& segments);

public:
	TypedColumnView<KEY_PT> typed_column_view;
	KEY_PT                  rle_vals[CFG::VEC_SZ];
	INDEX_PT                rle_idxs[CFG::VEC_SZ];
	up<Segment>             rle_val_segment;
};

template <typename INDEX_PT>
struct enc_rle_map_opr<fls_string_t, INDEX_PT> {
	explicit enc_rle_map_opr(const PhysicalExpr& expr,
	                         const col_pt&       column,
	                         ColumnDescriptorT&  column_descriptor,
	                         InterpreterState&   state);

	void PointTo(n_t vec_idx);
	void Map();
	void MoveSegments(vector<up<Segment>>& segments);

public:
	FlsStrColumnView string_col;
	fls_string_t     rle_vals[CFG::VEC_SZ];
	INDEX_PT         rle_idxs[CFG::VEC_SZ];
	up<Segment>      rle_val_bytes_segment;
	up<Segment>      rle_val_offset_segment;
	ofs_t            rle_val_offsets[CFG::VEC_SZ + 1];
	up<Buf>          buf;
};

/*--------------------------------------------------------------------------------------------------------------------*\
 * dec_rle_map_opr
\*--------------------------------------------------------------------------------------------------------------------*/
template <typename KEY_PT, typename INDEX_PT>
struct dec_rle_map_opr {
public:
	explicit dec_rle_map_opr(PhysicalExpr& physical_expr, const ColumnView& column_view, InterpreterState& state);

public:
	void PointTo(n_t vec_n);
	void Decode(n_t vec_idx, vector<KEY_PT>& data);

public:
	const INDEX_PT* idxs;
	SegmentView     rle_vals_segment_view;
	KEY_PT          temporary_tranposed_arr[CFG::VEC_SZ];
};

template <typename INDEX_PT>
struct dec_rle_map_opr<fls_string_t, INDEX_PT> {
public:
	explicit dec_rle_map_opr(PhysicalExpr& physical_expr, const ColumnView& column_view, InterpreterState& state);

public:
	void PointTo(n_t vec_n);
	void Decode(n_t vec_idx, vector<uint8_t>& byte_arr_vec, vector<ofs_t>& length_vec);

public:
	const INDEX_PT* idxs;
	INDEX_PT        temporary_idxs[CFG::VEC_SZ];

	SegmentView rle_vals_segment_view;
	SegmentView rle_offset_segment_view;
};

} // namespace fastlanes

#endif // FLS_EXPRESSION_RLE_EXPRESSION_HPP
