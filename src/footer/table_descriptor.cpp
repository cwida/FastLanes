#include "fls/footer/table_descriptor.hpp"
#include "fls/io/file.hpp"
#include "fls/json/fls_json.hpp"
#include "fls/json/nlohmann/json.hpp"
#include "fls/table/table.hpp"
#include <fls/connection.hpp>

namespace fastlanes {

// TableDescriptor::TableDescriptor()
//     : m_table_binary_size {0} {
// }
//
// // Deep-copy: clone each RowgroupDescriptor via its copy-ctor
// TableDescriptor::TableDescriptor(const TableDescriptor& o)
//     : m_rowgroup_descriptors {} // start empty
//     , m_table_binary_size(o.m_table_binary_size) {
// 	m_rowgroup_descriptors.reserve(o.m_rowgroup_descriptors.size());
// 	for (auto const& up_rg : o.m_rowgroup_descriptors) {
// 		// invoke RowgroupDescriptor’s own copy-ctor
// 		m_rowgroup_descriptors.emplace_back(std::make_unique<RowgroupDescriptorT>(*up_rg));
// 	}
// }
//
// n_t TableDescriptor::GetNRowgroups() const {
// 	return m_rowgroup_descriptors.size();
// }

// FIX ME
up<TableDescriptorT> make_table_descriptor(const Table& table) {
	auto table_descriptor = make_unique<TableDescriptorT>();

	for (n_t rowgroup_idx = 0; rowgroup_idx < table.get_n_rowgroups(); ++rowgroup_idx) {
		table_descriptor->m_rowgroup_descriptors.push_back(make_rowgroup_descriptor(*table.m_rowgroups[rowgroup_idx]));
	}
	table_descriptor->m_table_binary_size = 0;

	return table_descriptor;
}

up<TableDescriptorT> make_table_descriptor(const path& dir_path) {
	auto                 json_string      = File::read(dir_path);
	const nlohmann::json j                = nlohmann::json::parse(json_string);
	auto                 table_descriptor = j.get<TableDescriptorT>();
	return make_unique<TableDescriptorT>(table_descriptor);
}

up<TableDescriptorT> make_table_descriptor(const path& file_path, n_t offset, n_t size) {
	File file(file_path);
	Buf  buf; // OPTIMIZE ME
	file.ReadRange(buf, offset, size);
	const nlohmann::json j                = nlohmann::json::parse(buf.data(), buf.data() + size);
	auto                 table_descriptor = j.get<TableDescriptorT>();
	return make_unique<TableDescriptorT>(table_descriptor);
}

} // namespace fastlanes
