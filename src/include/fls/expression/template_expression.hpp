#ifndef FLS_EXPRESSION_[EXPRESSION_NAME] _EXPRESSION_HPP
#define FLS_EXPRESSION_ [EXPRESSION_NAME] _EXPRESSION_HPP

namespace fastlanes {
/*--------------------------------------------------------------------------------------------------------------------*/
class Segment;
class ColumnDescriptor;
class PhysicalExpr;
struct InterpreterState;
class ColumnView;
struct InterpreterState;
class Reader;
/*--------------------------------------------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------------------------------------------*\
 * enc_[EXPRESSION_NAME]_opr
\*--------------------------------------------------------------------------------------------------------------------*/
template <typename PT>
struct enc_[EXPRESSION_NAME] _opr {
	explicit enc_[EXPRESSION_NAME] _opr(const PhysicalExpr& expr,
	                                    const col_pt&       column,
	                                    ColumnDescriptor&   column_descriptor,
	                                    InterpreterState&   state);

	void PointTo(n_t vec_idx);
	void Encode();
	void MoveSegments(vector<up<Segment>>& segments);

public:
	up<Segment> n_exp_segment;
};

/*--------------------------------------------------------------------------------------------------------------------*\
 * dec_[EXPRESSION_NAME]_opr
\*--------------------------------------------------------------------------------------------------------------------*/
template <typename PT>
struct dec_[EXPRESSION_NAME] _opr {
public:
	explicit dec_[EXPRESSION_NAME] _opr(const ColumnView& column_view, InterpreterState& state);

public:
	void PointTo(n_t vec_n);
	void Decode();

public:
	[EXPRESSION_NAME] ::state<PT> state;
	SegmentView                   ffor_segment_view;
};

} // namespace fastlanes