#include "fls/table/rowgroup.hpp"
#include "fls/common/magic_enum.hpp"
#include "fls/cor/eng/decompressor.hpp"
#include "fls/csv/csv-parser/parser.hpp"
#include "fls/encoder/col_encoder.hpp"
#include "fls/expression/data_type.hpp"
#include "fls/json/nlohmann/json.hpp"
#include "fls/table/attribute.hpp"
#include "fls/table/chunk.hpp"
#include "fls/table/vector.hpp"

namespace fastlanes {

void init_logial_columns(const col_descriptions_t& schema, rowgroup_pt& columns);

// TODO [COPY] All return values here are copied to be put inside col_t variant. They should be moved.
col_pt init_logial_columns(const ColDescription& col_description) {
	switch (static_cast<DataType>(col_description.type)) {
	case DataType::LIST: {
		auto uped_list   = make_unique<List>();
		uped_list->child = init_logial_columns(*col_description.children.begin());
		return uped_list;
	}
	case DataType::STRUCT: {
		auto uped_struct = make_unique<Struct>();
		init_logial_columns(col_description.children, uped_struct->table);
		return uped_struct;
	}
	case DataType::MAP: {
		// MAP(KEY, VALUE) = LIST(STRUCT(KEY, VALUE))
		auto uped_struct = make_unique<Struct>();
		init_logial_columns(col_description.children, uped_struct->table);

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
		return make_unique<i08_col_t>();
	case DataType::INT16:
		return make_unique<i16_col_t>();
	case DataType::INT32:
		return make_unique<i32_col_t>();
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
	default:
		FLS_UNREACHABLE();
	}

	FLS_UNREACHABLE();
	return col_pt {};
}

void init_logial_columns(const col_descriptions_t& schema, rowgroup_pt& columns) {
	columns.reserve(schema.size());
	for (const auto& col_description : schema) {
		columns.emplace_back(init_logial_columns(col_description));
	}
}

Rowgroup::Rowgroup(const Schema& schema) // NOLINT
    : m_schema(schema)
    , n_tup(0)
    , internal_rowgroup {} {
	init_logial_columns(schema.col_descriptions(), internal_rowgroup);
}

DataType Rowgroup::GetDataType(const idx_t col_idx) const {
	/**/
	return m_schema[col_idx].type;
}

Schema& Rowgroup::GetSchema() {
	/**/
	return m_schema;
}

up<Rowgroup> Rowgroup::Project(const vector<idx_t>& idxs) {
	/**/
	auto  result = make_unique<Rowgroup>(*m_schema.Project(idxs));
	idx_t c      = {0};
	for (const auto idx : idxs) {
		result->internal_rowgroup[c++] = std::move(internal_rowgroup[idx]);
	}
	result->n_tup = n_tup;
	return result;
}

up<Rowgroup> Rowgroup::Project(const vector<string>& col_names) {
	vector<idx_t> idxs;
	for (const auto& col_name : col_names) {
		idxs.push_back(m_schema.LookUp(col_name));
	}

	return Project(idxs);
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

			if (tuple_1 != tuple_2) { return false; }
		}
		return true;
	}

	bool operator()(std::monostate&, std::monostate&) {
		FLS_UNREACHABLE();
		return false;
	}

	bool operator()(auto&, auto&) { return false; }
};

bool col_equality_visit(const col_pt& first_col, const col_pt& second_col) {
	return visit(col_equality_visitor {}, first_col, second_col);
}

bool Rowgroup::Equal(const n_t first_col_idx, const n_t second_col_idx) const {

	const auto& first_col  = internal_rowgroup[first_col_idx];
	const auto& second_col = internal_rowgroup[second_col_idx];

	if (first_col.index() != second_col.index()) { return false; }

	if (!col_equality_visit(first_col, second_col)) { return false; }

	return true;
}

