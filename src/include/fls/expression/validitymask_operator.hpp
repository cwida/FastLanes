#ifndef FLS_EXPRESSION_VALIDITYMASK_OPERATOR_HPP
#define FLS_EXPRESSION_VALIDITYMASK_OPERATOR_HPP

#include "fls/reader/segment.hpp"
#include "fls/std/type_traits.hpp"
#include "fls/table/rowgroup.hpp"
#include "fls/types/validitymask.hpp"

namespace fastlanes {
/*--------------------------------------------------------------------------------------------------------------------*/
class Segment;
struct ColumnDescriptorT;
class PhysicalExpr;
class ColumnView;
struct InterpreterState;
/*--------------------------------------------------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------------------------------------------------*\
 * validitymask
\*--------------------------------------------------------------------------------------------------------------------*/
struct enc_validitymask_opr {
public:
	explicit enc_validitymask_opr(const PhysicalExpr& physical_expr,
	                              const col_pt&       column,
	                              ColumnDescriptorT&  column_descriptor,
	                              InterpreterState&   state);

	void to_validitymask();
	void PointTo(n_t vec_idx);
	void MoveSegments(vector<up<Segment>>& segments);

public:
	TypedColumnView<uint8_t> typed_column_view;
	up<Segment>              validitymask_segment;
	ValidityMask             validitymask;
};

/*--------------------------------------------------------------------------------------------------------------------*\
 * dec_validitymask_opr
\*--------------------------------------------------------------------------------------------------------------------*/
struct dec_validitymask_opr {
public:
	explicit dec_validitymask_opr(const ColumnView& column_view, n_t segment_idx);

public:
	void     PointTo(n_t vec_n);
	uint8_t* Data();
	void     Materialize(n_t vec_idx, TypedCol<uint8_t>& des_col);

public:
	SegmentView data_segment;
};

} // namespace fastlanes

#endif // VALIDITYMASK_OPERATOR_HPP
