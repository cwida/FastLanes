#include "fls/reader/table_reader.hpp"
#include "fls/footer/table_descriptor.hpp"
#include "fls/reader/rowgroup_reader.hpp"
#include <fls/csv/csv.hpp>
#include <fls/encoder/materializer.hpp>

namespace fastlanes {
up<RowgroupReader> TableReader::get_rowgroup_reader(const n_t rowgroup_idx) const {
	auto rowgroup_reader =
	    make_unique<RowgroupReader>(m_dir_path, m_table_descriptor->m_rowgroup_descriptors[rowgroup_idx], m_connection);
	return rowgroup_reader;
}

up<Table> TableReader::materialize() const {
	auto table_up = std::make_unique<Table>(m_connection);

	for (n_t rowgroup_idx {0}; rowgroup_idx < m_table_descriptor->GetNRowgroups(); rowgroup_idx++) {
		auto rowgroup_up = get_rowgroup_reader(rowgroup_idx)->materialize();
		table_up->m_rowgroups.push_back(std::move(rowgroup_up));
	}

	return table_up;
}

void TableReader::to_csv(const path& file_path) const {
	const auto materialized_table_up = materialize();
	for (const auto& rowgroup_up : materialized_table_up->m_rowgroups) {
		CSV::to_csv(file_path, *rowgroup_up);
	}
}

TableReader::TableReader(const path& dir_path, Connection& connection)
    : m_connection(connection)
    , m_dir_path(dir_path) {
	// read get_descriptor
	m_table_descriptor = make_table_descriptor(dir_path / TABLE_DESCRIPTOR_FILE_NAME);
}
up<RowgroupReader> TableReader::operator[](const n_t rowgroup_idx) const {
	auto rowgroup_reader =
	    make_unique<RowgroupReader>(m_dir_path, m_table_descriptor->m_rowgroup_descriptors[rowgroup_idx], m_connection);
	return rowgroup_reader;
}

} // namespace fastlanes