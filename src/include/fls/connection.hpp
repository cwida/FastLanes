#ifndef FLS_CONNECTION_HPP
#define FLS_CONNECTION_HPP

#include "fls/common/alias.hpp" // for up, idx_t
#include "fls/common/status.hpp"
#include "fls/footer/rowgroup_descriptor.hpp" // for Footer
#include "fls/footer/table_descriptor.hpp"
#include "fls/reader/column_view.hpp" //
#include "fls/reader/rowgroup_reader.hpp"
#include "fls/reader/rowgroup_view.hpp" //
#include "fls/reader/segment.hpp"
#include "fls/reader/table_reader.hpp"
#include "fls/std/filesystem.hpp" // for path
#include "fls/std/vector.hpp"     // for vector
#include "fls/table/rowgroup.hpp" // for Rowgroup
#include "fls/table/table.hpp"    // for Reader

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
	//
	fls_bool inline_footer;
	//
	bool enable_verbose;
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
	friend class CsvReader;
	friend class Rowgroup;

public:
	Connection();
	explicit Connection(const Config& config);

public:
	/// READ CSV
	Connection& read_csv(const path& dir_path);
	/// READ CSV
	Connection& read_json(const path& dir_path);
	///! read a fls file return a reader
	up<TableReader> read_fls(const path& file_path);
	///!
	Connection& spell();
	///!
	Connection& to_fls(const path& dir_path);
	//
	Status verify_fls(const path& file_path);

	/**
	 *
	 */
	Connection& reset();
	///!
	Connection& project(const vector<idx_t>& idxs);
	///!
	[[nodiscard]] bool is_forced_schema_pool() const;
	///!
	[[nodiscard]] bool is_forced_schema() const;
	//
	[[nodiscard]] const vector<OperatorToken>& get_forced_schema_pool() const;
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
	[[nodiscard]] n_t get_sample_size() const;
	//
	Connection& force_schema(const vector<OperatorToken>& operator_token);
	//
	[[nodiscard]] const vector<OperatorToken>& get_forced_schema() const;
	//
	Connection& set_n_vectors_per_rowgroup(n_t n_vector_per_rowgroup);
	///!
	[[nodiscard]] Table& get_table() const;
	//
	[[nodiscard]] fls_bool is_footer_inlined() const;
	//
	Connection& inline_footer();

private:
	void prepare_table() const;
	void write_footer(const path& dir_path) const;

private:
	up<Config>           m_config;
	up<Table>            m_table;
	up<TableDescriptorT> m_table_descriptor;
};

constexpr static auto const* TABLE_DESCRIPTOR_FILE_NAME {"table_descriptor.fbb"};
constexpr static auto const* FASTLANES_FILE_NAME {"data.fls"};
constexpr static auto const* SCHEMA_FILE_NAME {"schema.json"};

up<Connection> connect();
} // namespace fastlanes

#endif