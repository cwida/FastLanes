#include "fls/reader/table_reader.hpp"
#include "fls/csv/csv.hpp"
#include "fls/encoder/materializer.hpp"
#include "fls/file/file_footer.hpp"
#include "fls/file/file_header.hpp"
#include "fls/footer/table_descriptor.hpp"
#include "fls/info.hpp"
#include "fls/io/file.hpp"
#include "fls/io/io.hpp"
#include "fls/reader/rowgroup_reader.hpp"

namespace fastlanes {
up<RowgroupReader> TableReader::get_rowgroup_reader(const n_t rowgroup_idx) const {
	auto rowgroup_reader = make_unique<RowgroupReader>(
	    m_file_path, *m_table_descriptor->m_rowgroup_descriptors[rowgroup_idx], m_connection);
	return rowgroup_reader;
}

up<Table> TableReader::materialize() const {
	auto table_up = std::make_unique<Table>(m_connection);

	for (n_t rowgroup_idx {0}; rowgroup_idx < m_table_descriptor->m_rowgroup_descriptors.size(); rowgroup_idx++) {
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

void TableReader::to_csv(const string& file_path) const {
	to_csv(path(file_path));
}

void TableReader::to_csv(const char* file_path) const {
	to_csv(path(file_path));
}

TableReader::TableReader(const path& file_path, Connection& connection)
    : m_connection(connection)
    , m_file_path(file_path) {

	FileFooter file_footer {};
	FileHeader file_header {};

	FileHeader::Load(file_header, file_path);
	FileFooter::Load(file_footer, file_path);

	if (file_header.settings.inline_footer) {
		m_table_descriptor =
		    make_table_descriptor(file_path, file_footer.table_descriptor_offset, file_footer.table_descriptor_size);
	} else {

		m_table_descriptor = make_table_descriptor(file_path.parent_path() / TABLE_DESCRIPTOR_FILE_NAME);
	}
}
up<RowgroupReader> TableReader::operator[](const n_t rowgroup_idx) const {
	auto rowgroup_reader = make_unique<RowgroupReader>(
	    m_file_path, *m_table_descriptor->m_rowgroup_descriptors[rowgroup_idx], m_connection);
	return rowgroup_reader;
}

} // namespace fastlanes