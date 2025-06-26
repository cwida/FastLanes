#ifndef FLS_WRITER_WRITERv2_HPP
#define FLS_WRITER_WRITERv2_HPP

#include "fls/cfg/cfg.hpp"
#include "fls/common/alias.hpp"
#include "fls/common/double.hpp"
#include "fls/encoder/encoder.hpp"
#include "fls/file/file_footer.hpp"
#include "fls/file/file_header.hpp"
#include "fls/flatbuffers/flatbuffers.hpp"
#include "fls/info.hpp"
#include "fls/std/filesystem.hpp"
#include "fls/table/rowgroup.hpp"
#include "fls/table/table.hpp"
#include "fls/wizard/wizard.hpp"
#include <iostream>
#include <memory>

namespace fastlanes {

template <typename PT>
struct DataTypeTraits;

template <>
struct DataTypeTraits<u08_pt> {
	static constexpr auto value = DataType::UINT8;
	using ColT                  = u08_col_t;
};
template <>
struct DataTypeTraits<u32_pt> {
	static constexpr auto value = DataType::UINT32;
	using ColT                  = u32_col_t;
};
template <>
struct DataTypeTraits<dbl_pt> {
	static constexpr auto value = DataType::DOUBLE;
	using ColT                  = dbl_col_t;
};
template <>
struct DataTypeTraits<flt_pt> {
	static constexpr auto value = DataType::FLOAT;
	using ColT                  = flt_col_t;
};
template <>
struct DataTypeTraits<str_pt> {
	static constexpr auto value = DataType::FLS_STR;
	using ColT                  = flt_col_t;
};

class RowGroupWriter;

inline bool isValidUint64(const std::string& str) {
	if (str.empty())
		return false;

	// Check if the string contains only digits
	for (char c : str) {
		if (!std::isdigit(c))
			return false;
	}

	try {
		// Convert to unsigned long long and check if it's within uint64_t range
		uint64_t value = std::stoull(str);
		return value <= std::numeric_limits<uint64_t>::max();
	} catch (const std::exception&) {
		return false; // Overflow or invalid conversion
	}
}

inline bool IsNumeric(const string& val_str) {
	if (val_str.empty()) {
		return false; // Empty string is not an integer
	}

	const size_t startIndex = (val_str[0] == '+' || val_str[0] == '-') ? 1 : 0;

	for (size_t i = startIndex; i < val_str.size(); ++i) {
		if (!std::isdigit(val_str[i])) {
			return false;
		}
	}

	return true;
}

struct WriterOptions {
	//! Schema which is used to encode incoming data.
	std::vector<std::unique_ptr<ColumnDescriptorT>> schema;
	//! Target file path (TODO: Should abstract this so it works for any transport.)
	path file_path;
	//! Target for committing write operations.
	Connection* connection;
	//! Amount of entries within a single vector. Must be a multiple of 1024.
	size_t vector_size = CFG::VEC_SZ;
	//! Amount of tuples within a single row group.
	size_t row_group_size = CFG::ROW_GROUP_SIZE;
	//! Maximum amount of row groups in a single file, when set to 0 there is no maximum.
	size_t max_row_groups = 0;
	//! If the footer is stored separately or within the Fastlanes file.
	fls_bool inlined_footer = fls_bool::FLS_TRUE;
	//!
	n_t sample_size = CFG::SAMPLER::SAMPLE_SIZE;
	//!
	vector<OperatorToken> forced_schema_pool;
	vector<OperatorToken> forced_schema;
	//! If enabled, flush must be called before any bytes are commited to the target storage medium.
	bool explicit_flush = false;

	void Validate() const {
		if (schema.empty()) {
			throw std::invalid_argument("schema cannot be empty");
		}
		if (file_path.empty()) {
			throw std::invalid_argument("file_path cannot be empty");
		}
		if (connection == nullptr) {
			throw std::invalid_argument("connection must be defined");
		}
		if (row_group_size == 0) {
			throw std::invalid_argument("row_group_size must be greater than 0");
		}
		if (row_group_size % 1024 != 0) {
			throw std::invalid_argument("row_group_size must be a multiple of 1024");
		}
		if (vector_size % 1024 != 0) {
			throw std::invalid_argument("vector_size must be a multiple of 1024");
		}
	}
};

class FileWriter {
	friend class RowGroupWriter;

public:
	class Builder {
	public:
		Builder& WithSchema(std::vector<std::unique_ptr<ColumnDescriptorT>>&& schema) {
			if (schema.empty()) {
				throw std::invalid_argument("schema cannot be empty");
			}
			options.schema = std::move(schema);
			return *this;
		}

