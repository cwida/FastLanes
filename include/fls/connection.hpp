#ifndef FLS_CONNECTION_HPP
#define FLS_CONNECTION_HPP

#include "fls/common/alias.hpp"             // for up, idx_t
#include "fls/encoder/rowgroup_encoder.hpp" // for RowgroupEncodingResult
#include "fls/encoder/single_col_decoder.hpp"
#include "fls/encoder/single_col_encoder.hpp"
#include "fls/footer/rowgroup_footer.hpp" // for Footer
#include "fls/reader/reader.hpp"          // for Reader
#include "fls/std/filesystem.hpp"         // for path
#include "fls/std/vector.hpp"             // for vector
#include "fls/table/rowgroup.hpp"         // for Rowgroup

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
	bool force_uncompressed;
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
	friend class NewEncoder;

public:
	Connection();

public:
	/// Read csv or json file.
	///  - autodetect if it is csv or json.
	///  - if there is a file with ".csv" extension, then it is csv
	///  - if there is a file with ".jsonl" extension, then it is json
	/// - schema is not inferred and is given by "schema.json" file
	Connection& read(const path& dir_path);
	///! read a fls file return a scanner
	Reader& read_fls(const path& dir_path);
	///!
	Connection& spell();
	///!
	Connection& to_fls(const path& dir_path);
	///! verify if encodings works.
	void verify_encoding();
	///!
	Connection& reset();
	///!
	Connection& project(const vector<idx_t>& idxs);
	/// force uncompressed
	Connection& force_uncompressed();

public:
	static void encode_from_memory(void*           input_p,
	                               n_t             n_tup,
	                               n_t             capacity,
	                               void*           encoded_p,
	                               bsz_t*          encoded_byte_size,
	                               const DataType& data_type,
	                               n_t             expr_id);
	///
	static void decode_to_memory(void* encoded_p, void* decoded_p, const DataType& data_type);

private:
	/// read from a dir object
	Connection& read(const Dir& dir);
	///!
	[[nodiscard]] Rowgroup& rowgroup() const;

private:
	up<Rowgroup>               m_rowgroup;
	up<Footer>                 m_rowgroup_footer;
	up<Reader>                 m_reader;
	up<RowgroupEncodingResult> m_encoding_result;
	up<Config>                 m_config;
};

constexpr static auto const* FOOTER_FILE_NAME {"footer.json"};
constexpr static auto const* PROFILING_FILE_NAME {"profiling.json"};
constexpr static auto const* FASTLANES_FILE_NAME {"data.fls"};
constexpr static auto const* SCHEMA_FILE_NAME {"schema.json"};
} // namespace fastlanes

#endif