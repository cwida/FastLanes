#include "fls/footer/rowgroup_descriptor.hpp"
#include "fls/cfg/cfg.hpp"
#include "fls/common/assert.hpp"
#include "fls/common/magic_enum.hpp"
#include "fls/io/file.hpp"
#include "fls/json/fls_json.hpp"
#include "fls/json/nlohmann/json.hpp"
#include "fls/table/rowgroup.hpp"

namespace fastlanes {

n_t RowgroupDescriptor::GetNextColIdx() const {
	/**/
	return static_cast<idx_t>(m_column_descriptors.size());
}

map RowgroupDescriptor::GetMap() const {
	/**/
	return m_name_idx_map;
}

idx_t RowgroupDescriptor::LookUp(const string& name) const {
	const auto it = m_name_idx_map.find(name);
	if (it == m_name_idx_map.end()) {
		throw std::runtime_error("name does not exist in the schema");
	}

	return it->second;
}

up<RowgroupDescriptor> RowgroupDescriptor::Project(const vector<idx_t>& idxs) const {
	auto footer = make_unique<RowgroupDescriptor>();

	idx_t new_idx = 0;
	for (idx_t idx : idxs) {
		if (idx >= m_column_descriptors.size()) {
			throw std::runtime_error("column index out of range");
		}

		// clone the original descriptor, then adjust its idx
		const auto& orig  = m_column_descriptors[idx];
		auto        clone = std::make_unique<ColumnDescriptorT>(*orig);
		clone->idx        = new_idx;

		// add to footer’s vectors
		footer->m_column_descriptors.push_back(std::move(clone));
		footer->m_name_idx_map.emplace(orig->name, new_idx);

		++new_idx;
	}

	return footer;
}

const_col_description_it RowgroupDescriptor::end() const {
	/**/
	return this->m_column_descriptors.end();
}

col_description_it RowgroupDescriptor::end() {
	/**/
	return this->m_column_descriptors.end();
}

const_col_description_it RowgroupDescriptor::begin() const {
	/**/
	return this->m_column_descriptors.begin();
}

col_description_it RowgroupDescriptor::begin() {
	/**/
	return this->m_column_descriptors.begin();
}

const ColumnDescriptorT& RowgroupDescriptor::operator[](const n_t idx) const {
	FLS_ASSERT_L(idx, m_column_descriptors.size());

	return *m_column_descriptors[idx];
}

RowgroupDescriptor::RowgroupDescriptor(const RowgroupDescriptor& o)
    : m_n_vec(o.m_n_vec)
    , m_column_descriptors {} // we’ll fill these in the body
    , m_name_idx_map(o.m_name_idx_map)
    , m_size(o.m_size)
    , m_offset(o.m_offset)
    , m_n_tuples(o.m_n_tuples) {
	m_column_descriptors.reserve(o.m_column_descriptors.size());
	for (auto const& up : o.m_column_descriptors) {
		m_column_descriptors.emplace_back(std::make_unique<ColumnDescriptorT>(*up));
	}
}

RowgroupDescriptor::RowgroupDescriptor()
    : m_n_vec(0)
    , m_column_descriptors {}
    , m_size {0}
    , m_n_tuples {0} {};

n_t GetNVector(const n_t n_tup) {
	return static_cast<n_t>(ceil(static_cast<double>(n_tup) / static_cast<double>(CFG::VEC_SZ)));
}

void RowgroupDescriptor::push_back(ColumnDescriptorT&& scheme) {
	/**/
	m_column_descriptors.push_back(make_unique<ColumnDescriptorT>(scheme));
}

vector<string> RowgroupDescriptor::GetColumnNames() const {
	vector<string> column_names;
	for (const auto& col_descriptor : m_column_descriptors) {
		column_names.push_back(col_descriptor->name);
	}

	return column_names;
}

vector<DataType> RowgroupDescriptor::GetDataTypes() const {
	vector<DataType> column_data_types;
	for (const auto& col_descriptor : m_column_descriptors) {
		column_data_types.push_back(col_descriptor->data_type);
	}

	return column_data_types;
}

n_t RowgroupDescriptor::GetNVectors() const {
	return m_n_vec;
}

void set_index(vector<up<ColumnDescriptorT>>& column_descriptors) {
	for (n_t col_idx = 0; col_idx < column_descriptors.size(); ++col_idx) {
		auto& column_descriptor = column_descriptors[col_idx];
		column_descriptor->idx  = col_idx;
		if (!column_descriptor->children.empty()) {
			set_index(column_descriptor->children);
		}
	}
}

up<RowgroupDescriptor> make_rowgroup_descriptor(const Rowgroup& rowgroup) {
	auto rowgroup_descriptor = make_unique<RowgroupDescriptor>(rowgroup.m_descriptor);

	// set the right col idx as it is ALWAYS not schema.json
	set_index(rowgroup_descriptor->m_column_descriptors);

	// set the num of vecs
	rowgroup_descriptor->m_n_vec    = rowgroup.VecCount();
	rowgroup_descriptor->m_n_tuples = rowgroup.n_tup;

	return rowgroup_descriptor;
}

up<RowgroupDescriptor> make_rowgroup_descriptor(const path& dir_path) {
	auto                 json_string     = File::read(dir_path);
	const nlohmann::json j               = nlohmann::json::parse(json_string);
	auto                 rowgroup_footer = j.get<RowgroupDescriptor>();
	return make_unique<RowgroupDescriptor>(rowgroup_footer);
}

ColumnDescriptorT& RowgroupDescriptor::operator[](const n_t idx) {
	return *m_column_descriptors[idx];
}

n_t RowgroupDescriptor::size() const {
	return m_column_descriptors.size();
}

} // namespace fastlanes
