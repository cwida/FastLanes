#include "fls/common/alias.hpp"  // for n_t, up, idx_t, make_unique
#include "fls/common/common.hpp" // for FLS_UNREACHABLE
#include "fls/common/string.hpp"
#include "fls/expression/expression_executor.hpp"
#include "fls/expression/interpreter.hpp"
#include "fls/expression/physical_expression.hpp"
#include "fls/footer/rowgroup_descriptor.hpp" // for ColumnMetadata, RowgroupDescriptor
#include "fls/std/variant.hpp"                // for visit
#include "fls/std/vector.hpp"                 // for vector
#include "fls/table/rowgroup.hpp"             // for Rowgroup, TypedCol (ptr ...
#include "fls/wizard/sampling_layout.hpp"
#include "fls/wizard/wizard_helpers.hpp"
#include <cstring>
#include <memory>    // for unique_ptr, make_unique
#include <stdexcept> // for runtime_error

namespace fastlanes {
DataType FindBestDataTypeForColumn(const col_pt& col);

bool IsDetermined(const ColumnDescriptorT& column_descriptor) {
	const bool is_determined = !column_descriptor.encoding_rpn->operator_tokens.empty();
	return is_determined;
}

n_t TryExpr(const rowgroup_pt&       col,
            const ColumnDescriptorT& column_descriptor,
            const OperatorToken&     token,
            RowgroupDescriptorT&     footer,
            n_t                      sample_size) {
	n_t size {0};

	// interpret
	InterpreterState  state;
	ColumnDescriptorT new_column_descriptor = column_descriptor;
	new_column_descriptor.encoding_rpn->operator_tokens.push_back(token);

	const auto physical_expr_up = Interpreter::Encoding::Interpret(new_column_descriptor, col, state);

	if (sample_size == 0 || sample_size > footer.m_n_vec) {
		sample_size = footer.m_n_vec;
	}

	const n_t*       vec_idxs;
	std::vector<n_t> dyn_layout; // keeps data alive if we fall back

	if (footer.m_n_vec == 64) {
		vec_idxs = sampling_layout_64.data();
	} else if (footer.m_n_vec == 32) {
		vec_idxs = sampling_layout_32.data();
	} else if (footer.m_n_vec == 2) {
		vec_idxs = sampling_layout_2.data();
	} else if (footer.m_n_vec == 1) {
		vec_idxs = sampling_layout_1.data();
	} else {
		// Runtime path
		dyn_layout = sampling_layout_dynamic(footer.m_n_vec);
		vec_idxs   = dyn_layout.data();
	}

	for (n_t vec_idx {0}; vec_idx < sample_size; ++vec_idx) {
		n_t mapped_idx = vec_idxs[vec_idx];
		physical_expr_up->PointTo(mapped_idx);
		ExprExecutor::execute(*physical_expr_up, mapped_idx);
	}

	physical_expr_up->Finalize();
	size = physical_expr_up->Size(sample_size, footer.m_n_vec);

	return size;
}

struct gather_statistics_visitor {
	explicit gather_statistics_visitor(ColumnDescriptorT& a_column_descriptor)
	    : column_descriptor(a_column_descriptor) {
	}

	template <typename PT>
	void operator()(const up<TypedCol<PT>>& col) const {
		column_descriptor.max->binary_data.resize(sizeof(PT));
		std::memcpy(column_descriptor.max->binary_data.data(), &col->m_stats.max, sizeof(PT));
		column_descriptor.n_null = col->m_stats.n_nulls;
	}
	void operator()(const up<FLSStrColumn>& str_col) const {
		const auto size = str_col->m_stats.maximum_n_bytes_p_value;
		column_descriptor.max->binary_data.resize(size);
		std::memcpy(column_descriptor.max->binary_data.data(), str_col->byte_arr.data(), size);
	}

	void operator()(const up<Struct>& fls_struct) const {

		for (n_t col_idx {0}; col_idx < column_descriptor.children.size(); col_idx++) {
			auto& nested_column_descriptor = column_descriptor.children[col_idx];
			visit(gather_statistics_visitor {*nested_column_descriptor}, fls_struct->internal_rowgroup[col_idx]);
		}
	}

	void operator()(const auto&) const {
		FLS_UNREACHABLE();
	}

