#include "fls/expression/encoding_operator.hpp"
#include "fls/cfg/cfg.hpp"
#include "fls/common/string.hpp"
#include "fls/cor/lyt/buf.hpp"
#include "fls/expression/analyze_operator.hpp"
#include "fls/expression/interpreter.hpp"
#include "fls/expression/physical_expression.hpp"
#include "fls/ffor.hpp"
#include "fls/ffor_util.hpp"
#include "fls/primitive/bitpack/bitpack.hpp"
#include "fls/primitive/copy/fls_copy.hpp"
#include "fls/reader/segment.hpp"
#include <cstring>

namespace fastlanes {
/*--------------------------------------------------------------------------------------------------------------------*\
 * enc_scan_opr
\*--------------------------------------------------------------------------------------------------------------------*/
template <typename PT>
enc_scan_opr<PT>::enc_scan_opr(const PhysicalExpr& expr,
                               const col_pt&       column,
                               ColumnDescriptorT&  column_descriptor,
                               InterpreterState&   state)
    : typed_column_view(column) {
}

template <typename PT>
void enc_scan_opr<PT>::PointTo(n_t vec_idx) {
	typed_column_view.PointTo(vec_idx);
}

template <typename PT>
void enc_scan_opr<PT>::Copy() {
	std::memcpy(data, typed_column_view.Data(), TypedColumnView<PT>::GetSizeOfOneVector());
}

template struct enc_scan_opr<i64_pt>;
template struct enc_scan_opr<i32_pt>;
template struct enc_scan_opr<i16_pt>;
template struct enc_scan_opr<i08_pt>;
template struct enc_scan_opr<u64_pt>;
template struct enc_scan_opr<u32_pt>;
template struct enc_scan_opr<u16_pt>;
template struct enc_scan_opr<u08_pt>;
/*--------------------------------------------------------------------------------------------------------------------*\
 * enc_dict_opr
\*--------------------------------------------------------------------------------------------------------------------*/
template <typename VALUE_PT, typename INDEX_PT>
enc_dict_map_opr<VALUE_PT, INDEX_PT>::enc_dict_map_opr(const PhysicalExpr& expr,
                                                       const col_pt&       column,
                                                       ColumnDescriptorT&  column_descriptor,
                                                       InterpreterState&   state)
    : typed_column_view(column) {
}

template <typename VALUE_PT, typename INDEX_PT>
void enc_dict_map_opr<VALUE_PT, INDEX_PT>::PointTo(n_t vec_idx) {
	typed_column_view.PointTo(vec_idx);
}

template <typename VALUE_PT, typename INDEX_PT>
void enc_dict_map_opr<VALUE_PT, INDEX_PT>::Map() {
	[[maybe_unused]] const auto& bimap_frequency =
	    typed_column_view.GetStats()->bimap_frequency; // todo get bimap_frequency from bimap_frequency operator

	const auto* value_p = typed_column_view.Data();

	for (auto idx = 0; idx < CFG::VEC_SZ; ++idx) {
		const auto value = value_p[idx];
		index_arr[idx]   = static_cast<INDEX_PT>(bimap_frequency.get_key(value));
	}
}

template struct enc_dict_map_opr<i64_pt, u32_pt>;
template struct enc_dict_map_opr<i64_pt, u16_pt>;
template struct enc_dict_map_opr<i64_pt, u08_pt>;
template struct enc_dict_map_opr<i32_pt, u32_pt>;
template struct enc_dict_map_opr<i32_pt, u16_pt>;
template struct enc_dict_map_opr<i32_pt, u08_pt>;
template struct enc_dict_map_opr<i16_pt, u16_pt>;
template struct enc_dict_map_opr<i16_pt, u08_pt>;
template struct enc_dict_map_opr<i08_pt, u08_pt>;
template struct enc_dict_map_opr<dbl_pt, u32_pt>;
template struct enc_dict_map_opr<dbl_pt, u16_pt>;
template struct enc_dict_map_opr<dbl_pt, u08_pt>;
template struct enc_dict_map_opr<flt_pt, u32_pt>;
template struct enc_dict_map_opr<flt_pt, u16_pt>;
template struct enc_dict_map_opr<flt_pt, u08_pt>;

template <typename INDEX_PT>
enc_dict_map_opr<fls_string_t, INDEX_PT>::enc_dict_map_opr(const PhysicalExpr& expr,
                                                           const col_pt&       column,
                                                           ColumnDescriptorT&  column_descriptor,
                                                           InterpreterState&   state)
    : column_view(column) {
}

template <typename INDEX_PT>
void enc_dict_map_opr<fls_string_t, INDEX_PT>::PointTo(n_t vec_idx) {
	column_view.PointTo(vec_idx);
}

template <typename INDEX_PT>
void enc_dict_map_opr<fls_string_t, INDEX_PT>::Map() {
	[[maybe_unused]] const auto& dict =
	    column_view.stats.bimap; // todo get bimap_frequency from bimap_frequency operator

	const auto* string_p_arr = column_view.String_p();
	const auto* lengths_arr  = column_view.Length();

	for (auto idx = 0; idx < CFG::VEC_SZ; ++idx) {
		const fls_string_t fls_string = {string_p_arr[idx], lengths_arr[idx]};
		index_arr[idx]                = static_cast<INDEX_PT>(dict.get_value(fls_string));
	}
}

template struct enc_dict_map_opr<fls_string_t, u32_pt>;
template struct enc_dict_map_opr<fls_string_t, u16_pt>;
template struct enc_dict_map_opr<fls_string_t, u08_pt>;

/*--------------------------------------------------------------------------------------------------------------------*\
 * enc_uncompressed_opr
\*--------------------------------------------------------------------------------------------------------------------*/
template <typename PT>
enc_uncompressed_opr<PT>::enc_uncompressed_opr(const PhysicalExpr& physical_expr,
                                               const col_pt&       column,
                                               ColumnDescriptorT&  column_descriptor,
                                               InterpreterState&   state)
    : typed_column_view(column) {

	segment = make_unique<Segment>();
}
template <typename PT>

void enc_uncompressed_opr<PT>::Copy() {
	FLS_ASSERT_NOT_NULL_POINTER(typed_column_view.Data())
	copy<PT>(typed_column_view.Data(), data);
	segment->Flush(typed_column_view.Data(), TypedColumnView<PT>::GetSizeOfOneVector());
}

template <typename PT>
void enc_uncompressed_opr<PT>::PointTo(const n_t vec_idx) {
	typed_column_view.PointTo(vec_idx);
}

template struct enc_uncompressed_opr<i64_pt>;
template struct enc_uncompressed_opr<i32_pt>;
template struct enc_uncompressed_opr<i16_pt>;
template struct enc_uncompressed_opr<i08_pt>;
template struct enc_uncompressed_opr<u64_pt>;
template struct enc_uncompressed_opr<u32_pt>;
template struct enc_uncompressed_opr<u16_pt>;
template struct enc_uncompressed_opr<u08_pt>;
template struct enc_uncompressed_opr<dbl_pt>;
template struct enc_uncompressed_opr<flt_pt>;

/*--------------------------------------------------------------------------------------------------------------------*\
 * enc_fls_str_uncompressed_op
\*--------------------------------------------------------------------------------------------------------------------*/
enc_fls_str_uncompressed_op::enc_fls_str_uncompressed_op(const col_pt& column)
    : fls_string_column_view(column) {
	data_segment   = make_unique<Segment>();
	length_segment = make_unique<Segment>();
}

void enc_fls_str_uncompressed_op::PointTo(const n_t vec_idx) {
	fls_string_column_view.PointTo(vec_idx);
}
void enc_fls_str_uncompressed_op::Copy() const {
	len_t ttl_size {0};
	for (auto idx = 0; idx < CFG::VEC_SZ; ++idx) {
		ttl_size += fls_string_column_view.Length()[idx];
	}
	data_segment->Flush(fls_string_column_view.Data(), ttl_size);
	length_segment->Flush(fls_string_column_view.Length(), FlsStrColumnView::GetSizeOfOneVector());
}

/*--------------------------------------------------------------------------------------------------------------------*\
 * enc struct opr
\*--------------------------------------------------------------------------------------------------------------------*/
enc_struct_opr::enc_struct_opr(const col_pt& column, ColumnDescriptorT& column_descriptor) {

	auto visitor = overloaded {[&](std::monostate&) { FLS_UNREACHABLE(); },
	                           [&](const up<Struct>& struct_col) {
		                           for (auto& child_column_descriptor : column_descriptor.children) {
			                           InterpreterState state;

			                           auto child_physical_expr = Interpreter::Encoding::Interpret(
			                               *child_column_descriptor, struct_col->internal_rowgroup, state);
			                           internal_exprs.emplace_back(child_physical_expr);
		                           }
	                           },
	                           //
	                           [&](const auto&) {
		                           FLS_UNREACHABLE()
	                           }};

	visit(visitor, column);
}

/*--------------------------------------------------------------------------------------------------------------------*\
 * enc ffor opr
\*--------------------------------------------------------------------------------------------------------------------*/
template <typename PT>
struct VisitorFunctor {
	enc_ffor_opr<PT>*   that;
	const PhysicalExpr* expression; // pointer so we can use inside operator()

