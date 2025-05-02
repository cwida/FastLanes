#include "fls/connection.hpp"
#include "fls/cor/lyt/buf.hpp"     // for Buf
#include "fls/encoder/encoder.hpp" // for Encoder
#include "fls/expression/decoding_operator.hpp"
#include "fls/expression/encoding_operator.hpp"
#include "fls/expression/predicate_operator.hpp"
#include "fls/file/file_footer.hpp"
#include "fls/file/file_header.hpp"
#include "fls/footer/rowgroup_descriptor.hpp" // for RowgroupDescriptor
#include "fls/info.hpp"
#include "fls/io/file.hpp"       // for File
#include "fls/io/io.hpp"         // for IO, io
#include "fls/json/fls_json.hpp" // for JSON
#include "fls/reader/csv_reader.hpp"
#include "fls/reader/json_reader.hpp"
#include "fls/reader/segment.hpp"
#include "fls/std/string.hpp"     // for string
#include "fls/table/dir.hpp"      // for Dir, FileT
#include "fls/table/rowgroup.hpp" // for Rowgroup
#include "fls/table/table.hpp"
#include "fls/wizard/wizard.hpp" // for Wizard
#include <filesystem>            // for directory_iterator, begin
#include <memory>                // for make_unique, operator==
#include <stdexcept>             // for runtime_error
#include <string>                // for basic_string, string