		Builder& WithPath(const path& file_path) {
			options.file_path = file_path;
			return *this;
		}

		Builder& WithConnection(Connection& conn) {
			options.connection = &conn;
			return *this;
		}

		Builder& WithVectorSize(const size_t vec_size) {
			if (vec_size % 1024 != 0) {
				throw std::invalid_argument("vector_size must be a multiple of 1024");
			}
			options.vector_size = vec_size;
			return *this;
		}

		Builder& WithRowGroupSize(const size_t rg_size) {
			if (rg_size == 0) {
				throw std::invalid_argument("row_group_size must be greater than 0");
			}
			if (rg_size % 1024 != 0) {
				throw std::invalid_argument("row_group_size must be a multiple of 1024");
			}
			options.row_group_size = rg_size;
			return *this;
		}

		Builder& WithMaxRowGroups(const size_t rg_max) {
			options.max_row_groups = rg_max;
			return *this;
		}

		Builder& WithInlinedFooter(const fls_bool inlined_footer) {
			options.inlined_footer = inlined_footer;
			return *this;
		}

		Builder& WithForcedSchemaPool(vector<OperatorToken>&& operator_token) {
			options.forced_schema_pool = std::move(operator_token);
			return *this;
		}

		Builder& WithForcedSchema(vector<OperatorToken>&& operator_token) {
			options.forced_schema = std::move(operator_token);
			return *this;
		}

		Builder& WithExplicitFlush() {
			options.explicit_flush = true;
			return *this;
		}

		[[nodiscard]] FileWriter Build() {
			// Verify that the connection and file path are set.
			options.Validate();
			return FileWriter(std::move(options));
		}

	private:
		WriterOptions options {};
	};

	void Open() {
		FileHeader::Write(*options.connection, options.file_path);
		table = make_unique<Table>();
	};

	up<RowGroupWriter> CreateRowGroupWriter() {
		return make_unique<RowGroupWriter>(*this);
	}

	void Close() {
		for (auto& rowgroup : table->m_rowgroups) {
			rowgroup->Init();
			rowgroup->Cast();
			rowgroup->Finalize();
			rowgroup->GetStatistics();
		}
		auto wizard           = make_unique<Wizard<FileWriter>>(*this);
		auto table_descriptor = wizard->Spell();
		Encoder::encode(*table, *table_descriptor, options.file_path);
		const n_t table_descriptor_size =
		    FlatBuffers::Write(options.inlined_footer, options.file_path, *table_descriptor);
		const FileFooter file_footer {
		    table_descriptor->m_table_binary_size, table_descriptor_size, Info::get_magic_bytes()};

		FileFooter::Write(options.file_path, file_footer);
	};

	Table& GetTable() const {
		return *table;
	}

	n_t GetSampleSize() const {
		return options.sample_size;
	}

	bool IsForcedSchemaPool() const {
		return !options.forced_schema_pool.empty();
	}
	const vector<OperatorToken>& GetForcedSchemaPool() const {
		return options.forced_schema_pool;
	}

	bool IsForcedSchema() const {
		return !options.forced_schema.empty();
	}
	const vector<OperatorToken>& GetForcedSchema() const {
		return options.forced_schema;
	}

private:
	explicit FileWriter(WriterOptions&& opts)
	    : options(std::move(opts)) {

	    };

	void FlushRowGroup(up<Rowgroup>&& row_group) {
		// TODO: commit to transport.
		table->m_rowgroups.push_back(std::move(row_group));
	}

private:
	WriterOptions options;
	up<Table>     table;
};

// TODO: Currently single use, should we make it multiple use?
class RowGroupWriter {
public:
	explicit RowGroupWriter(FileWriter& file_writer)
	    : file_writer(file_writer) {

		row_group_descriptor = make_unique<RowgroupDescriptorT>();

		std::vector<std::unique_ptr<ColumnDescriptorT>> cds;
		cds.reserve(file_writer.options.schema.size());
		for (const auto& cd : file_writer.options.schema) {
			cds.push_back(make_unique<ColumnDescriptorT>(*cd));
		}
		row_group_descriptor->m_column_descriptors = std::move(cds);
		// TODO: We don't use the max capacity, managed by the writer
		row_group        = make_unique<Rowgroup>(*row_group_descriptor, 2048);
		row_group->n_tup = 2048;
	}
	~RowGroupWriter() {
	}