	void operator()(const sp<enc_analyze_opr<PT, false>>& opr) {
		that->bw   = &opr->bw;
		that->base = &opr->base;
		that->data = opr->data;
	}

	void operator()(const sp<enc_analyze_opr<make_signed_t<PT>, false>>& opr) {
		that->bw   = &opr->bw;
		that->base = reinterpret_cast<PT*>(&opr->base);
		that->data = reinterpret_cast<PT*>(opr->data);
	}

	void operator()(const sp<enc_analyze_opr<PT, true>>& opr) {
		that->bw   = &opr->bw;
		that->base = &opr->base;
		that->data = opr->data;
	}

	void operator()(const sp<enc_analyze_opr<make_signed_t<PT>, true>>& opr) {
		that->bw   = &opr->bw;
		that->base = reinterpret_cast<PT*>(&opr->base);
		that->data = reinterpret_cast<PT*>(opr->data);
	}

	void operator()(const sp<enc_slpatch_opr<PT>>&) {
		// Safely step backward to [expr.size() - 2], if it exists
		if (expression->operators.size() >= 2) {
			visit(*this, expression->operators[expression->operators.size() - 2]);
		}
	}

	void operator()(const sp<enc_slpatch_opr<make_signed_t<PT>>>&) {
		// Safely step backward to [expr.size() - 2], if it exists
		if (expression->operators.size() >= 2) {
			visit(*this, expression->operators[expression->operators.size() - 2]);
		}
	}

