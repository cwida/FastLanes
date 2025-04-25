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
#include "fls/reader/reader.hpp"              // for Reader
#include "fls/reader/segment.hpp"
#include "fls/std/string.hpp"     // for string
#include "fls/table/dir.hpp"      // for Dir, FileT
#include "fls/table/rowgroup.hpp" // for Rowgroup
#include "fls/wizard/wizard.hpp"  // for Wizard
#include <filesystem>             // for directory_iterator, begin
#include <memory>                 // for make_unique, operator==
#include <stdexcept>              // for runtime_error
#include <string>                 // for basic_string, string

namespace fastlanes {

Connection::Connection() {
	m_config = make_unique<Config>();
}

Connection::Connection(const Config& config) {
	m_config = make_unique<Config>(config);
};

Connection& Connection::read(const path& dir_path) {
	FileSystem::check_if_dir_exists(dir_path);

	// init
	Dir  dir;
	bool is_schema_found {false};
	bool is_file_found {false};

	for (const auto& entry : std::filesystem::directory_iterator(dir_path)) {
		const auto& file_path     = entry.path();
		auto        file_path_str = file_path.string();
		if (const auto schema_path = file_path_str.find(SCHEMA_FILE_NAME); schema_path != std::string::npos) {
			is_schema_found = true;
			dir.schema_path = file_path;
		}

		if (const auto schema_path = file_path.string().find("csv"); schema_path != std::string::npos) {
			is_file_found = true;
			dir.file_path = file_path;
			dir.file_t    = FileT::CSV;
		}

		if (const auto schema_path = file_path.string().find("jsonl"); schema_path != std::string::npos) {
			is_file_found = true;
			dir.file_path = file_path;
			dir.file_t    = FileT::JSON;
		}
	}

	if (!is_schema_found) {
		throw std::runtime_error("schema is not found!");
	}
	if (!is_file_found) {
		throw std::runtime_error("csv/json file is not found!");
	}

	return read(dir);
}

Reader& Connection::read_fls(const path& dir_path) {
	FileSystem::check_if_dir_exists(dir_path);

	// init
	m_reader = make_unique<Reader>(dir_path, *this);

	return *m_reader;
}

Connection& Connection::read(const Dir& dir) {
	auto                 json_string         = File::read(dir.schema_path);
	const nlohmann::json j                   = nlohmann::json::parse(json_string);
	auto                 rowgroup_descriptor = j.get<RowgroupDescriptor>();
	m_rowgroup                               = make_unique<Rowgroup>(rowgroup_descriptor);

	switch (dir.file_t) {
	case FileT::JSON: {
		m_rowgroup->ReadJson(dir.file_path);
		break;
	}
	case FileT::CSV: {
		m_rowgroup->ReadCsv(dir.file_path);
		break;
	}
	default:
		throw std::runtime_error("The given FILE TYPE is not supported!");
	}

	return *this;
}

void Connection::prepare_rowgroup() {
	if (m_rowgroup == nullptr) {
		/**/
		throw std::runtime_error("Data is not loaded.");
	}

	// could be combined
	m_rowgroup->Init();
	m_rowgroup->Cast();
	m_rowgroup->Finalize();
	m_rowgroup->GetStatistics();
}

Connection& Connection::spell() {
	if (m_rowgroup == nullptr) {
		/**/
		throw std::runtime_error("Data is not loaded.");
	}

	m_rowgroup_descriptor = Wizard::Spell(*this);

	return *this;
}

Connection& Connection::to_fls(const path& dir_path) {
	{
		// check if data is loaded into memory
		if (m_rowgroup == nullptr) {
			throw std::runtime_error("Data is not loaded.");
		}
	}

	{
		// prepare_rowgroup
		prepare_rowgroup();
	}

	{
		//  make a rowgroup-footer if there is no rowgroup-footer .
		if (m_rowgroup_descriptor == nullptr) {
			spell();
		}
	}

	{
		// encode
		io  file_io = make_unique<File>(dir_path / FASTLANES_FILE_NAME); // TODO[io]
		Buf buf;                                                         // TODO[memory pool]
		Encoder::encode(*this, buf);
		IO::flush(file_io, buf);
	}

	{
		// write footer
		JSON::write<RowgroupDescriptor>(dir_path, *m_rowgroup_descriptor);
	}

	return *this;
}

Connection& Connection::reset() {
	m_rowgroup_descriptor.reset();
	m_rowgroup.reset();
	m_reader.reset();

	return *this;
}

Connection& Connection::project(const vector<idx_t>& idxs) {
	if (m_rowgroup == nullptr) {
		throw std::runtime_error("Data is not loaded.");
	}

	m_rowgroup = m_rowgroup->Project(idxs);

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

Rowgroup& Connection::rowgroup() const {
	//
	return *m_rowgroup;
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