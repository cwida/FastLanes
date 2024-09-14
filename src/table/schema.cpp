#include "fls/table/schema.hpp"
#include "fls/common/assert.hpp"
#include "fls/common/magic_enum.hpp"
#include "fls/io/file.hpp"
#include "fls/json/nlohmann/json.hpp"
#include "fls/printer/output.hpp"
#include "fls/printer/output_factory.hpp"

namespace fastlanes {

DataType TypeLookUp(const std::string& str) {
	static std::unordered_map<std::string, DataType> const TABLE {
	    {"bigint", DataType::INT64},       //
	    {"BIGINT", DataType::INT64},       //
	    {"string", DataType::STR},         //
	    {"varchar", DataType::STR},        //
	    {"VARCHAR", DataType::STR},        //
	    {"double", DataType::DOUBLE},      //
	    {"DOUBLE", DataType::DOUBLE},      //
	    {"list", DataType::LIST},          //
	    {"struct", DataType::STRUCT},      //
	    {"map", DataType::MAP},            //
	    {"integer", DataType::INT64},      // TODO [TYPE] INT32
	    {"smallint", DataType::INT64},     // TODO [TYPE] INT16
	    {"UINT32", DataType::INT64},       // TODO [TYPE] UINT32
	    {"UINT8", DataType::INT64},        // TODO [TYPE] UINT8
	    {"float", DataType::DOUBLE},       // TODO [TYPE] FLOAT
	    {"boolean", DataType::FALLBACK},   // TODO [TYPE] BOOLEAN
	    {"BOOLEAN", DataType::FALLBACK},   // TODO [TYPE] BOOLEAN
	    {"TIMESTAMP", DataType::FALLBACK}, // TODO [TYPE] Handle as numeric
	    {"timestamp", DataType::FALLBACK}, // TODO [TYPE] Handle as numeric
	    {"skip", DataType::FALLBACK},      //
	    {"json", DataType::FALLBACK},      //
	    {"date", DataType::FALLBACK},      // TODO [TYPE] Handle as numeric
	    {"Date", DataType::FALLBACK},      //
	    {"DATE", DataType::FALLBACK},      //
	    {"SMALLINT", DataType::INT64},     // clickhouse types
	    {"INTEGER", DataType::INT64},      // clickhouse types
	    {"VARCHAR(255)", DataType::STR},   // clickhouse types
	    {"CHAR", DataType::STR},           // clickhouse types
	    {"TEXT", DataType::STR}            //
	};                                     // clickhouse types

	const auto it = TABLE.find(str);
	if (it == TABLE.end()) { throw std::runtime_error("type " + str + " not found"); }

	return it->second;
}

void read_schema(const nlohmann::json& columns_node, col_descriptions_t& columns, map& name_idx_map) {
	for (size_t i {0}; i < columns_node.size(); ++i) {
		const auto&        column_node = columns_node[i];
		const std::string& column_name = column_node.at("name");
		const std::string& column_type = column_node.at("type");
		const auto&        type        = TypeLookUp(column_type);

		name_idx_map.emplace(column_name, i);
		auto& col_description = columns.emplace_back(i, column_name, type);
		if (type == DataType::LIST || type == DataType::STRUCT || type == DataType::MAP) {
			read_schema(column_node.at("children"), col_description.children, col_description.name_idx_map);
		}
	}
}

Schema::Schema(const path& schema_json_file) {
	/**/
	const auto schema_dump = File::read(schema_json_file);
	parse_json_text(schema_dump);
}
Schema::Schema(const string& json_dump) {
	/**/
	parse_json_text(json_dump);
}

void Schema::AddCol(const ColDescription& col) {
	/**/
	m_col_descriptions.push_back(col);
}

idx_t Schema::GetNextColIdx() const {
	/**/
	return static_cast<idx_t>(m_col_descriptions.size());
}

sz_t Schema::size() const {
	/**/
	return m_col_descriptions.size();
}

map Schema::GetMap() const {
	/**/
	return m_name_idx_map;
}

idx_t Schema::LookUp(const string& name) const {
	const auto it = m_name_idx_map.find(name);
	if (it == m_name_idx_map.end()) { throw std::runtime_error("name does not exist in the schema"); }

	return it->second;
}

up<Schema> Schema::Project(const vector<idx_t>& idxs) const {
	auto new_schema = make_unique<Schema>();

	idx_t new_idx {0};
	for (const auto idx : idxs) {
		// new description
		auto new_descrption = m_col_descriptions[idx];
		new_descrption.idx  = new_idx;
		new_schema->m_col_descriptions.push_back(new_descrption);
		// new mapping
		new_schema->m_name_idx_map.emplace(m_col_descriptions[idx].name, new_idx);

		new_idx++;
	}

	return new_schema;
}

void Schema::parse_json_text(const string& json_text) {
	const auto schema = nlohmann::json::parse(json_text);
	read_schema(schema.at("columns"), m_col_descriptions, m_name_idx_map);
}

const_col_descripption_it Schema::end() const {
	/**/
	return this->m_col_descriptions.end();
}

col_descripption_it Schema::end() {
	/**/
	return this->m_col_descriptions.end();
}

const_col_descripption_it Schema::begin() const {
	/**/
	return this->m_col_descriptions.begin();
}

col_descripption_it Schema::begin() {
	/**/
	return this->m_col_descriptions.begin();
}

const ColDescription& Schema::operator[](idx_t idx) const {
	FLS_ASSERT_L(idx, m_col_descriptions.size());

	return m_col_descriptions[idx];
}

Schema::Schema(const col_descriptions_t& col_descriptions) {
	for (auto& col_description : col_descriptions) {
		m_col_descriptions.push_back(col_description);
		m_name_idx_map.emplace(col_description.name, col_description.idx);
	}
}

} // namespace fastlanes
