#include "fls/table/rowgroup.hpp"
#include "fls/common/magic_enum.hpp"
#include "fls/common/string.hpp"
#include "fls/connection.hpp"
#include "fls/csv/csv-parser/parser.hpp"
#include "fls/expression/data_type.hpp"
#include "fls/footer/rowgroup_descriptor.hpp"
#include "fls/json/nlohmann/json.hpp"
#include "fls/reader/segment.hpp"
#include "fls/table/attribute.hpp"
#include "fls/table/chunk.hpp"
#include "fls/table/vector.hpp"

namespace fastlanes {

void init_logial_columns(const ColumnDescriptors& footer, rowgroup_pt& columns);

// TODO [COPY] All return values here are copied to be put inside col_t variant. They should be moved.
col_pt init_logial_columns(const ColumnDescriptorT& col_descriptor) {
	switch (static_cast<DataType>(col_descriptor.data_type)) {
	case DataType::LIST: {
		auto uped_list   = make_unique<List>();
		uped_list->child = init_logial_columns(**col_descriptor.children.begin());
		return uped_list;
	}
	case DataType::STRUCT: {
		auto uped_struct = make_unique<Struct>();
		init_logial_columns(col_descriptor.children, uped_struct->internal_rowgroup);
		return uped_struct;
	}
	case DataType::MAP: {
		// MAP(KEY, VALUE) = LIST(STRUCT(KEY, VALUE))
		auto uped_struct = make_unique<Struct>();
		init_logial_columns(col_descriptor.children, uped_struct->internal_rowgroup);

		auto uped_list   = make_unique<List>();
		uped_list->child = std::move(uped_struct);
		return uped_list;
	}
	case DataType::UINT8:
		return make_unique<u08_col_t>();
	case DataType::UINT32:
		return make_unique<u32_col_t>();
	case DataType::UINT64:
		return make_unique<u64_col_t>();
	case DataType::INT8:
		return make_unique<col_i08>();
	case DataType::INT16:
		return make_unique<col_i16>();
	case DataType::INT32:
		return make_unique<col_i32>();
	case DataType::DECIMAL:
	case DataType::INT64:
		return make_unique<col_i64>();
	case DataType::FLOAT:
		return make_unique<flt_col_t>();
	case DataType::STR:
		return make_unique<str_col_t>();
	case DataType::DOUBLE:
		return make_unique<dbl_col_t>();
	case DataType::FALLBACK:
		return make_unique<str_col_t>();
	case DataType::FLS_STR:
		return make_unique<FLSStrColumn>();
	default:
		FLS_UNREACHABLE();
	}

	FLS_UNREACHABLE();
	return col_pt {};
}

void init_logial_columns(const ColumnDescriptors& footer, rowgroup_pt& columns) {
	columns.reserve(footer.size());
	for (const auto& col_descriptor : footer) {
		columns.emplace_back(init_logial_columns(*col_descriptor));
	}
}

Rowgroup::Rowgroup(const RowgroupDescriptorT& footer, const Connection& connection)
    : m_descriptor(footer)
    , n_tup(footer.m_n_tuples)
    , m_connection(connection)
    , capacity(connection.m_config->n_vector_per_rowgroup * CFG::VEC_SZ) {
	init_logial_columns(footer.m_column_descriptors, internal_rowgroup);
}

up<Rowgroup> Rowgroup::Project(const vector<idx_t>& idxs, const Connection& connection) {
	/**/
	FLS_IMPLEMENT_THIS()
	// auto  result = make_unique<Rowgroup>(*m_descriptor.Project(idxs), connection);
	// idx_t c      = {0};
	// for (const auto idx : idxs) {
	// 	result->internal_rowgroup[c++] = std::move(internal_rowgroup[idx]);
	// }
	// result->n_tup = n_tup;
	// return result;
}

/*--------------------------------------------------------------------------------------------------------------------*\
 * GetStatistics
\*--------------------------------------------------------------------------------------------------------------------*/
struct get_statistics_visitor {

	explicit get_statistics_visitor() = default;

