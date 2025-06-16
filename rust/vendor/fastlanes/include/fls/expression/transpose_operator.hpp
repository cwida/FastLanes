#ifndef FLS_EXPRESSION_TRANSPOSE_OPERATOR_HPP
#define FLS_EXPRESSION_TRANSPOSE_OPERATOR_HPP

#include "fls/cfg/cfg.hpp"
#include "fls/table/rowgroup.hpp"

namespace fastlanes {
/*--------------------------------------------------------------------------------------------------------------------*/
class Segment;
struct ColumnDescriptorT;
class PhysicalExpr;
struct InterpreterState;
class ColumnView;
/*--------------------------------------------------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------------------------------------------------*\
 * enc_transpose_opr
\*--------------------------------------------------------------------------------------------------------------------*/
template <typename PT>
struct enc_transpose_opr {
public:
	explicit enc_transpose_opr(const PhysicalExpr& expr,
	                           const col_pt&       col,
	                           ColumnDescriptorT&  column_descriptor,
	                           InterpreterState&   state);

	void Transpose();

public:
	PT* data;
	PT  transposed_data[CFG::VEC_SZ];
};

/*--------------------------------------------------------------------------------------------------------------------*\
 * dec transpose opr
\*--------------------------------------------------------------------------------------------------------------------*/
template <typename PT>
struct dec_transpose_opr {
public:
	explicit dec_transpose_opr(PhysicalExpr& physical_expr, const ColumnView& column_view, InterpreterState& state);

public:
	void Materialize(n_t vec_idx, TypedCol<PT>& deocded_data);
	PT*  transposed_data;

public:
};
} // namespace fastlanes

#endif // FLS_EXPRESSION_TRANSPOSE_OPERATOR_HPP
