#ifndef FLS_EXPRESSION_ENCODING_OPERATOR_HPP
#define FLS_EXPRESSION_ENCODING_OPERATOR_HPP

#include "fls/cfg/cfg.hpp"
#include "fls/table/rowgroup.hpp"

namespace fastlanes {
/*--------------------------------------------------------------------------------------------------------------------*/
class Segment;
struct ColumnDescriptorT;
class PhysicalExpr;
struct InterpreterState;
/*--------------------------------------------------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------------------------------------------------*\
 * enc_scan_opr
\*--------------------------------------------------------------------------------------------------------------------*/
template <typename PT>
struct enc_scan_opr {
public:
	explicit enc_scan_opr(const PhysicalExpr& expr,
	                      const col_pt&       column,
	                      ColumnDescriptorT&  column_descriptor,
	                      InterpreterState&   state);

	void PointTo(n_t vec_idx);
	void Copy();

public:
	TypedColumnView<PT> typed_column_view;
	PT                  data[CFG::VEC_SZ];
};

/*--------------------------------------------------------------------------------------------------------------------*\
 * enc_map_opr
\*--------------------------------------------------------------------------------------------------------------------*/
template <typename KEY_PT, typename INDEX_PT>
struct enc_dict_map_opr {
	explicit enc_dict_map_opr(const PhysicalExpr& expr,
	                          const col_pt&       column,
	                          ColumnDescriptorT&  column_descriptor,
	                          InterpreterState&   state);
	void PointTo(n_t vec_idx);
	void Map();

	TypedColumnView<KEY_PT> typed_column_view;
	INDEX_PT                index_arr[CFG::VEC_SZ];
};

template <typename INDEX_PT>
struct enc_dict_map_opr<fls_string_t, INDEX_PT> {
	explicit enc_dict_map_opr(const PhysicalExpr& expr,
	                          const col_pt&       column,
	                          ColumnDescriptorT&  column_descriptor,
	                          InterpreterState&   state);
	void PointTo(n_t vec_idx);
	void Map();

	FlsStrColumnView column_view;
	INDEX_PT         index_arr[CFG::VEC_SZ];
};
/*--------------------------------------------------------------------------------------------------------------------*\
 * enc_constant_op
\*--------------------------------------------------------------------------------------------------------------------*/
struct enc_constant_opr {
	enc_constant_opr() = default;
};

/*--------------------------------------------------------------------------------------------------------------------*\
 * enc_uncompressed_op
\*--------------------------------------------------------------------------------------------------------------------*/
template <typename PT>
struct enc_uncompressed_opr {
public:
	explicit enc_uncompressed_opr(const PhysicalExpr& physical_expr,
	                              const col_pt&       column,
	                              ColumnDescriptorT&  column_descriptor,
	                              InterpreterState&   state);

	void Copy();
	void PointTo(n_t vec_idx);

public:
	TypedColumnView<PT> typed_column_view;
	up<Segment>         segment;
	PT                  data[CFG::VEC_SZ];
};

/*--------------------------------------------------------------------------------------------------------------------*\
 * enc_fls_str_uncompressed_op
\*--------------------------------------------------------------------------------------------------------------------*/
struct enc_fls_str_uncompressed_op {
public:
	explicit enc_fls_str_uncompressed_op(const col_pt& column);

	void Copy() const;
	void PointTo(n_t vec_idx);

public:
	FlsStrColumnView fls_string_column_view;
	up<Segment>      data_segment;
	up<Segment>      length_segment;
};

/*--------------------------------------------------------------------------------------------------------------------*\
 * enc_struct_opr
\*--------------------------------------------------------------------------------------------------------------------*/
struct enc_struct_opr {
	enc_struct_opr(const col_pt& column, ColumnDescriptorT& column_descriptor);

	vector<sp<class PhysicalExpr>> internal_exprs;
};

/*--------------------------------------------------------------------------------------------------------------------*\
 * enc_bitpack_opr
\*--------------------------------------------------------------------------------------------------------------------*/
template <typename PT>
struct enc_ffor_opr {
public:
	explicit enc_ffor_opr(const PhysicalExpr& expr,
	                      const col_pt&       col,
	                      ColumnDescriptorT&  column_descriptor,
	                      InterpreterState&   state);

	void PointTo(n_t vec_idx);
	void ffor();

public:
	PT*         data;
	up<Segment> bitpacked_segment;
	up<Segment> base_segment;
	up<Segment> bitwidth_segment;
	PT          bitpacked_arr[CFG::VEC_SZ];
	bw_t*       bw;
	PT*         base;
};

} // namespace fastlanes

#endif // FLS_EXPRESSION_ENCODING_OPERATOR_HPP