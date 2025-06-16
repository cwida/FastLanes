#include "fls/encoder/materializer.hpp"
#include "fls/cfg/cfg.hpp"
#include "fls/expression/alp_expression.hpp"
#include "fls/expression/cross_rle_operator.hpp"
#include "fls/expression/data_type.hpp"
#include "fls/expression/decoding_operator.hpp"
#include "fls/expression/dict_expression.hpp"
#include "fls/expression/frequency_operator.hpp"
#include "fls/expression/fsst12_dict_operator.hpp"
#include "fls/expression/fsst12_expression.hpp"
#include "fls/expression/fsst_dict_operator.hpp"
#include "fls/expression/fsst_expression.hpp"
#include "fls/expression/null_operator.hpp"
#include "fls/expression/physical_expression.hpp"
#include "fls/expression/rle_expression.hpp"
#include "fls/expression/slpatch_operator.hpp"
#include "fls/expression/transpose_operator.hpp"
#include "fls/primitive/copy/fls_copy.hpp"
#include "fls/primitive/untranspose/untranspose.hpp"
#include "fls/reader/segment.hpp"
#include "fls/std/type_traits.hpp"
#include "fls/table/rowgroup.hpp"

namespace fastlanes {

Materializer::Materializer(Rowgroup& rowgroup)
    : rowgroup(rowgroup) {
}

struct material_visitor {
	explicit material_visitor(n_t vec_idx)
	    : vec_idx(vec_idx) {};

	template <typename PT>
	void operator()(const sp<dec_uncompressed_opr<PT>>& opr, up<TypedCol<PT>>& typed_col) const {
		for (n_t idx {0}; idx < CFG::VEC_SZ; ++idx) {
			// fixme (reserve and memcopy);
			typed_col->data.push_back(opr->Data()[idx]);
		}
	}
	template <typename PT>
	void operator()(const sp<dec_unffor_opr<PT>>& opr, up<TypedCol<PT>>& typed_col) const {
		typed_col->data.resize(typed_col->data.size() + CFG::VEC_SZ);
		copy<PT>(opr->Data(), typed_col->data.data() + vec_idx * CFG::VEC_SZ);
	}
	template <typename PT>
	void operator()(const sp<dec_unffor_opr<PT>>& opr, up<TypedCol<std::make_signed_t<PT>>>& typed_col) const {
		typed_col->data.resize(typed_col->data.size() + CFG::VEC_SZ);
		copy<PT>(opr->Data(), reinterpret_cast<PT*>(typed_col->data.data()) + vec_idx * CFG::VEC_SZ);
	}
	template <typename PT>
	void operator()(const sp<dec_alp_opr<PT>>& opr, up<TypedCol<PT>>& typed_col) const {
		for (n_t idx {0}; idx < CFG::VEC_SZ; ++idx) {
			typed_col->data.push_back(opr->decoded_arr[idx]);
		}
	}
	template <typename PT>
	void operator()(const sp<dec_alp_rd_opr<PT>>& opr, up<TypedCol<PT>>& typed_col) const {
		typed_col->data.resize(typed_col->data.size() + CFG::VEC_SZ);
		copy<PT>(opr->glue_arr, typed_col->data.data() + vec_idx * CFG::VEC_SZ);
	}
	template <typename PT>
	void operator()(const sp<dec_constant_opr<PT>>& opr, up<TypedCol<PT>>& typed_col) const {
		// fixme (reserve and set);
		for (n_t idx {0}; idx < CFG::VEC_SZ; ++idx) {
			typed_col->data.push_back(opr->value);
		}
	}
	void operator()(const sp<dec_constant_str_opr>& opr, up<FLSStrColumn>& str_col) const {
		const auto constant_value_size = static_cast<len_t>(opr->bytes.size());

		for (n_t idx = 0; idx < CFG::VEC_SZ; ++idx) {
			str_col->length_arr.push_back(constant_value_size);
		}

		// optimize
		for (n_t idx {0}; idx < CFG::VEC_SZ; ++idx) {
			str_col->byte_arr.insert(str_col->byte_arr.end(), opr->bytes.begin(), opr->bytes.end());
		}
	}
	template <typename PT>
	void operator()(const sp<PhysicalExpr>& expr, up<TypedCol<PT>>& typed_col) const {
		auto visitor = [this, &typed_col](auto&& arg) {
			(*this)(std::forward<decltype(arg)>(arg), typed_col);
		};
		visit(visitor, expr->operators[expr->operators.size() - 1]);
	}
	void operator()(const sp<PhysicalExpr>& expr, up<FLSStrColumn>& typed_col) const {
		auto visitor = [this, &typed_col](auto&& arg) {
			(*this)(std::forward<decltype(arg)>(arg), typed_col);
		};
		visit(visitor, expr->operators[0]);
	}
	void operator()(const sp<dec_struct_opr>& struct_expr, up<Struct>& struct_col) const {
		for (n_t expr_idx {0}; expr_idx < struct_expr->internal_exprs.size(); ++expr_idx) {
			visit(material_visitor {vec_idx},
			      struct_expr->internal_exprs[expr_idx]
			          ->operators[struct_expr->internal_exprs[expr_idx]->operators.size() - 1],
			      struct_col->internal_rowgroup[expr_idx]);
		}
	}
	void operator()(const sp<dec_fls_str_uncompressed_opr>& opr, up<FLSStrColumn>& str_col) const {
		for (n_t idx {0}; idx < CFG::VEC_SZ; ++idx) {
			str_col->length_arr.push_back(opr->Length()[idx]);
		}
		const size_t old_size = str_col->byte_arr.size(); // Save the current size
		str_col->byte_arr.resize(old_size + opr->byte_arr_segment.Size());
		std::memcpy(str_col->byte_arr.data() + old_size, opr->Data(), opr->byte_arr_segment.Size());
	}
	void operator()(const sp<dec_fsst_opr>& opr, up<FLSStrColumn>& str_col) const {
		opr->Decode(str_col->byte_arr, str_col->length_arr);
	}
	void operator()(const sp<dec_fsst12_opr>& opr, up<FLSStrColumn>& str_col) const {
		opr->Decode(str_col->byte_arr, str_col->length_arr);
	}
	// DICT
	template <typename KEY_PT, typename INDEX_PT>
	void operator()(const sp<dec_dict_opr<KEY_PT, INDEX_PT>>& dict_expr, up<TypedCol<KEY_PT>>& typed_col) const {
		const auto* key_p   = dict_expr->Keys();
		const auto* index_p = dict_expr->Index();

		for (n_t idx {0}; idx < CFG::VEC_SZ; ++idx) {
			typed_col->data.push_back(key_p[index_p[idx]]);
		}
	}
	template <typename INDEX_PT>
	void operator()(const sp<dec_dict_opr<fls_string_t, INDEX_PT>>& opr, up<FLSStrColumn>& str_col) const {
		opr->Decode(str_col->byte_arr, str_col->length_arr);
	}
	template <typename INDEX_PT>
	void operator()(const sp<dec_fsst_dict_opr<INDEX_PT>>& opr, up<FLSStrColumn>& str_col) const {
		opr->Decode(str_col->byte_arr, str_col->length_arr);
	}
	template <typename INDEX_PT>
	void operator()(const sp<dec_fsst12_dict_opr<INDEX_PT>>& opr, up<FLSStrColumn>& str_col) const {
		opr->Decode(str_col->byte_arr, str_col->length_arr);
	}
	template <typename KEY_PT, typename INDEX_PT>
	void operator()(const sp<dec_rle_map_opr<KEY_PT, INDEX_PT>>& opr, up<TypedCol<KEY_PT>>& typed_col) const {
		opr->Decode(vec_idx, typed_col->data);
	}
	template <typename INDEX_PT>
	void operator()(const sp<dec_rle_map_opr<fls_string_t, INDEX_PT>>& opr, up<FLSStrColumn>& typed_col) const {
		opr->Decode(vec_idx, typed_col->byte_arr, typed_col->length_arr);
	}

