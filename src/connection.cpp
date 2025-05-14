#include "fls/connection.hpp"
#include "fls/cor/lyt/buf.hpp"     // for Buf
#include "fls/encoder/encoder.hpp" // for Encoder
#include "fls/expression/decoding_operator.hpp"
#include "fls/expression/encoding_operator.hpp"
#include "fls/expression/predicate_operator.hpp"
#include "fls/file/file_footer.hpp"
#include "fls/file/file_header.hpp"
#include "fls/flatbuffers/flatbuffers.hpp"
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

up<TableReader> Connection::read_fls(const path& file_path) {
	FileSystem::check_if_file_exists(file_path);

	// init
	return make_unique<TableReader>(file_path, *this);
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

void Connection::write_footer(const path& file_path) const {
	// Write table descriptor

	const n_t        table_descriptor_size = FlatBuffers::Write(*this, file_path, *m_table_descriptor);
	const FileFooter file_footer {
	    m_table_descriptor->m_table_binary_size, table_descriptor_size, Info::get_magic_bytes()};

	FileFooter::Write(*this, file_path, file_footer);
}

up<Connection> connect() {
	return make_unique<Connection>();
}

Connection& Connection::spell() {
	if (m_table == nullptr) {
		/**/
		throw std::runtime_error("Data is not loaded.");
	}

	m_table_descriptor = Wizard::Spell(*this);

	return *this;
}

Connection& Connection::to_fls(const path& file_path) {
	if (exists(file_path)) {
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

	FileHeader::Write(*this, file_path);

	// encode
	Encoder::encode(*this, file_path);

	// write the footer
	write_footer(file_path);

	return *this;
}

Status Connection::verify_fls(const path& file_path) {
	FileHeader file_header {};
	FileHeader::Load(file_header, file_path);

	if (file_header.magic_bytes != Info::get_magic_bytes()) {
		return Status::Error(Status::ErrorCode::ERR_5_INVALID_MAGIC_BYTES);
	}
	if (file_header.version != Info::get_version_bytes()) {
		return Status::Error(Status::ErrorCode::ERR_6_INVALID_VERSION_BYTES);
	}

	FileFooter file_footer {};
	FileFooter::Load(file_footer, file_path);

	if (file_footer.magic_bytes != Info::get_magic_bytes()) {
		return Status::Error(Status::ErrorCode::ERR_5_INVALID_MAGIC_BYTES);
	}

	return Status::Ok();
}

Connection& Connection::reset() {
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
    , inline_footer(CFG::Footer::IS_INLINED)
    , enable_verbose(CFG::Defaults::ENABLE_VERBOSE) {
}

} // namespace fastlanes