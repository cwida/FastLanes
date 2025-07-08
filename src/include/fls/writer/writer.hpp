#ifndef FLS_WRITER_WRITER_HPP
#define FLS_WRITER_WRITER_HPP

#include "fls/cor/lyt/buf.hpp"
#include "fls/io/io.hpp"
#include "fls/std/filesystem.hpp"
#include "fls/table/rowgroup.hpp"

namespace fastlanes {

constexpr std::string_view FOOTER_NAME = "table_descriptor.fbb";

/*--------------------------------------------------------------------------------------------------------------------*/
class Connection;
struct TableDescriptorT;
class RowGroupWriter;
/*--------------------------------------------------------------------------------------------------------------------*/
struct WriterOptions {
	WriterOptions()                           = default;
	WriterOptions(WriterOptions&&)            = default;
	WriterOptions& operator=(WriterOptions&&) = default;

	WriterOptions(const WriterOptions&)            = delete;
	WriterOptions& operator=(const WriterOptions&) = delete;

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
	friend class Builder;

public:
	class Builder {
	public:
		Builder& WithSchema(std::vector<std::unique_ptr<ColumnDescriptorT>>&& schema) {
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

		[[nodiscard]] std::unique_ptr<FileWriter> Build() {
			// Verify that the connection and file path are set.
			options.Validate();
			return std::unique_ptr<FileWriter>(new FileWriter(std::move(options)));
		}

	private:
		WriterOptions options {};
	};

	void Open();

	void Close();

	up<RowGroupWriter> CreateRowGroupWriter();

	[[nodiscard]] n_t GetSampleSize() const {
		return options.sample_size;
	}

	[[nodiscard]] bool IsForcedSchemaPool() const {
		return !options.forced_schema_pool.empty();
	}

	[[nodiscard]] const vector<OperatorToken>& GetForcedSchemaPool() const {
		return options.forced_schema_pool;
	}

	[[nodiscard]] bool IsForcedSchema() const {
		return !options.forced_schema.empty();
	}

	[[nodiscard]] const vector<OperatorToken>& GetForcedSchema() const {
		return options.forced_schema;
	}

private:
	explicit FileWriter(WriterOptions&& opts);

	void WriteFooter();
	void FlushRowGroup(const Buf& buf, up<RowgroupDescriptorT>&& descriptor);

private:
	WriterOptions options;
	std::mutex    flush_lock;
	io            io_target;
	io            io_footer;

	up<TableDescriptorT> table_descriptor;
	n_t                  cur_file_offset = 0;
	size_t               n_row_groups    = 0;
};

} // namespace fastlanes

#endif // FLS_WRITER_WRITER_HPP
