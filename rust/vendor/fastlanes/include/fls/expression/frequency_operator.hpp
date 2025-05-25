#ifndef FLS_EXPRESSION_FREQUENCY_OPERATOR_HPP
#define FLS_EXPRESSION_FREQUENCY_OPERATOR_HPP

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
 * enc_frequency_opr
\*--------------------------------------------------------------------------------------------------------------------*/
template <typename PT>
struct enc_frequency_opr {
public:
	explicit enc_frequency_opr(const PhysicalExpr& expr,
	                           const col_pt&       col,
	                           ColumnDescriptorT&  column_descriptor,
	                           InterpreterState&   state);

	void Encode();
	void PointTo(n_t vec_idx);
	void Finalize();
	void MoveSegments(vector<up<Segment>>& segments);

public:
	TypedColumnView<PT> col_viewer;
	up<Segment>         exception_values_seg;
	up<Segment>         exception_positions_seg;
	up<Segment>         n_exceptions_seg;
	up<Segment>         frequent_value_seg;
	PT                  frequent_val;
	PT                  exception_vals[CFG::VEC_SZ];
	vec_idx_t           exception_positions[CFG::VEC_SZ];
};

struct enc_frequency_str_opr {
public:
	explicit enc_frequency_str_opr(const PhysicalExpr& expr,
	                               const col_pt&       col,
	                               ColumnDescriptorT&  column_descriptor,
	                               InterpreterState&   state);

	void Encode();
	void PointTo(n_t vec_idx);
	void Finalize();
	void MoveSegments(vector<up<Segment>>& segments);

public:
	up<Buf>          length_buf;
	up<Buf>          bytes_buf;
	FlsStrColumnView col_viewer;
	up<Segment>      exception_values_seg;
	up<Segment>      exception_positions_seg;
	up<Segment>      n_exceptions_seg;
	up<Segment>      frequent_value_bytes_seg;
	up<Segment>      frequent_value_size_seg;
	up<Segment>      exception_values_bytes_seg;
	up<Segment>      exception_values_offset_seg;

	fls_string_t frequent_val;
	fls_string_t exception_vals[CFG::VEC_SZ];
	vec_idx_t    exception_positions[CFG::VEC_SZ];
};

/*--------------------------------------------------------------------------------------------------------------------*\
 * dec frequency opr
\*--------------------------------------------------------------------------------------------------------------------*/
template <typename PT>
struct dec_frequency_opr {
public:
	explicit dec_frequency_opr(PhysicalExpr& physical_expr, const ColumnView& column_view, InterpreterState& state);

public:
	void PointTo(n_t vec_idx);
	void Decode(n_t vec_idx);
	void Materialize(n_t vec_idx, TypedCol<PT>& typed_col);
	PT   data[CFG::VEC_SZ];
	PT   frequent_val;

public:
	SegmentView frequent_value_seg;
	SegmentView exceptions_segment;
	SegmentView exceptions_position_segment;
	SegmentView n_exceptions_segment;
};

struct dec_frequency_str_opr {
public:
	explicit dec_frequency_str_opr(PhysicalExpr& physical_expr, const ColumnView& column_view, InterpreterState& state);

public:
	void PointTo(n_t vec_idx);
	void Decode();
	void Materialize(n_t vec_idx, FLSStrColumn& typed_col);

public:
	SegmentView  frequent_value_bytes_seg;
	SegmentView  frequent_value_size_seg;
	SegmentView  n_exceptions_seg;
	SegmentView  exception_positions_seg;
	SegmentView  exception_values_bytes_seg;
	SegmentView  exception_values_offset_seg;
	fls_string_t frequent_val;
};

} // namespace fastlanes

#endif // FLS_EXPRESSION_S_PATCH_OPERATOR_HPP