	template <typename PT>
	void operator()(up<TypedCol<PT>>& typed_col) {
	}

	void operator()(up<FLSStrColumn>& str_col) {
		auto& is_constant = str_col->m_stats.is_constant;
		auto& hashtable   = str_col->m_stats.bimap;
		auto& str_p_arr   = str_col->str_p_arr;
		auto& length_arr  = str_col->length_arr;

		// check constness
		for (auto val_idx {0}; val_idx < str_col->length_arr.size(); ++val_idx) {
			if (val_idx != 0) {
				is_constant = is_constant && Str::Equal(*str_col, *str_col, val_idx, val_idx - 1);
			}

			// into the hashtable
			const fls_string_t current_fls_str = {str_p_arr[val_idx], length_arr[val_idx]};
			if (!hashtable.contains_key(current_fls_str)) {
				n_t current_idx = hashtable.size();
				hashtable.insert(current_fls_str, current_idx);
			}
			// else {
			// 	dict_element->repetition = dict_element->repetition + 1;
			// }
		}
		//
	}

	void operator()(up<Struct>& str_col) const {
	}

	void operator()(auto& col) const {
		FLS_UNREACHABLE();
	}
};

void Rowgroup::GetStatistics() {
	for (auto& col : internal_rowgroup) {
		visit(get_statistics_visitor {}, col);
	}
}

/*--------------------------------------------------------------------------------------------------------------------*\
 * Finalize
\*--------------------------------------------------------------------------------------------------------------------*/
struct finalize_visitor {
	explicit finalize_visitor() = default;

	template <typename PT>
	void operator()(up<TypedCol<PT>>& typed_column) const {
		auto& min             = typed_column->m_stats.min;
		auto& max             = typed_column->m_stats.max;
		auto& bimap_frequency = typed_column->m_stats.bimap_frequency;

		// into the dictionary
		for (n_t val_idx {0}; val_idx < typed_column->data.size(); val_idx++) {
			const auto current_val = typed_column->data[val_idx];
			if (!bimap_frequency.contains_value(current_val)) {
				n_t current_idx = bimap_frequency.size();
				bimap_frequency.insert(current_idx, {current_val});
			}

			min = std::min(min, current_val);
			max = std::max(max, current_val);
		}
	}

	void operator()(up<FLSStrColumn>& str_col) const {
		str_col->str_p_arr.resize(str_col->length_arr.size());
		len_t cur_offset = 0;
		for (idx_t val_idx {0}; val_idx < str_col->length_arr.size(); ++val_idx) {
			str_col->str_p_arr[val_idx] = (&str_col->byte_arr[cur_offset]);
			str_col->fls_str_arr.emplace_back(
			    fls_string_t {(&str_col->byte_arr[cur_offset]), str_col->length_arr[val_idx]});
			cur_offset += str_col->length_arr[val_idx];
		}

		str_col->fsst_str_p_arr.resize(str_col->fsst_length_arr.size());
		cur_offset = 0;
		for (idx_t val_idx {0}; val_idx < str_col->fsst_length_arr.size(); ++val_idx) {
			str_col->fsst_str_p_arr[val_idx] = (&str_col->fsst_byte_arr[cur_offset]);

			cur_offset += str_col->fsst_length_arr[val_idx];
		}
	}

	void operator()(up<Struct>& struct_col) const {
		for (auto& col : struct_col->internal_rowgroup) {
			visit(finalize_visitor {}, col);
		}
	}

	void operator()(auto& col) const {
		FLS_UNREACHABLE();
	}
};

void Rowgroup::Finalize() {
	for (auto& col : internal_rowgroup) {
		visit(finalize_visitor {}, col);
	}
}

/*--------------------------------------------------------------------------------------------------------------------*\
 * Cast Check
\*--------------------------------------------------------------------------------------------------------------------*/
struct col_cast_visitor {
	explicit col_cast_visitor(const ColumnDescriptorT& column_descriptor)
	    : column_descriptor(column_descriptor) {
	}

