#ifndef FLS_EXPRESSION_ANALYZE_OPERATOR_HPP
#define FLS_EXPRESSION_ANALYZE_OPERATOR_HPP

#include "alp/common.hpp"
#include "fls/cfg/cfg.hpp"
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
 * Histogram
\*--------------------------------------------------------------------------------------------------------------------*/
template <typename PT>
class Histogram {
public:
	Histogram() = default; //
public:
	void Cal(PT* data);
	void Reset();

public:
	std::vector<PT>       val_vec; //
	std::vector<uint16_t> rep_vec; //
};
/*--------------------------------------------------------------------------------------------------------------------*\
 * enc_analyze_opr
\*--------------------------------------------------------------------------------------------------------------------*/
template <typename PT, bool IS_PATCHED = false>
struct enc_analyze_opr {
public:
	explicit enc_analyze_opr(const PhysicalExpr& expr,
	                         const col_pt&       col,
	                         ColumnDescriptorT&  column_descriptor,
	                         InterpreterState&   state);

	void Analyze();
	void PointTo(n_t vec_idx);

public:
	PT            copy_of_data[CFG::VEC_SZ];
	PT*           data;
	PT            base;
	vec_idx_t     n_exceptions;
	alp::exp_p_t  exception_pos_arr[CFG::VEC_SZ];
	PT            exceptions[CFG::VEC_SZ];
	bw_t          bw;
	Histogram<PT> histogram;
	NullMapView   null_map_view;
	bool          is_rsum;
};

} // namespace fastlanes

#endif // FLS_EXPRESSION_ANALYZE_OPERATOR_HPP
