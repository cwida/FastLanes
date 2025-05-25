#include "fls/reader/json_reader.hpp"
#include "fls/common/assert.hpp"
#include "fls/connection.hpp"
#include "fls/io/file.hpp"
#include "fls/json/fls_json.hpp"
#include "fls/json/nlohmann/json.hpp"
#include "fls/table/attribute.hpp"
#include "fls/table/rowgroup.hpp"
#include "fls/table/table.hpp"

namespace fastlanes {

void parse_json_tuple(const nlohmann::json& json, rowgroup_pt& columns, const ColumnDescriptors& column_descriptor);

void parse_json_value(const nlohmann::json& json_value, col_pt& column, const ColumnDescriptorT& column_descriptor) {
	const bool is_null = json_value.is_null();

	visit(overloaded {
	          [](std::monostate&) { throw std::runtime_error("Unreachable"); },
	          [&](up<List>& list_column) {
		          list_column->null_map_arr.push_back(is_null);
		          auto& offsets = list_column->ofs_arr;
		          offsets.push_back(offsets.empty() ? 0 : offsets.back() + static_cast<ofs_t>(json_value.size()));
		          if (is_null) {
			          return;
		          }

		          if (column_descriptor.data_type == DataType::MAP) {
			          auto& struct_col = std::get<up<Struct>>(list_column->child);

			          for (auto& [key, value] : json_value.items()) {
				          const auto key_value_struct = nlohmann::json {{"key", key}, {"value", value}};
				          parse_json_tuple(key_value_struct, struct_col->internal_rowgroup, column_descriptor.children);
				          struct_col->null_map_arr.push_back(false);
			          }
			          return;
		          }

		          for (auto& child : json_value) {
			          parse_json_value(child, list_column->child, **column_descriptor.children.begin());
		          }
	          },
	          [&](up<Struct>& struct_col) {
		          struct_col->null_map_arr.push_back(is_null);
		          parse_json_tuple(json_value, struct_col->internal_rowgroup, column_descriptor.children);
	          },
	          [&](up<str_col_t>& typed_column) {
		          string val = json_value.dump();
		          Attribute::Ingest(column, val, column_descriptor); // FIXME
	          },
	          [&]<typename PT>(up<TypedCol<PT>>& typed_column) {
		          string val = json_value.dump();
		          Attribute::Ingest(column, val, column_descriptor); // FIXME
	          },
	          [&](up<FLSStrColumn>& typed_column) {
		          string val = json_value.dump();
		          Attribute::Ingest(column, val, column_descriptor); // FIXME
	          },
	          [&](auto&) {
		          FLS_UNREACHABLE();
	          }},
	      column);
}

void parse_json_tuple(const nlohmann::json& json, rowgroup_pt& columns, const ColumnDescriptors& column_descriptor) {
	for (idx_t i = 0; i < column_descriptor.size(); ++i) {
		const auto& col_description = column_descriptor[i];

		const nlohmann::json* value;
		if (!json.contains(col_description->name)) {
			value = nullptr;
		} else {
			value = &json[col_description->name];
		}
		parse_json_value(value == nullptr ? nlohmann::json() : *value, columns[i], *col_description);
	}
}

up<Table> JsonReader::Read(const path& dir_path, const Connection& connection) {
	auto table = make_unique<Table>(connection);
	bool is_schema_found {false};
	bool is_file_found {false};
	path found_jsonl_path;
	path found_schema_path;

	for (const auto& entry : std::filesystem::directory_iterator(dir_path)) {
		const auto& file_path     = entry.path();
		auto        file_path_str = file_path.string();
		if (const auto schema_path = file_path_str.find(SCHEMA_FILE_NAME); schema_path != std::string::npos) {
			is_schema_found   = true;
			found_schema_path = file_path;
		}

		if (const auto schema_path = file_path.string().find(".jsonl"); schema_path != std::string::npos) {
			is_file_found    = true;
			found_jsonl_path = file_path;
		}
	}

	if (!is_schema_found) {
		throw std::runtime_error("schema is not found!");
	}
	if (!is_file_found) {
		throw std::runtime_error("jsonl file is not found!");
	}

	auto                 json_string         = File::read(found_schema_path);
	const nlohmann::json j                   = nlohmann::json::parse(json_string);
	auto                 rowgroup_descriptor = j.get<RowgroupDescriptorT>();

	std::ifstream jsonl_stream = FileSystem::open_r(found_jsonl_path.c_str());
	string        line;

	n_t  n_tup {0};
	auto cur_rowgroup = make_unique<Rowgroup>(rowgroup_descriptor, connection);
	while (getline(jsonl_stream, line)) {
		const auto tuple = nlohmann::json::parse(line);
		parse_json_tuple(tuple, cur_rowgroup->internal_rowgroup, rowgroup_descriptor.m_column_descriptors);
		n_tup = n_tup + 1;

		if (n_tup == cur_rowgroup->capacity) {
			cur_rowgroup->n_tup = n_tup;
			table->m_rowgroups.push_back(std::move(cur_rowgroup));
			cur_rowgroup = make_unique<Rowgroup>(rowgroup_descriptor, connection);
			n_tup        = 0;
		}
	}

	if (n_tup != 0) {
		cur_rowgroup->n_tup = n_tup;
		table->m_rowgroups.push_back(std::move(cur_rowgroup));
	}

	return table;
};
} // namespace fastlanes