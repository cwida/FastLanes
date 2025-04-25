#ifndef FLS_CONNECTION_HPP
#define FLS_CONNECTION_HPP

#include "fls/common/alias.hpp"               // for up, idx_t
#include "fls/footer/rowgroup_descriptor.hpp" // for Footer
#include "fls/reader/column_view.hpp"         //
#include "fls/reader/reader.hpp"              // for Reader
#include "fls/reader/segment.hpp"
#include "fls/std/filesystem.hpp" // for path
#include "fls/std/vector.hpp"     // for vector
#include "fls/table/rowgroup.hpp" // for Rowgroup

namespace fastlanes {
/*--------------------------------------------------------------------------------------------------------------------*/
class Dir;
/*--------------------------------------------------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------------------------------------------------*\
 * Config
\*--------------------------------------------------------------------------------------------------------------------*/
class Config {
public:
	Config();

public:
	bool                  is_forced_schema_pool;
	vector<OperatorToken> forced_schema_pool;
	bool                  is_forced_schema;
	vector<OperatorToken> forced_schema;
	n_t                   sample_size;
	n_t                   n_vector_per_rowgroup;
};
/*--------------------------------------------------------------------------------------------------------------------*\
 * FLS
\*--------------------------------------------------------------------------------------------------------------------*/
class Connection {
public:
	friend class column;
	friend class equal;
	friend class RowgroupEncoder;
	friend class Wizard;
	friend class Encoder;

public:
	Connection();
	explicit Connection(const Config& config);

public:
	/// Read csv or json file.
	///  - autodetect if it is csv or json.
	///  - if there is a file with ".csv" extension, then it is csv
	///  - if there is a file with ".jsonl" extension, then it is json
	/// - schema is not inferred and is given by "schema.json" file
	Connection& read(const path& dir_path);
	///! read a fls file return a reader
	Reader& read_fls(const path& dir_path);
	///!
	Connection& spell();
	///!
	Connection& to_fls(const path& dir_path);
	///!
	Connection& reset();
	///!
	Connection& project(const vector<idx_t>& idxs);
	///!
	bool is_forced_schema_pool() const;
	///!
	bool is_forced_schema() const;
	//
	const vector<OperatorToken>& get_forced_schema_pool() const;
	//
	Connection& force_schema_pool(const vector<OperatorToken>& operator_token);
	// API:
	// If the specified sample size exceeds the row group size, it is capped at the row group size.
	// A sample size of 0 is reserved for forcing fastlanes to use the entire row group as the sample size.
	//
	// Sets the sample size.
	// @param n_vecs The desired sample size in terms of vector count. Use 0 to default to the row group size.
	// @return Reference to the current Connection object.
	Connection& set_sample_size(n_t n_vecs);
	//
	n_t get_sample_size() const;
	//
	Connection& force_schema(const vector<OperatorToken>& operator_token);
	//
	const vector<OperatorToken>& get_forced_schema() const;
	//
	Connection& set_n_vectors_per_rowgroup(n_t n_vector_per_rowgroup);
	///!
	[[nodiscard]] Rowgroup& rowgroup() const;

private:
	/// read from a dir object
	Connection& read(const Dir& dir);
	void        prepare_rowgroup();

private:
	up<Rowgroup>           m_rowgroup;
	up<RowgroupDescriptor> m_rowgroup_descriptor;
	up<Reader>             m_reader;
	up<Config>             m_config;
};

constexpr static auto const* FOOTER_FILE_NAME {"fls_footer.json"};
constexpr static auto const* PROFILING_FILE_NAME {"fls_profiling.json"};
constexpr static auto const* FASTLANES_FILE_NAME {"data.fls"};
constexpr static auto const* SCHEMA_FILE_NAME {"schema.json"};
} // namespace fastlanes

#endif