	col_pt operator()(up<FLSStrColumn>& str_col) {
		auto       casted_col = make_unique<TypedCol<i32_pt>>();
		const auto n_tup      = str_col->length_arr.size();
		casted_col->data.resize(n_tup);

		len_t cur_offset = 0;
		for (n_t val_idx {0}; val_idx < n_tup; val_idx++) {
			std::string str(reinterpret_cast<const char*>(&str_col->byte_arr[cur_offset]),
			                str_col->length_arr[val_idx]);
			auto        casted_string = std::stol(str);
			casted_col->data[val_idx] = static_cast<i32_pt>(casted_string);
			cur_offset += str_col->length_arr[val_idx];
		}

		casted_col->null_map_arr = str_col->null_map_arr;

		return casted_col;
	}
	template <typename PT>
	col_pt operator()(up<TypedCol<PT>>& col) {
		if constexpr (!std::is_same_v<PT, str_pt> && !std::is_same_v<PT, bol_pt>) {
			switch (column_descriptor.data_type) {
			case DataType::INT8: {
				auto       casted_col = make_unique<col_i08>();
				const auto n_tup      = col->data.size();
				casted_col->data.resize(n_tup);
				for (n_t val_idx {0}; val_idx < n_tup; val_idx++) {
					casted_col->data[val_idx] = static_cast<i08_pt>(col->data[val_idx]);
				}
				casted_col->null_map_arr = col->null_map_arr;
				return casted_col;
			}
			case DataType::INT16: {
				auto       casted_col = make_unique<col_i16>();
				const auto n_tup      = col->data.size();
				casted_col->data.resize(n_tup);
				for (n_t val_idx {0}; val_idx < n_tup; val_idx++) {
					casted_col->data[val_idx] = static_cast<i16_pt>(col->data[val_idx]);
				}
				casted_col->null_map_arr = col->null_map_arr;
				return casted_col;
			}
			case DataType::INT32: {
				auto       casted_col = make_unique<col_i32>();
				const auto n_tup      = col->data.size();
				casted_col->data.resize(n_tup);
				for (n_t val_idx {0}; val_idx < n_tup; val_idx++) {
					casted_col->data[val_idx] = static_cast<i32_pt>(col->data[val_idx]);
				}
				casted_col->null_map_arr = col->null_map_arr;
				return casted_col;
			}
			case DataType::INT64: {
				auto       casted_col = make_unique<col_i64>();
				const auto n_tup      = col->data.size();
				casted_col->data.resize(n_tup);
				for (n_t val_idx {0}; val_idx < n_tup; val_idx++) {
					casted_col->data[val_idx] = static_cast<i64_pt>(col->data[val_idx]);
				}
				casted_col->null_map_arr = col->null_map_arr;
				return casted_col;
			}
			default:
				FLS_UNREACHABLE();
			}
		} else {
			FLS_UNREACHABLE()
		}
	}

	col_pt operator()(std::monostate&) {
		FLS_UNREACHABLE();
	}
	col_pt operator()(auto& arg) {
		FLS_UNREACHABLE_WITH_TYPE(arg);
	}