	ColumnDescriptorT& column_descriptor;
};

void gather_statistics(const rowgroup_pt& rowgroup, vector<up<ColumnDescriptorT>>& column_descriptors) {
	for (n_t col_idx {0}; col_idx < column_descriptors.size(); col_idx++) {
		auto& column_descriptor = column_descriptors[col_idx];
		visit(gather_statistics_visitor {*column_descriptor}, rowgroup[col_idx]);
	}
}

void init(vector<up<ColumnDescriptorT>>& column_descriptors) {
	for (n_t col_idx {0}; col_idx < column_descriptors.size(); col_idx++) {
		auto& column_descriptor         = column_descriptors[col_idx];
		column_descriptor->max          = make_unique<BinaryValueT>();
		column_descriptor->encoding_rpn = make_unique<RPNT>();
	}
}

/*--------------------------------------------------------------------------------------------------------------------*/
struct constant_visitor {
	ColumnDescriptorT& column_descriptor;

	void operator()(std::monostate&) {
		FLS_UNREACHABLE();
	}
	template <typename PT>
	void operator()(const up<TypedCol<PT>>& typed_col) {
		if (typed_col->m_stats.IsConstant()) {
			switch (column_descriptor.data_type) {
			case DataType::DOUBLE: {
				column_descriptor.encoding_rpn->operator_tokens.emplace_back(OperatorToken::EXP_CONSTANT_DBL);
				break;
			}
			case DataType::FLOAT: {
				column_descriptor.encoding_rpn->operator_tokens.emplace_back(OperatorToken::EXP_CONSTANT_FLT);
				break;
			}
			case DataType::INT64: {
				column_descriptor.encoding_rpn->operator_tokens.emplace_back(OperatorToken::EXP_CONSTANT_I64);
				break;
			}
			case DataType::INT32: {
				column_descriptor.encoding_rpn->operator_tokens.emplace_back(OperatorToken::EXP_CONSTANT_I32);
				break;
			}
			case DataType::INT16: {
				column_descriptor.encoding_rpn->operator_tokens.emplace_back(OperatorToken::EXP_CONSTANT_I16);
				break;
			}
			case DataType::INT8: {
				column_descriptor.encoding_rpn->operator_tokens.emplace_back(OperatorToken::EXP_CONSTANT_I08);
				break;
			}
			case DataType::UINT8: {
				column_descriptor.encoding_rpn->operator_tokens.emplace_back(OperatorToken::EXP_CONSTANT_U08);
				break;
			}
			case DataType::INVALID:
			default:;
				FLS_UNREACHABLE()
			}
		}
	}
	void operator()(const up<Struct>& struct_col) {
	}
	void operator()(const up<FLSStrColumn>& fls_str_column) {
		if (fls_str_column->m_stats.is_constant) {
			column_descriptor.encoding_rpn->operator_tokens.emplace_back(OperatorToken::EXP_CONSTANT_STR);
		}
	}
	void operator()(auto&) {
		FLS_UNREACHABLE();
	}
};

void constant_visit(const col_pt& col, ColumnDescriptorT& column_descriptor) {
	//
	visit(constant_visitor {column_descriptor}, col);
}

void constant_check(const rowgroup_pt& rowgroup, vector<up<ColumnDescriptorT>>& column_descriptors) {
	for (n_t col_idx {0}; col_idx < rowgroup.size(); col_idx++) {
		constant_visit(rowgroup[col_idx], *column_descriptors[col_idx]);
	}
}

/*--------------------------------------------------------------------------------------------------------------------*/
struct null_visitor {
	ColumnDescriptorT& column_descriptor;

