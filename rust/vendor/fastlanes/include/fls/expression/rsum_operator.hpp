#ifndef FLS_EXPRESSION_RSUM_OPERATOR_HPP
#define FLS_EXPRESSION_RSUM_OPERATOR_HPP

#include "fls/cfg/cfg.hpp"
#include "fls/reader/segment.hpp"
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
 * enc_rsum_opr
\*--------------------------------------------------------------------------------------------------------------------*/
template <typename PT>
struct enc_rsum_opr {
public:
	explicit enc_rsum_opr(const PhysicalExpr& expr,
	                      const col_pt&       col,
	                      ColumnDescriptorT&  column_descriptor,
	                      InterpreterState&   state);

	void Rsum();
	void MoveSegments(vector<up<Segment>>& segments);

public:
	PT*         data;
	PT          deltas[CFG::VEC_SZ];
	PT          rsumed_bases[CFG::VEC_SZ];
	up<Segment> bases_segment;
};

/*--------------------------------------------------------------------------------------------------------------------*\
 * dec rsum opr
\*--------------------------------------------------------------------------------------------------------------------*/
template <typename PT>
struct dec_rsum_opr {
public:
	explicit dec_rsum_opr(PhysicalExpr& physical_expr, const ColumnView& column_view, InterpreterState& state);

public:
	void PointTo(n_t vec_n);
	void Unrsum(n_t vec_idx);

public:
	SegmentView bases_segment_view;
	const PT*   deltas;
	PT          idxs[CFG::VEC_SZ];
};

} // namespace fastlanes

#endif // FLS_EXPRESSION_RSUM_OPERATOR_HPP