	const ColumnDescriptorT& column_descriptor;
};

col_pt cast_visit(rowgroup_pt& rowgroup, const ColumnDescriptorT& column_descriptor) {
	return visit(col_cast_visitor {column_descriptor}, rowgroup[column_descriptor.idx]);
}

template <typename PT>
DataType getSmallestSignedType(PT min, PT max) {
	if constexpr (!std::is_same_v<PT, string> && !std::is_same_v<PT, bool>) {
		if (min >= std::numeric_limits<int8_t>::min() && max <= std::numeric_limits<int8_t>::max()) {
			return DataType::INT8;
		}
		if (min >= std::numeric_limits<int16_t>::min() && max <= std::numeric_limits<int16_t>::max()) {
			return DataType::INT16;
		}
		if (min >= std::numeric_limits<int32_t>::min() && max <= std::numeric_limits<int32_t>::max()) {
			return DataType::INT32;
		}
		return DataType::INT64;
	} else {
		FLS_UNREACHABLE()
	}
}

void cast(rowgroup_pt& rowgroup, ColumnDescriptorT& column_descriptor) {
	bool should_be_cast {false};

	visit(overloaded {
	          [&](up<FLSStrColumn>& string_col) {
		          should_be_cast = string_col->m_stats.is_numeric;
		          if (should_be_cast) {
			          column_descriptor.data_type = DataType::INT32;
		          }
	          },
	          [&]<typename PT>(up<TypedCol<PT>>& typed_col) {
		          if (column_descriptor.data_type == DataType::DECIMAL) {
			          column_descriptor.data_type = DataType::INT64;
			          should_be_cast              = true;
		          }

		          auto casted_data_type = getSmallestSignedType<PT>(typed_col->m_stats.min, typed_col->m_stats.max);
		          if (casted_data_type != column_descriptor.data_type) {
			          should_be_cast              = true;
			          column_descriptor.data_type = casted_data_type;
		          }
	          },
	          [&](up<TypedCol<dbl_pt>>& double_col) {
		          auto is_double_castable = double_col->m_stats.is_double_castable;
		          if (is_double_castable) {
			          const auto casted_data_type =
			              getSmallestSignedType<dbl_pt>(double_col->m_stats.min, double_col->m_stats.max);
			          should_be_cast              = true;
			          column_descriptor.data_type = casted_data_type;
		          }
	          },
	          [&](up<TypedCol<flt_pt>>& float_column) {
		          // TODO
	          },
	          [&](up<Struct>& struct_col) {},
	          [&](auto& arg) { FLS_UNREACHABLE_WITH_TYPE(arg) },
	      },
	      rowgroup[column_descriptor.idx]);

	if (should_be_cast) {
		rowgroup[column_descriptor.idx] = cast_visit(rowgroup, column_descriptor);
	}
}

void cast_check(rowgroup_pt& rowgroup, RowgroupDescriptorT& footer) {
	const auto n_col = rowgroup.size();

	// brute_force
	for (n_t col_idx {0}; col_idx < n_col; col_idx++) {
		auto& column_descriptor = footer.m_column_descriptors[col_idx];
		cast(rowgroup, *column_descriptor);
	}
}

void Rowgroup::Cast() {
	cast_check(internal_rowgroup, m_descriptor);
}

void Rowgroup::Init() {
	for (n_t col_idx {0}; col_idx < m_descriptor.m_size; col_idx++) {
		auto& column_descriptor = m_descriptor.m_column_descriptors[col_idx];
		column_descriptor->idx  = col_idx;
	}
}

void fill_in(col_pt& col, n_t how_many_to_fill) {

	visit(overloaded {
	          [&](up<FLSStrColumn>& string_col) {},
	          [&]<typename PT>(up<TypedCol<PT>>& typed_col) {
		          PT last_element = typed_col->data.back();
		          for (n_t val_idx {0}; val_idx < how_many_to_fill; val_idx++) {
			          typed_col->data.push_back(last_element);
		          }
	          },
	          [&](up<Struct>& struct_col) {},
	          [&](auto& arg) { FLS_UNREACHABLE_WITH_TYPE(arg) },
	      },
	      col);
}

void Rowgroup::FillMissingValues(const n_t how_many_to_fill) {
	const auto n_col = internal_rowgroup.size();

	// brute_force
	for (n_t col_idx {0}; col_idx < n_col; col_idx++) {
		fill_in(internal_rowgroup[col_idx], how_many_to_fill);
	}
}

/*--------------------------------------------------------------------------------------------------------------------*/
void cast_from_logical_to_physical(const Rowgroup& old_table, Rowgroup& new_table) {
	for (idx_t idx {0}; idx < old_table.ColCount(); ++idx) {
		std::visit( //
		    overloaded {
		        [](auto&, auto&) { throw std::runtime_error("Incompatible type"); },
		        [&]<typename LT, typename PT>(const up<TypedCol<LT>>& source_col, up<TypedCol<PT>>& target_col) {
			        if constexpr (is_numeric<LT>() && is_numeric<PT>()) {
				        for (const auto item : source_col->data) {
					        auto tmp = item;
					        target_col->data.push_back(static_cast<PT>(tmp));
				        }
			        }
		        }},
		    old_table.internal_rowgroup[idx],
		    new_table.internal_rowgroup[idx]);
	}
}

struct rowgroup_equality_visitor {
	template <typename PT>
	bool operator()(const up<TypedCol<PT>>& org_col, const up<TypedCol<PT>>& decoded_col) const {
		// FLS_ASSERT_E(org_col->data.size(), org_col->null_map_arr.size())
		for (idx_t idx {0}; idx < org_col->data.size(); ++idx) {
			const auto& original_val = org_col->data[idx];
			const auto& decoded_val  = decoded_col->data[idx];
			if (org_col->null_map_arr[idx]) {
				continue;
			}

			if (original_val != decoded_val) {
				return false;
			}
		}
		return true;
	}
	bool operator()(const up<Struct>& left, const up<Struct>& right) const {
		if (left->internal_rowgroup.size() != right->internal_rowgroup.size()) {
			return false;
		}

		for (idx_t col_idx {0}; col_idx < left->internal_rowgroup.size(); ++col_idx) {
			const auto result = visit(
			    rowgroup_equality_visitor {}, left->internal_rowgroup[col_idx], right->internal_rowgroup[col_idx]);

			if (result == false) {
				return false;
			}
		}
		return true;
	}

