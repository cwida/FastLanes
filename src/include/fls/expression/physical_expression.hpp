// ────────────────────────────────────────────────────────
// |                      FastLanes                       |
// ────────────────────────────────────────────────────────
// src/include/fls/expression/physical_expression.hpp
// ────────────────────────────────────────────────────────
#ifndef FLS_EXPRESSION_PHYSICAL_EXPRESSION_HPP
#define FLS_EXPRESSION_PHYSICAL_EXPRESSION_HPP

#include "decoding_operator.hpp"
#include "fls/common/common.hpp"
#include "fls/std/variant.hpp"
#include "fls/std/vector.hpp"
#include "fls/table/chunk.hpp"
#include <fls/connection.hpp>

namespace fastlanes {
/*--------------------------------------------------------------------------------------------------------------------*/
class Buf;
struct ColumnDescriptorT;
// DECODE
template <typename PT>
struct dec_uncompressed_opr;
template <typename PT>
struct dec_constant_opr;
struct dec_constant_str_opr;
template <typename PT>
struct dec_unffor_opr;
template <typename KEY_PT, typename INDEX_PT>
struct dec_dict_opr;
// ENCODE
struct enc_struct_opr;
struct enc_constant_opr;
template <typename PT>
struct enc_ffor_opr;
template <typename PT>
struct enc_uncompressed_opr;
template <typename KEY_PT, typename INDEX_PT>
struct enc_dict_map_opr;
template <typename PT>
struct enc_scan_opr;
template <typename KEY_PT>
struct enc_dict_opr;
template <typename PT>
struct enc_alp_opr;
template <typename PT>
struct dec_alp_opr;
template <typename PT>
struct enc_alp_rd_opr;
template <typename PT>
struct dec_alp_rd_opr;
struct enc_fsst_opr;
struct enc_fsst12_opr;
struct dec_fsst_opr;
struct dec_fsst12_opr;
struct enc_fsst_dict_opr;
template <typename PT>
struct dec_fsst_dict_opr;
template <typename KEY_PT, typename INDEX_PT>
struct enc_rle_map_opr;
template <typename KEY_PT, typename INDEX_PT>
struct dec_rle_map_opr;
template <typename PT>
struct enc_transpose_opr;
template <typename PT>
struct enc_rsum_opr;
template <typename PT>
struct dec_rsum_opr;
template <typename PT>
struct dec_scan_opr;
template <typename PT>
struct dec_transpose_opr;
template <typename PT, bool USE_PATCHING>
struct enc_analyze_opr;
template <typename PT>
struct enc_slpatch_opr;
template <typename PT>
struct dec_slpatch_opr;
template <typename PT>
struct enc_null_opr;
template <typename PT>
struct dec_null_opr;
struct enc_fsst12_dict_opr;
template <typename PT>
struct dec_fsst12_dict_opr;
template <typename PT>
struct enc_frequency_opr;
template <typename PT>
struct dec_frequency_opr;
struct enc_frequency_str_opr;
struct dec_frequency_str_opr;
template <typename PT>
struct enc_cross_rle_opr;
template <typename PT>
struct dec_cross_rle_opr;
struct enc_validitymask_opr;
struct dec_validitymask_opr;
template <typename PT>
struct enc_data_parallel_patch_opr;
/*--------------------------------------------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------------------------------------------*\
 * Encoding sub-variant (~110 alternatives)
\*--------------------------------------------------------------------------------------------------------------------*/
using enc_physical_operator = variant<std::monostate,
                                      // ALP
                                      sp<enc_alp_opr<dbl_pt>>,
                                      sp<enc_alp_opr<flt_pt>>,
                                      sp<enc_alp_rd_opr<dbl_pt>>,
                                      sp<enc_alp_rd_opr<flt_pt>>,
                                      // SCAN
                                      sp<enc_scan_opr<i64_pt>>,
                                      sp<enc_scan_opr<i32_pt>>,
                                      sp<enc_scan_opr<i16_pt>>,
                                      sp<enc_scan_opr<i08_pt>>,
                                      sp<enc_scan_opr<u64_pt>>,
                                      sp<enc_scan_opr<u32_pt>>,
                                      sp<enc_scan_opr<u16_pt>>,
                                      sp<enc_scan_opr<u08_pt>>,
                                      // PREDICATION
                                      sp<struct predicate_eq_vector_constant_i64>,
                                      sp<struct predicate_GT_i64>,
                                      sp<struct predicate_LE_i64>,
                                      sp<struct predicate_and_selection_ds>,
                                      // UNCOMPRESSED
                                      sp<enc_uncompressed_opr<i64_pt>>,
                                      sp<enc_uncompressed_opr<i32_pt>>,
                                      sp<enc_uncompressed_opr<i16_pt>>,
                                      sp<enc_uncompressed_opr<i08_pt>>,
                                      sp<enc_uncompressed_opr<u64_pt>>,
                                      sp<enc_uncompressed_opr<u32_pt>>,
                                      sp<enc_uncompressed_opr<u16_pt>>,
                                      sp<enc_uncompressed_opr<u08_pt>>,
                                      sp<enc_uncompressed_opr<dbl_pt>>,
                                      sp<enc_uncompressed_opr<flt_pt>>,
                                      sp<enc_constant_opr>,
                                      sp<struct enc_fls_str_uncompressed_op>,
                                      sp<struct enc_struct_opr>,
                                      // DICT
                                      sp<enc_dict_opr<i64_pt>>,
                                      sp<enc_dict_opr<i32_pt>>,
                                      sp<enc_dict_opr<i16_pt>>,
                                      sp<enc_dict_opr<i08_pt>>,
                                      sp<enc_dict_opr<u08_pt>>,
                                      sp<enc_dict_opr<dbl_pt>>,
                                      sp<enc_dict_opr<fls_string_t>>,
                                      sp<enc_dict_opr<flt_pt>>,
                                      sp<struct enc_dict_map_opr<i64_pt, u32_pt>>,
                                      sp<struct enc_dict_map_opr<i64_pt, u16_pt>>,
                                      sp<struct enc_dict_map_opr<i64_pt, u08_pt>>,
                                      sp<struct enc_dict_map_opr<i32_pt, u32_pt>>,
                                      sp<struct enc_dict_map_opr<i32_pt, u16_pt>>,
                                      sp<struct enc_dict_map_opr<i32_pt, u08_pt>>,
                                      sp<struct enc_dict_map_opr<i16_pt, u16_pt>>,
                                      sp<struct enc_dict_map_opr<i16_pt, u08_pt>>,
                                      sp<struct enc_dict_map_opr<i08_pt, u08_pt>>,
                                      sp<struct enc_dict_map_opr<dbl_pt, u32_pt>>,
                                      sp<struct enc_dict_map_opr<dbl_pt, u16_pt>>,
                                      sp<struct enc_dict_map_opr<dbl_pt, u08_pt>>,
                                      sp<struct enc_dict_map_opr<fls_string_t, u32_pt>>,
                                      sp<struct enc_dict_map_opr<fls_string_t, u16_pt>>,
                                      sp<struct enc_dict_map_opr<fls_string_t, u08_pt>>,
                                      sp<struct enc_dict_map_opr<flt_pt, u32_pt>>,
                                      sp<struct enc_dict_map_opr<flt_pt, u16_pt>>,
                                      sp<struct enc_dict_map_opr<flt_pt, u08_pt>>,
                                      // FFOR
                                      sp<enc_ffor_opr<u64_pt>>,
                                      sp<enc_ffor_opr<u32_pt>>,
                                      sp<enc_ffor_opr<u16_pt>>,
                                      sp<enc_ffor_opr<u08_pt>>,
                                      // FSST
                                      sp<struct enc_fsst_opr>,
                                      sp<struct enc_fsst12_opr>,
                                      // NULL
                                      sp<enc_null_opr<dbl_pt>>,
                                      sp<enc_null_opr<i16_pt>>,
                                      sp<enc_null_opr<i32_pt>>,
                                      sp<enc_null_opr<flt_pt>>,
                                      // FREQUENCY
                                      sp<enc_frequency_opr<dbl_pt>>,
                                      sp<enc_frequency_opr<u08_pt>>,
                                      sp<enc_frequency_opr<i08_pt>>,
                                      sp<enc_frequency_opr<i16_pt>>,
                                      sp<enc_frequency_opr<i32_pt>>,
                                      sp<enc_frequency_opr<i64_pt>>,
                                      sp<enc_frequency_opr<flt_pt>>,
                                      sp<enc_frequency_str_opr>,
                                      // RLE
                                      sp<struct enc_rle_map_opr<dbl_pt, u16_pt>>,
                                      sp<struct enc_rle_map_opr<flt_pt, u16_pt>>,
                                      sp<struct enc_rle_map_opr<i64_pt, u16_pt>>,
                                      sp<struct enc_rle_map_opr<i32_pt, u16_pt>>,
                                      sp<struct enc_rle_map_opr<i16_pt, u16_pt>>,
                                      sp<struct enc_rle_map_opr<i08_pt, u16_pt>>,
                                      sp<struct enc_rle_map_opr<u08_pt, u16_pt>>,
                                      sp<struct enc_rle_map_opr<fls_string_t, u16_pt>>,
                                      // SLPATCH
                                      sp<enc_slpatch_opr<u64_pt>>,
                                      sp<enc_slpatch_opr<u32_pt>>,
                                      sp<enc_slpatch_opr<u16_pt>>,
                                      sp<enc_slpatch_opr<u08_pt>>,
                                      sp<enc_slpatch_opr<i64_pt>>,
                                      sp<enc_slpatch_opr<i32_pt>>,
                                      sp<enc_slpatch_opr<i16_pt>>,
                                      sp<enc_slpatch_opr<i08_pt>>,
                                      // ANALYZE
                                      sp<enc_analyze_opr<u64_pt, false>>,
                                      sp<enc_analyze_opr<u32_pt, false>>,
                                      sp<enc_analyze_opr<u16_pt, false>>,
                                      sp<enc_analyze_opr<u08_pt, false>>,
                                      sp<enc_analyze_opr<u64_pt, true>>,
                                      sp<enc_analyze_opr<u32_pt, true>>,
                                      sp<enc_analyze_opr<u16_pt, true>>,
                                      sp<enc_analyze_opr<u08_pt, true>>,
                                      sp<enc_analyze_opr<i64_pt, false>>,
                                      sp<enc_analyze_opr<i32_pt, false>>,
                                      sp<enc_analyze_opr<i16_pt, false>>,
                                      sp<enc_analyze_opr<i08_pt, false>>,
                                      sp<enc_analyze_opr<i64_pt, true>>,
                                      sp<enc_analyze_opr<i32_pt, true>>,
                                      sp<enc_analyze_opr<i16_pt, true>>,
                                      sp<enc_analyze_opr<i08_pt, true>>,
                                      // TRANSPOSE
                                      sp<enc_transpose_opr<u08_pt>>,
                                      sp<enc_transpose_opr<u16_pt>>,
                                      sp<enc_transpose_opr<u32_pt>>,
                                      sp<enc_transpose_opr<u64_pt>>,
                                      sp<enc_transpose_opr<i08_pt>>,
                                      sp<enc_transpose_opr<i16_pt>>,
                                      sp<enc_transpose_opr<i32_pt>>,
                                      sp<enc_transpose_opr<i64_pt>>,
                                      // CROSS RLE
                                      sp<enc_cross_rle_opr<u08_pt>>,
                                      sp<enc_cross_rle_opr<i08_pt>>,
                                      sp<enc_cross_rle_opr<i16_pt>>,
                                      sp<enc_cross_rle_opr<i32_pt>>,
                                      sp<enc_cross_rle_opr<i64_pt>>,
                                      sp<enc_cross_rle_opr<dbl_pt>>,
                                      sp<enc_cross_rle_opr<flt_pt>>,
                                      sp<enc_cross_rle_opr<fls_string_t>>,
                                      // VALIDITY MASK
                                      sp<enc_validitymask_opr>,
                                      // RSUM
                                      sp<enc_rsum_opr<u08_pt>>,
                                      sp<enc_rsum_opr<u16_pt>>,
                                      sp<enc_rsum_opr<u32_pt>>,
                                      sp<enc_rsum_opr<u64_pt>>,
                                      sp<enc_rsum_opr<i08_pt>>,
                                      sp<enc_rsum_opr<i16_pt>>,
                                      sp<enc_rsum_opr<i32_pt>>,
                                      sp<enc_rsum_opr<i64_pt>>,
                                      // DICT FSST
                                      sp<enc_fsst_dict_opr>,
                                      sp<enc_fsst12_dict_opr>,
                                      // DATA PARALLELIZE PATCH
                                      sp<enc_data_parallel_patch_opr<dbl_pt>>,
                                      sp<enc_data_parallel_patch_opr<flt_pt>>>;

/*--------------------------------------------------------------------------------------------------------------------*\
 * Decoding sub-variant (~137 alternatives)
\*--------------------------------------------------------------------------------------------------------------------*/
using dec_physical_operator = variant<std::monostate,
                                      // ALP
                                      sp<struct dec_alp_opr<dbl_pt>>,
                                      sp<struct dec_alp_opr<flt_pt>>,
                                      sp<struct dec_alp_rd_opr<dbl_pt>>,
                                      sp<struct dec_alp_rd_opr<flt_pt>>,
                                      // UNCOMPRESSED
                                      sp<struct dec_uncompressed_opr<i64_pt>>,
                                      sp<struct dec_uncompressed_opr<i32_pt>>,
                                      sp<struct dec_uncompressed_opr<i16_pt>>,
                                      sp<struct dec_uncompressed_opr<i08_pt>>,
                                      sp<struct dec_uncompressed_opr<u64_pt>>,
                                      sp<struct dec_uncompressed_opr<u32_pt>>,
                                      sp<struct dec_uncompressed_opr<u16_pt>>,
                                      sp<struct dec_uncompressed_opr<u08_pt>>,
                                      sp<struct dec_uncompressed_opr<dbl_pt>>,
                                      sp<struct dec_uncompressed_opr<flt_pt>>,
                                      sp<dec_fls_str_uncompressed_opr>,
                                      // CONSTANT
                                      sp<struct dec_constant_opr<i64_pt>>,
                                      sp<struct dec_constant_opr<i32_pt>>,
                                      sp<struct dec_constant_opr<i16_pt>>,
                                      sp<struct dec_constant_opr<i08_pt>>,
                                      sp<struct dec_constant_opr<u64_pt>>,
                                      sp<struct dec_constant_opr<u32_pt>>,
                                      sp<struct dec_constant_opr<u16_pt>>,
                                      sp<struct dec_constant_opr<u08_pt>>,
                                      sp<struct dec_constant_opr<dbl_pt>>,
                                      sp<struct dec_constant_opr<flt_pt>>,
                                      sp<struct dec_constant_str_opr>,
                                      sp<struct dec_struct_opr>,
                                      // SCAN
                                      sp<struct dec_scan_opr<u32_pt>>,
                                      // DICT
                                      sp<struct dec_dict_opr<i64_pt, u32_pt>>,
                                      sp<struct dec_dict_opr<i64_pt, u16_pt>>,
                                      sp<struct dec_dict_opr<i64_pt, u08_pt>>,
                                      sp<struct dec_dict_opr<i32_pt, u32_pt>>,
                                      sp<struct dec_dict_opr<i32_pt, u16_pt>>,
                                      sp<struct dec_dict_opr<i32_pt, u08_pt>>,
                                      sp<struct dec_dict_opr<i16_pt, u16_pt>>,
                                      sp<struct dec_dict_opr<i16_pt, u08_pt>>,
                                      sp<struct dec_dict_opr<i08_pt, u08_pt>>,
                                      sp<struct dec_dict_opr<u08_pt, u08_pt>>,
                                      sp<struct dec_dict_opr<dbl_pt, u32_pt>>,
                                      sp<struct dec_dict_opr<dbl_pt, u16_pt>>,
                                      sp<struct dec_dict_opr<dbl_pt, u08_pt>>,
                                      sp<dec_dict_opr<fls_string_t, u32_pt>>,
                                      sp<dec_dict_opr<fls_string_t, u16_pt>>,
                                      sp<dec_dict_opr<fls_string_t, u08_pt>>,
                                      sp<struct dec_dict_opr<flt_pt, u32_pt>>,
                                      sp<struct dec_dict_opr<flt_pt, u16_pt>>,
                                      sp<struct dec_dict_opr<flt_pt, u08_pt>>,
                                      // UNFFOR
                                      sp<struct dec_unffor_opr<u64_pt>>,
                                      sp<struct dec_unffor_opr<u32_pt>>,
                                      sp<struct dec_unffor_opr<u16_pt>>,
                                      sp<struct dec_unffor_opr<u08_pt>>,
                                      // FSST
                                      sp<struct dec_fsst_opr>,
                                      sp<struct dec_fsst12_opr>,
                                      // NULL
                                      sp<dec_null_opr<dbl_pt>>,
                                      sp<dec_null_opr<i16_pt>>,
                                      sp<dec_null_opr<i32_pt>>,
                                      sp<dec_null_opr<flt_pt>>,
                                      // FREQUENCY
                                      sp<dec_frequency_opr<dbl_pt>>,
                                      sp<dec_frequency_opr<u08_pt>>,
                                      sp<dec_frequency_opr<i08_pt>>,
                                      sp<dec_frequency_opr<i16_pt>>,
                                      sp<dec_frequency_opr<i32_pt>>,
                                      sp<dec_frequency_opr<i64_pt>>,
                                      sp<dec_frequency_opr<flt_pt>>,
                                      sp<dec_frequency_str_opr>,
                                      // RLE
                                      sp<struct dec_rle_map_opr<dbl_pt, u16_pt>>,
                                      sp<struct dec_rle_map_opr<flt_pt, u16_pt>>,
                                      sp<struct dec_rle_map_opr<i64_pt, u16_pt>>,
                                      sp<struct dec_rle_map_opr<i32_pt, u16_pt>>,
                                      sp<struct dec_rle_map_opr<i16_pt, u16_pt>>,
                                      sp<struct dec_rle_map_opr<i08_pt, u16_pt>>,
                                      sp<struct dec_rle_map_opr<u08_pt, u16_pt>>,
                                      sp<struct dec_rle_map_opr<fls_string_t, u16_pt>>,
                                      // SLPATCH
                                      sp<dec_slpatch_opr<u64_pt>>,
                                      sp<dec_slpatch_opr<u32_pt>>,
                                      sp<dec_slpatch_opr<u16_pt>>,
                                      sp<dec_slpatch_opr<u08_pt>>,
                                      sp<dec_slpatch_opr<i64_pt>>,
                                      sp<dec_slpatch_opr<i32_pt>>,
                                      sp<dec_slpatch_opr<i16_pt>>,
                                      sp<dec_slpatch_opr<i08_pt>>,
                                      // TRANSPOSE
                                      sp<dec_transpose_opr<u08_pt>>,
                                      sp<dec_transpose_opr<u16_pt>>,
                                      sp<dec_transpose_opr<u32_pt>>,
                                      sp<dec_transpose_opr<u64_pt>>,
                                      sp<dec_transpose_opr<i08_pt>>,
                                      sp<dec_transpose_opr<i16_pt>>,
                                      sp<dec_transpose_opr<i32_pt>>,
                                      sp<dec_transpose_opr<i64_pt>>,
                                      // CROSS RLE
                                      sp<dec_cross_rle_opr<u08_pt>>,
                                      sp<dec_cross_rle_opr<i08_pt>>,
                                      sp<dec_cross_rle_opr<i16_pt>>,
                                      sp<dec_cross_rle_opr<i32_pt>>,
                                      sp<dec_cross_rle_opr<i64_pt>>,
                                      sp<dec_cross_rle_opr<dbl_pt>>,
                                      sp<dec_cross_rle_opr<flt_pt>>,
                                      sp<dec_cross_rle_opr<fls_string_t>>,
                                      // VALIDITY MASK
                                      sp<dec_validitymask_opr>,
                                      // RSUM
                                      sp<dec_rsum_opr<u08_pt>>,
                                      sp<dec_rsum_opr<u16_pt>>,
                                      sp<dec_rsum_opr<u32_pt>>,
                                      sp<dec_rsum_opr<u64_pt>>,
                                      sp<dec_rsum_opr<i08_pt>>,
                                      sp<dec_rsum_opr<i16_pt>>,
                                      sp<dec_rsum_opr<i32_pt>>,
                                      sp<dec_rsum_opr<i64_pt>>,
                                      // DICT FSST
                                      sp<dec_fsst_dict_opr<u32_pt>>,
                                      sp<dec_fsst_dict_opr<u16_pt>>,
                                      sp<dec_fsst_dict_opr<u08_pt>>,
                                      sp<dec_fsst12_dict_opr<u32_pt>>,
                                      sp<dec_fsst12_dict_opr<u16_pt>>,
                                      sp<dec_fsst12_dict_opr<u08_pt>>>;

/*--------------------------------------------------------------------------------------------------------------------*\
 * physical_operator: outer wrapper. sp<PhysicalExpr> at outer level because it is
 * created during encoding but accessed during decoding (recursive unwrapping).
\*--------------------------------------------------------------------------------------------------------------------*/
using physical_operator = variant<std::monostate, enc_physical_operator, dec_physical_operator, sp<class PhysicalExpr>>;

/*--------------------------------------------------------------------------------------------------------------------*\
 * Visit helpers — dispatch into the correct sub-variant, halving the dispatch table.
\*--------------------------------------------------------------------------------------------------------------------*/
// Visit both enc and dec (for visitors that handle all operator types)
template <typename Visitor>
void visit_physical(Visitor&& vis, physical_operator& op) {
	visit(overloaded {
	          [&](std::monostate& m) { vis(m); },
	          [&](enc_physical_operator& enc) { visit(std::forward<Visitor>(vis), enc); },
	          [&](dec_physical_operator& dec) { visit(std::forward<Visitor>(vis), dec); },
	          [&](sp<class PhysicalExpr>& pe) { vis(pe); },
	      },
	      op);
}
template <typename Visitor>
void visit_physical(Visitor&& vis, const physical_operator& op) {
	visit(overloaded {
	          [&](const std::monostate& m) { vis(m); },
	          [&](const enc_physical_operator& enc) { visit(std::forward<Visitor>(vis), enc); },
	          [&](const dec_physical_operator& dec) { visit(std::forward<Visitor>(vis), dec); },
	          [&](const sp<class PhysicalExpr>& pe) { vis(pe); },
	      },
	      op);
}

// Visit encoding sub-variant only (also handles sp<PhysicalExpr>)
template <typename Visitor>
void visit_enc(Visitor&& vis, physical_operator& op) {
	visit(overloaded {
	          [&](enc_physical_operator& enc) { visit(std::forward<Visitor>(vis), enc); },
	          [&](sp<class PhysicalExpr>& pe) { vis(pe); },
	          [&](auto&) { FLS_UNREACHABLE(); },
	      },
	      op);
}
template <typename Visitor>
void visit_enc(Visitor&& vis, const physical_operator& op) {
	visit(overloaded {
	          [&](const enc_physical_operator& enc) { visit(std::forward<Visitor>(vis), enc); },
	          [&](const sp<class PhysicalExpr>& pe) { vis(pe); },
	          [&](const auto&) { FLS_UNREACHABLE(); },
	      },
	      op);
}

// Visit decoding sub-variant only (also handles sp<PhysicalExpr>)
template <typename Visitor>
void visit_dec(Visitor&& vis, physical_operator& op) {
	visit(overloaded {
	          [&](dec_physical_operator& dec) { visit(std::forward<Visitor>(vis), dec); },
	          [&](sp<class PhysicalExpr>& pe) { vis(pe); },
	          [&](auto&) { FLS_UNREACHABLE(); },
	      },
	      op);
}
template <typename Visitor>
void visit_dec(Visitor&& vis, const physical_operator& op) {
	visit(overloaded {
	          [&](const dec_physical_operator& dec) { visit(std::forward<Visitor>(vis), dec); },
	          [&](const sp<class PhysicalExpr>& pe) { vis(pe); },
	          [&](const auto&) { FLS_UNREACHABLE(); },
	      },
	      op);
}

// Two-variant visit for materializer: unwraps physical_operator then visits with col_pt
template <typename Visitor, typename ColVariant>
void visit_dec(Visitor&& vis, const physical_operator& op, ColVariant& col) {
	visit(overloaded {
	          [&](const dec_physical_operator& dec) {
		          visit([&](const auto& inner) { visit([&](auto& c) { vis(inner, c); }, col); }, dec);
	          },
	          [&](const sp<class PhysicalExpr>& pe) { visit([&](auto& c) { vis(pe, c); }, col); },
	          [&](const auto&) { FLS_UNREACHABLE(); },
	      },
	      op);
}

using physical_operators = vector<physical_operator>;
using physical_operands  = vector<fls_vec>;

class FLS_API PhysicalExpr {
public:
	physical_operators operators;
	physical_operands  operands;

public:
	~PhysicalExpr();
	PhysicalExpr();

	PhysicalExpr(const PhysicalExpr&)            = delete;
	PhysicalExpr& operator=(const PhysicalExpr&) = delete;
	PhysicalExpr(PhysicalExpr&&)                 = default;
	PhysicalExpr& operator=(PhysicalExpr&&)      = default;

public:
	//
	void PointTo(n_t vec_idx) const;
	//
	void Flush(Buf& buf, ColumnDescriptorT& column_descriptor, uint8_t* helper_buffer) const;
	//
	[[nodiscard]] n_t Size(n_t sample_size, n_t n_vecs) const;
	//
	void Finalize() const;

public:
	n_t n_active_operators;
};

} // namespace fastlanes

#endif // FLS_EXPRESSION_PHYSICAL_EXPRESSION_HPP
