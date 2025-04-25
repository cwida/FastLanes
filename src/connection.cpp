#include "fls/connection.hpp"
#include "fls/cor/lyt/buf.hpp"     // for Buf
#include "fls/encoder/encoder.hpp" // for Encoder
#include "fls/expression/decoding_operator.hpp"
#include "fls/expression/encoding_operator.hpp"
#include "fls/expression/predicate_operator.hpp"
#include "fls/footer/rowgroup_descriptor.hpp" // for RowgroupDescriptor
#include "fls/io/file.hpp"                    // for File
#include "fls/io/io.hpp"                      // for IO, io
#include "fls/json/fls_json.hpp"              // for JSON
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

	// encode
	Buf buf; // TODO[memory pool]
	Encoder::encode(*this, buf, dir_path);

	// write table descriptor
	JSON::write<TableDescriptor>(dir_path, *m_table_descriptor);

	return *this;
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

/*--------------------------------------------------------------------------------------------------------------------*\
 * Config
\*--------------------------------------------------------------------------------------------------------------------*/

Config::Config()
    : is_forced_schema_pool(false)
    , is_forced_schema(false)
    , sample_size(CFG::SAMPLER::SAMPLE_SIZE)
    , n_vector_per_rowgroup(CFG::RowGroup::N_VECTORS_PER_ROWGROUP) {
}
} // namespace fastlanes