	void operator()(std::monostate&) {
		FLS_UNREACHABLE();
	}
	template <typename PT>
	void operator()(const up<TypedCol<PT>>& typed_col) {
		const auto nulls_percentage =
		    static_cast<double>(typed_col->m_stats.n_nulls) / static_cast<double>(typed_col->data.size());
		if (nulls_percentage > CFG::NULLS::NULLS_THRESHOLD_PERCENTAGE) {
			switch (column_descriptor.data_type) {
			case DataType::DOUBLE: {
				column_descriptor.encoding_rpn->operator_tokens.emplace_back(OperatorToken::EXP_NULL_DBL);
				break;
			}
			case DataType::FLOAT: {
				column_descriptor.encoding_rpn->operator_tokens.emplace_back(OperatorToken::EXP_NULL_FLT);
				break;
			}
			case DataType::INT16: {
				column_descriptor.encoding_rpn->operator_tokens.emplace_back(OperatorToken::EXP_NULL_I16);
				break;
			}
			case DataType::INT32: {
				column_descriptor.encoding_rpn->operator_tokens.emplace_back(OperatorToken::EXP_NULL_I32);
				break;
			}
			case DataType::INT64:
			case DataType::UINT8:
			case DataType::INVALID:
			default:;
				FLS_UNREACHABLE()
			}
		}
	}
	void operator()(const up<Struct>& struct_col) {
	}
	void operator()(const up<FLSStrColumn>& fls_str_column) {
	}
	void operator()(auto&) {
		FLS_UNREACHABLE();
	}
};

void null_visit(const col_pt& col, ColumnDescriptorT& column_descriptor) {
	visit(null_visitor {column_descriptor}, col);
}

void null_check(const rowgroup_pt& rowgroup, vector<up<ColumnDescriptorT>>& column_descriptors) {
	for (n_t col_idx {0}; col_idx < rowgroup.size(); col_idx++) {
		if (IsDetermined(*column_descriptors[col_idx])) {
			continue;
		}
		null_visit(rowgroup[col_idx], *column_descriptors[col_idx]);
	}
}
/*--------------------------------------------------------------------------------------------------------------------*/
struct col_equality_visitor {
	template <typename PT>
	bool operator()(const up<TypedCol<PT>>& first_col, const up<TypedCol<PT>>& second_col) {
		for (n_t idx {0}; idx < first_col->data.size(); ++idx) {
			// const auto& is_value_1_null = typed_vec_1->nullmap_span[idx];
			// const auto& is_value_2_null = typed_vec_2->nullmap_span[idx];
			//
			// // if either of values are null, it is equal
			// if (is_value_1_null || is_value_2_null) {
			// 	//
			// 	return true;
			// }

			const auto& tuple_1 = first_col->data[idx];
			const auto& tuple_2 = second_col->data[idx];

			if (tuple_1 != tuple_2) {
				return false;
			}
		}
		return true;
	}

	bool operator()(const up<FLSStrColumn>& first_col, const up<FLSStrColumn>& second_col) {
		for (n_t index {0}; index < first_col->ofs_arr.size(); ++index) {
			const bool columns_are_equal = Str::Equal(*first_col, *second_col, index, index);
			if (!columns_are_equal) { //
				return false;
			}
		}
		return true;
	}

	bool operator()(std::monostate&, std::monostate&) {
		FLS_UNREACHABLE();
	}

