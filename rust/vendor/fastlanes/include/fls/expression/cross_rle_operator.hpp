#ifndef FLS_EXPRESSION_CROSS_RLE_HPP
#define FLS_EXPRESSION_CROSS_RLE_HPP

#include "fls/reader/segment.hpp"
#include "fls/std/type_traits.hpp"
#include "fls/table/rowgroup.hpp"
#include <fls/common/string.hpp>

namespace fastlanes {
/*--------------------------------------------------------------------------------------------------------------------*/
class Segment;
struct ColumnDescriptorT;
class PhysicalExpr;
class ColumnView;
struct InterpreterState;
/*--------------------------------------------------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------------------------------------------------*\
 * enc_cross_rle_opr
\*--------------------------------------------------------------------------------------------------------------------*/
template <typename PT>
struct enc_cross_rle_opr {
public:
	explicit enc_cross_rle_opr(const PhysicalExpr& expr,
	                           const col_pt&       col,
	                           ColumnDescriptorT&  column_descriptor,
	                           InterpreterState&   state);

	void Finalize();
	void MoveSegments(vector<up<Segment>>& segments);

public:
	TypedColumnView<PT> col_viewer;
	up<Segment>         values_seg;
	up<Segment>         lengths_seg;
	up<Buf>             values;
	up<Buf>             lengths;
};

template <>
struct enc_cross_rle_opr<fls_string_t> {
public:
	explicit enc_cross_rle_opr(const PhysicalExpr& expr,
	                           const col_pt&       col,
	                           ColumnDescriptorT&  column_descriptor,
	                           InterpreterState&   state);

	void Finalize();
	void MoveSegments(vector<up<Segment>>& segments);

public:
	up<Buf>          lengths_buf;
	up<Buf>          values_bytes_buf;
	up<Buf>          values_offset_buf;
	FlsStrColumnView col_viewer;
	up<Segment>      values_bytes_seg;
	up<Segment>      values_offset_seg;
	up<Segment>      lengths_seg;
};

/*--------------------------------------------------------------------------------------------------------------------*\
 * dec cross_rle opr
\*--------------------------------------------------------------------------------------------------------------------*/
template <typename PT>
struct dec_cross_rle_opr {
public:
	explicit dec_cross_rle_opr(PhysicalExpr& physical_expr, const ColumnView& column_view, InterpreterState& state);

public:
	void Materialize(n_t vec_idx, TypedCol<PT>& typed_col);

public:
	SegmentView values_segment;
	SegmentView lengths_segment;
};

template <>
struct dec_cross_rle_opr<fls_string_t> {
public:
	explicit dec_cross_rle_opr(PhysicalExpr& physical_expr, const ColumnView& column_view, InterpreterState& state);

public:
	void Materialize(n_t vec_idx, FLSStrColumn& typed_col);

public:
	SegmentView values_bytes_seg;
	SegmentView values_offset_seg;
	SegmentView lengths_segment;
};

} // namespace fastlanes

#endif // FLS_EXPRESSION_S_PATCH_OPERATOR_HPP
