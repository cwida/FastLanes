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
/*--------------------------------------------------------------------------------------------------------------------*/

using physical_operator = variant<std::monostate,
                                  // ALP
                                  sp<enc_alp_opr<dbl_pt>>,
                                  sp<enc_alp_opr<flt_pt>>,
                                  sp<enc_alp_rd_opr<dbl_pt>>,
                                  sp<enc_alp_rd_opr<flt_pt>>,
                                  sp<struct dec_alp_opr<dbl_pt>>,
                                  sp<struct dec_alp_opr<flt_pt>>,
                                  sp<struct dec_alp_rd_opr<dbl_pt>>,
                                  sp<struct dec_alp_rd_opr<flt_pt>>,
                                  // scan
                                  sp<enc_scan_opr<i64_pt>>,
                                  sp<enc_scan_opr<i32_pt>>,
                                  sp<enc_scan_opr<i16_pt>>,
                                  sp<enc_scan_opr<i08_pt>>,
                                  sp<enc_scan_opr<u64_pt>>,
                                  sp<enc_scan_opr<u32_pt>>,
                                  sp<enc_scan_opr<u16_pt>>,
                                  sp<enc_scan_opr<u08_pt>>,
                                  // predication
                                  sp<struct predicate_eq_vector_constant_i64>,
                                  sp<struct predicate_GT_i64>,
                                  sp<struct predicate_LE_i64>,
                                  sp<struct predicate_and_selection_ds>,
                                  // decoding
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
                                  // DICT
                                  sp<enc_dict_opr<i64_pt>>,
                                  sp<enc_dict_opr<i32_pt>>,
                                  sp<enc_dict_opr<i16_pt>>,
                                  sp<enc_dict_opr<i08_pt>>,
                                  sp<enc_dict_opr<dbl_pt>>,
                                  sp<enc_dict_opr<fls_string_t>>,
                                  sp<enc_dict_opr<flt_pt>>,
                                  sp<struct dec_dict_opr<i64_pt, u32_pt>>,
                                  sp<struct dec_dict_opr<i64_pt, u16_pt>>,
                                  sp<struct dec_dict_opr<i64_pt, u08_pt>>,
                                  sp<struct dec_dict_opr<i32_pt, u32_pt>>,
                                  sp<struct dec_dict_opr<i32_pt, u16_pt>>,
                                  sp<struct dec_dict_opr<i32_pt, u08_pt>>,
                                  sp<struct dec_dict_opr<i16_pt, u16_pt>>,
                                  sp<struct dec_dict_opr<i16_pt, u08_pt>>,
                                  sp<struct dec_dict_opr<i08_pt, u08_pt>>,
                                  sp<struct dec_dict_opr<dbl_pt, u32_pt>>,
                                  sp<struct dec_dict_opr<dbl_pt, u16_pt>>,
                                  sp<struct dec_dict_opr<dbl_pt, u08_pt>>,
                                  sp<dec_dict_opr<fls_string_t, u32_pt>>,
                                  sp<dec_dict_opr<fls_string_t, u16_pt>>,
                                  sp<dec_dict_opr<fls_string_t, u08_pt>>,
                                  sp<struct dec_dict_opr<flt_pt, u32_pt>>,
                                  sp<struct dec_dict_opr<flt_pt, u16_pt>>,
                                  sp<struct dec_dict_opr<flt_pt, u08_pt>>,
                                  // uncompressed
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
                                  sp<class PhysicalExpr>, //
                                  sp<struct enc_struct_opr>,
                                  // SCAN
                                  sp<struct dec_scan_opr<u32_pt>>,
                                  // FFOR
                                  sp<enc_ffor_opr<u64_pt>>,
                                  sp<enc_ffor_opr<u32_pt>>,
                                  sp<enc_ffor_opr<u16_pt>>,
                                  sp<enc_ffor_opr<u08_pt>>,
                                  // UNFFOR
                                  sp<struct dec_unffor_opr<u64_pt>>,
                                  sp<struct dec_unffor_opr<u32_pt>>,
                                  sp<struct dec_unffor_opr<u16_pt>>,
                                  sp<struct dec_unffor_opr<u08_pt>>,
                                  // DICT
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
                                  // FSST
                                  sp<struct enc_fsst_opr>,
                                  sp<struct enc_fsst12_opr>,
                                  sp<struct dec_fsst_opr>,
                                  sp<struct dec_fsst12_opr>,
                                  // NULL
                                  sp<enc_null_opr<dbl_pt>>,
                                  sp<dec_null_opr<dbl_pt>>,
                                  sp<enc_null_opr<i16_pt>>,
                                  sp<dec_null_opr<i16_pt>>,
                                  sp<enc_null_opr<i32_pt>>,
                                  sp<dec_null_opr<i32_pt>>,
                                  sp<enc_null_opr<flt_pt>>,
                                  sp<dec_null_opr<flt_pt>>,
                                  // FREQUENCY
                                  sp<enc_frequency_opr<dbl_pt>>,
                                  sp<dec_frequency_opr<dbl_pt>>,
                                  sp<enc_frequency_opr<i08_pt>>,
                                  sp<dec_frequency_opr<i08_pt>>,
                                  sp<enc_frequency_opr<i16_pt>>,
                                  sp<dec_frequency_opr<i16_pt>>,
                                  sp<enc_frequency_opr<i32_pt>>,
                                  sp<dec_frequency_opr<i32_pt>>,
                                  sp<enc_frequency_opr<i64_pt>>,
                                  sp<dec_frequency_opr<i64_pt>>,
                                  sp<enc_frequency_opr<flt_pt>>,
                                  sp<dec_frequency_opr<flt_pt>>,
                                  sp<enc_frequency_str_opr>,
                                  sp<dec_frequency_str_opr>,
                                  // RLE
                                  sp<struct enc_rle_map_opr<dbl_pt, u16_pt>>,
                                  sp<struct dec_rle_map_opr<dbl_pt, u16_pt>>,
                                  sp<struct enc_rle_map_opr<flt_pt, u16_pt>>,
                                  sp<struct dec_rle_map_opr<flt_pt, u16_pt>>,
                                  sp<struct enc_rle_map_opr<i64_pt, u16_pt>>,
                                  sp<struct dec_rle_map_opr<i64_pt, u16_pt>>,
                                  sp<struct enc_rle_map_opr<i32_pt, u16_pt>>,
                                  sp<struct dec_rle_map_opr<i32_pt, u16_pt>>,
                                  sp<struct enc_rle_map_opr<i16_pt, u16_pt>>,
                                  sp<struct dec_rle_map_opr<i16_pt, u16_pt>>,
                                  sp<struct enc_rle_map_opr<i08_pt, u16_pt>>,
                                  sp<struct dec_rle_map_opr<i08_pt, u16_pt>>,
                                  sp<struct enc_rle_map_opr<fls_string_t, u16_pt>>,
                                  sp<struct dec_rle_map_opr<fls_string_t, u16_pt>>,
                                  // FFOR
                                  sp<enc_slpatch_opr<u64_pt>>,
                                  sp<enc_slpatch_opr<u32_pt>>,
                                  sp<enc_slpatch_opr<u16_pt>>,
                                  sp<enc_slpatch_opr<u08_pt>>,
                                  sp<dec_slpatch_opr<u64_pt>>,
                                  sp<dec_slpatch_opr<u32_pt>>,
                                  sp<dec_slpatch_opr<u16_pt>>,
                                  sp<dec_slpatch_opr<u08_pt>>,
                                  sp<enc_slpatch_opr<i64_pt>>,
                                  sp<enc_slpatch_opr<i32_pt>>,
                                  sp<enc_slpatch_opr<i16_pt>>,
                                  sp<enc_slpatch_opr<i08_pt>>,
                                  sp<dec_slpatch_opr<i64_pt>>,
                                  sp<dec_slpatch_opr<i32_pt>>,
                                  sp<dec_slpatch_opr<i16_pt>>,
                                  sp<dec_slpatch_opr<i08_pt>>,
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
                                  sp<enc_transpose_opr<u16_pt>>,
                                  sp<enc_transpose_opr<u32_pt>>,
                                  sp<enc_transpose_opr<i08_pt>>,
                                  sp<enc_transpose_opr<i16_pt>>,
                                  sp<enc_transpose_opr<i32_pt>>,
                                  sp<enc_transpose_opr<i64_pt>>,
                                  sp<dec_transpose_opr<i08_pt>>,
                                  sp<dec_transpose_opr<i16_pt>>,
                                  sp<dec_transpose_opr<i32_pt>>,
                                  sp<dec_transpose_opr<i64_pt>>,
                                  // CROSS RLE
                                  sp<enc_cross_rle_opr<i08_pt>>,
                                  sp<dec_cross_rle_opr<i08_pt>>,
                                  sp<enc_cross_rle_opr<i16_pt>>,
                                  sp<dec_cross_rle_opr<i16_pt>>,
                                  sp<enc_cross_rle_opr<i32_pt>>,
                                  sp<dec_cross_rle_opr<i32_pt>>,
                                  sp<enc_cross_rle_opr<i64_pt>>,
                                  sp<dec_cross_rle_opr<i64_pt>>,
                                  sp<enc_cross_rle_opr<dbl_pt>>,
                                  sp<dec_cross_rle_opr<dbl_pt>>,
                                  sp<enc_cross_rle_opr<flt_pt>>,
                                  sp<dec_cross_rle_opr<flt_pt>>,
                                  sp<enc_cross_rle_opr<fls_string_t>>,
                                  sp<dec_cross_rle_opr<fls_string_t>>,
                                  // RSUM
                                  sp<enc_rsum_opr<u16_pt>>,
                                  sp<struct dec_rsum_opr<u16_pt>>,
                                  sp<enc_rsum_opr<u32_pt>>,
                                  sp<dec_rsum_opr<u32_pt>>,
                                  sp<enc_rsum_opr<i64_pt>>,
                                  sp<dec_rsum_opr<i64_pt>>,
                                  sp<enc_rsum_opr<i08_pt>>,
                                  sp<dec_rsum_opr<i08_pt>>,
                                  sp<enc_rsum_opr<i16_pt>>,
                                  sp<dec_rsum_opr<i16_pt>>,
                                  sp<enc_rsum_opr<i32_pt>>,
                                  sp<dec_rsum_opr<i32_pt>>,
                                  // DICT FSST
                                  sp<enc_fsst_dict_opr>,
                                  sp<dec_fsst_dict_opr<u32_pt>>,
                                  sp<dec_fsst_dict_opr<u16_pt>>,
                                  sp<dec_fsst_dict_opr<u08_pt>>,
                                  sp<enc_fsst12_dict_opr>,
                                  sp<dec_fsst12_dict_opr<u32_pt>>,
                                  sp<dec_fsst12_dict_opr<u16_pt>>,
                                  sp<dec_fsst12_dict_opr<u08_pt>>
                                  //
                                  >;

using physical_operators = vector<physical_operator>;
using physical_operands  = vector<fls_vec>;

class PhysicalExpr {
public:
	physical_operators operators;
	physical_operands  operands;

public:
	~PhysicalExpr();
	PhysicalExpr();

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