	bool operator()(auto&, auto&) {
		return false;
	}
};

bool col_equality_visit(const col_pt& first_col, const col_pt& second_col) {
	return visit(col_equality_visitor {}, first_col, second_col);
}

bool Equal(const col_pt& first_col, const col_pt& second_col) {

	if (first_col.index() != second_col.index()) {
		return false;
	}

	if (!col_equality_visit(first_col, second_col)) {
		return false;
	}

	return true;
}

void equality_check(const rowgroup_pt& rowgroup, vector<up<ColumnDescriptorT>>& column_descriptors) {
	const auto n_col = rowgroup.size();

	// brute_force
	for (n_t first_col_idx {0}; first_col_idx < n_col; first_col_idx++) {
		for (n_t second_col_idx {first_col_idx + 1}; second_col_idx < n_col; second_col_idx++) {
			auto& column_descriptor = column_descriptors[second_col_idx];
			if (IsDetermined(*column_descriptor)) {
				continue;
			}

			if (const auto is_equal = Equal(rowgroup[first_col_idx], rowgroup[second_col_idx]); is_equal) {
				switch (column_descriptor->data_type) {
				case DataType::DOUBLE:
				case DataType::FLS_STR:
				case DataType::INT64:
				case DataType::INT32:
				case DataType::INT16:
				case DataType::FLOAT:
				case DataType::INT8: {
					column_descriptor->encoding_rpn->operator_tokens.emplace_back(OperatorToken::EXP_EQUAL);
					column_descriptor->encoding_rpn->operand_tokens.emplace_back(first_col_idx);
					break;
				}
				case DataType::INVALID:
				default: {
					FLS_UNREACHABLE();
				}
				}
			}
		}
	}
}

/*--------------------------------------------------------------------------------------------------------------------*\
 * Expression Check
\*--------------------------------------------------------------------------------------------------------------------*/
[[maybe_unused]] constexpr n_t SAMPLE_SIZE {1};

OperatorToken ChooseBestExpr(const std::vector<up<ExpressionResultT>>& options) {
	FLS_ASSERT_FALSE(options.empty()); // make sure to add the semicolon

	// Find the element with the smallest 'size' member
	auto bestIt = std::min_element(
	    options.begin(), options.end(), [](const up<ExpressionResultT>& a, const up<ExpressionResultT>& b) {
		    return a->size < b->size;
	    });

	// Dereference the unique_ptr to get the operator_token
	return (*bestIt)->operator_token;
}

bool IsDictionaryEncodingRequired(const ColumnDescriptorT& column_descriptor) {
	if (column_descriptor.encoding_rpn->operator_tokens.empty()) {
		return false;
	}

	if (column_descriptor.encoding_rpn->operator_tokens[0] == OperatorToken::WIZARD_DICTIONARY_ENCODE) {
		//
		return true;
	}

	return false;
}

bool IsDictionaryChoosingRequired(const ColumnDescriptorT& column_descriptor) {
	if (column_descriptor.encoding_rpn->operator_tokens.empty()) {
		return false;
	}

	const auto operator_token = column_descriptor.encoding_rpn->operator_tokens[0];

	if (operator_token == OperatorToken::WIZARD_CHOOSE_DICT) {
		return true;
	}

	return false;
}

/*--------------------------------------------------------------------------------------------------------------------*/
bool is_good_for_dictionary_encoding(const col_pt& col) {
	return visit(overloaded {//
	                         [](std::monostate&) {
		                         FLS_UNREACHABLE();
		                         return false;
	                         },
	                         [&]<typename PT>(const up<TypedCol<PT>>& typed_col) {
		                         // calculate the uniqness based on n_run
		                         const auto tmp_n_tup       = typed_col->data.size();
		                         const auto n_unique_values = typed_col->m_stats.bimap_frequency.size();
		                         const auto uniqness_ratio =
		                             static_cast<double>(n_unique_values) / static_cast<double>(tmp_n_tup);

		                         if (uniqness_ratio >= CFG::CCC::MAX_UNIQUENESS_RATIO_FOR_DICTIONARY_ENCODING) {
			                         return false;
		                         }

		                         return true;
	                         },
	                         [&](const up<FLSStrColumn>& typed_col) {
		                         // calculate the uniqness based on n_run
		                         const auto tmp_n_tup       = typed_col->length_arr.size();
		                         const auto n_unique_values = typed_col->m_stats.bimap.size();
		                         const auto uniqness_ratio =
		                             static_cast<double>(n_unique_values) / static_cast<double>(tmp_n_tup);

		                         if (uniqness_ratio > CFG::CCC::MAX_UNIQUENESS_RATIO_FOR_DICTIONARY_ENCODING) {
			                         return false;
		                         }

		                         return true;
	                         },
	                         [](const up<Struct>& struct_col) { return false; },
	                         [](auto& arg) {
		                         FLS_UNREACHABLE_WITH_TYPE(arg)
		                         return false;
	                         }},
	             col);
}

/*--------------------------------------------------------------------------------------------------------------------*/
template <typename PT, bool isFlipped>
bool checkMappingImpl(const up<FLSStrColumn>& left_col, const up<TypedCol<PT>>& right_col) {
	using ForwardMapType =
	    std::conditional_t<isFlipped, std::unordered_map<PT, fls_string_t>, std::unordered_map<fls_string_t, PT>>;

	using ReverseMapType =
	    std::conditional_t<isFlipped, std::unordered_map<fls_string_t, PT>, std::unordered_map<PT, fls_string_t>>;

	ForwardMapType forward_map;
	ReverseMapType reverse_map;

	n_t num_rows = left_col->length_arr.size();
	for (n_t row_idx = 0; row_idx < num_rows; ++row_idx) {
		typename ForwardMapType::key_type right_value;
		typename ReverseMapType::key_type left_value;

		const auto& is_left_val_null  = left_col->null_map_arr[row_idx];
		const auto& is_right_val_null = right_col->null_map_arr[row_idx];

		if (is_left_val_null != is_right_val_null) {
			return false;
		}
		if (is_left_val_null) {
			continue;
		}

		if constexpr (isFlipped) {
			right_value = right_col->data[row_idx];                                                  // PT
			left_value  = fls_string_t(left_col->str_p_arr[row_idx], left_col->length_arr[row_idx]); // fls_string_t
		} else {
			right_value = fls_string_t(left_col->str_p_arr[row_idx], left_col->length_arr[row_idx]); // fls_string_t
			left_value  = right_col->data[row_idx];                                                  // PT
		}

		// Check forward mapping
		auto forward_it = forward_map.find(right_value);
		if (forward_it != forward_map.end()) {
			if (forward_it->second != left_value) {
				return false;
			}
		} else {
			forward_map.emplace(right_value, left_value);
		}

		// Check reverse mapping
		auto reverse_it = reverse_map.find(left_value);
		if (reverse_it != reverse_map.end()) {
			if (reverse_it->second != right_value) {
				//
				return false;
			}
		} else {
			reverse_map.emplace(left_value, right_value);
		}
	}

	return true;
}

bool checkMappingImpl(const up<FLSStrColumn>& left_col, const up<FLSStrColumn>& right_col) {
	using ForwardMapType = std::unordered_map<fls_string_t, fls_string_t>;
	using ReverseMapType = std::unordered_map<fls_string_t, fls_string_t>;

	ForwardMapType forward_map;
	ReverseMapType reverse_map;

	n_t num_rows = left_col->length_arr.size();
	for (n_t row_idx = 0; row_idx < num_rows; ++row_idx) {

		const auto& is_left_val_null  = left_col->null_map_arr[row_idx];
		const auto& is_right_val_null = right_col->null_map_arr[row_idx];

		if (is_left_val_null != is_right_val_null) {
			return false;
		}
		if (is_left_val_null) {
			continue;
		}

		auto right_value = fls_string_t(left_col->str_p_arr[row_idx], left_col->length_arr[row_idx]);   // fls_string_t
		auto left_value  = fls_string_t(right_col->str_p_arr[row_idx], right_col->length_arr[row_idx]); // fls_string_t

		// Check forward mapping
		auto forward_it = forward_map.find(right_value);
		if (forward_it != forward_map.end()) {
			if (forward_it->second != left_value) {
				return false;
			}
		} else {
			forward_map.emplace(right_value, left_value);
		}

		// Check reverse mapping
		auto reverse_it = reverse_map.find(left_value);
		if (reverse_it != reverse_map.end()) {
			if (reverse_it->second != right_value) {
				return false;
			}
		} else {
			reverse_map.emplace(left_value, right_value);
		}
	}

	return true;
}

struct col_map_1t1_visitor {
	template <typename FIRST_PT, typename SECOND_PT>
	bool operator()(const up<TypedCol<FIRST_PT>>& left_col, const up<TypedCol<SECOND_PT>>& right_col) {
		unordered_map<FIRST_PT, SECOND_PT> forward_map; // Maps from col_1 to col_2
		unordered_map<SECOND_PT, FIRST_PT> reverse_map; // Maps from col_2 to col_1

		for (n_t row_idx {0}; row_idx < left_col->data.size(); ++row_idx) {
			const auto& left_val  = left_col->data[row_idx];
			const auto& right_val = right_col->data[row_idx];

			const auto& is_left_val_null  = left_col->null_map_arr[row_idx];
			const auto& is_right_val_null = right_col->null_map_arr[row_idx];

			if (is_left_val_null != is_right_val_null) {
				return false;
			}
			if (is_left_val_null) {
				continue;
			}

			// Check the forward mapping (tuple1 -> tuple2)
			if (forward_map.contains(left_val)) {
				const auto& pair = forward_map.find(left_val);
				if (pair->second != right_val) {
					return false;
				}
			} else {
				forward_map.emplace(left_val, right_val);
			}

			// Check the reverse mapping (tuple2 -> tuple1)
			if (reverse_map.contains(right_val)) {
				const auto& pair = reverse_map.find(right_val);
				if (pair->second != left_val) {
					return false;
				}
			} else {
				reverse_map.emplace(right_val, left_val);
			}
		}

		return true; // If no conflicts, the mapping is bijective
	}