/*--------------------------------------------------------------------------------------------------------------------*/
struct col_map_1t1_visitor {
	template <typename FIRST_PT, typename SECOND_PT>
	bool operator()(const up<TypedCol<FIRST_PT>>& col_1, const up<TypedCol<SECOND_PT>>& col_2) {
		unordered_map<FIRST_PT, SECOND_PT> hash_map;
		for (n_t tup_idx {0}; tup_idx < col_1->data.size(); ++tup_idx) {
			const auto& tuple1 = col_1->data[tup_idx];
			const auto& tuple2 = col_2->data[tup_idx];

			if (hash_map.contains(tuple1)) {
				const auto& pair = hash_map.find(tuple1);
				if (pair->second != tuple2) { return false; }
			} else {
				hash_map.emplace(tuple1, tuple2);
			}
		}
		return true;
	}

	bool operator()(std::monostate&, std::monostate&) {
		FLS_UNREACHABLE();
		return false;
	}

	bool operator()(auto&, auto&) { return false; }
};

bool map_1t1_visit(const col_pt& col_1, const col_pt& col_2) { return visit(col_map_1t1_visitor {}, col_1, col_2); }

bool Rowgroup::IsMap1t1(const n_t first_col_idx, const n_t second_col_idx) const {
	return map_1t1_visit(internal_rowgroup[first_col_idx], internal_rowgroup[second_col_idx]);
}