namespace fastlanes {

Connection::Connection() {
	m_config = make_unique<Config>();
}

Connection::Connection(const Config& config) {
	m_config = make_unique<Config>(config);
}

Connection& Connection::read_csv(const path& dir_path) {
	m_table = CsvReader::Read(dir_path, *this);

	return *this;
}

Connection& Connection::read_json(const path& dir_path) {
	m_table = JsonReader::Read(dir_path, *this);

	return *this;
}

TableReader& Connection::read_fls(const path& dir_path) {
	FileSystem::check_if_dir_exists(dir_path);

	// init
	m_reader = make_unique<TableReader>(dir_path, *this);

	return *m_reader;
}

void prepare_rowgroup(Rowgroup& rowgroup) {

	// could be combined
	rowgroup.Init();
	rowgroup.Cast();
	rowgroup.Finalize();
	rowgroup.GetStatistics();
}

void Connection::prepare_table() const {
	for (auto& rowgroup : m_table->m_rowgroups) {
		prepare_rowgroup(*rowgroup);
	}
}

Connection& Connection::spell() {
	if (m_table == nullptr) {
		/**/
		throw std::runtime_error("Data is not loaded.");
	}

	m_table_descriptor = Wizard::Spell(*this);

	return *this;
}

Connection& Connection::to_fls(const path& dir_path) {
	if (const path file_path = dir_path / FASTLANES_FILE_NAME; exists(file_path)) {
		throw std::runtime_error("Fastlanes file already exists at: " + file_path.string());
	}

	// check if data is loaded into memory
	if (m_table == nullptr) {
		throw std::runtime_error("data is not loaded.");
	}

	prepare_table();

	//  make a rowgroup-get_descriptor if there is no rowgroup-get_descriptor .
	if (m_table_descriptor == nullptr) {
		spell();
	}

	FileHeader::Write(*this, dir_path);

	// encode
	Encoder::encode(*this, dir_path);

	// write table descriptor
	JSON::write<TableDescriptor>(*this, dir_path, *m_table_descriptor);

	FileFooter::Write(*this, dir_path);

	return *this;
}

VerificationResult Connection::verify_fls(const path& file_path) {
	io io = make_unique<File>(file_path); // todo[IO]

	if (const auto file_size = IO::get_size(io); file_size < sizeof(FileHeader) + sizeof(FileFooter)) {
		return VerificationResult::Error(VerificationResult::ErrorCode::ERR_1_SMALL_FILE_SIZE);
	}

	std::ifstream file(file_path, std::ios::binary);

	auto fastlanes_file = FileSystem::open_r(file_path);

	// Read first 24 bytes
	FileHeader file_header {};
	file.read(reinterpret_cast<char*>(&file_header), sizeof(FileHeader));

	if (file_header.magic_bytes != Info::get_magic_bytes()) {
		return VerificationResult::Error(VerificationResult::ErrorCode::ERR_5_INVALID_MAGIC_BYTES);
	}
	if (file_header.version != Info::get_version_bytes()) {
		return VerificationResult::Error(VerificationResult::ErrorCode::ERR_6_INVALID_VERSION_BYTES);
	}

	// Seek to 8 bytes before end
	file.seekg(-8, std::ios::end);

	// Read last 8 bytes
	FileFooter file_footer {};
	file.read(reinterpret_cast<char*>(&file_footer), sizeof(FileFooter));

	if (file_footer.magic_bytes != Info::get_magic_bytes()) {
		return VerificationResult::Error(VerificationResult::ErrorCode::ERR_5_INVALID_MAGIC_BYTES);
	}

	return VerificationResult::Ok();
}

Connection& Connection::reset() {
	m_reader.reset();
	m_table_descriptor.reset();
	m_table.reset();

	return *this;
}

Connection& Connection::project(const vector<idx_t>& idxs) {
	if (m_table == nullptr) {
		throw std::runtime_error("Data is not loaded.");
	}

	m_table = m_table->Project(idxs);

	return *this;
}

bool Connection::is_forced_schema_pool() const {
	return m_config->is_forced_schema_pool;
}

bool Connection::is_forced_schema() const {
	return m_config->is_forced_schema;
}

const vector<OperatorToken>& Connection::get_forced_schema_pool() const {
	//
	return m_config->forced_schema_pool;
}

Connection& Connection::force_schema_pool(const vector<OperatorToken>& operator_token) {
	m_config->is_forced_schema_pool = true;

	m_config->forced_schema_pool = operator_token;

	return *this;
}

Connection& Connection::force_schema(const vector<OperatorToken>& operator_token) {
	m_config->is_forced_schema = true;

	m_config->forced_schema = operator_token;

	return *this;
}

const vector<OperatorToken>& Connection::get_forced_schema() const {
	//
	return m_config->forced_schema;
}

Connection& Connection::set_n_vectors_per_rowgroup(n_t n_vector_per_rowgroup) {
	m_config->n_vector_per_rowgroup = n_vector_per_rowgroup;
	return *this;
}

Connection& Connection::set_sample_size(n_t n_vecs) {
	m_config->sample_size = n_vecs;
	return *this;
}

n_t Connection::get_sample_size() const {
	return m_config->sample_size;
}

Table& Connection::get_table() const {
	//
	return *m_table;
}

fls_bool Connection::is_footer_inlined() const {
	return m_config->inline_footer;
}

Connection& Connection::inline_footer() {
	m_config->inline_footer = FLS_TRUE;

	return *this;
}

/*--------------------------------------------------------------------------------------------------------------------*\
 * Config
\*--------------------------------------------------------------------------------------------------------------------*/

Config::Config()
    : is_forced_schema_pool(false)
    , is_forced_schema(false)
    , sample_size(CFG::SAMPLER::SAMPLE_SIZE)
    , n_vector_per_rowgroup(CFG::RowGroup::N_VECTORS_PER_ROWGROUP)
    , inline_footer(CFG::Footer::IS_INLINED) {
}

/*--------------------------------------------------------------------------------------------------------------------*\
 * VerificationResult
\*--------------------------------------------------------------------------------------------------------------------*/

// Constructor
VerificationResult::VerificationResult(bool success, ErrorCode code)
    : success(success)
    , code(code) {
}

// Static factory for Ok
VerificationResult VerificationResult::Ok() {
	return {true, ErrorCode::Ok};
}

// Static factory for Error
VerificationResult VerificationResult::Error(ErrorCode code) {
	return {false, code};
}

// Message lookup
std::string_view VerificationResult::message_for(ErrorCode code) {
	switch (code) {
	case ErrorCode::Ok:
		return "";
	case ErrorCode::ERR_1_SMALL_FILE_SIZE:
		return "File too small";
	case ErrorCode::ERR_2_INVALID_HEADER:
		return "Invalid header";
	case ErrorCode::ERR_3_INVALID_FOOTER:
		return "Invalid footer";
	case ErrorCode::ERR_4_INVALID_CHECKSUM:
		return "Checksum mismatch";
	case ErrorCode::ERR_5_INVALID_MAGIC_BYTES:
		return "Invalid magic bytes";
	case ErrorCode::ERR_6_INVALID_VERSION_BYTES:
		return "Unsupported version";
	case ErrorCode::ERR_7_INVALID_ROWGROUP_DESCRIPTOR:
		return "Corrupt row group descriptor";
	case ErrorCode::ERR_8_INVALID_TABLE_DESCRIPTOR:
		return "Corrupt table descriptor";
	case ErrorCode::ERR_9_INVALID_ROWGROUP_COUNT:
		return "Invalid row group count";
	case ErrorCode::ERR_10_INVALID_ROWGROUP_SIZE:
		return "Row group size mismatch";
	case ErrorCode::Error2:
		return "Generic error"; // TODO: Rename or remove
	default:
		return "Unknown error";
	}
}

} // namespace fastlanes