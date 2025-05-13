#include "fls/expression/interpreter.hpp"
#include "fls/common/common.hpp"
#include "fls/common/exception.hpp"
#include "fls/connection.hpp"
#include "fls/expression/alp_expression.hpp"
#include "fls/expression/analyze_operator.hpp"
#include "fls/expression/cross_rle_operator.hpp"
#include "fls/expression/decoding_operator.hpp"
#include "fls/expression/dict_expression.hpp"
#include "fls/expression/encoding_operator.hpp"
#include "fls/expression/frequency_operator.hpp"
#include "fls/expression/fsst12_dict_operator.hpp"
#include "fls/expression/fsst12_expression.hpp"
#include "fls/expression/fsst_dict_operator.hpp"
#include "fls/expression/fsst_expression.hpp"
#include "fls/expression/null_operator.hpp"
#include "fls/expression/physical_expression.hpp"
#include "fls/expression/rle_expression.hpp"
#include "fls/expression/rpn.hpp"
#include "fls/expression/rsum_operator.hpp"
#include "fls/expression/scan_operator.hpp"
#include "fls/expression/slpatch_operator.hpp"
#include "fls/expression/transpose_operator.hpp"
#include "fls/reader/column_view.hpp"
#include "fls/std/type_traits.hpp"
#include "fls/table/rowgroup.hpp"