/*--------------------------------------------------------------------------------------------------------------------*/
bool Rowgroup::is_good_for_ditionary_encoding(const n_t col_idx) const {

	constexpr double UNIQUENESS_RATIO_FOR_DICTIONARY_ENCODING = 0.25; // todo[UNIQUENESS_RATIO_FOR_DICTIONARY_ENCODING]

	const auto& col = internal_rowgroup[col_idx];
	return visit(overloaded {//
	                         [](std::monostate&) {
		                         FLS_UNREACHABLE();
		                         return false;
	                         },
	                         [&]<typename PT>(const up<TypedCol<PT>>& typed_col) {
		                         // calculate the uniqness based on n_run
		                         const auto tmp_n_tup       = this->RowCount();
		                         const auto n_unique_values = typed_col->m_stats.dict.size();
		                         const auto uniqness_ratio =
		                             static_cast<double>(n_unique_values) / static_cast<double>(tmp_n_tup);

		                         if (uniqness_ratio > UNIQUENESS_RATIO_FOR_DICTIONARY_ENCODING) { return false; }

		                         return true;
	                         },
	                         [](auto&) {
		                         return false;
	                         }},
	             col);
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

void Rowgroup::ReadCsv(const path& csv_path, char delimiter, char terminator) {

	/*Infer Schema /TODO[FUTURE-WORK] */

	// Parse
	std::ifstream        csv_stream = FileSystem::open_r(csv_path.c_str());
	aria::csv::CsvParser parser     = aria::csv::CsvParser(csv_stream).delimiter(delimiter).terminator(terminator);

	for (auto& tuple : parser) {
		for (uint64_t col_c {0}; auto& val : tuple) {
			FLS_ASSERT_EQUALITY(tuple.size(), ColCount())

			col_pt& column = internal_rowgroup[col_c];
			visit(overloaded {//
			                  [&]<typename PT>(up<TypedCol<PT>>& typed_column) {
				                  /**/
				                  Attribute<PT>::Ingest(*typed_column, val);
			                  },
			                  [](std::monostate&) {
				                  /**/
				                  FLS_UNREACHABLE();
			                  },
			                  [](auto&) {
				                  FLS_UNREACHABLE();
			                  }},
			      column);
			col_c = col_c + 1;
		}
		n_tup = n_tup + 1;
	}
}

void parse_json_tuple(const nlohmann::json& json, rowgroup_pt& columns, const col_descriptions_t& schema);

void parse_json_value(const nlohmann::json& json_value, col_pt& column, const ColDescription& col_description) {
	const bool is_null = json_value.is_null();

	visit(overloaded {
	          [](std::monostate&) { throw std::runtime_error("Unreachable"); },
	          [&](up<List>& list_column) {
		          list_column->null_map_arr.push_back(is_null);
		          auto& offsets = list_column->ofs_arr;
		          offsets.push_back((offsets.empty() ? 0 : offsets.back()) + json_value.size());
		          if (is_null) { return; }

		          if (col_description.type == DataType::MAP) {
			          auto& struct_col = std::get<up<Struct>>(list_column->child);

			          for (auto& [key, value] : json_value.items()) {
				          const auto key_value_struct = nlohmann::json {{"key", key}, {"value", value}};
				          parse_json_tuple(key_value_struct, struct_col->table, col_description.children);
				          struct_col->null_map_arr.push_back(false);
			          }
			          return;
		          }

		          for (auto& child : json_value) {
			          parse_json_value(child, list_column->child, *col_description.children.begin());
		          }
	          },
	          [&](up<Struct>& struct_col) {
		          struct_col->null_map_arr.push_back(is_null);
		          parse_json_tuple(json_value, struct_col->table, col_description.children);
	          },
	          [&](up<str_col_t>& typed_column) {
		          typed_column->null_map_arr.push_back(is_null);
		          typed_column->data.push_back(is_null ? Attribute<str_pt>::Null() : json_value.dump());
	          },
	          [&]<typename T>(up<TypedCol<T>>& typed_column) {
		          typed_column->null_map_arr.push_back(is_null);
		          typed_column->data.push_back(is_null ? Attribute<T>::Null() : json_value.get<T>());
	          } //
	      },
	      column);
}

void parse_json_tuple(const nlohmann::json& json, rowgroup_pt& columns, const col_descriptions_t& schema) {
	for (idx_t i = 0; i < schema.size(); ++i) {
		const auto& col_description = schema[i];

		const nlohmann::json* value;
		if (!json.contains(col_description.name)) {
			value = nullptr;
		} else {
			value = &json[col_description.name];
		}
		parse_json_value(value == nullptr ? nlohmann::json() : *value, columns[i], col_description);
	}
}

void Rowgroup::ReadJson(const path& json_path) {
	std::ifstream json_stream = FileSystem::open_r(json_path.c_str());
	string        line;
	while (getline(json_stream, line)) {
		const auto tuple = nlohmann::json::parse(line);
		parse_json_tuple(tuple, internal_rowgroup, m_schema.col_descriptions());
		n_tup = n_tup + 1;
	}
}

nlohmann::json to_json(const rowgroup_pt& columns, const col_descriptions_t& schema);

nlohmann::json to_json(const col_pt& column, const ColDescription& col_description) {
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
		        if (col_description.type == DataType::MAP) {
			        const auto& struct_col = std::get<up<Struct>>(list_col->child);
			        return nlohmann::json {{"nullmap", list_col->null_map_arr},
			                               {"offsets", list_col->ofs_arr},
			                               {"data", to_json(struct_col->table, col_description.children)}};
		        }

		        return nlohmann::json {{"nullmap", list_col->null_map_arr},
		                               {"offsets", list_col->ofs_arr},
		                               {"data", to_json(list_col->child, *col_description.children.begin())}};
	        },
	        [&](const up<Struct>& struct_col) {
		        return nlohmann::json {{"nullmap", struct_col->null_map_arr},
		                               {"data", to_json(struct_col->table, col_description.children)}};
	        },
	    },
	    column);
}

nlohmann::json to_json(const rowgroup_pt& columns, const col_descriptions_t& schema) {
	nlohmann::json json_object;
	for (idx_t i = 0; i < schema.size(); ++i) {
		const auto& column                = columns[i];
		const auto& col_description       = schema[i];
		json_object[col_description.name] = to_json(column, col_description);
	}
	return json_object;
}

void Rowgroup::WriteJson(std::ostream& os) const {
	const auto json = to_json(internal_rowgroup, m_schema.col_descriptions());
	os << json;
}

n_t Rowgroup::RowCount() const {
	FLS_ASSERT_CORRECT_N(n_tup)
	return n_tup;
}

n_t Rowgroup::VecCount() const {
	//
	return n_tup / CFG::VEC_SZ;
}

n_t Rowgroup::ColCount() const {
	/**/
	return m_schema.size();
}

idx_t Rowgroup::LookUp(const string& name) const {
	/**/
	return m_schema.LookUp(name);
}
} // namespace fastlanes