	template <typename PT>
	void WriteColumn(idx_t col_idx, std::vector<std::span<PT>> column) {
		for (auto vector : column) {
			WriteVector(vector, col_idx);
		}
	}

	void Flush() {
		file_writer.FlushRowGroup(std::move(row_group));
		// TODO (optional): After flushing we create a new row_group so that we can keep reusing the same row_group
		// writer.
	};

private:
	template <typename PT>
	void WriteVector(std::span<PT> src_column, idx_t col_idx) {
		auto& col_variant = row_group->internal_rowgroup[col_idx];

		if constexpr (std::is_same_v<PT, str_pt>) {
			visit(overloaded {
			          [&](up<FLSStrColumn>& fls_str_column) {
				          if constexpr (std::is_same_v<PT, str_pt>) {
					          FLSStringIngest(*fls_str_column, src_column);
				          }
			          },

			          [](auto&) { FLS_UNREACHABLE(); },
			      },
			      col_variant);
		} else {
			visit(overloaded {
			          [&](up<typename DataTypeTraits<PT>::ColT>& typed_column) {
				          TypedIngest<PT>(*typed_column, src_column);
			          },

			          [](auto&) { FLS_UNREACHABLE(); },
			      },
			      col_variant);
		}
	}

	template <typename PT>
	PT TypedNull() {
		static constexpr i08_pt I08_NULL   = 0;
		static constexpr i16_pt I16_NULL   = 0;
		static constexpr i32_pt I32_NULL   = 0;
		static constexpr i64_pt I64_NULL   = 0;
		static constexpr u08_pt U08_NULL   = 0;
		static constexpr u16_pt U16_NULL   = 0;
		static constexpr u32_pt U32_NULL   = 0;
		static constexpr u64_pt U64_NULL   = 0;
		static constexpr bol_pt BOOL_NULL  = false;
		static constexpr flt_pt FLOAT_NULL = 0.0;
		static constexpr dbl_pt DBL_NULL   = 0.0;
		static constexpr char   STR_NULL[] = "NULL";

		if constexpr (std::is_same_v<PT, i08_pt>) {
			return I08_NULL;
		} else if constexpr (std::is_same_v<PT, i16_pt>) {
			return I16_NULL;
		} else if constexpr (std::is_same_v<PT, i32_pt>) {
			return I32_NULL;
		} else if constexpr (std::is_same_v<PT, i64_pt>) {
			return I64_NULL;
		} else if constexpr (std::is_same_v<PT, u08_pt>) {
			return U08_NULL;
		} else if constexpr (std::is_same_v<PT, u16_pt>) {
			return U16_NULL;
		} else if constexpr (std::is_same_v<PT, u32_pt>) {
			return U32_NULL;
		} else if constexpr (std::is_same_v<PT, u64_pt>) {
			return U64_NULL;
		} else if constexpr (std::is_same_v<PT, str_pt>) {
			return STR_NULL;
		} else if constexpr (std::is_same_v<PT, bol_pt>) {
			return BOOL_NULL;
		} else if constexpr (std::is_same_v<PT, flt_pt>) {
			return FLOAT_NULL;
		} else if constexpr (std::is_same_v<PT, dbl_pt>) {
			return DBL_NULL;
		}

		FLS_UNREACHABLE();
	}