	// Overload for std::monostate
	void operator()(std::monostate) {
		FLS_UNREACHABLE();
	}

	// Catch-all for unexpected types
	void operator()(auto& arg) {
		FLS_UNREACHABLE_WITH_TYPE(arg);
	}
};

template <typename PT>
enc_ffor_opr<PT>::enc_ffor_opr(const PhysicalExpr& expr,
                               const col_pt&       col,
                               ColumnDescriptorT&  column_descriptor,
                               InterpreterState&   state) {

	VisitorFunctor functor {this, &expr};

	if (!expr.operators.empty()) {
		visit(functor, expr.operators.back());
	}

	auto& [operator_tokens, operand_tokens] = *column_descriptor.encoding_rpn;

	operand_tokens.emplace_back(state.cur_operand++);
	operand_tokens.emplace_back(state.cur_operand++);
	operand_tokens.emplace_back(state.cur_operand++);

	bitpacked_segment = make_unique<Segment>();
	bitwidth_segment  = make_unique<Segment>();
	base_segment      = make_unique<Segment>();
}

template <typename PT>
void enc_ffor_opr<PT>::PointTo(n_t vec_idx) {
}

template <typename PT>
void enc_ffor_opr<PT>::ffor() {
	const auto* in_p = data;
	generated::ffor::fallback::scalar::ffor(in_p, bitpacked_arr, *bw, base);

	const n_t n_bytes = calculate_bitpacked_vector_size(*bw);
	bitwidth_segment->Flush(bw, sizeof(bw_t));
	base_segment->Flush(base, sizeof(PT));
	bitpacked_segment->Flush(bitpacked_arr, n_bytes);
};

template struct enc_ffor_opr<u64_pt>;
template struct enc_ffor_opr<u32_pt>;
template struct enc_ffor_opr<u16_pt>;
template struct enc_ffor_opr<u08_pt>;
} // namespace fastlanes