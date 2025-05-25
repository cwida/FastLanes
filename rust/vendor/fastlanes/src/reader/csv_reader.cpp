#include "fls/reader/csv_reader.hpp"
#include "fls/common/assert.hpp"
#include "fls/connection.hpp"
#include "fls/csv/csv-parser/parser.hpp"
#include "fls/io/file.hpp"
#include "fls/json/fls_json.hpp"
#include "fls/json/nlohmann/json.hpp"
#include "fls/table/attribute.hpp"
#include "fls/table/rowgroup.hpp"
#include "fls/table/table.hpp"

namespace fastlanes {

up<Table> CsvReader::Read(const path& dir_path, const Connection& connection) {
	auto table = make_unique<Table>(connection);
	bool is_schema_found {false};
	bool is_file_found {false};
	path found_csv_path;
	path found_schema_path;

	for (const auto& entry : std::filesystem::directory_iterator(dir_path)) {
		const auto& file_path     = entry.path();
		auto        file_path_str = file_path.string();
		if (const auto schema_path = file_path_str.find(SCHEMA_FILE_NAME); schema_path != std::string::npos) {
			is_schema_found   = true;
			found_schema_path = file_path;
		}

		if (const auto schema_path = file_path.string().find(".csv"); schema_path != std::string::npos) {
			is_file_found  = true;
			found_csv_path = file_path;
		}
	}

	if (!is_schema_found) {
		throw std::runtime_error("schema is not found!");
	}
	if (!is_file_found) {
		throw std::runtime_error("csv file is not found!");
	}

	auto                 json_string         = File::read(found_schema_path);
	const nlohmann::json j                   = nlohmann::json::parse(json_string);
	auto                 rowgroup_descriptor = j.get<RowgroupDescriptorT>();
	set_index(rowgroup_descriptor.m_column_descriptors);

	char delimiter  = '|';
	char terminator = '\n';

	// Parse
	std::ifstream        csv_stream = FileSystem::open_r(found_csv_path.c_str());
	aria::csv::CsvParser parser     = aria::csv::CsvParser(csv_stream).delimiter(delimiter).terminator(terminator);

	n_t  n_tup {0};
	auto cur_rowgroup = make_unique<Rowgroup>(rowgroup_descriptor, connection);
	for (auto& tuple : parser) {
		for (uint64_t col_idx {0}; auto& val : tuple) {
			[[maybe_unused]] const auto n_cols = cur_rowgroup->ColCount();
			FLS_ASSERT_EQUALITY(tuple.size(), n_cols)
			col_pt& physical_column = cur_rowgroup->internal_rowgroup[col_idx];
			Attribute::Ingest(physical_column, val, *cur_rowgroup->m_descriptor.m_column_descriptors[col_idx]);
			col_idx = col_idx + 1;
		}
		n_tup = n_tup + 1;

		if (n_tup == cur_rowgroup->capacity) {
			cur_rowgroup->n_tup = n_tup;
			table->m_rowgroups.push_back(std::move(cur_rowgroup));
			cur_rowgroup = make_unique<Rowgroup>(rowgroup_descriptor, connection);
			n_tup        = 0;
		}
	}
	if (n_tup != 0) {
		const n_t leftover = n_tup % CFG::VEC_SZ;
		if (leftover != 0) {
			n_t how_many_to_fill = CFG::VEC_SZ - leftover;
			cur_rowgroup->FillMissingValues(how_many_to_fill);
		}
		cur_rowgroup->n_tup = n_tup;
		table->m_rowgroups.push_back(std::move(cur_rowgroup));
	}

	return table;
};
} // namespace fastlanes