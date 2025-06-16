#ifndef FLS_EXPRESSION_SLPATCH_OPERATOR_HPP
#define FLS_EXPRESSION_SLPATCH_OPERATOR_HPP

#include "fls/reader/segment.hpp"
#include "fls/std/type_traits.hpp"
#include "fls/table/rowgroup.hpp"

namespace fastlanes {
/*--------------------------------------------------------------------------------------------------------------------*/
class Segment;
struct ColumnDescriptorT;
class PhysicalExpr;
class ColumnView;
struct InterpreterState;
/*--------------------------------------------------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------------------------------------------------*\
 * enc_slpatch_opr
\*--------------------------------------------------------------------------------------------------------------------*/
template <typename PT>
struct enc_slpatch_opr {
public:
	explicit enc_slpatch_opr(const PhysicalExpr& expr,
	                         const col_pt&       col,
	                         ColumnDescriptorT&  column_descriptor,
	                         InterpreterState&   state);

	void Store();
	void MoveSegments(vector<up<Segment>>& segments);

public:
	PT*         exceptions;
	uint16_t*   n_exceptions_p;
	vec_idx_t*  exception_pos_arr;
	up<Segment> exceptions_segment;
	up<Segment> exceptions_position_segment;
	up<Segment> n_exceptions_segment;
};

/*--------------------------------------------------------------------------------------------------------------------*\
 * dec slpatch opr
\*--------------------------------------------------------------------------------------------------------------------*/
template <typename PT>
struct dec_slpatch_opr {
public:
	explicit dec_slpatch_opr(PhysicalExpr& physical_expr, const ColumnView& column_view, InterpreterState& state);

public:
	void PointTo(n_t vec_n);
	void Patch(n_t vec_idx);
	void Materialize(n_t vec_idx, TypedCol<PT>& typed_col);

public:
	PT*         data;
	SegmentView exceptions_segment;
	SegmentView exceptions_position_segment;
	SegmentView n_exceptions_segment;
};

} // namespace fastlanes

#endif // FLS_EXPRESSION_S_PATCH_OPERATOR_HPP