	bool operator()(const up<FLSStrColumn>& org_col, const up<FLSStrColumn>& decoded_col) const {
		if (org_col->length_arr.size() != decoded_col->length_arr.size()) {
			return false;
		}

		for (idx_t idx {0}; idx < org_col->length_arr.size(); ++idx) {
			if (org_col->null_map_arr[idx]) {
				continue;
			}
			const fls_string_t org_fls_string {org_col->str_p_arr[idx], org_col->length_arr[idx]};
			const fls_string_t decoded_fls_string {decoded_col->str_p_arr[idx], decoded_col->length_arr[idx]};

			if (org_fls_string != decoded_fls_string) {
				return false;
			}
		}
		return true;
	}

	bool operator()(const auto& arg1, const auto& arg2) const {
		FLS_UNREACHABLE_WITH_TYPES(arg1, arg2)
	}
};

RowgroupComparisonResult Rowgroup::operator==(const Rowgroup& other_rowgroup) const {
	RowgroupComparisonResult result {true, 0, 0, ""};
	if (this->n_tup != other_rowgroup.n_tup) {
		result.is_equal    = false;
		result.description = "number of values in the rowgroups does not match.";
		return result;
	}

	if (this->internal_rowgroup.size() != other_rowgroup.internal_rowgroup.size()) {
		result.is_equal    = false;
		result.description = "number of columns in the rowgroups does not match.";
		return result;
	}

	for (n_t col_idx {0}; col_idx < this->internal_rowgroup.size(); col_idx++) {
		const auto is_this_col_equal = visit(
		    rowgroup_equality_visitor {}, this->internal_rowgroup[col_idx], other_rowgroup.internal_rowgroup[col_idx]);
		if (is_this_col_equal == false) {
			result.is_equal                = false;
			result.first_failed_column_idx = col_idx;
			result.description = "the content of column with index" + std::to_string(col_idx) + "does not match.";
			return result;
		}
	}

	return result;
}

void Rowgroup::ReadCsv(const path& csv_path, char delimiter, char terminator) {

	/*Infer RowgroupDescriptor /TODO[FUTURE-WORK] */

	// Parse
	std::ifstream        csv_stream = FileSystem::open_r(csv_path.c_str());
	aria::csv::CsvParser parser     = aria::csv::CsvParser(csv_stream).delimiter(delimiter).terminator(terminator);

	for (auto& tuple : parser) {
		for (uint64_t col_idx {0}; auto& val : tuple) {
			[[maybe_unused]] const auto n_cols = ColCount();
			FLS_ASSERT_EQUALITY(tuple.size(), n_cols)
			col_pt& physical_column = internal_rowgroup[col_idx];
			Attribute::Ingest(physical_column, val, *m_descriptor.m_column_descriptors[col_idx]);
			col_idx = col_idx + 1;
		}
		n_tup = n_tup + 1;
	}

	FLS_ASSERT_ZERO(n_tup % CFG::VEC_SZ)
}

nlohmann::json to_json(const rowgroup_pt& columns, const ColumnDescriptors& footer);

nlohmann::json to_json(const col_pt& column, const ColumnDescriptorT& col_description) {
	return std::visit( //
	    overloaded {
	        [](const std::monostate&) {
		        // TODO [SKIP]
		        return nlohmann::json {};
	        },
	        [&]<typename T>(const up<TypedCol<T>>& typed_col) {
		        return nlohmann::json {{"nullmap", typed_col->null_map_arr}, //
		                               {"data", typed_col->data}};
	        },
	        [&](const up<List>& list_col) {
		        if (col_description.data_type == DataType::MAP) {
			        const auto& struct_col = std::get<up<Struct>>(list_col->child);
			        return nlohmann::json {{"nullmap", list_col->null_map_arr},
			                               {"offsets", list_col->ofs_arr},
			                               {"data", to_json(struct_col->internal_rowgroup, col_description.children)}};
		        }

		        return nlohmann::json {{"nullmap", list_col->null_map_arr},
		                               {"offsets", list_col->ofs_arr},
		                               {"data", to_json(list_col->child, **col_description.children.begin())}};
	        },
	        [&](const up<Struct>& struct_col) {
		        return nlohmann::json {{"nullmap", struct_col->null_map_arr},
		                               {"data", to_json(struct_col->internal_rowgroup, col_description.children)}};
	        },
	        [&](const auto&) {
		        return nlohmann::json {};
		        FLS_UNREACHABLE();
	        }},
	    column);
}

nlohmann::json to_json(const rowgroup_pt& columns, const ColumnDescriptors& footer) {
	nlohmann::json json_object;
	for (idx_t i = 0; i < footer.size(); ++i) {
		const auto& column                 = columns[i];
		const auto& col_description        = footer[i];
		json_object[col_description->name] = to_json(column, *col_description);
	}
	return json_object;
}

void Rowgroup::WriteJson(std::ostream& os) const {
	const auto json = to_json(internal_rowgroup, m_descriptor.m_column_descriptors);
	os << json;
}

n_t Rowgroup::RowCount() const {
	FLS_ASSERT_CORRECT_N(n_tup)
	return n_tup;
}

n_t Rowgroup::VecCount() const {
	return (n_tup + CFG::VEC_SZ - 1) / CFG::VEC_SZ;
}

n_t Rowgroup::ColCount() const {
	/**/
	return m_descriptor.m_column_descriptors.size();
}

/*--------------------------------------------------------------------------------------------------------------------*\
 * TypedColumnView
\*--------------------------------------------------------------------------------------------------------------------*/
template <typename PT>
TypedColumnView<PT>::TypedColumnView(const col_pt& column)
    : m_vec_idx(INVALID_N) {
	std::visit(overloaded {//
	                       [&](const up<TypedCol<PT>>& typed_col) {
		                       //
		                       m_data    = typed_col->data.data();
		                       m_stats_p = &typed_col->m_stats;
		                       n_vals    = typed_col->data.size();
		                       m_bools   = typed_col->null_map_arr.data();
		                       n_tuples  = typed_col->data.size();
	                       },
	                       [&](const std::monostate&) { FLS_UNREACHABLE() },
	                       [&](const auto& arg) {
		                       FLS_UNREACHABLE_WITH_TYPE(arg)
	                       }},
	           //
	           column);
}
template <typename PT>
const PT* TypedColumnView<PT>::Data() {
	FLS_ASSERT_CORRECT_IDX(m_vec_idx)

	return m_data + (m_vec_idx * CFG::VEC_SZ);
}

template <typename PT>
const PT* TypedColumnView<PT>::Data(n_t vec_idx) {
	FLS_ASSERT_CORRECT_IDX(vec_idx)

	return m_data + (vec_idx * CFG::VEC_SZ);
}

template <typename PT>
n_t TypedColumnView<PT>::TotalSize() const {
	return n_vals;
}

template <typename PT>
const uint8_t* TypedColumnView<PT>::NullMap() const {
	FLS_ASSERT_CORRECT_IDX(m_vec_idx)

	return m_bools + (m_vec_idx * CFG::VEC_SZ);
}

template <typename PT>
const n_t TypedColumnView<PT>::GetNTuples() const {
	return n_tuples;
}

template class TypedColumnView<i64_pt>;
template class TypedColumnView<i32_pt>;
template class TypedColumnView<i16_pt>;
template class TypedColumnView<i08_pt>;
template class TypedColumnView<u64_pt>;
template class TypedColumnView<u32_pt>;
template class TypedColumnView<u16_pt>;
template class TypedColumnView<u08_pt>;
template class TypedColumnView<dbl_pt>;
template class TypedColumnView<flt_pt>;

/*--------------------------------------------------------------------------------------------------------------------*\
 * NullMapView
\*--------------------------------------------------------------------------------------------------------------------*/

NullMapView::NullMapView(const col_pt& column) {
	std::visit(overloaded {
	               [&]<typename PT>(const up<TypedCol<PT>>& typed_col) { m_null_map = typed_col->null_map_arr.data(); },
	               [&](const up<FLSStrColumn>& fls_str_column) { m_null_map = fls_str_column->null_map_arr.data(); },
	               [&](const std::monostate&) { FLS_UNREACHABLE() },
	               [&](const auto& arg) {
		               FLS_UNREACHABLE_WITH_TYPE(arg)
	               }},
	           column);
}
const uint8_t* NullMapView::NullMap() const {
	FLS_ASSERT_CORRECT_IDX(m_vec_idx)

	return m_null_map + (m_vec_idx * CFG::VEC_SZ);
}
/*--------------------------------------------------------------------------------------------------------------------*\
 * FlsStrColumnView
\*--------------------------------------------------------------------------------------------------------------------*/
FlsStrColumnView::FlsStrColumnView(const col_pt& column)
    : vec_idx(INVALID_N)
    , stats([&]() -> FlsStringStats& {
	    return std::visit(overloaded {[&](const up<FLSStrColumn>& fls_str_column) -> FlsStringStats& {
		                                  string_p        = fls_str_column->str_p_arr.data();
		                                  n_tuples        = fls_str_column->length_arr.size();
		                                  length_ptr      = fls_str_column->length_arr.data();
		                                  fsst_string_p   = fls_str_column->fsst_str_p_arr.data();
		                                  fsst_length_ptr = fls_str_column->fsst_length_arr.data();
		                                  fls_string_p    = fls_str_column->fls_str_arr.data();

		                                  return fls_str_column->m_stats;
	                                  },
	                                  [&](const auto&) -> FlsStringStats& {
		                                  FLS_UNREACHABLE();
	                                  }},
	                      column);
    }()) {
}

uint8_t* FlsStrColumnView::Data() const {
	return string_p[vec_idx * CFG::VEC_SZ];
}

uint8_t** FlsStrColumnView::String_p() const {
	return &string_p[vec_idx * CFG::VEC_SZ];
}

len_t* FlsStrColumnView::Length() const {
	return length_ptr + (vec_idx * CFG::VEC_SZ);
}

uint8_t** FlsStrColumnView::FsstString() const {
	return &fsst_string_p[vec_idx * CFG::VEC_SZ];
}
len_t* FlsStrColumnView::FSSTLength() const {
	return fsst_length_ptr + (vec_idx * CFG::VEC_SZ);
}

fls_string_t* FlsStrColumnView::String() const {
	return fls_string_p + (vec_idx * CFG::VEC_SZ);
}

const n_t FlsStrColumnView::GetNTuples() const {
	return n_tuples;
}

void FlsStrColumnView::PointTo(const n_t a_vec_n) {
	this->vec_idx = a_vec_n;
}

} // namespace fastlanes