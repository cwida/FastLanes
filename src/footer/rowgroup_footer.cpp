#include "fls/footer/rowgroup_footer.hpp"
#include "fls/cfg/cfg.hpp"
#include "fls/common/assert.hpp"
#include "fls/common/magic_enum.hpp"
#include "fls/io/file.hpp"
#include "fls/json/fls_json.hpp"
#include "fls/json/nlohmann/json.hpp"
#include "fls/table/rowgroup.hpp"

namespace fastlanes {
void Footer::AddCol(const ColumnDescriptor& col) {
	/**/
	m_column_descriptors.push_back(col);
}

n_t Footer::GetNextColIdx() const {
	/**/
	return static_cast<idx_t>(m_column_descriptors.size());
}

map Footer::GetMap() const {
	/**/
	return m_name_idx_map;
}

idx_t Footer::LookUp(const string& name) const {
	const auto it = m_name_idx_map.find(name);
	if (it == m_name_idx_map.end()) {
		throw std::runtime_error("name does not exist in the schema");
	}

	return it->second;
}

up<Footer> Footer::Project(const vector<idx_t>& idxs) const {
	auto footer = make_unique<Footer>();

	idx_t new_idx {0};
	for (const auto idx : idxs) {
		if (idx >= m_column_descriptors.size()) {
			throw std::runtime_error("column index out of range");
		}
		// new description
		auto descriptor = m_column_descriptors[idx];
		descriptor.idx  = new_idx;
		footer->m_column_descriptors.push_back(descriptor);
		// new mapping
		footer->m_name_idx_map.emplace(m_column_descriptors[idx].name, new_idx);

		new_idx++;
	}

	return footer;
}

const_col_descripption_it Footer::end() const {
	/**/
	return this->m_column_descriptors.end();
}

col_descripption_it Footer::end() {
	/**/
	return this->m_column_descriptors.end();
}

const_col_descripption_it Footer::begin() const {
	/**/
	return this->m_column_descriptors.begin();
}

col_descripption_it Footer::begin() {
	/**/
	return this->m_column_descriptors.begin();
}

const ColumnDescriptor& Footer::operator[](const n_t idx) const {
	FLS_ASSERT_L(idx, m_column_descriptors.size());

	return m_column_descriptors[idx];
}

Footer::Footer()
    : m_n_vec(0)
    , m_rowgroup_size {0} {};

n_t GetNVector(const n_t n_tup) {
	return static_cast<n_t>(ceil(static_cast<double>(n_tup) / static_cast<double>(CFG::VEC_SZ)));
}

void Footer::push_back(ColumnDescriptor&& scheme) {
	/**/
	m_column_descriptors.push_back(scheme);
}

vector<string> Footer::GetColumnNames() const {
	vector<string> column_names;
	for (const auto& col_descriptor : m_column_descriptors) {
		column_names.push_back(col_descriptor.name);
	}

	return column_names;
}

vector<DataType> Footer::GetDataTypes() const {
	vector<DataType> column_data_types;
	for (const auto& col_descriptor : m_column_descriptors) {
		column_data_types.push_back(col_descriptor.data_type);
	}

	return column_data_types;
}

n_t Footer::GetNVectors() const {
	return m_n_vec;
}

void set_index(ColumnDescriptors& column_descriptors) {
	for (n_t col_idx = 0; col_idx < column_descriptors.size(); ++col_idx) {
		auto& column_descriptor = column_descriptors[col_idx];
		column_descriptor.idx   = col_idx;
		if (!column_descriptor.children.empty()) {
			set_index(column_descriptor.children);
		}
	}
}

up<Footer> make_footer(const Rowgroup& rowgroup) {
	auto footer = make_unique<Footer>(rowgroup.m_footer);

	// set the right col idx as it is ALWAYS not schema.json
	set_index(footer->m_column_descriptors);

	// set the num of vecs
	footer->m_n_vec = rowgroup.VecCount();

	return footer;
}

up<Footer> make_footer(const path& dir_path) {
	auto                 json_string     = File::read(dir_path);
	const nlohmann::json j               = nlohmann::json::parse(json_string);
	auto                 rowgroup_footer = j.get<Footer>();
	return make_unique<Footer>(rowgroup_footer);
}

ColumnDescriptor& Footer::operator[](const n_t idx) {
	return m_column_descriptors[idx];
}

n_t Footer::size() const {
	return m_column_descriptors.size();
}

} // namespace fastlanes