	void FLSStringIngest(FLSStrColumn& fls_str_column, std::span<const str_pt> src_column) {
		const auto count = src_column.size();

		auto& byte_arr            = fls_str_column.byte_arr;
		auto& ofs_arr             = fls_str_column.ofs_arr;
		auto& max_n_bytes_p_value = fls_str_column.m_stats.maximum_n_bytes_p_value;
		auto& length_arr          = fls_str_column.length_arr;
		auto& is_numeric          = fls_str_column.m_stats.is_numeric;

		auto& fsst_byte_arr   = fls_str_column.fsst_byte_arr;
		auto& fsst_length_arr = fls_str_column.fsst_length_arr;

		if (length_arr.empty()) {
			is_numeric = true;
		}

		for (idx_t i = 0; i < count; i++) {
			str_pt value = src_column[i];
			if (value.size() > CFG::String::max_bytes_per_string) {
				throw std::runtime_error("String of size " + std::to_string(value.size()) +
				                         " exceeds the maximum allowed size of " +
				                         std::to_string(CFG::String::max_bytes_per_string) + " bytes.");
			}
			const bool is_null = value == TypedNull<str_pt>();

			fls_str_column.null_map_arr.push_back(is_null);
			string current_val;
			if (!is_null) {
				current_val                          = value;
				fls_str_column.m_stats.last_seen_val = current_val;
			} else {
				current_val = fls_str_column.m_stats.last_seen_val;
			}

			if (is_numeric && !is_null && !isValidUint64(current_val)) {
				is_numeric = false;
			}

			const size_t old_size = byte_arr.size(); // Save the current size
			ofs_arr.push_back(static_cast<ofs_t>(byte_arr.size()));
			byte_arr.resize(byte_arr.size() + current_val.size());
			std::memcpy(byte_arr.data() + old_size, current_val.data(), current_val.size());
			length_arr.push_back(static_cast<len_t>(current_val.size()));

			// calculate maximum size of a value
			max_n_bytes_p_value = (max_n_bytes_p_value > current_val.size()) ? max_n_bytes_p_value : current_val.size();
			is_numeric          = is_numeric && IsNumeric(value);

			// FSST
			{
				// check if it NULL
				if (!is_null) {
					current_val                          = value;
					fls_str_column.m_stats.last_seen_val = current_val;
				} else {
					current_val = "";
				}

				// push
				const size_t fsst_old_size = fsst_byte_arr.size(); // Save the current size
				fsst_byte_arr.resize(fsst_byte_arr.size() + current_val.size());
				std::memcpy(fsst_byte_arr.data() + fsst_old_size, current_val.data(), current_val.size());
				fsst_length_arr.push_back(static_cast<len_t>(current_val.size()));
			}
		}
	}

	template <typename PT>
	void TypedIngest(TypedCol<PT>& typed_column, std::span<const PT> src_column) {
		auto  count = src_column.size();
		auto& stats = typed_column.m_stats;
		auto& data  = typed_column.data;
		auto& nulls = typed_column.null_map_arr;

		if (typed_column.data.empty()) {
			typed_column.m_stats.last_seen_val = TypedNull<PT>();
			if constexpr (std::is_same_v<PT, dbl_pt>) {
				stats.is_double_castable = true;
			}
		}

		const idx_t prev_size = data.size();
		data.resize(prev_size + count);
		nulls.resize(prev_size + count);

		auto target_ptr = data.data() + prev_size;
		auto null_ptr   = nulls.data() + prev_size;

		PT&   min                = stats.min;
		PT&   max                = stats.max;
		auto& last_seen_val      = stats.last_seen_val;
		auto& n_nulls            = stats.n_nulls;
		bool& is_double_castable = stats.is_double_castable;

		for (idx_t i = 0; i < count; i++) {
			PT         value   = src_column[i];
			const bool is_null = value == TypedNull<PT>();
			null_ptr[i]        = is_null;

			if (is_null) {
				++n_nulls;
				target_ptr[i] = last_seen_val;
			} else {
				target_ptr[i] = value;
				last_seen_val = value;

				min = std::min(min, value);
				max = std::max(max, value);

				if constexpr (std::is_same_v<PT, dbl_pt>) {
					if (is_double_castable && !Double::is_safely_castable_to_int64(value)) {
						is_double_castable = false;
					}
				}
			}
		}

		stats.min           = min;
		stats.max           = max;
		stats.last_seen_val = last_seen_val;
		stats.n_nulls       = n_nulls;

		if constexpr (std::is_same_v<PT, dbl_pt>) {
			stats.is_double_castable = is_double_castable;
		}
	}

private:
	FileWriter&             file_writer;
	up<RowgroupDescriptorT> row_group_descriptor;
	up<Rowgroup>            row_group;
	std::vector<n_t>        n_tuples_per_column;
};

} // namespace fastlanes

#endif // FLS_WRITER_WRITERv2_HPP