namespace fastlanes {
/*--------------------------------------------------------------------------------------------------------------------*\
 * make_enc_uncompressed_expr
\*--------------------------------------------------------------------------------------------------------------------*/
template <typename PT>
void make_enc_uncompressed_expr(PhysicalExpr&      physical_expr,
                                const rowgroup_pt& rowgroup,
                                ColumnDescriptorT& column_descriptor,
                                InterpreterState&  state) {

	auto& [operator_tokens, operand_tokens] = *column_descriptor.encoding_rpn;
	operand_tokens.emplace_back(0);

	const auto& column = rowgroup[column_descriptor.idx];
	physical_expr.operators.emplace_back(
	    make_shared<enc_uncompressed_opr<PT>>(physical_expr, column, column_descriptor, state));
}

/*--------------------------------------------------------------------------------------------------------------------*\
 * make_enc_struct_expr
\*--------------------------------------------------------------------------------------------------------------------*/
void make_enc_struct_expr(PhysicalExpr&      physical_expr,
                          const rowgroup_pt& rowgroup,
                          ColumnDescriptorT& column_descriptor,
                          InterpreterState&  state) {

	const auto& col = rowgroup[column_descriptor.idx];

	physical_expr.operators.emplace_back(make_shared<enc_struct_opr>(col, column_descriptor));
}

/*--------------------------------------------------------------------------------------------------------------------*\
 * make_enc_fls_str_uncompressed_expr
\*--------------------------------------------------------------------------------------------------------------------*/
void make_fls_str_uncompressed_expr(PhysicalExpr&      physical_expr,
                                    const rowgroup_pt& rowgroup,
                                    ColumnDescriptorT& column_descriptor,
                                    InterpreterState&  state) {

	auto& [operator_tokens, operand_tokens] = *column_descriptor.encoding_rpn;
	operand_tokens.emplace_back(0);
	operand_tokens.emplace_back(1);

	const auto& column = rowgroup[column_descriptor.idx];
	physical_expr.operators.emplace_back(make_shared<enc_fls_str_uncompressed_op>(column));
}

/*--------------------------------------------------------------------------------------------------------------------*\
 * make_fsst_expr
\*--------------------------------------------------------------------------------------------------------------------*/
template <typename FSSTOperator>
void make_fsst_expr(PhysicalExpr&      physical_expr,
                    const rowgroup_pt& rowgroup,
                    ColumnDescriptorT& column_descriptor,
                    InterpreterState&  state) {
	const auto& column = rowgroup[column_descriptor.idx];
	physical_expr.operators.emplace_back(make_shared<FSSTOperator>(physical_expr, column, column_descriptor, state));
}

/*--------------------------------------------------------------------------------------------------------------------*\
 * make_fsst_delta_expr
\*--------------------------------------------------------------------------------------------------------------------*/
template <typename FSSTOperator>
void make_fsst_delta_expr(PhysicalExpr&      physical_expr,
                          const rowgroup_pt& rowgroup,
                          ColumnDescriptorT& column_descriptor,
                          InterpreterState&  state) {

	const auto& column    = rowgroup[column_descriptor.idx];
	auto&       operators = physical_expr.operators;

	operators.emplace_back(make_shared<FSSTOperator>(physical_expr, column, column_descriptor, state));
	operators.emplace_back(make_shared<enc_transpose_opr<ofs_t>>(physical_expr, column, column_descriptor, state));
	operators.emplace_back(make_shared<enc_rsum_opr<ofs_t>>(physical_expr, column, column_descriptor, state));
	operators.emplace_back(make_shared<enc_analyze_opr<ofs_t>>(physical_expr, column, column_descriptor, state));
	operators.emplace_back(make_shared<enc_ffor_opr<ofs_t>>(physical_expr, column, column_descriptor, state));
}

/*--------------------------------------------------------------------------------------------------------------------*\
 * make_enc_fsst_delta_slpatch_expr
\*--------------------------------------------------------------------------------------------------------------------*/
template <typename FSSTOperator>
void make_enc_fsst_delta_slpatch_expr(PhysicalExpr&      physical_expr,
                                      const rowgroup_pt& rowgroup,
                                      ColumnDescriptorT& column_descriptor,
                                      InterpreterState&  state) {

	const auto& column    = rowgroup[column_descriptor.idx];
	auto&       operators = physical_expr.operators;

	operators.emplace_back(make_shared<FSSTOperator>(physical_expr, column, column_descriptor, state));
	operators.emplace_back(make_shared<enc_transpose_opr<ofs_t>>(physical_expr, column, column_descriptor, state));
	operators.emplace_back(make_shared<enc_rsum_opr<ofs_t>>(physical_expr, column, column_descriptor, state));
	operators.emplace_back(make_shared<enc_analyze_opr<ofs_t, true>>(physical_expr, column, column_descriptor, state));
	operators.emplace_back(make_shared<enc_slpatch_opr<ofs_t>>(physical_expr, column, column_descriptor, state));
	operators.emplace_back(make_shared<enc_ffor_opr<ofs_t>>(physical_expr, column, column_descriptor, state));
}

/*--------------------------------------------------------------------------------------------------------------------*\
 * make_enc_ffor_expr
\*--------------------------------------------------------------------------------------------------------------------*/
template <typename PT>
void make_enc_ffor_expr(PhysicalExpr&      physical_expr,
                        const rowgroup_pt& rowgroup,
                        ColumnDescriptorT& column_descriptor,
                        InterpreterState&  state) {
	const auto& column    = rowgroup[column_descriptor.idx];
	auto&       operators = physical_expr.operators;

	operators.emplace_back(make_shared<enc_scan_opr<PT>>(physical_expr, column, column_descriptor, state));
	operators.emplace_back(make_shared<enc_analyze_opr<PT>>(physical_expr, column, column_descriptor, state));
	operators.emplace_back(
	    make_shared<enc_ffor_opr<make_unsigned_t<PT>>>(physical_expr, column, column_descriptor, state));
}

/*--------------------------------------------------------------------------------------------------------------------*\
 * make_enc_ffor_slpatch_expr
\*--------------------------------------------------------------------------------------------------------------------*/
template <typename PT>
void make_enc_ffor_slpatch_expr(PhysicalExpr&      physical_expr,
                                const rowgroup_pt& rowgroup,
                                ColumnDescriptorT& column_descriptor,
                                InterpreterState&  state) {
	const auto& column    = rowgroup[column_descriptor.idx];
	auto&       operators = physical_expr.operators;

	operators.emplace_back(make_shared<enc_scan_opr<PT>>(physical_expr, column, column_descriptor, state));
	operators.emplace_back(make_shared<enc_analyze_opr<PT, true>>(physical_expr, column, column_descriptor, state));
	operators.emplace_back(make_shared<enc_slpatch_opr<PT>>(physical_expr, column, column_descriptor, state));
	operators.emplace_back(
	    make_shared<enc_ffor_opr<make_unsigned_t<PT>>>(physical_expr, column, column_descriptor, state));
}

/*--------------------------------------------------------------------------------------------------------------------*\
 * make_enc_null_expr
\*--------------------------------------------------------------------------------------------------------------------*/
template <typename PT>
void make_enc_null_expr(PhysicalExpr&      physical_expr,
                        const rowgroup_pt& rowgroup,
                        ColumnDescriptorT& column_descriptor,
                        InterpreterState&  state) {
	const auto& column    = rowgroup[column_descriptor.idx];
	auto&       operators = physical_expr.operators;

	operators.emplace_back(make_shared<enc_null_opr<PT>>(physical_expr, column, column_descriptor, state));
}

/*--------------------------------------------------------------------------------------------------------------------*\
 * make_enc_null_expr
\*--------------------------------------------------------------------------------------------------------------------*/
template <typename PT>
void make_enc_frequency_expr(PhysicalExpr&      physical_expr,
                             const rowgroup_pt& rowgroup,
                             ColumnDescriptorT& column_descriptor,
                             InterpreterState&  state) {
	const auto& column    = rowgroup[column_descriptor.idx];
	auto&       operators = physical_expr.operators;

	operators.emplace_back(make_shared<enc_frequency_opr<PT>>(physical_expr, column, column_descriptor, state));
}

/*--------------------------------------------------------------------------------------------------------------------*\
 * enc_frequency_str_opr
\*--------------------------------------------------------------------------------------------------------------------*/
void make_enc_frequency_str_opr(PhysicalExpr&      physical_expr,
                                const rowgroup_pt& rowgroup,
                                ColumnDescriptorT& column_descriptor,
                                InterpreterState&  state) {
	const auto& column    = rowgroup[column_descriptor.idx];
	auto&       operators = physical_expr.operators;

	operators.emplace_back(make_shared<enc_frequency_str_opr>(physical_expr, column, column_descriptor, state));
}

/*--------------------------------------------------------------------------------------------------------------------*\
 * make_enc_cross_rle_opr
\*--------------------------------------------------------------------------------------------------------------------*/
template <typename PT>
void make_enc_cross_rle_opr(PhysicalExpr&      physical_expr,
                            const rowgroup_pt& rowgroup,
                            ColumnDescriptorT& column_descriptor,
                            InterpreterState&  state) {
	const auto& column    = rowgroup[column_descriptor.idx];
	auto&       operators = physical_expr.operators;

	operators.emplace_back(make_shared<enc_cross_rle_opr<PT>>(physical_expr, column, column_descriptor, state));
}

/*--------------------------------------------------------------------------------------------------------------------*\
 * make_enc_dict_ffor_expr
\*--------------------------------------------------------------------------------------------------------------------*/
template <typename KEY_PT, typename INDEX_PT>
void make_enc_dict_ffor_expr(PhysicalExpr&      physical_expr,
                             const rowgroup_pt& rowgroup,
                             ColumnDescriptorT& column_descriptor,
                             InterpreterState&  state) {
	auto&       operators = physical_expr.operators;
	const auto& column    = rowgroup[column_descriptor.idx];

	operators.emplace_back(make_shared<enc_dict_opr<KEY_PT>>(physical_expr, column, column_descriptor, state));
	operators.emplace_back(
	    make_shared<enc_dict_map_opr<KEY_PT, INDEX_PT>>(physical_expr, column, column_descriptor, state));
	operators.emplace_back(make_shared<enc_analyze_opr<INDEX_PT>>(physical_expr, column, column_descriptor, state));
	operators.emplace_back(make_shared<enc_ffor_opr<INDEX_PT>>(physical_expr, column, column_descriptor, state));
}

/*--------------------------------------------------------------------------------------------------------------------*\
 * make_enc_dict_ffor_slpatch_expr
\*--------------------------------------------------------------------------------------------------------------------*/
template <typename KEY_PT, typename INDEX_PT>
void make_enc_dict_ffor_slpatch_expr(PhysicalExpr&      physical_expr,
                                     const rowgroup_pt& rowgroup,
                                     ColumnDescriptorT& column_descriptor,
                                     InterpreterState&  state) {
	auto&       operators = physical_expr.operators;
	const auto& column    = rowgroup[column_descriptor.idx];

	operators.emplace_back(make_shared<enc_dict_opr<KEY_PT>>(physical_expr, column, column_descriptor, state));
	operators.emplace_back(
	    make_shared<enc_dict_map_opr<KEY_PT, INDEX_PT>>(physical_expr, column, column_descriptor, state));
	operators.emplace_back(
	    make_shared<enc_analyze_opr<INDEX_PT, true>>(physical_expr, column, column_descriptor, state));
	operators.emplace_back(make_shared<enc_slpatch_opr<INDEX_PT>>(physical_expr, column, column_descriptor, state));
	operators.emplace_back(make_shared<enc_ffor_opr<INDEX_PT>>(physical_expr, column, column_descriptor, state));
}

/*--------------------------------------------------------------------------------------------------------------------*\
 * make_enc_fsst_dict_ffor_expr
\*--------------------------------------------------------------------------------------------------------------------*/
template <typename FSST_DICT_ENCODER_T, typename KEY_PT, typename INDEX_PT>
void make_enc_fsst_dict_ffor_expr(PhysicalExpr&      physical_expr,
                                  const rowgroup_pt& rowgroup,
                                  ColumnDescriptorT& column_descriptor,
                                  InterpreterState&  state) {
	auto&       operators = physical_expr.operators;
	const auto& column    = rowgroup[column_descriptor.idx];

	operators.emplace_back(make_shared<FSST_DICT_ENCODER_T>(physical_expr, column, column_descriptor, state));
	operators.emplace_back(
	    make_shared<enc_dict_map_opr<KEY_PT, INDEX_PT>>(physical_expr, column, column_descriptor, state));
	operators.emplace_back(make_shared<enc_analyze_opr<INDEX_PT>>(physical_expr, column, column_descriptor, state));
	operators.emplace_back(make_shared<enc_ffor_opr<INDEX_PT>>(physical_expr, column, column_descriptor, state));
}

/*--------------------------------------------------------------------------------------------------------------------*\
 * make_enc_fsst_dict_ffor_slpatch_expr
\*--------------------------------------------------------------------------------------------------------------------*/
template <typename FSSTDictEncoder, typename KEY_PT, typename INDEX_PT>
void make_enc_fsst_dict_ffor_slpatch_expr(PhysicalExpr&      physical_expr,
                                          const rowgroup_pt& rowgroup,
                                          ColumnDescriptorT& column_descriptor,
                                          InterpreterState&  state) {
	auto&       operators = physical_expr.operators;
	const auto& column    = rowgroup[column_descriptor.idx];

	operators.emplace_back(make_shared<FSSTDictEncoder>(physical_expr, column, column_descriptor, state));
	operators.emplace_back(
	    make_shared<enc_dict_map_opr<KEY_PT, INDEX_PT>>(physical_expr, column, column_descriptor, state));
	operators.emplace_back(
	    make_shared<enc_analyze_opr<INDEX_PT, true>>(physical_expr, column, column_descriptor, state));
	operators.emplace_back(make_shared<enc_slpatch_opr<INDEX_PT>>(physical_expr, column, column_descriptor, state));
	operators.emplace_back(make_shared<enc_ffor_opr<INDEX_PT>>(physical_expr, column, column_descriptor, state));
}

/*--------------------------------------------------------------------------------------------------------------------*\
 * make_enc_fsst_dict_expr
\*--------------------------------------------------------------------------------------------------------------------*/
template <typename FSSTDictTypeEncoder>
void make_enc_fsst_dict_expr(PhysicalExpr&      physical_expr,
                             const rowgroup_pt& rowgroup,
                             ColumnDescriptorT& column_descriptor,
                             InterpreterState&  state) {
	auto&       operators = physical_expr.operators;
	const auto& column    = rowgroup[column_descriptor.idx];

	operators.emplace_back(make_shared<FSSTDictTypeEncoder>(physical_expr, column, column_descriptor, state));
}

/*--------------------------------------------------------------------------------------------------------------------*\
 * make_enc_dict_expr
\*--------------------------------------------------------------------------------------------------------------------*/
template <typename KEY_PT>
void make_enc_dict_expr(PhysicalExpr&      physical_expr,
                        const rowgroup_pt& rowgroup,
                        ColumnDescriptorT& column_descriptor,
                        InterpreterState&  state) {
	auto&       operators = physical_expr.operators;
	const auto& column    = rowgroup[column_descriptor.idx];

	operators.emplace_back(make_shared<enc_dict_opr<KEY_PT>>(physical_expr, column, column_descriptor, state));
}

/*--------------------------------------------------------------------------------------------------------------------*\
 * make_alp_expr
\*--------------------------------------------------------------------------------------------------------------------*/
template <typename PT>
void make_enc_alp_expr(PhysicalExpr&      physical_expr,
                       const rowgroup_pt& rowgroup,
                       ColumnDescriptorT& column_descriptor,
                       InterpreterState&  state) {
	auto&       operators = physical_expr.operators;
	const auto& column    = rowgroup[column_descriptor.idx];

	operators.emplace_back(make_shared<enc_alp_opr<PT>>(physical_expr, column, column_descriptor, state));
}

/*--------------------------------------------------------------------------------------------------------------------*\
 * make_rle_expr
\*--------------------------------------------------------------------------------------------------------------------*/
template <typename KEY_PT, typename INDEX_PT>
void make_enc_rle_expr(PhysicalExpr&      physical_expr,
                       const rowgroup_pt& rowgroup,
                       ColumnDescriptorT& column_descriptor,
                       InterpreterState&  state) {
	auto&       operators = physical_expr.operators;
	const auto& column    = rowgroup[column_descriptor.idx];

	operators.emplace_back(
	    make_shared<enc_rle_map_opr<KEY_PT, INDEX_PT>>(physical_expr, column, column_descriptor, state));
	operators.emplace_back(make_shared<enc_transpose_opr<INDEX_PT>>(physical_expr, column, column_descriptor, state));
	operators.emplace_back(make_shared<enc_rsum_opr<INDEX_PT>>(physical_expr, column, column_descriptor, state));
	operators.emplace_back(make_shared<enc_analyze_opr<INDEX_PT>>(physical_expr, column, column_descriptor, state));
	operators.emplace_back(make_shared<enc_ffor_opr<INDEX_PT>>(physical_expr, column, column_descriptor, state));
}

/*--------------------------------------------------------------------------------------------------------------------*\
 * make_rle_slpatch_expr
\*--------------------------------------------------------------------------------------------------------------------*/
template <typename KEY_PT, typename INDEX_PT>
void make_enc_rle_slpatch_expr(PhysicalExpr&      physical_expr,
                               const rowgroup_pt& rowgroup,
                               ColumnDescriptorT& column_descriptor,
                               InterpreterState&  state) {
	auto&       operators = physical_expr.operators;
	const auto& column    = rowgroup[column_descriptor.idx];

	operators.emplace_back(
	    make_shared<enc_rle_map_opr<KEY_PT, INDEX_PT>>(physical_expr, column, column_descriptor, state));
	operators.emplace_back(make_shared<enc_transpose_opr<INDEX_PT>>(physical_expr, column, column_descriptor, state));
	operators.emplace_back(make_shared<enc_rsum_opr<INDEX_PT>>(physical_expr, column, column_descriptor, state));
	operators.emplace_back(
	    make_shared<enc_analyze_opr<INDEX_PT, true>>(physical_expr, column, column_descriptor, state));
	operators.emplace_back(make_shared<enc_slpatch_opr<INDEX_PT>>(physical_expr, column, column_descriptor, state));
	operators.emplace_back(make_shared<enc_ffor_opr<INDEX_PT>>(physical_expr, column, column_descriptor, state));
}

/*--------------------------------------------------------------------------------------------------------------------*\
 * make_delta_expr
\*--------------------------------------------------------------------------------------------------------------------*/
template <typename PT>
void make_enc_delta_expr(PhysicalExpr&      physical_expr,
                         const rowgroup_pt& rowgroup,
                         ColumnDescriptorT& column_descriptor,
                         InterpreterState&  state) {
	auto&       operators = physical_expr.operators;
	const auto& column    = rowgroup[column_descriptor.idx];

	operators.emplace_back(make_shared<enc_scan_opr<PT>>(physical_expr, column, column_descriptor, state));
	operators.emplace_back(make_shared<enc_transpose_opr<PT>>(physical_expr, column, column_descriptor, state));
	operators.emplace_back(make_shared<enc_rsum_opr<PT>>(physical_expr, column, column_descriptor, state));
	operators.emplace_back(make_shared<enc_analyze_opr<PT>>(physical_expr, column, column_descriptor, state));
	operators.emplace_back(
	    make_shared<enc_ffor_opr<make_unsigned_t<PT>>>(physical_expr, column, column_descriptor, state));
}
/*--------------------------------------------------------------------------------------------------------------------*\
 * make_alp_expr
\*--------------------------------------------------------------------------------------------------------------------*/
template <typename PT>
void make_enc_alp_rd_expr(PhysicalExpr&      physical_expr,
                          const rowgroup_pt& rowgroup,
                          ColumnDescriptorT& column_descriptor,
                          InterpreterState&  state) {
	auto&       operators = physical_expr.operators;
	const auto& column    = rowgroup[column_descriptor.idx];

	operators.emplace_back(make_shared<enc_alp_rd_opr<PT>>(physical_expr, column, column_descriptor, state));
}

/*--------------------------------------------------------------------------------------------------------------------*\
 * Interpreter::Encoding
\*--------------------------------------------------------------------------------------------------------------------*/

InterpreterState::InterpreterState()
    : cur_operator(0)
    , cur_operand(0)
    , n_segments(0) {
}

sp<PhysicalExpr> Interpreter::Encoding::Interpret(ColumnDescriptorT& column_descriptor,
                                                  const rowgroup_pt& physical_rowgroup,
                                                  InterpreterState&  state) {
	// return
	auto physical_expr = make_shared<PhysicalExpr>();

	for (auto& [operator_tokens, operand_tokens] = *column_descriptor.encoding_rpn;
	     const auto& operator_token : operator_tokens) {
		using enum OperatorToken;
		switch (operator_token) {
		case EXP_UNCOMPRESSED_I64: {
			make_enc_uncompressed_expr<i64_pt>(*physical_expr, physical_rowgroup, column_descriptor, state);
			break;
		}
		case EXP_UNCOMPRESSED_I32: {
			make_enc_uncompressed_expr<i32_pt>(*physical_expr, physical_rowgroup, column_descriptor, state);
			break;
		}
		case EXP_UNCOMPRESSED_I16: {
			make_enc_uncompressed_expr<i16_pt>(*physical_expr, physical_rowgroup, column_descriptor, state);
			break;
		}
		case EXP_UNCOMPRESSED_U08: {
			make_enc_uncompressed_expr<u08_pt>(*physical_expr, physical_rowgroup, column_descriptor, state);
			break;
		}
		case EXP_FFOR_I64: {
			make_enc_ffor_expr<i64_pt>(*physical_expr, physical_rowgroup, column_descriptor, state);
			break;
		}
		case EXP_FFOR_I32: {
			make_enc_ffor_expr<i32_pt>(*physical_expr, physical_rowgroup, column_descriptor, state);
			break;
		}
		case EXP_FFOR_I16: {
			make_enc_ffor_expr<i16_pt>(*physical_expr, physical_rowgroup, column_descriptor, state);
			break;
		}
		case EXP_FFOR_I08: {
			make_enc_ffor_expr<i08_pt>(*physical_expr, physical_rowgroup, column_descriptor, state);
			break;
		}
		case EXP_UNCOMPRESSED_DBL: {
			make_enc_uncompressed_expr<dbl_pt>(*physical_expr, physical_rowgroup, column_descriptor, state);
			break;
		}
		case EXP_UNCOMPRESSED_FLT: {
			make_enc_uncompressed_expr<flt_pt>(*physical_expr, physical_rowgroup, column_descriptor, state);
			break;
		}
		case EXP_UNCOMPRESSED_I08: {
			make_enc_uncompressed_expr<i08_pt>(*physical_expr, physical_rowgroup, column_descriptor, state);
			break;
		}
		case EXP_UNCOMPRESSED_STR: {
			make_fls_str_uncompressed_expr(*physical_expr, physical_rowgroup, column_descriptor, state);
			break;
		}
		case EXP_CONSTANT_DBL:
		case EXP_CONSTANT_I64:
		case EXP_CONSTANT_I32:
		case EXP_CONSTANT_I16:
		case EXP_CONSTANT_I08:
		case EXP_CONSTANT_STR:
		case EXP_CONSTANT_U08:
		case EXP_CONSTANT_FLT:
		case EXP_EQUAL: {
			break;
		}
		case EXP_STRUCT: {
			make_enc_struct_expr(*physical_expr, physical_rowgroup, column_descriptor, state);
			break;
		}
		case EXP_DICT_I64_FFOR_U32: {
			make_enc_dict_ffor_expr<i64_pt, u32_pt>(*physical_expr, physical_rowgroup, column_descriptor, state);
			break;
		}
		case EXP_DICT_I64_FFOR_U16: {
			make_enc_dict_ffor_expr<i64_pt, u16_pt>(*physical_expr, physical_rowgroup, column_descriptor, state);
			break;
		}
		case EXP_DICT_I64_FFOR_U08: {
			make_enc_dict_ffor_expr<i64_pt, u08_pt>(*physical_expr, physical_rowgroup, column_descriptor, state);
			break;
		}
		case EXP_DICT_I32_FFOR_U32: {
			make_enc_dict_ffor_expr<i32_pt, u32_pt>(*physical_expr, physical_rowgroup, column_descriptor, state);
			break;
		}
		case EXP_DICT_I32_FFOR_U16: {
			make_enc_dict_ffor_expr<i32_pt, u16_pt>(*physical_expr, physical_rowgroup, column_descriptor, state);
			break;
		}
		case EXP_DICT_I32_FFOR_U08: {
			make_enc_dict_ffor_expr<i32_pt, u08_pt>(*physical_expr, physical_rowgroup, column_descriptor, state);
			break;
		}
		case EXP_DICT_I16_FFOR_U16: {
			make_enc_dict_ffor_expr<i16_pt, u16_pt>(*physical_expr, physical_rowgroup, column_descriptor, state);
			break;
		}
		case EXP_DICT_DBL_FFOR_U32: {
			make_enc_dict_ffor_expr<dbl_pt, u32_pt>(*physical_expr, physical_rowgroup, column_descriptor, state);
			break;
		}
		case EXP_DICT_I16_FFOR_U08: {
			make_enc_dict_ffor_expr<i16_pt, u08_pt>(*physical_expr, physical_rowgroup, column_descriptor, state);
			break;
		}
		case EXP_DICT_I08_FFOR_U08: {
			make_enc_dict_ffor_expr<i08_pt, u08_pt>(*physical_expr, physical_rowgroup, column_descriptor, state);
			break;
		}
		case EXP_DICT_DBL_FFOR_U16: {
			make_enc_dict_ffor_expr<dbl_pt, u16_pt>(*physical_expr, physical_rowgroup, column_descriptor, state);
			break;
		}
		case EXP_DICT_FLT_FFOR_U16: {
			make_enc_dict_ffor_expr<flt_pt, u16_pt>(*physical_expr, physical_rowgroup, column_descriptor, state);
			break;
		}
		case EXP_DICT_DBL_FFOR_U08: {
			make_enc_dict_ffor_expr<dbl_pt, u08_pt>(*physical_expr, physical_rowgroup, column_descriptor, state);
			break;
		}
		case EXP_DICT_FLT_FFOR_U08: {
			make_enc_dict_ffor_expr<flt_pt, u08_pt>(*physical_expr, physical_rowgroup, column_descriptor, state);
			break;
		}
		case EXP_DICT_I64_U08:
		case EXP_DICT_I64_U16:
		case EXP_DICT_I64_U32: {
			make_enc_dict_expr<i64_pt>(*physical_expr, physical_rowgroup, column_descriptor, state);
			break;
		}
		case EXP_DICT_I32_U08:
		case EXP_DICT_I32_U16:
		case EXP_DICT_I32_U32: {
			make_enc_dict_expr<i32_pt>(*physical_expr, physical_rowgroup, column_descriptor, state);
			break;
		}
		case EXP_DICT_I16_U08:
		case EXP_DICT_I16_U16: {
			make_enc_dict_expr<i16_pt>(*physical_expr, physical_rowgroup, column_descriptor, state);
			break;
		}
		case EXP_DICT_I08_U08: {
			make_enc_dict_expr<i08_pt>(*physical_expr, physical_rowgroup, column_descriptor, state);
			break;
		}
		case EXP_DICT_DBL_U08:
		case EXP_DICT_DBL_U16:
		case EXP_DICT_DBL_U32: {
			make_enc_dict_expr<dbl_pt>(*physical_expr, physical_rowgroup, column_descriptor, state);
			break;
		}
		case EXP_DICT_STR_U08:
		case EXP_DICT_STR_U16:
		case EXP_DICT_STR_U32: {
			make_enc_dict_expr<fls_string_t>(*physical_expr, physical_rowgroup, column_descriptor, state);
			break;
		}
		case EXP_ALP_DBL: {
			make_enc_alp_expr<dbl_pt>(*physical_expr, physical_rowgroup, column_descriptor, state);
			break;
		}
		case EXP_ALP_FLT: {
			make_enc_alp_expr<flt_pt>(*physical_expr, physical_rowgroup, column_descriptor, state);
			break;
		}
		case EXP_ALP_RD_DBL: {
			make_enc_alp_rd_expr<dbl_pt>(*physical_expr, physical_rowgroup, column_descriptor, state);
			break;
		}
		case EXP_ALP_RD_FLT: {
			make_enc_alp_rd_expr<flt_pt>(*physical_expr, physical_rowgroup, column_descriptor, state);
			break;
		}
		case EXP_FSST: {
			make_fsst_expr<enc_fsst_opr>(*physical_expr, physical_rowgroup, column_descriptor, state);
			break;
		}
		case EXP_FSST12: {
			make_fsst_expr<enc_fsst12_opr>(*physical_expr, physical_rowgroup, column_descriptor, state);
			break;
		}
		case EXP_DICT_STR_FFOR_U32: {
			make_enc_dict_ffor_expr<fls_string_t, u32_pt>(*physical_expr, physical_rowgroup, column_descriptor, state);
			break;
		}
		case EXP_DICT_STR_FFOR_U16: {
			make_enc_dict_ffor_expr<fls_string_t, u16_pt>(*physical_expr, physical_rowgroup, column_descriptor, state);
			break;
		}
		case EXP_DICT_STR_FFOR_U08: {
			make_enc_dict_ffor_expr<fls_string_t, u08_pt>(*physical_expr, physical_rowgroup, column_descriptor, state);
			break;
		}
		case EXP_FSST_DICT_STR_FFOR_U32: {
			make_enc_fsst_dict_ffor_expr<enc_fsst_dict_opr, fls_string_t, u32_pt>(
			    *physical_expr, physical_rowgroup, column_descriptor, state);
			break;
		}
		case EXP_FSST_DICT_STR_FFOR_U16: {
			make_enc_fsst_dict_ffor_expr<enc_fsst_dict_opr, fls_string_t, u16_pt>(
			    *physical_expr, physical_rowgroup, column_descriptor, state);
			break;
		}
		case EXP_FSST_DICT_STR_FFOR_U08: {
			make_enc_fsst_dict_ffor_expr<enc_fsst_dict_opr, fls_string_t, u08_pt>(
			    *physical_expr, physical_rowgroup, column_descriptor, state);
			break;
		}

		case EXP_RLE_DBL_U16: {
			make_enc_rle_expr<dbl_pt, u16_pt>(*physical_expr, physical_rowgroup, column_descriptor, state);
			break;
		}
		case EXP_RLE_FLT_U16: {
			make_enc_rle_expr<flt_pt, u16_pt>(*physical_expr, physical_rowgroup, column_descriptor, state);
			break;
		}
		case EXP_RLE_I64_U16: {
			make_enc_rle_expr<i64_pt, u16_pt>(*physical_expr, physical_rowgroup, column_descriptor, state);
			break;
		}
		case EXP_RLE_I32_U16: {
			make_enc_rle_expr<i32_pt, u16_pt>(*physical_expr, physical_rowgroup, column_descriptor, state);
			break;
		}
		case EXP_RLE_I16_U16: {
			make_enc_rle_expr<i16_pt, u16_pt>(*physical_expr, physical_rowgroup, column_descriptor, state);
			break;
		}
		case EXP_RLE_I08_U16: {
			make_enc_rle_expr<i08_pt, u16_pt>(*physical_expr, physical_rowgroup, column_descriptor, state);
			break;
		}
		case EXP_RLE_STR_U16: {
			make_enc_rle_expr<fls_string_t, u16_pt>(*physical_expr, physical_rowgroup, column_descriptor, state);
			break;
		}
		case EXP_FSST_DELTA: {
			make_fsst_delta_expr<enc_fsst_opr>(*physical_expr, physical_rowgroup, column_descriptor, state);
			break;
		}
		case EXP_FSST12_DELTA: {
			make_fsst_delta_expr<enc_fsst12_opr>(*physical_expr, physical_rowgroup, column_descriptor, state);
			break;
		}
		case EXP_DELTA_I64: {
			make_enc_delta_expr<i64_pt>(*physical_expr, physical_rowgroup, column_descriptor, state);
			break;
		}
		case EXP_DELTA_I32: {
			make_enc_delta_expr<i32_pt>(*physical_expr, physical_rowgroup, column_descriptor, state);
			break;
		}
		case EXP_DELTA_I16: {
			make_enc_delta_expr<i16_pt>(*physical_expr, physical_rowgroup, column_descriptor, state);
			break;
		}
		case EXP_DELTA_I08: {
			make_enc_delta_expr<i08_pt>(*physical_expr, physical_rowgroup, column_descriptor, state);
			break;
		}
		case EXP_FFOR_SLPATCH_I64: {
			make_enc_ffor_slpatch_expr<i64_pt>(*physical_expr, physical_rowgroup, column_descriptor, state);
			break;
		}
		case EXP_FFOR_SLPATCH_I32: {
			make_enc_ffor_slpatch_expr<i32_pt>(*physical_expr, physical_rowgroup, column_descriptor, state);
			break;
		}
		case EXP_FFOR_SLPATCH_I16: {
			make_enc_ffor_slpatch_expr<i16_pt>(*physical_expr, physical_rowgroup, column_descriptor, state);
			break;
		}
		case EXP_FFOR_SLPATCH_I08: {
			make_enc_ffor_slpatch_expr<i08_pt>(*physical_expr, physical_rowgroup, column_descriptor, state);
			break;
		}
		case EXP_DICT_I64_FFOR_SLPATCH_U16: {
			make_enc_dict_ffor_slpatch_expr<i64_pt, u16_pt>(
			    *physical_expr, physical_rowgroup, column_descriptor, state);
			break;
		}
		case EXP_DICT_I64_FFOR_SLPATCH_U32: {
			make_enc_dict_ffor_slpatch_expr<i64_pt, u32_pt>(
			    *physical_expr, physical_rowgroup, column_descriptor, state);
			break;
		}
		case EXP_DICT_I32_FFOR_SLPATCH_U32: {
			make_enc_dict_ffor_slpatch_expr<i32_pt, u32_pt>(
			    *physical_expr, physical_rowgroup, column_descriptor, state);
			break;
		}
		case EXP_DICT_I32_FFOR_SLPATCH_U16: {
			make_enc_dict_ffor_slpatch_expr<i32_pt, u16_pt>(
			    *physical_expr, physical_rowgroup, column_descriptor, state);
			break;
		}
		case EXP_DICT_I32_FFOR_SLPATCH_U08: {
			make_enc_dict_ffor_slpatch_expr<i32_pt, u08_pt>(
			    *physical_expr, physical_rowgroup, column_descriptor, state);
			break;
		}
		case EXP_DICT_DBL_FFOR_SLPATCH_U16: {
			make_enc_dict_ffor_slpatch_expr<dbl_pt, u16_pt>(
			    *physical_expr, physical_rowgroup, column_descriptor, state);
			break;
		}
		case EXP_DICT_STR_FFOR_SLPATCH_U32: {
			make_enc_dict_ffor_slpatch_expr<fls_string_t, u32_pt>(
			    *physical_expr, physical_rowgroup, column_descriptor, state);
			break;
		}
		case EXP_DICT_STR_FFOR_SLPATCH_U16: {
			make_enc_dict_ffor_slpatch_expr<fls_string_t, u16_pt>(
			    *physical_expr, physical_rowgroup, column_descriptor, state);
			break;
		}
		case EXP_DICT_STR_FFOR_SLPATCH_U08: {
			make_enc_dict_ffor_slpatch_expr<fls_string_t, u08_pt>(
			    *physical_expr, physical_rowgroup, column_descriptor, state);
			break;
		}
		case EXP_DICT_I16_FFOR_SLPATCH_U08: {
			make_enc_dict_ffor_slpatch_expr<i16_pt, u08_pt>(
			    *physical_expr, physical_rowgroup, column_descriptor, state);
			break;
		}
		case EXP_DICT_I08_FFOR_SLPATCH_U08: {
			make_enc_dict_ffor_slpatch_expr<i08_pt, u08_pt>(
			    *physical_expr, physical_rowgroup, column_descriptor, state);
			break;
		}
		case EXP_DICT_I16_FFOR_SLPATCH_U16: {
			make_enc_dict_ffor_slpatch_expr<i16_pt, u16_pt>(
			    *physical_expr, physical_rowgroup, column_descriptor, state);
			break;
		}
		case EXP_DICT_I64_FFOR_SLPATCH_U08: {
			make_enc_dict_ffor_slpatch_expr<i64_pt, u08_pt>(
			    *physical_expr, physical_rowgroup, column_descriptor, state);
			break;
		}
		case EXP_DICT_DBL_FFOR_SLPATCH_U08: {
			make_enc_dict_ffor_slpatch_expr<dbl_pt, u08_pt>(
			    *physical_expr, physical_rowgroup, column_descriptor, state);
			break;
		}
		case EXP_DICT_FLT_FFOR_SLPATCH_U08: {
			make_enc_dict_ffor_slpatch_expr<flt_pt, u08_pt>(
			    *physical_expr, physical_rowgroup, column_descriptor, state);
			break;
		}
		case EXP_DICT_FLT_FFOR_SLPATCH_U16: {
			make_enc_dict_ffor_slpatch_expr<flt_pt, u16_pt>(
			    *physical_expr, physical_rowgroup, column_descriptor, state);
			break;
		}
		case EXP_DICT_DBL_FFOR_SLPATCH_U32: {
			make_enc_dict_ffor_slpatch_expr<dbl_pt, u32_pt>(
			    *physical_expr, physical_rowgroup, column_descriptor, state);
			break;
		}
		case EXP_FSST_DICT_STR_FFOR_SLPATCH_U32: {
			make_enc_fsst_dict_ffor_slpatch_expr<enc_fsst_dict_opr, fls_string_t, u32_pt>(
			    *physical_expr, physical_rowgroup, column_descriptor, state);
			break;
		}
		case EXP_FSST_DICT_STR_FFOR_SLPATCH_U16: {
			make_enc_fsst_dict_ffor_slpatch_expr<enc_fsst_dict_opr, fls_string_t, u16_pt>(
			    *physical_expr, physical_rowgroup, column_descriptor, state);
			break;
		}
		case EXP_FSST_DICT_STR_FFOR_SLPATCH_U08: {
			make_enc_fsst_dict_ffor_slpatch_expr<enc_fsst_dict_opr, fls_string_t, u08_pt>(
			    *physical_expr, physical_rowgroup, column_descriptor, state);
			break;
		}
		case EXP_FSST12_DICT_STR_FFOR_SLPATCH_U32: {
			make_enc_fsst_dict_ffor_slpatch_expr<enc_fsst12_dict_opr, fls_string_t, u32_pt>(
			    *physical_expr, physical_rowgroup, column_descriptor, state);
			break;
		}
		case EXP_FSST12_DICT_STR_FFOR_SLPATCH_U16: {
			make_enc_fsst_dict_ffor_slpatch_expr<enc_fsst12_dict_opr, fls_string_t, u16_pt>(
			    *physical_expr, physical_rowgroup, column_descriptor, state);
			break;
		}
		case EXP_FSST12_DICT_STR_FFOR_SLPATCH_U08: {
			make_enc_fsst_dict_ffor_slpatch_expr<enc_fsst12_dict_opr, fls_string_t, u08_pt>(
			    *physical_expr, physical_rowgroup, column_descriptor, state);
			break;
		}
		case EXP_NULL_DBL: {
			make_enc_null_expr<dbl_pt>(*physical_expr, physical_rowgroup, column_descriptor, state);
			break;
		}
		case EXP_NULL_FLT: {
			make_enc_null_expr<flt_pt>(*physical_expr, physical_rowgroup, column_descriptor, state);
			break;
		}
		case EXP_NULL_I16: {
			make_enc_null_expr<i16_pt>(*physical_expr, physical_rowgroup, column_descriptor, state);
			break;
		}
		case EXP_NULL_I32: {
			make_enc_null_expr<i32_pt>(*physical_expr, physical_rowgroup, column_descriptor, state);
			break;
		}
		case EXP_RLE_I64_SLPATCH_U16: {
			make_enc_rle_slpatch_expr<i64_pt, u16_pt>(*physical_expr, physical_rowgroup, column_descriptor, state);
			break;
		}
		case EXP_RLE_I32_SLPATCH_U16: {
			make_enc_rle_slpatch_expr<i32_pt, u16_pt>(*physical_expr, physical_rowgroup, column_descriptor, state);
			break;
		}
		case EXP_RLE_I16_SLPATCH_U16: {
			make_enc_rle_slpatch_expr<i16_pt, u16_pt>(*physical_expr, physical_rowgroup, column_descriptor, state);
			break;
		}
		case EXP_RLE_I08_SLPATCH_U16: {
			make_enc_rle_slpatch_expr<i08_pt, u16_pt>(*physical_expr, physical_rowgroup, column_descriptor, state);
			break;
		}
		case EXP_RLE_STR_SLPATCH_U16: {
			make_enc_rle_slpatch_expr<fls_string_t, u16_pt>(
			    *physical_expr, physical_rowgroup, column_descriptor, state);
			break;
		}
		case EXP_RLE_DBL_SLPATCH_U16: {
			make_enc_rle_slpatch_expr<dbl_pt, u16_pt>(*physical_expr, physical_rowgroup, column_descriptor, state);
			break;
		}
		case EXP_RLE_FLT_SLPATCH_U16: {
			make_enc_rle_slpatch_expr<flt_pt, u16_pt>(*physical_expr, physical_rowgroup, column_descriptor, state);
			break;
		}
		case EXP_FSST_DICT_STR_U32:
		case EXP_FSST_DICT_STR_U16:
		case EXP_FSST_DICT_STR_U08: {
			make_enc_fsst_dict_expr<enc_fsst_dict_opr>(*physical_expr, physical_rowgroup, column_descriptor, state);
			break;
		}
		case EXP_FSST_DELTA_SLPATCH: {
			make_enc_fsst_delta_slpatch_expr<enc_fsst_opr>(*physical_expr, physical_rowgroup, column_descriptor, state);
			break;
		}
		case EXP_FSST12_DELTA_SLPATCH: {
			make_enc_fsst_delta_slpatch_expr<enc_fsst12_opr>(
			    *physical_expr, physical_rowgroup, column_descriptor, state);
			break;
		}
		case WIZARD_DICTIONARY_ENCODE: {
			FLS_UNREACHABLE()
		}
		case EXP_FSST12_DICT_STR_U32:
		case EXP_FSST12_DICT_STR_U16:
		case EXP_FSST12_DICT_STR_U08: {
			make_enc_fsst_dict_expr<enc_fsst12_dict_opr>(*physical_expr, physical_rowgroup, column_descriptor, state);
			break;
		}
		case EXP_FSST12_DICT_STR_FFOR_U32: {
			make_enc_fsst_dict_ffor_expr<enc_fsst12_dict_opr, fls_string_t, u32_pt>(
			    *physical_expr, physical_rowgroup, column_descriptor, state);
			break;
		}
		case EXP_FSST12_DICT_STR_FFOR_U16: {
			make_enc_fsst_dict_ffor_expr<enc_fsst12_dict_opr, fls_string_t, u16_pt>(
			    *physical_expr, physical_rowgroup, column_descriptor, state);
			break;
		}
		case EXP_FSST12_DICT_STR_FFOR_U08: {
			make_enc_fsst_dict_ffor_expr<enc_fsst12_dict_opr, fls_string_t, u08_pt>(
			    *physical_expr, physical_rowgroup, column_descriptor, state);
			break;
		}
		case EXP_FREQUENCY_DBL: {
			make_enc_frequency_expr<dbl_pt>(*physical_expr, physical_rowgroup, column_descriptor, state);
			break;
		}
		case EXP_FREQUENCY_FLT: {
			make_enc_frequency_expr<flt_pt>(*physical_expr, physical_rowgroup, column_descriptor, state);
			break;
		}
		case EXP_FREQUENCY_I08: {
			make_enc_frequency_expr<i08_pt>(*physical_expr, physical_rowgroup, column_descriptor, state);
			break;
		}
		case EXP_FREQUENCY_I16: {
			make_enc_frequency_expr<i16_pt>(*physical_expr, physical_rowgroup, column_descriptor, state);
			break;
		}
		case EXP_FREQUENCY_I32: {
			make_enc_frequency_expr<i32_pt>(*physical_expr, physical_rowgroup, column_descriptor, state);
			break;
		}
		case EXP_FREQUENCY_I64: {
			make_enc_frequency_expr<i64_pt>(*physical_expr, physical_rowgroup, column_descriptor, state);
			break;
		}
		case EXP_FREQUENCY_STR: {
			make_enc_frequency_str_opr(*physical_expr, physical_rowgroup, column_descriptor, state);
			break;
		}
		case EXP_CROSS_RLE_I08: {
			make_enc_cross_rle_opr<i08_pt>(*physical_expr, physical_rowgroup, column_descriptor, state);
			break;
		}
		case EXP_CROSS_RLE_I16: {
			make_enc_cross_rle_opr<i16_pt>(*physical_expr, physical_rowgroup, column_descriptor, state);
			break;
		}
		case EXP_CROSS_RLE_I32: {
			make_enc_cross_rle_opr<i32_pt>(*physical_expr, physical_rowgroup, column_descriptor, state);
			break;
		}
		case EXP_CROSS_RLE_I64: {
			make_enc_cross_rle_opr<i64_pt>(*physical_expr, physical_rowgroup, column_descriptor, state);
			break;
		}
		case EXP_CROSS_RLE_DBL: {
			make_enc_cross_rle_opr<dbl_pt>(*physical_expr, physical_rowgroup, column_descriptor, state);
			break;
		}
		case EXP_CROSS_RLE_FLT: {
			make_enc_cross_rle_opr<flt_pt>(*physical_expr, physical_rowgroup, column_descriptor, state);
			break;
		}
		case EXP_CROSS_RLE_STR: {
			make_enc_cross_rle_opr<fls_string_t>(*physical_expr, physical_rowgroup, column_descriptor, state);
			break;
		}

		case INVALID:
		default:
			throw_not_supported_exception(operator_token);
			FLS_UNREACHABLE();
		}
	}

	return physical_expr;
}

/*--------------------------------------------------------------------------------------------------------------------*\
 * make_dec_uncompressed_expr
\*--------------------------------------------------------------------------------------------------------------------*/
template <typename PT>
void make_dec_uncompressed_expr(PhysicalExpr&           physical_expr,
                                const ColumnView&       column_view,
                                const InterpreterState& state) {
	auto& rpn = column_view.column_descriptor.encoding_rpn;

	FLS_ASSERT_E(rpn->operand_tokens.size(), 1)

	physical_expr.operators.emplace_back(
	    make_shared<dec_uncompressed_opr<PT>>(column_view, rpn->operand_tokens.back()));
}

/*--------------------------------------------------------------------------------------------------------------------*\
 * make_dec_fls_str_uncompressed_expr
\*--------------------------------------------------------------------------------------------------------------------*/
void make_dec_fls_str_uncompressed_expr(PhysicalExpr&     physical_expr,
                                        const ColumnView& column_view,
                                        InterpreterState& state) {

	auto& rpn = column_view.column_descriptor.encoding_rpn;

	physical_expr.operators.emplace_back(make_shared<dec_fls_str_uncompressed_opr>(column_view, *rpn));
	state.cur_operator = state.cur_operator + 1;
}

/*--------------------------------------------------------------------------------------------------------------------*\
 * make_dec_fsst_expr
\*--------------------------------------------------------------------------------------------------------------------*/
template <typename FSSTDecoder>
void make_dec_fsst_expr(PhysicalExpr& physical_expr, const ColumnView& column_view, InterpreterState& state) {
	state.cur_operand = column_view.column_descriptor.encoding_rpn->operand_tokens.size() - 1;
	physical_expr.operators.emplace_back(make_shared<dec_scan_opr<ofs_t>>(column_view, state));
	physical_expr.operators.emplace_back(make_shared<FSSTDecoder>(physical_expr, column_view, state));
	state.cur_operator = state.cur_operator + 2;
}

/*--------------------------------------------------------------------------------------------------------------------*\
 * make_dec_fsst_delta_expr
\*--------------------------------------------------------------------------------------------------------------------*/
template <typename FSSTDecoder>
void make_dec_fsst_delta_expr(PhysicalExpr& physical_expr, const ColumnView& column_view, InterpreterState& state) {
	state.cur_operand = column_view.column_descriptor.encoding_rpn->operand_tokens.size() - 1;
	physical_expr.operators.emplace_back(make_shared<dec_unffor_opr<ofs_t>>(column_view, state));
	physical_expr.operators.emplace_back(make_shared<dec_rsum_opr<ofs_t>>(physical_expr, column_view, state));
	physical_expr.operators.emplace_back(make_shared<FSSTDecoder>(physical_expr, column_view, state));
	state.cur_operator = state.cur_operator + 3;
}

/*--------------------------------------------------------------------------------------------------------------------*\
 * make_dec_fsst_delta_slpatch_expr
\*--------------------------------------------------------------------------------------------------------------------*/
template <typename FSSTDecoder>
void make_dec_fsst_delta_slpatch_expr(PhysicalExpr&     physical_expr,
                                      const ColumnView& column_view,
                                      InterpreterState& state) {
	state.cur_operand = column_view.column_descriptor.encoding_rpn->operand_tokens.size() - 1;
	physical_expr.operators.emplace_back(make_shared<dec_unffor_opr<ofs_t>>(column_view, state));
	physical_expr.operators.emplace_back(make_shared<dec_slpatch_opr<ofs_t>>(physical_expr, column_view, state));
	physical_expr.operators.emplace_back(make_shared<dec_rsum_opr<ofs_t>>(physical_expr, column_view, state));
	physical_expr.operators.emplace_back(make_shared<FSSTDecoder>(physical_expr, column_view, state));
	state.cur_operator = state.cur_operator + 3;
}

/*--------------------------------------------------------------------------------------------------------------------*\
 * make_dec_ffor_expr
\*--------------------------------------------------------------------------------------------------------------------*/
template <typename PT>
void make_dec_ffor_expr(PhysicalExpr& physical_expr, const ColumnView& column_view, InterpreterState& state) {
	state.cur_operand = column_view.column_descriptor.encoding_rpn->operand_tokens.size() - 1;
	physical_expr.operators.emplace_back(make_shared<dec_unffor_opr<make_unsigned_t<PT>>>(column_view, state));
}

/*--------------------------------------------------------------------------------------------------------------------*\
 * make_dec_ffor_sl_patch_expr
\*--------------------------------------------------------------------------------------------------------------------*/
template <typename PT>
void make_dec_ffor_slpatch_expr(PhysicalExpr& physical_expr, const ColumnView& column_view, InterpreterState& state) {
	state.cur_operand = column_view.column_descriptor.encoding_rpn->operand_tokens.size() - 1;
	physical_expr.operators.emplace_back(make_shared<dec_unffor_opr<make_unsigned_t<PT>>>(column_view, state));
	physical_expr.operators.emplace_back(make_shared<dec_slpatch_opr<PT>>(physical_expr, column_view, state));
}

/*--------------------------------------------------------------------------------------------------------------------*\
 * make_dec_alp_expr
\*--------------------------------------------------------------------------------------------------------------------*/
template <typename PT>
void make_dec_alp_expr(PhysicalExpr& physical_expr, const ColumnView& column_view, InterpreterState& state) {
	state.cur_operand = column_view.column_descriptor.encoding_rpn->operand_tokens.size() - 1;
	physical_expr.operators.emplace_back(make_shared<dec_alp_opr<PT>>(column_view, state));
}

/*--------------------------------------------------------------------------------------------------------------------*\
 * make_dec_alp_rd_expr
\*--------------------------------------------------------------------------------------------------------------------*/
template <typename PT>
void make_dec_alp_rd_expr(PhysicalExpr& physical_expr, const ColumnView& column_view, InterpreterState& state) {
	state.cur_operand = column_view.column_descriptor.encoding_rpn->operand_tokens.size() - 1;
	physical_expr.operators.emplace_back(make_shared<dec_alp_rd_opr<PT>>(column_view, state));
}

/*--------------------------------------------------------------------------------------------------------------------*\
 * make_dec_dict_ffor_expr
\*--------------------------------------------------------------------------------------------------------------------*/
template <typename KEY_PT, typename INDEX_PT>
void make_dec_dict_ffor_expr(PhysicalExpr& physical_expr, const ColumnView& column_view, InterpreterState& state) {
	state.cur_operand = column_view.column_descriptor.encoding_rpn->operand_tokens.size() - 1;
	physical_expr.operators.emplace_back(make_shared<dec_unffor_opr<INDEX_PT>>(column_view, state));
	physical_expr.operators.emplace_back(
	    make_shared<dec_dict_opr<KEY_PT, INDEX_PT>>(physical_expr, column_view, state));
}

/*--------------------------------------------------------------------------------------------------------------------*\
 * make_dec_null_expr
\*--------------------------------------------------------------------------------------------------------------------*/
template <typename PT>
void make_dec_null_expr(PhysicalExpr& physical_expr, const ColumnView& column_view, InterpreterState& state) {
	state.cur_operand = column_view.column_descriptor.encoding_rpn->operand_tokens.size() - 1;
	physical_expr.operators.emplace_back(make_shared<dec_null_opr<PT>>(physical_expr, column_view, state));
}

/*--------------------------------------------------------------------------------------------------------------------*\
 * make_dec_frequency_expr
\*--------------------------------------------------------------------------------------------------------------------*/
template <typename PT>
void make_dec_frequency_expr(PhysicalExpr& physical_expr, const ColumnView& column_view, InterpreterState& state) {
	state.cur_operand = column_view.column_descriptor.encoding_rpn->operand_tokens.size() - 1;
	physical_expr.operators.emplace_back(make_shared<dec_frequency_opr<PT>>(physical_expr, column_view, state));
}

/*--------------------------------------------------------------------------------------------------------------------*\
 * make_dec_frequency_str_expr
\*--------------------------------------------------------------------------------------------------------------------*/
void make_dec_frequency_str_expr(PhysicalExpr& physical_expr, const ColumnView& column_view, InterpreterState& state) {
	state.cur_operand = column_view.column_descriptor.encoding_rpn->operand_tokens.size() - 1;
	physical_expr.operators.emplace_back(make_shared<dec_frequency_str_opr>(physical_expr, column_view, state));
}

/*--------------------------------------------------------------------------------------------------------------------*\
 * make_dec_cross_rle_expr
\*--------------------------------------------------------------------------------------------------------------------*/
template <typename PT>
void make_dec_cross_rle_expr(PhysicalExpr& physical_expr, const ColumnView& column_view, InterpreterState& state) {
	state.cur_operand = column_view.column_descriptor.encoding_rpn->operand_tokens.size() - 1;
	physical_expr.operators.emplace_back(make_shared<dec_cross_rle_opr<PT>>(physical_expr, column_view, state));
}

/*--------------------------------------------------------------------------------------------------------------------*\
 * make_dec_dict_ffor_slpatch_expr
\*--------------------------------------------------------------------------------------------------------------------*/
template <typename KEY_PT, typename INDEX_PT>
void make_dec_dict_ffor_slpatch_expr(PhysicalExpr&     physical_expr,
                                     const ColumnView& column_view,
                                     InterpreterState& state) {
	state.cur_operand = column_view.column_descriptor.encoding_rpn->operand_tokens.size() - 1;
	physical_expr.operators.emplace_back(make_shared<dec_unffor_opr<INDEX_PT>>(column_view, state));
	physical_expr.operators.emplace_back(make_shared<dec_slpatch_opr<INDEX_PT>>(physical_expr, column_view, state));
	physical_expr.operators.emplace_back(
	    make_shared<dec_dict_opr<KEY_PT, INDEX_PT>>(physical_expr, column_view, state));
}

/*--------------------------------------------------------------------------------------------------------------------*\
 * make_dec_fsst_dict_ffor_expr
\*--------------------------------------------------------------------------------------------------------------------*/
template <typename FSST_DICT_DECODER_T, typename INDEX_PT>
void make_dec_fsst_dict_ffor_expr(PhysicalExpr& physical_expr, const ColumnView& column_view, InterpreterState& state) {
	state.cur_operand = column_view.column_descriptor.encoding_rpn->operand_tokens.size() - 1;
	physical_expr.operators.emplace_back(make_shared<dec_unffor_opr<INDEX_PT>>(column_view, state));
	physical_expr.operators.emplace_back(make_shared<FSST_DICT_DECODER_T>(physical_expr, column_view, state));
}

/*--------------------------------------------------------------------------------------------------------------------*\
 * make_dec_fsst_dict_ffor_slpatch_expr
\*--------------------------------------------------------------------------------------------------------------------*/
template <typename FSSTDictDecoder, typename INDEX_PT>
void make_dec_fsst_dict_ffor_slpatch_expr(PhysicalExpr&     physical_expr,
                                          const ColumnView& column_view,
                                          InterpreterState& state) {
	state.cur_operand = column_view.column_descriptor.encoding_rpn->operand_tokens.size() - 1;
	physical_expr.operators.emplace_back(make_shared<dec_unffor_opr<INDEX_PT>>(column_view, state));
	physical_expr.operators.emplace_back(make_shared<dec_slpatch_opr<INDEX_PT>>(physical_expr, column_view, state));
	physical_expr.operators.emplace_back(make_shared<FSSTDictDecoder>(physical_expr, column_view, state));
}

/*--------------------------------------------------------------------------------------------------------------------*\
 * make_dec_fsst_dict_expr
\*--------------------------------------------------------------------------------------------------------------------*/
template <typename FSSTDictTypeDecoder>
void make_dec_fsst_dict_expr(RowgroupReader&   reader,
                             PhysicalExpr&     physical_expr,
                             const ColumnView& column_view,
                             InterpreterState& state) {
	state.cur_operand                      = column_view.column_descriptor.encoding_rpn->operand_tokens.size() - 1;
	auto [operator_tokens, operand_tokens] = *column_view.column_descriptor.encoding_rpn;

	state.cur_operand = column_view.column_descriptor.encoding_rpn->operand_tokens.size() - 1;
	physical_expr.operators.emplace_back(reader.m_expressions[operand_tokens.at(0)]);
	physical_expr.operators.emplace_back(make_shared<FSSTDictTypeDecoder>(physical_expr, column_view, state));
}

/*--------------------------------------------------------------------------------------------------------------------*\
 * make_dec_dict_expr
\*--------------------------------------------------------------------------------------------------------------------*/
template <typename KEY_PT, typename INDEX_PT>
void make_dec_dict_expr(RowgroupReader&   reader,
                        PhysicalExpr&     physical_expr,
                        const ColumnView& column_view,
                        InterpreterState& state) {

	auto [operator_tokens, operand_tokens] = *column_view.column_descriptor.encoding_rpn;

	physical_expr.operators.emplace_back(reader.m_expressions[operand_tokens.at(state.cur_operand++)]);
	physical_expr.operators.emplace_back(
	    make_shared<dec_dict_opr<KEY_PT, INDEX_PT>>(physical_expr, column_view, state));
}

/*--------------------------------------------------------------------------------------------------------------------*\
 * make_dec_rle_expr
\*--------------------------------------------------------------------------------------------------------------------*/
template <typename KEY_PT, typename INDEX_PT>
void make_dec_rle_expr(RowgroupReader&   reader,
                       PhysicalExpr&     physical_expr,
                       const ColumnView& column_view,
                       InterpreterState& state) {

	auto [operator_tokens, operand_tokens] = *column_view.column_descriptor.encoding_rpn;

	state.cur_operand  = column_view.column_descriptor.encoding_rpn->operand_tokens.size() - 1;
	state.cur_operator = 0;

	physical_expr.operators.emplace_back(make_shared<dec_unffor_opr<INDEX_PT>>(column_view, state));
	physical_expr.operators.emplace_back(make_shared<dec_rsum_opr<INDEX_PT>>(physical_expr, column_view, state));
	physical_expr.operators.emplace_back(
	    make_shared<dec_rle_map_opr<KEY_PT, INDEX_PT>>(physical_expr, column_view, state));
}

/*--------------------------------------------------------------------------------------------------------------------*\
 * make_dec_rle_slpatch_expr
\*--------------------------------------------------------------------------------------------------------------------*/
template <typename KEY_PT, typename INDEX_PT>
void make_dec_rle_slpatch_expr(RowgroupReader&   reader,
                               PhysicalExpr&     physical_expr,
                               const ColumnView& column_view,
                               InterpreterState& state) {

	auto [operator_tokens, operand_tokens] = *column_view.column_descriptor.encoding_rpn;

	state.cur_operand  = column_view.column_descriptor.encoding_rpn->operand_tokens.size() - 1;
	state.cur_operator = 0;

	physical_expr.operators.emplace_back(make_shared<dec_unffor_opr<INDEX_PT>>(column_view, state));
	physical_expr.operators.emplace_back(make_shared<dec_slpatch_opr<INDEX_PT>>(physical_expr, column_view, state));
	physical_expr.operators.emplace_back(make_shared<dec_rsum_opr<INDEX_PT>>(physical_expr, column_view, state));
	physical_expr.operators.emplace_back(
	    make_shared<dec_rle_map_opr<KEY_PT, INDEX_PT>>(physical_expr, column_view, state));
}

/*--------------------------------------------------------------------------------------------------------------------*\
 * make_dec_delta_expr
\*--------------------------------------------------------------------------------------------------------------------*/
template <typename PT>
void make_dec_delta_expr(RowgroupReader&   reader,
                         PhysicalExpr&     physical_expr,
                         const ColumnView& column_view,
                         InterpreterState& state) {

	auto [operator_tokens, operand_tokens] = *column_view.column_descriptor.encoding_rpn;

	state.cur_operand  = column_view.column_descriptor.encoding_rpn->operand_tokens.size() - 1;
	state.cur_operator = 0;

	physical_expr.operators.emplace_back(make_shared<dec_unffor_opr<make_unsigned_t<PT>>>(column_view, state));
	physical_expr.operators.emplace_back(make_shared<dec_rsum_opr<PT>>(physical_expr, column_view, state));
	physical_expr.operators.emplace_back(make_shared<dec_transpose_opr<PT>>(physical_expr, column_view, state));
}
/*--------------------------------------------------------------------------------------------------------------------*\
 * make_dec_fls_str_uncompressed_expr
\*--------------------------------------------------------------------------------------------------------------------*/
template <typename KEY_PT, typename INDEX_PT>
void make_dec_expr(PhysicalExpr& physical_expr, ColumnView& column_view, InterpreterState& state) {

	physical_expr.operators.emplace_back(make_shared<dec_dict_opr<KEY_PT, INDEX_PT>>(column_view));
	state.cur_operator = state.cur_operator + 1;
}

/*--------------------------------------------------------------------------------------------------------------------*\
 * make_dec_constant_expr
\*--------------------------------------------------------------------------------------------------------------------*/
template <typename PT>
void make_dec_constant_expr(PhysicalExpr& physical_expr, const ColumnView& column_view, InterpreterState& state) {

	physical_expr.operators.emplace_back(make_shared<dec_constant_opr<PT>>(column_view));
	state.cur_operator = state.cur_operator + 1;
}

/*--------------------------------------------------------------------------------------------------------------------*\
 * make_dec_constant_str_expr
\*--------------------------------------------------------------------------------------------------------------------*/
void make_dec_constant_str_expr(PhysicalExpr& physical_expr, const ColumnView& column_view, InterpreterState& state) {
	physical_expr.operators.emplace_back(make_shared<dec_constant_str_opr>(column_view));
	state.cur_operator = state.cur_operator + 1;
}

/*--------------------------------------------------------------------------------------------------------------------*\
 * make_dec_equality_expr
\*--------------------------------------------------------------------------------------------------------------------*/
void make_dec_equality_expr(PhysicalExpr& physical_expr, RowgroupReader& reader, const vector<n_t>& operand_tokens) {
	//
	physical_expr.operators.emplace_back(
	    reader.m_expressions[operand_tokens.at(0)]
	        ->operators[reader.m_expressions[operand_tokens.at(0)]->operators.size() - 1]);
}

/*--------------------------------------------------------------------------------------------------------------------*\
 * make_dec_struct_expr
\*--------------------------------------------------------------------------------------------------------------------*/
void make_dec_struct_expr(const ColumnDescriptorT& column_descriptor,
                          const ColumnView&        column_view,
                          PhysicalExpr&            physical_expr,
                          InterpreterState&        state,
                          RowgroupReader&          reader) {

	physical_expr.operators.emplace_back(make_shared<dec_struct_opr>(column_descriptor, column_view, state, reader));
	state.cur_operator = state.cur_operator + 1;
}

/*--------------------------------------------------------------------------------------------------------------------*\
 * Interpreter
\*--------------------------------------------------------------------------------------------------------------------*/
void Interpreter::Decoding::Interpret(const ColumnDescriptorT& column_descriptor,
                                      const ColumnView&        column_view,
                                      PhysicalExpr&            physical_expr,
                                      InterpreterState&        state,
                                      RowgroupReader&          reader) {

	for (const auto& [operator_tokens, operand_tokens] = *column_descriptor.encoding_rpn;
	     const auto& operator_token : operator_tokens) {
		using enum OperatorToken;
		switch (operator_token) {
		case EXP_UNCOMPRESSED_I64: {
			make_dec_uncompressed_expr<i64_pt>(physical_expr, column_view, state);
			break;
		}
		case EXP_UNCOMPRESSED_I32: {
			make_dec_uncompressed_expr<i32_pt>(physical_expr, column_view, state);
			break;
		}
		case EXP_UNCOMPRESSED_I16: {
			make_dec_uncompressed_expr<i16_pt>(physical_expr, column_view, state);
			break;
		}
		case EXP_UNCOMPRESSED_U08: {
			make_dec_uncompressed_expr<u08_pt>(physical_expr, column_view, state);
			break;
		}
		case EXP_UNCOMPRESSED_DBL: {
			make_dec_uncompressed_expr<dbl_pt>(physical_expr, column_view, state);
			break;
		}
		case EXP_UNCOMPRESSED_FLT: {
			make_dec_uncompressed_expr<flt_pt>(physical_expr, column_view, state);
			break;
		}
		case EXP_UNCOMPRESSED_STR: {
			make_dec_fls_str_uncompressed_expr(physical_expr, column_view, state);
			break;
		}
		case EXP_UNCOMPRESSED_I08: {
			make_dec_uncompressed_expr<i08_pt>(physical_expr, column_view, state);
			break;
		}
		case EXP_FSST: {
			make_dec_fsst_expr<dec_fsst_opr>(physical_expr, column_view, state);
			break;
		}
		case EXP_FSST_DELTA: {
			make_dec_fsst_delta_expr<dec_fsst_opr>(physical_expr, column_view, state);
			break;
		}
		case EXP_FSST12_DELTA: {
			make_dec_fsst_delta_expr<dec_fsst12_opr>(physical_expr, column_view, state);
			break;
		}
		case EXP_FSST12: {
			make_dec_fsst_expr<dec_fsst12_opr>(physical_expr, column_view, state);
			break;
		}
		case EXP_CONSTANT_I64: {
			make_dec_constant_expr<i64_pt>(physical_expr, column_view, state);
			break;
		}
		case EXP_CONSTANT_I32: {
			make_dec_constant_expr<i32_pt>(physical_expr, column_view, state);
			break;
		}
		case EXP_CONSTANT_I16: {
			make_dec_constant_expr<i16_pt>(physical_expr, column_view, state);
			break;
		}
		case EXP_CONSTANT_I08: {
			make_dec_constant_expr<i08_pt>(physical_expr, column_view, state);
			break;
		}
		case EXP_CONSTANT_U08: {
			make_dec_constant_expr<u08_pt>(physical_expr, column_view, state);
			break;
		}
		case EXP_CONSTANT_DBL: {
			make_dec_constant_expr<dbl_pt>(physical_expr, column_view, state);
			break;
		}
		case EXP_CONSTANT_FLT: {
			make_dec_constant_expr<flt_pt>(physical_expr, column_view, state);
			break;
		}
		case EXP_CONSTANT_STR: {
			make_dec_constant_str_expr(physical_expr, column_view, state);
			break;
		}
		case EXP_EQUAL: {
			make_dec_equality_expr(physical_expr, reader, operand_tokens);
			break;
		}
		case EXP_STRUCT: {
			make_dec_struct_expr(column_descriptor, column_view, physical_expr, state, reader);
			break;
		}
		case EXP_FFOR_I64: {
			make_dec_ffor_expr<i64_pt>(physical_expr, column_view, state);
			break;
		}
		case EXP_FFOR_I32: {
			make_dec_ffor_expr<i32_pt>(physical_expr, column_view, state);
			break;
		}
		case EXP_FFOR_I16: {
			make_dec_ffor_expr<i16_pt>(physical_expr, column_view, state);
			break;
		}
		case EXP_FFOR_I08: {
			make_dec_ffor_expr<i08_pt>(physical_expr, column_view, state);
			break;
		}
		case EXP_DICT_I64_FFOR_U32: {
			make_dec_dict_ffor_expr<i64_pt, u32_pt>(physical_expr, column_view, state);
			break;
		}
		case EXP_DICT_I64_FFOR_U16: {
			make_dec_dict_ffor_expr<i64_pt, u16_pt>(physical_expr, column_view, state);
			break;
		}
		case EXP_DICT_I64_FFOR_U08: {
			make_dec_dict_ffor_expr<i64_pt, u08_pt>(physical_expr, column_view, state);
			break;
		}
		case EXP_DICT_I32_FFOR_U32: {
			make_dec_dict_ffor_expr<i32_pt, u32_pt>(physical_expr, column_view, state);
			break;
		}
		case EXP_DICT_I32_FFOR_U16: {
			make_dec_dict_ffor_expr<i32_pt, u16_pt>(physical_expr, column_view, state);
			break;
		}
		case EXP_DICT_I32_FFOR_U08: {
			make_dec_dict_ffor_expr<i32_pt, u08_pt>(physical_expr, column_view, state);
			break;
		}
		case EXP_DICT_I16_FFOR_U16: {
			make_dec_dict_ffor_expr<i16_pt, u16_pt>(physical_expr, column_view, state);
			break;
		}
		case EXP_DICT_I16_FFOR_U08: {
			make_dec_dict_ffor_expr<i16_pt, u08_pt>(physical_expr, column_view, state);
			break;
		}
		case EXP_DICT_I08_FFOR_U08: {
			make_dec_dict_ffor_expr<i08_pt, u08_pt>(physical_expr, column_view, state);
			break;
		}
		case EXP_DICT_DBL_FFOR_U32: {
			make_dec_dict_ffor_expr<dbl_pt, u32_pt>(physical_expr, column_view, state);
			break;
		}
		case EXP_DICT_DBL_FFOR_U16: {
			make_dec_dict_ffor_expr<dbl_pt, u16_pt>(physical_expr, column_view, state);
			break;
		}
		case EXP_DICT_FLT_FFOR_U16: {
			make_dec_dict_ffor_expr<flt_pt, u16_pt>(physical_expr, column_view, state);
			break;
		}
		case EXP_DICT_DBL_FFOR_U08: {
			make_dec_dict_ffor_expr<dbl_pt, u08_pt>(physical_expr, column_view, state);
			break;
		}
		case EXP_DICT_FLT_FFOR_U08: {
			make_dec_dict_ffor_expr<flt_pt, u08_pt>(physical_expr, column_view, state);
			break;
		}
		case EXP_DICT_I64_U32: {
			make_dec_dict_expr<i64_pt, u32_pt>(reader, physical_expr, column_view, state);
			break;
		}
		case EXP_DICT_I64_U08: {
			make_dec_dict_expr<i64_pt, u08_pt>(reader, physical_expr, column_view, state);
			break;
		}
		case EXP_DICT_I32_U32: {
			make_dec_dict_expr<i32_pt, u32_pt>(reader, physical_expr, column_view, state);
			break;
		}
		case EXP_DICT_I32_U16: {
			make_dec_dict_expr<i32_pt, u16_pt>(reader, physical_expr, column_view, state);
			break;
		}
		case EXP_DICT_I64_U16: {
			make_dec_dict_expr<i64_pt, u16_pt>(reader, physical_expr, column_view, state);
			break;
		}
		case EXP_DICT_I32_U08: {
			make_dec_dict_expr<i32_pt, u08_pt>(reader, physical_expr, column_view, state);
			break;
		}
		case EXP_DICT_I16_U16: {
			make_dec_dict_expr<i16_pt, u16_pt>(reader, physical_expr, column_view, state);
			break;
		}
		case EXP_DICT_I16_U08: {
			make_dec_dict_expr<i16_pt, u08_pt>(reader, physical_expr, column_view, state);
			break;
		}
		case EXP_DICT_I08_U08: {
			make_dec_dict_expr<i08_pt, u08_pt>(reader, physical_expr, column_view, state);
			break;
		}
		case EXP_DICT_DBL_U32: {
			make_dec_dict_expr<dbl_pt, u32_pt>(reader, physical_expr, column_view, state);
			break;
		}
		case EXP_DICT_DBL_U16: {
			make_dec_dict_expr<dbl_pt, u16_pt>(reader, physical_expr, column_view, state);
			break;
		}
		case EXP_DICT_DBL_U08: {
			make_dec_dict_expr<dbl_pt, u08_pt>(reader, physical_expr, column_view, state);
			break;
		}
		case EXP_DICT_STR_U32: {
			make_dec_dict_expr<fls_string_t, u32_pt>(reader, physical_expr, column_view, state);
			break;
		}
		case EXP_DICT_STR_U16: {
			make_dec_dict_expr<fls_string_t, u16_pt>(reader, physical_expr, column_view, state);
			break;
		}
		case EXP_DICT_STR_U08: {
			make_dec_dict_expr<fls_string_t, u08_pt>(reader, physical_expr, column_view, state);
			break;
		}
		case EXP_ALP_DBL: {
			make_dec_alp_expr<dbl_pt>(physical_expr, column_view, state);
			break;
		}
		case EXP_ALP_FLT: {
			make_dec_alp_expr<flt_pt>(physical_expr, column_view, state);
			break;
		}
		case EXP_ALP_RD_DBL: {
			make_dec_alp_rd_expr<dbl_pt>(physical_expr, column_view, state);
			break;
		}
		case EXP_ALP_RD_FLT: {
			make_dec_alp_rd_expr<flt_pt>(physical_expr, column_view, state);
			break;
		}
		case EXP_DICT_STR_FFOR_U32: {
			make_dec_dict_ffor_expr<fls_string_t, u32_pt>(physical_expr, column_view, state);
			break;
		}
		case EXP_DICT_STR_FFOR_U16: {
			make_dec_dict_ffor_expr<fls_string_t, u16_pt>(physical_expr, column_view, state);
			break;
		}
		case EXP_DICT_STR_FFOR_U08: {
			make_dec_dict_ffor_expr<fls_string_t, u08_pt>(physical_expr, column_view, state);
			break;
		}
		case EXP_FSST_DICT_STR_FFOR_U32: {
			make_dec_fsst_dict_ffor_expr<dec_fsst_dict_opr<u32_pt>, u32_pt>(physical_expr, column_view, state);
			break;
		}
		case EXP_FSST_DICT_STR_FFOR_U16: {
			make_dec_fsst_dict_ffor_expr<dec_fsst_dict_opr<u16_pt>, u16_pt>(physical_expr, column_view, state);
			break;
		}
		case EXP_FSST_DICT_STR_FFOR_U08: {
			make_dec_fsst_dict_ffor_expr<dec_fsst_dict_opr<u08_pt>, u08_pt>(physical_expr, column_view, state);
			break;
		}
		case EXP_RLE_DBL_U16: {
			make_dec_rle_expr<dbl_pt, u16_pt>(reader, physical_expr, column_view, state);
			break;
		}
		case EXP_RLE_FLT_U16: {
			make_dec_rle_expr<flt_pt, u16_pt>(reader, physical_expr, column_view, state);
			break;
		}
		case EXP_RLE_I64_U16: {
			make_dec_rle_expr<i64_pt, u16_pt>(reader, physical_expr, column_view, state);
			break;
		}
		case EXP_RLE_I32_U16: {
			make_dec_rle_expr<i32_pt, u16_pt>(reader, physical_expr, column_view, state);
			break;
		}
		case EXP_RLE_I16_U16: {
			make_dec_rle_expr<i16_pt, u16_pt>(reader, physical_expr, column_view, state);
			break;
		}
		case EXP_RLE_I08_U16: {
			make_dec_rle_expr<i08_pt, u16_pt>(reader, physical_expr, column_view, state);
			break;
		}
		case EXP_RLE_STR_U16: {
			make_dec_rle_expr<fls_string_t, u16_pt>(reader, physical_expr, column_view, state);
			break;
		}
		case EXP_DELTA_I64: {
			make_dec_delta_expr<i64_pt>(reader, physical_expr, column_view, state);
			break;
		}
		case EXP_DELTA_I32: {
			make_dec_delta_expr<i32_pt>(reader, physical_expr, column_view, state);
			break;
		}
		case EXP_DELTA_I16: {
			make_dec_delta_expr<i16_pt>(reader, physical_expr, column_view, state);
			break;
		}
		case EXP_DELTA_I08: {
			make_dec_delta_expr<i08_pt>(reader, physical_expr, column_view, state);
			break;
		}
		case EXP_FFOR_SLPATCH_I64: {
			make_dec_ffor_slpatch_expr<i64_pt>(physical_expr, column_view, state);
			break;
		}
		case EXP_FFOR_SLPATCH_I32: {
			make_dec_ffor_slpatch_expr<i32_pt>(physical_expr, column_view, state);
			break;
		}
		case EXP_FFOR_SLPATCH_I16: {
			make_dec_ffor_slpatch_expr<i16_pt>(physical_expr, column_view, state);
			break;
		}
		case EXP_FFOR_SLPATCH_I08: {
			make_dec_ffor_slpatch_expr<i08_pt>(physical_expr, column_view, state);
			break;
		}
		case EXP_DICT_DBL_FFOR_SLPATCH_U16: {
			make_dec_dict_ffor_slpatch_expr<dbl_pt, u16_pt>(physical_expr, column_view, state);
			break;
		}
		case EXP_DICT_STR_FFOR_SLPATCH_U32: {
			make_dec_dict_ffor_slpatch_expr<fls_string_t, u32_pt>(physical_expr, column_view, state);
			break;
		}
		case EXP_DICT_STR_FFOR_SLPATCH_U16: {
			make_dec_dict_ffor_slpatch_expr<fls_string_t, u16_pt>(physical_expr, column_view, state);
			break;
		}
		case EXP_DICT_STR_FFOR_SLPATCH_U08: {
			make_dec_dict_ffor_slpatch_expr<fls_string_t, u08_pt>(physical_expr, column_view, state);
			break;
		}
		case EXP_DICT_I16_FFOR_SLPATCH_U08: {
			make_dec_dict_ffor_slpatch_expr<i16_pt, u08_pt>(physical_expr, column_view, state);
			break;
		}
		case EXP_DICT_I08_FFOR_SLPATCH_U08: {
			make_dec_dict_ffor_slpatch_expr<i08_pt, u08_pt>(physical_expr, column_view, state);
			break;
		}
		case EXP_DICT_I16_FFOR_SLPATCH_U16: {
			make_dec_dict_ffor_slpatch_expr<i16_pt, u16_pt>(physical_expr, column_view, state);
			break;
		}
		case EXP_DICT_I64_FFOR_SLPATCH_U08: {
			make_dec_dict_ffor_slpatch_expr<i64_pt, u08_pt>(physical_expr, column_view, state);
			break;
		}
		case EXP_DICT_DBL_FFOR_SLPATCH_U08: {
			make_dec_dict_ffor_slpatch_expr<dbl_pt, u08_pt>(physical_expr, column_view, state);
			break;
		}
		case EXP_DICT_FLT_FFOR_SLPATCH_U08: {
			make_dec_dict_ffor_slpatch_expr<flt_pt, u08_pt>(physical_expr, column_view, state);
			break;
		}
		case EXP_DICT_FLT_FFOR_SLPATCH_U16: {
			make_dec_dict_ffor_slpatch_expr<flt_pt, u16_pt>(physical_expr, column_view, state);
			break;
		}
		case EXP_DICT_DBL_FFOR_SLPATCH_U32: {
			make_dec_dict_ffor_slpatch_expr<dbl_pt, u32_pt>(physical_expr, column_view, state);
			break;
		}
		case EXP_DICT_I32_FFOR_SLPATCH_U08: {
			make_dec_dict_ffor_slpatch_expr<i32_pt, u08_pt>(physical_expr, column_view, state);
			break;
		}
		case EXP_DICT_I32_FFOR_SLPATCH_U16: {
			make_dec_dict_ffor_slpatch_expr<i32_pt, u16_pt>(physical_expr, column_view, state);
			break;
		}
		case EXP_DICT_I64_FFOR_SLPATCH_U16: {
			make_dec_dict_ffor_slpatch_expr<i64_pt, u16_pt>(physical_expr, column_view, state);
			break;
		}
		case EXP_FSST_DICT_STR_FFOR_SLPATCH_U32: {
			make_dec_fsst_dict_ffor_slpatch_expr<dec_fsst_dict_opr<u32_pt>, u32_pt>(physical_expr, column_view, state);
			break;
		}
		case EXP_FSST_DICT_STR_FFOR_SLPATCH_U16: {
			make_dec_fsst_dict_ffor_slpatch_expr<dec_fsst_dict_opr<u16_pt>, u16_pt>(physical_expr, column_view, state);
			break;
		}
		case EXP_FSST_DICT_STR_FFOR_SLPATCH_U08: {
			make_dec_fsst_dict_ffor_slpatch_expr<dec_fsst_dict_opr<u08_pt>, u08_pt>(physical_expr, column_view, state);
			break;
		}
		case EXP_FSST12_DICT_STR_FFOR_SLPATCH_U32: {
			make_dec_fsst_dict_ffor_slpatch_expr<dec_fsst12_dict_opr<u32_pt>, u32_pt>(
			    physical_expr, column_view, state);
			break;
		}
		case EXP_FSST12_DICT_STR_FFOR_SLPATCH_U16: {
			make_dec_fsst_dict_ffor_slpatch_expr<dec_fsst12_dict_opr<u16_pt>, u16_pt>(
			    physical_expr, column_view, state);
			break;
		}
		case EXP_FSST12_DICT_STR_FFOR_SLPATCH_U08: {
			make_dec_fsst_dict_ffor_slpatch_expr<dec_fsst12_dict_opr<u08_pt>, u08_pt>(
			    physical_expr, column_view, state);
			break;
		}
		case EXP_NULL_DBL: {
			make_dec_null_expr<dbl_pt>(physical_expr, column_view, state);
			break;
		}
		case EXP_NULL_FLT: {
			make_dec_null_expr<flt_pt>(physical_expr, column_view, state);
			break;
		}
		case EXP_NULL_I32: {
			make_dec_null_expr<i32_pt>(physical_expr, column_view, state);
			break;
		}
		case EXP_NULL_I16: {
			make_dec_null_expr<i16_pt>(physical_expr, column_view, state);
			break;
		}
		case EXP_RLE_I64_SLPATCH_U16: {
			make_dec_rle_slpatch_expr<i64_pt, u16_pt>(reader, physical_expr, column_view, state);
			break;
		}
		case EXP_RLE_I32_SLPATCH_U16: {
			make_dec_rle_slpatch_expr<i32_pt, u16_pt>(reader, physical_expr, column_view, state);
			break;
		}
		case EXP_RLE_I16_SLPATCH_U16: {
			make_dec_rle_slpatch_expr<i16_pt, u16_pt>(reader, physical_expr, column_view, state);
			break;
		}
		case EXP_RLE_I08_SLPATCH_U16: {
			make_dec_rle_slpatch_expr<i08_pt, u16_pt>(reader, physical_expr, column_view, state);
			break;
		}
		case EXP_RLE_STR_SLPATCH_U16: {
			make_dec_rle_slpatch_expr<fls_string_t, u16_pt>(reader, physical_expr, column_view, state);
			break;
		}
		case EXP_RLE_DBL_SLPATCH_U16: {
			make_dec_rle_slpatch_expr<dbl_pt, u16_pt>(reader, physical_expr, column_view, state);
			break;
		}
		case EXP_RLE_FLT_SLPATCH_U16: {
			make_dec_rle_slpatch_expr<flt_pt, u16_pt>(reader, physical_expr, column_view, state);
			break;
		}
		case EXP_FSST_DICT_STR_U32: {
			make_dec_fsst_dict_expr<dec_fsst_dict_opr<u32_pt>>(reader, physical_expr, column_view, state);
			break;
		}
		case EXP_FSST_DICT_STR_U16: {
			make_dec_fsst_dict_expr<dec_fsst_dict_opr<u16_pt>>(reader, physical_expr, column_view, state);
			break;
		}
		case EXP_FSST_DICT_STR_U08: {
			make_dec_fsst_dict_expr<dec_fsst_dict_opr<u08_pt>>(reader, physical_expr, column_view, state);
			break;
		}
		case EXP_FSST_DELTA_SLPATCH: {
			make_dec_fsst_delta_slpatch_expr<dec_fsst_opr>(physical_expr, column_view, state);
			break;
		}
		case EXP_FSST12_DELTA_SLPATCH: {
			make_dec_fsst_delta_slpatch_expr<dec_fsst12_opr>(physical_expr, column_view, state);
			break;
		}
		case EXP_FSST12_DICT_STR_U32: {
			make_dec_fsst_dict_expr<dec_fsst12_dict_opr<u32_pt>>(reader, physical_expr, column_view, state);
			break;
		}
		case EXP_FSST12_DICT_STR_U16: {
			make_dec_fsst_dict_expr<dec_fsst12_dict_opr<u16_pt>>(reader, physical_expr, column_view, state);
			break;
		}
		case EXP_FSST12_DICT_STR_U08: {
			make_dec_fsst_dict_expr<dec_fsst12_dict_opr<u08_pt>>(reader, physical_expr, column_view, state);
			break;
		}
		case EXP_FSST12_DICT_STR_FFOR_U32: {
			make_dec_fsst_dict_ffor_expr<dec_fsst12_dict_opr<u32_pt>, u32_pt>(physical_expr, column_view, state);
			break;
		}
		case EXP_FSST12_DICT_STR_FFOR_U16: {
			make_dec_fsst_dict_ffor_expr<dec_fsst12_dict_opr<u16_pt>, u16_pt>(physical_expr, column_view, state);
			break;
		}
		case EXP_FSST12_DICT_STR_FFOR_U08: {
			make_dec_fsst_dict_ffor_expr<dec_fsst12_dict_opr<u08_pt>, u08_pt>(physical_expr, column_view, state);
			break;
		}
		case EXP_FREQUENCY_DBL: {
			make_dec_frequency_expr<dbl_pt>(physical_expr, column_view, state);
			break;
		}
		case EXP_FREQUENCY_FLT: {
			make_dec_frequency_expr<flt_pt>(physical_expr, column_view, state);
			break;
		}
		case EXP_FREQUENCY_I08: {
			make_dec_frequency_expr<i08_pt>(physical_expr, column_view, state);
			break;
		}
		case EXP_FREQUENCY_I16: {
			make_dec_frequency_expr<i16_pt>(physical_expr, column_view, state);
			break;
		}
		case EXP_FREQUENCY_I32: {
			make_dec_frequency_expr<i32_pt>(physical_expr, column_view, state);
			break;
		}
		case EXP_FREQUENCY_I64: {
			make_dec_frequency_expr<i64_pt>(physical_expr, column_view, state);
			break;
		}
		case EXP_FREQUENCY_STR: {
			make_dec_frequency_str_expr(physical_expr, column_view, state);
			break;
		}
		case EXP_CROSS_RLE_I08: {
			make_dec_cross_rle_expr<i08_pt>(physical_expr, column_view, state);
			break;
		}
		case EXP_CROSS_RLE_I16: {
			make_dec_cross_rle_expr<i16_pt>(physical_expr, column_view, state);
			break;
		}
		case EXP_CROSS_RLE_I32: {
			make_dec_cross_rle_expr<i32_pt>(physical_expr, column_view, state);
			break;
		}
		case EXP_CROSS_RLE_I64: {
			make_dec_cross_rle_expr<i64_pt>(physical_expr, column_view, state);
			break;
		}
		case EXP_CROSS_RLE_DBL: {
			make_dec_cross_rle_expr<dbl_pt>(physical_expr, column_view, state);
			break;
		}
		case EXP_CROSS_RLE_FLT: {
			make_dec_cross_rle_expr<flt_pt>(physical_expr, column_view, state);
			break;
		}
		case EXP_CROSS_RLE_STR: {
			make_dec_cross_rle_expr<fls_string_t>(physical_expr, column_view, state);
			break;
		}
		case INVALID:
		default:
			FLS_UNREACHABLE();
		}
	}
}

/*--------------------------------------------------------------------------------------------------------------------*\
 * make_decoding_expression
\*--------------------------------------------------------------------------------------------------------------------*/
sp<PhysicalExpr> make_decoding_expression(const ColumnDescriptorT& column_descriptor,
                                          const ColumnView&        column_view,
                                          RowgroupReader&          reader,
                                          InterpreterState&        state) {
	auto physical_expr = make_shared<PhysicalExpr>();
	Interpreter::Decoding::Interpret(column_descriptor, column_view, *physical_expr, state, reader);

	return physical_expr;
}

} // namespace fastlanes