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

void TableReader::verify_the_table(const path& dir_path, Connection& connection) {
	const auto file_name = dir_path / FASTLANES_FILE_NAME;
	io         io        = make_unique<File>(file_name); // todo[IO]

	if (const auto file_size = IO::get_size(io); file_size < sizeof(FileHeader) + sizeof(FileFooter)) {
		throw std::runtime_error("wrong format for fastlanes. fastlanes has at least 24 bytes.");
	}

	std::ifstream file(file_name, std::ios::binary);

	auto fastlanes_file = FileSystem::open_r(file_name);

	// Read first 24 bytes
	FileHeader file_header {};
	file.read(reinterpret_cast<char*>(&file_header), sizeof(FileHeader));

	if (file_header.magic_bytes != Info::get_magic_bytes()) {
		throw std::runtime_error("wrong format for fastlanes. the header magic bytes does not match");
	}
	if (file_header.version != Info::get_version_bytes()) {
		throw std::runtime_error("wrong format for fastlanes. the version does not match");
	}

	// Seek to 8 bytes before end
	file.seekg(-8, std::ios::end);

	// Read last 8 bytes
	FileFooter file_footer {};
	file.read(reinterpret_cast<char*>(&file_footer), sizeof(FileFooter));

	if (file_header.magic_bytes != Info::get_magic_bytes()) {
		throw std::runtime_error("wrong format for fastlanes. the footer magic bytes does not match");
	}
}

TableReader::TableReader(const path& dir_path, Connection& connection)
    : m_connection(connection)
    , m_dir_path(dir_path) {
	m_table_descriptor = make_table_descriptor(dir_path / TABLE_DESCRIPTOR_FILE_NAME);
}
up<RowgroupReader> TableReader::operator[](const n_t rowgroup_idx) const {
	auto rowgroup_reader =
	    make_unique<RowgroupReader>(m_dir_path, m_table_descriptor->m_rowgroup_descriptors[rowgroup_idx], m_connection);
	return rowgroup_reader;
}

} // namespace fastlanes