	template <typename PT>
	bool operator()(const up<FLSStrColumn>& col_1, const up<TypedCol<PT>>& col_2) {
		return checkMappingImpl<PT, false>(col_1, col_2);
	}

	template <typename PT>
	bool operator()(const up<TypedCol<PT>>& col_2, const up<FLSStrColumn>& col_1) {
		return checkMappingImpl<PT, true>(col_1, col_2);
	}

	bool operator()(const up<FLSStrColumn>& col_1, const up<FLSStrColumn>& col_2) {
		return checkMappingImpl(col_1, col_2);
	}

	bool operator()(std::monostate&, std::monostate&) {
		FLS_UNREACHABLE();
	}

	bool operator()(auto&, auto&) {
		return false;
	}
};

bool map_1t1_visit(const col_pt& col_1, const col_pt& col_2) {
	return visit(col_map_1t1_visitor {}, col_1, col_2);
}

bool IsMap1t1(const col_pt& first_col, const col_pt& second_col) {
	return map_1t1_visit(first_col, second_col);
}

void PushExternalDictionaryEncoding(ColumnDescriptorT& second_column_descriptor, DataType common_data_type_for_index) {
	switch (second_column_descriptor.data_type) {
	case DataType::INT64: {
		switch (common_data_type_for_index) {
		case DataType::UINT32: {
			second_column_descriptor.encoding_rpn->operator_tokens.emplace_back(OperatorToken::EXP_DICT_I64_U32);
			break;
		}
		case DataType::UINT16: {
			second_column_descriptor.encoding_rpn->operator_tokens.emplace_back(OperatorToken::EXP_DICT_I64_U16);
			break;
		}
		case DataType::UINT8: {
			second_column_descriptor.encoding_rpn->operator_tokens.emplace_back(OperatorToken::EXP_DICT_I64_U08);
			break;
		}
		default:
			FLS_UNREACHABLE();
		}
		break;
	}
	case DataType::INT32: {
		switch (common_data_type_for_index) {
		case DataType::UINT32: {
			second_column_descriptor.encoding_rpn->operator_tokens.emplace_back(OperatorToken::EXP_DICT_I32_U32);
			break;
		}
		case DataType::UINT16: {
			second_column_descriptor.encoding_rpn->operator_tokens.emplace_back(OperatorToken::EXP_DICT_I32_U16);
			break;
		}
		case DataType::UINT8: {
			second_column_descriptor.encoding_rpn->operator_tokens.emplace_back(OperatorToken::EXP_DICT_I32_U08);
			break;
		}
		default:
			FLS_UNREACHABLE();
		}
		break;
	}
	case DataType::INT16: {
		switch (common_data_type_for_index) {
		case DataType::UINT16: {
			second_column_descriptor.encoding_rpn->operator_tokens.emplace_back(OperatorToken::EXP_DICT_I16_U16);
			break;
		}
		case DataType::UINT8: {
			second_column_descriptor.encoding_rpn->operator_tokens.emplace_back(OperatorToken::EXP_DICT_I16_U08);
			break;
		}
		default:
			FLS_UNREACHABLE();
		}
		break;
	}
	case DataType::DOUBLE: {
		switch (common_data_type_for_index) {
		case DataType::UINT32: {
			second_column_descriptor.encoding_rpn->operator_tokens.emplace_back(OperatorToken::EXP_DICT_DBL_U32);
			break;
		}
		case DataType::UINT16: {
			second_column_descriptor.encoding_rpn->operator_tokens.emplace_back(OperatorToken::EXP_DICT_DBL_U16);
			break;
		}
		case DataType::UINT8: {
			second_column_descriptor.encoding_rpn->operator_tokens.emplace_back(OperatorToken::EXP_DICT_DBL_U08);
			break;
		}
		default:
			FLS_UNREACHABLE();
		}
		break;
	}
	case DataType::FLS_STR: {
		second_column_descriptor.encoding_rpn->operator_tokens.emplace_back(OperatorToken::WIZARD_CHOOSE_DICT);
		switch (common_data_type_for_index) {
		case DataType::UINT32: {
			second_column_descriptor.encoding_rpn->operand_tokens.emplace_back(static_cast<n_t>(DataType::UINT32));
			break;
		}
		case DataType::UINT16: {
			second_column_descriptor.encoding_rpn->operand_tokens.emplace_back(static_cast<n_t>(DataType::UINT16));
			break;
		}
		case DataType::UINT8: {
			second_column_descriptor.encoding_rpn->operand_tokens.emplace_back(static_cast<n_t>(DataType::UINT8));
			break;
		}
		default:
			FLS_UNREACHABLE();
		}
		break;
	}
	case DataType::INT8: {
		switch (common_data_type_for_index) {
		case DataType::UINT8: {
			second_column_descriptor.encoding_rpn->operator_tokens.emplace_back(OperatorToken::EXP_DICT_I08_U08);
			break;
		}
		default:
			FLS_UNREACHABLE();
		}
		break;
	}
	case DataType::FLOAT: {
		switch (common_data_type_for_index) {
		case DataType::UINT8: {
			second_column_descriptor.encoding_rpn->operator_tokens.emplace_back(OperatorToken::EXP_DICT_FLT_U08);
			break;
		}
		default:
			FLS_UNREACHABLE();
		}
		break;
	}
	case DataType::INVALID:
	default: {
		FLS_UNREACHABLE();
	}
	}
}

n_t GetCardinality(const col_pt& col) {
	n_t cardinality {0};
	visit(overloaded {//
	                  [](const std::monostate&) { FLS_UNREACHABLE(); },
	                  [&]<typename PT>(const up<TypedCol<PT>>& typed_col) {
		                  cardinality = typed_col->m_stats.bimap_frequency.size();
	                  },
	                  [&](const up<FLSStrColumn>& typed_col) { cardinality = typed_col->m_stats.bimap.size(); },
	                  [&](const up<Struct>& struct_col) { FLS_UNREACHABLE(); },
	                  [](const auto& arg) {
		                  FLS_UNREACHABLE_WITH_TYPE(arg)
	                  }},
	      col);

	return cardinality;
}

DataType FindBestDataTypeForColumn(const col_pt& col) {
	const auto col_cardinality = GetCardinality(col);

	if (col_cardinality <= static_cast<size_t>(std::numeric_limits<uint8_t>::max()) + 1) {
		return DataType::UINT8;
	}
	if (col_cardinality <= static_cast<size_t>(std::numeric_limits<uint16_t>::max()) + 1) {
		return DataType::UINT16;
	}
	return DataType::UINT32;

	FLS_UNREACHABLE();
}

DataType FindBestDataTypeForIndex(const col_pt& right, const col_pt& left) {
	const auto left_col_cardinality  = GetCardinality(left);
	const auto right_col_cardinality = GetCardinality(right);

	return FindBestDataTypeForColumn(left_col_cardinality > right_col_cardinality ? left : right);
}

void map_1t1_check(const rowgroup_pt& rowgroup, vector<up<ColumnDescriptorT>>& footer) {
	const auto n_col = rowgroup.size();

	// brute_force
	for (n_t first_col_idx {0}; first_col_idx < n_col; first_col_idx++) {
		auto& first_column_descriptor = footer[first_col_idx];
		if (IsDetermined(*first_column_descriptor)) {
			continue;
		}

		for (n_t second_col_idx {first_col_idx + 1}; second_col_idx < n_col; second_col_idx++) {
			auto& second_column_descriptor = footer[second_col_idx];
			if (IsDetermined(*second_column_descriptor)) {
				continue;
			}
			if (!is_good_for_dictionary_encoding(rowgroup[first_col_idx])) {
				continue;
			}

			if (const auto is_map_1t1 = IsMap1t1(rowgroup[first_col_idx], rowgroup[second_col_idx]); is_map_1t1) {

				auto common_data_type_for_index =
				    FindBestDataTypeForIndex(rowgroup[first_col_idx], rowgroup[second_col_idx]);

				first_column_descriptor->encoding_rpn->operator_tokens.emplace_back(
				    OperatorToken::WIZARD_DICTIONARY_ENCODE);
				first_column_descriptor->encoding_rpn->operand_tokens.emplace_back(
				    static_cast<n_t>(common_data_type_for_index));

				second_column_descriptor->encoding_rpn->operand_tokens.emplace_back(first_col_idx);
				PushExternalDictionaryEncoding(*second_column_descriptor, common_data_type_for_index);
			}
		}
	}
}

} // namespace fastlanes
