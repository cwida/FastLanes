#ifndef FLS_EXPRESSION_NULL_OPERATOR_HPP
#define FLS_EXPRESSION_NULL_OPERATOR_HPP

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
 * enc_null_opr
\*--------------------------------------------------------------------------------------------------------------------*/
template <typename PT>
struct enc_null_opr {
public:
	explicit enc_null_opr(const PhysicalExpr& expr,
	                      const col_pt&       col,
	                      ColumnDescriptorT&  column_descriptor,
	                      InterpreterState&   state);

	void Store();
	void PointTo(n_t vec_idx);
	void MoveSegments(vector<up<Segment>>& segments);

public:
	TypedColumnView<PT> type_col_data;
	up<Segment>         vals_segment;
	up<Segment>         vals_position_segment;
	up<Segment>         n_vals_segment;
	PT                  vals[CFG::VEC_SZ];
	vec_idx_t           vals_position[CFG::VEC_SZ];
};

/*--------------------------------------------------------------------------------------------------------------------*\
 * dec null opr
\*--------------------------------------------------------------------------------------------------------------------*/
template <typename PT>
struct dec_null_opr {
public:
	explicit dec_null_opr(PhysicalExpr& physical_expr, const ColumnView& column_view, InterpreterState& state);

public:
	void PointTo(n_t vec_n);
	void Materialize(n_t vec_idx, TypedCol<PT>& typed_col);

public:
	SegmentView vals_segment;
	SegmentView vals_position_segment;
	SegmentView n_vals_segment;
};

} // namespace fastlanes

#endif // FLS_EXPRESSION_S_PATCH_OPERATOR_HPP
