#include "fls/encoder/random_accessor.hpp"
#include "fls/cfg/cfg.hpp"
#include "fls/cor/lyt/vec.hpp"
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
#include "fls/primitive/fls_memset/fls_memset.hpp"
#include "fls/primitive/untranspose/untranspose.hpp"
#include "fls/reader/segment.hpp"
#include "fls/std/type_traits.hpp"
#include "fls/table/rowgroup.hpp"

namespace fastlanes {

RandomAccessor::RandomAccessor() {
	data_1_buf = make_unique<Buf>();
	data_2_buf = make_unique<Buf>();
}

// struct random_accessor_visitor {
//	explicit random_accessor_visitor(n_t vec_idx,  RandomAccessor& random_accessor)
//	    : vec_idx(vec_idx),
//	    random_accessor(random_accessor){};
//
//	template <typename PT>
//	void operator()(const sp<dec_uncompressed_opr<PT>>& opr) const {
//		for (n_t idx {0}; idx < CFG::VEC_SZ; ++idx) {
//			// fixme (reserve and memcopy);
//			typed_col->data.push_back(opr->Data()[idx]);
//		}
//	}
//	template <typename PT>
//	void operator()(const sp<dec_unffor_opr<PT>>& opr) const {
//		copy<PT>(opr->Data(),reinterpret_cast<PT*>(random_accessor.data_1_buf->data()));
//	}
//	template <typename PT>
//	void operator()(const sp<dec_unffor_opr<PT>>& opr) const {
//		copy<PT>(opr->Data(), reinterpret_cast<PT*>(random_accessor.data_1_buf->data()));
//	}
//	template <typename PT>
//	void operator()(const sp<dec_alp_opr<PT>>& opr) const {
//		copy<PT>(opr->decoded_arr, reinterpret_cast<PT*>(random_accessor.data_1_buf->data()));
//	}
//	template <typename PT>
//	void operator()(const sp<dec_alp_rd_opr<PT>>& opr) const {
//		copy<PT>(opr->glue_arr, reinterpret_cast<PT*>(random_accessor.data_1_buf->data()));
//	}
//	template <typename PT>
//	void operator()(const sp<dec_constant_opr<PT>>& opr) const {
//		fls_memset<PT>(&opr->value, reinterpret_cast<PT*>(random_accessor.data_1_buf->data()));
//	}
//	void operator()(const sp<dec_constant_str_opr>& opr) const {
//		const auto constant_value_size = static_cast<len_t>(opr->bytes.size());
//		fls_memset<len_t>(&constant_value_size, reinterpret_cast<len_t*>(random_accessor.data_1_buf->data()));
//		// optimize
//		for (n_t idx {0}; idx < CFG::VEC_SZ; ++idx) {
//			str_col->byte_arr.insert(str_col->byte_arr.end(), opr->bytes.begin(), opr->bytes.end());
//		}
//	}
//	template <typename PT>
//	void operator()(const sp<PhysicalExpr>& expr) const {
//		auto visitor = [this, &typed_col](auto&& arg) {
//			(*this)(std::forward<decltype(arg)>(arg), typed_col);
//		};
//		visit(visitor, expr->operators[expr->operators.size() - 1]);
//	}
//	void operator()(const sp<PhysicalExpr>& expr) const {
//		auto visitor = [this, &typed_col](auto&& arg) {
//			(*this)(std::forward<decltype(arg)>(arg), typed_col);
//		};
//		visit(visitor, expr->operators[0]);
//	}
//	void operator()(const sp<dec_struct_opr>& struct_expr) const {
//	}
//	void operator()(const sp<dec_fls_str_uncompressed_opr>& opr) const {
//		for (n_t idx {0}; idx < CFG::VEC_SZ; ++idx) {
//			str_col->length_arr.push_back(opr->Length()[idx]);
//		}
//		const size_t old_size = str_col->byte_arr.size(); // Save the current size
//		str_col->byte_arr.resize(old_size + opr->byte_arr_segment.Size());
//		std::memcpy(str_col->byte_arr.data() + old_size, opr->Data(), opr->byte_arr_segment.Size());
//	}
//	void operator()(const sp<dec_fsst_opr>& opr) const {
//		opr->Decode(str_col->byte_arr, str_col->length_arr);
//	}
//	void operator()(const sp<dec_fsst12_opr>& opr) const {
//		opr->Decode(str_col->byte_arr, str_col->length_arr);
//	}
//	// DICT
//	template <typename KEY_PT, typename INDEX_PT>
//	void operator()(const sp<dec_dict_opr<KEY_PT, INDEX_PT>>& dict_expr) const {
//		const auto* key_p   = dict_expr->Keys();
//		const auto* index_p = dict_expr->Index();
//
//		for (n_t idx {0}; idx < CFG::VEC_SZ; ++idx) {
//			typed_col->data.push_back(key_p[index_p[idx]]);
//		}
//	}
//	template <typename INDEX_PT>
//	void operator()(const sp<dec_dict_opr<fls_string_t, INDEX_PT>>& opr) const {
//		opr->Decode(str_col->byte_arr, str_col->length_arr);
//	}
//	template <typename INDEX_PT>
//	void operator()(const sp<dec_fsst_dict_opr<INDEX_PT>>& opr) const {
//		opr->Decode(str_col->byte_arr, str_col->length_arr);
//	}
//	template <typename INDEX_PT>
//	void operator()(const sp<dec_fsst12_dict_opr<INDEX_PT>>& opr) const {
//		opr->Decode(str_col->byte_arr, str_col->length_arr);
//	}
//	template <typename KEY_PT, typename INDEX_PT>
//	void operator()(const sp<dec_rle_map_opr<KEY_PT, INDEX_PT>>& opr) const {
//		opr->Decode(vec_idx, typed_col->data);
//	}
//	template <typename INDEX_PT>
//	void operator()(const sp<dec_rle_map_opr<fls_string_t, INDEX_PT>>& opr) const {
//		opr->Decode(vec_idx, typed_col->byte_arr, typed_col->length_arr);
//	}
//
//	template <typename PT>
//	void operator()(const sp<dec_null_opr<PT>>& opr) const {
//		opr->Materialize(vec_idx, *typed_col);
//	}
//	template <typename PT>
//	void operator()(const sp<dec_transpose_opr<PT>>& opr) const {
//		opr->Materialize(vec_idx, *typed_col);
//	}
//	template <typename PT>
//	void operator()(const sp<dec_slpatch_opr<PT>>& opr) const {
//		opr->Materialize(vec_idx, *typed_col);
//	}
//	template <typename PT>
//	void operator()(const sp<dec_frequency_opr<PT>>& opr) const {
//		opr->Materialize(vec_idx, *typed_col);
//	}
//	void operator()(const sp<dec_frequency_str_opr>& opr) const {
//		opr->Materialize(vec_idx, *typed_col);
//	}
//	template <typename PT>
//	void operator()(const sp<dec_cross_rle_opr<PT>>& opr) const {
//		opr->Materialize(vec_idx, *typed_col);
//	}
//	void operator()(const sp<dec_cross_rle_opr<fls_string_t>>& opr) const {
//		opr->Materialize(vec_idx, *typed_col);
//	}
//	void operator()(const auto& opr, auto& col) const { FLS_UNREACHABLE_WITH_TYPES(opr, col); }
//	//
//	n_t vec_idx;
//	RandomAccessor& random_accessor;
// };
//
// void RandomAccessor::RandomAccess(const vector<sp<PhysicalExpr>>& expressions, n_t val_idx) {
//	FLS_ASSERT_E(expressions.size(), rowgroup.internal_rowgroup.size());
//
//	for (n_t col_idx {0}; col_idx < expressions.size(); ++col_idx) {
//		const auto& expr = expressions[col_idx];
//
//		FLS_ASSERT_NOT_EMPTY_VEC(expr->operators);
//
//		visit(random_accessor_visitor {val_idx,*this}, expr->operators[expr->operators.size() - 1]);
//	}

} // namespace fastlanes