	template <typename PT>
	void operator()(const sp<dec_null_opr<PT>>& opr, up<TypedCol<PT>>& typed_col) const {
		opr->Materialize(vec_idx, *typed_col);
	}
	template <typename PT>
	void operator()(const sp<dec_transpose_opr<PT>>& opr, up<TypedCol<PT>>& typed_col) const {
		opr->Materialize(vec_idx, *typed_col);
	}
	template <typename PT>
	void operator()(const sp<dec_slpatch_opr<PT>>& opr, up<TypedCol<PT>>& typed_col) const {
		opr->Materialize(vec_idx, *typed_col);
	}
	template <typename PT>
	void operator()(const sp<dec_frequency_opr<PT>>& opr, up<TypedCol<PT>>& typed_col) const {
		opr->Materialize(vec_idx, *typed_col);
	}
	void operator()(const sp<dec_frequency_str_opr>& opr, up<FLSStrColumn>& typed_col) const {
		opr->Materialize(vec_idx, *typed_col);
	}
	template <typename PT>
	void operator()(const sp<dec_cross_rle_opr<PT>>& opr, up<TypedCol<PT>>& typed_col) const {
		opr->Materialize(vec_idx, *typed_col);
	}
	void operator()(const sp<dec_cross_rle_opr<fls_string_t>>& opr, up<FLSStrColumn>& typed_col) const {
		opr->Materialize(vec_idx, *typed_col);
	}
	void operator()(const auto& opr, auto& col) const {
		FLS_UNREACHABLE_WITH_TYPES(opr, col);
	}
	//
	n_t vec_idx;
};

void Materializer::Materialize(const vector<sp<PhysicalExpr>>& expressions, n_t vec_idx) const {
	FLS_ASSERT_E(expressions.size(), rowgroup.internal_rowgroup.size());

	for (n_t col_idx {0}; col_idx < expressions.size(); ++col_idx) {
		const auto& expr = expressions[col_idx];
		auto&       col  = rowgroup.internal_rowgroup[col_idx];

		FLS_ASSERT_NOT_EMPTY_VEC(expr->operators);

		expr->PointTo(vec_idx);
		visit(material_visitor {vec_idx}, expr->operators[expr->operators.size() - 1], col);
	}

	// rowgroup.n_tup = rowgroup.n_tup + CFG::VEC_SZ;
}

} // namespace fastlanes
