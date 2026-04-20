// ────────────────────────────────────────────────────────
// |                      FastLanes                       |
// ────────────────────────────────────────────────────────
// src/expression/enc_transpose_operator.cpp
// ────────────────────────────────────────────────────────
#include "fls/common/alias.hpp"
#include "fls/common/common.hpp"
#include "fls/expression/data_type.hpp"
#include "fls/expression/encoding_operator.hpp"
#include "fls/expression/fsst12_expression.hpp"
#include "fls/expression/fsst_expression.hpp"
#include "fls/expression/interpreter.hpp"
#include "fls/expression/physical_expression.hpp"
#include "fls/expression/rle_expression.hpp"
#include "fls/expression/rsum_operator.hpp"
#include "fls/expression/transpose_operator.hpp"
#include "fls/reader/segment.hpp"
#include "fls/std/variant.hpp"
#include "fls/table/rowgroup.hpp"
#include "fls_gen/transpose/transpose.hpp"
#include <variant>

namespace fastlanes {
/*--------------------------------------------------------------------------------------------------------------------*\
 * enc transpose opr
\*--------------------------------------------------------------------------------------------------------------------*/
template <typename PT>
enc_transpose_opr<PT>::enc_transpose_opr(const PhysicalExpr& expr,
                                         const col_pt&       col,
                                         ColumnDescriptorT&  column_descriptor,
                                         InterpreterState&   state) {

	visit_enc(overloaded {
	              [&](const sp<enc_uncompressed_opr<PT>>& opr) {
		              data = opr->data;
		              opr->segment->MakeTemporary();
	              },
	              [&](const sp<enc_scan_opr<PT>>& opr) { data = opr->data; },
	              [&](const sp<enc_fsst_opr>& opr) {
		              if constexpr (std::is_same_v<PT, ofs_t>) {
			              data = opr->fsst_encoded_offset_arr + 1;
			              opr->fsst_offset_segment->MakeTemporary();
			              column_descriptor.encoding_rpn->operand_tokens.pop_back();
			              state.cur_operand -= 1;
		              } else {
			              FLS_UNREACHABLE();
		              }
	              },
	              [&](const sp<enc_fsst12_opr>& opr) {
		              if constexpr (std::is_same_v<PT, ofs_t>) {
			              data = opr->fsst12_encoded_offset_arr + 1;
			              opr->fsst12_offset_segment->MakeTemporary();
			              column_descriptor.encoding_rpn->operand_tokens.pop_back();
			              state.cur_operand -= 1;
		              } else {
			              FLS_UNREACHABLE();
		              }
	              },
	              [&]<typename VALUE_PT>(const sp<enc_dict_map_opr<VALUE_PT, PT>>& opr) { data = opr->index_arr; },
	              [&]<typename VALUE_PT>(const sp<enc_rle_map_opr<VALUE_PT, PT>>& opr) { data = opr->rle_idxs; },
	              [&](std::monostate&) { FLS_UNREACHABLE(); },
	              [&](auto& arg) { FLS_UNREACHABLE_WITH_TYPE(arg); },
	          },
	          expr.operators[state.cur_operator++]);
}

template <typename PT>
void enc_transpose_opr<PT>::Transpose() {
	::generated::transpose::fallback::scalar::transpose_i(data, transposed_data);
}

template struct enc_transpose_opr<u08_pt>;
template struct enc_transpose_opr<u16_pt>;
template struct enc_transpose_opr<u32_pt>;
template struct enc_transpose_opr<u64_pt>;
template struct enc_transpose_opr<i08_pt>;
template struct enc_transpose_opr<i16_pt>;
template struct enc_transpose_opr<i32_pt>;
template struct enc_transpose_opr<i64_pt>;

} // namespace fastlanes
