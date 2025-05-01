#ifndef BENCHMARKER_HPP
#define BENCHMARKER_HPP

#include "data/fastlanes_data.hpp"
#include "fastlanes.hpp"
#include "fls/connection.hpp"
#include "fls/info.hpp"
#include "fls/printer/az_printer.hpp"
#include "fls/std/filesystem.hpp"
#include <algorithm> // For std::sort
#include <fstream>
#include <future> // For std::async and std::future
#include <mutex>  // For std::mutex and std::lock_guard
#include <thread> // For std::this_thread::get_id
#include <tuple>
#include <vector>

namespace fastlanes {
struct DetailedTableView {
	std::string_view table_name;
	std::string_view path;
	vector<idx_t>    sub_idxs;
};
using detailed_dataset_view_t = std::span<DetailedTableView>;

using dataset_view_t = std::span<const std::pair<std::string_view, std::string_view>>;
const path fastlanes_repo_data_path {FLS_CMAKE_SOURCE_DIR};

class CompressionRatioBenchmarker {
public:
	// Method to write a table's data to a thread-specific FLS directory
	void Write(const string_view file_path, const path& thread_specific_fls_dir_path) const {
		const path dir_path = fastlanes_repo_data_path / string(file_path);

		// Ensure the thread-specific directory exists
		create_directories(thread_specific_fls_dir_path);

		// Original rowgroup
		Connection con1;
		con1.reset().read_csv(dir_path);
		con1.to_fls(thread_specific_fls_dir_path);
	}
	// Method to write a table's data to a thread-specific FLS directory
	void Write(const string_view file_path, const path& thread_specific_fls_dir_path, const vector<idx_t>& idxs) const {
		const path dir_path = fastlanes_repo_data_path / string(file_path);

		// Ensure the thread-specific directory exists
		create_directories(thread_specific_fls_dir_path);

		// Original rowgroup
		Connection con1;
		con1.reset().read_csv(dir_path).project(idxs);
		con1.to_fls(thread_specific_fls_dir_path);
	}
	// Method to write a table's data to a thread-specific FLS directory
	void Write(const string_view file_path, const path& thread_specific_fls_dir_path, n_t sample_size) const {
		const path dir_path = fastlanes_repo_data_path / string(file_path);

		// Ensure the thread-specific directory exists
		create_directories(thread_specific_fls_dir_path);

		// Original rowgroup
		Connection con1;
		con1.reset().read_csv(dir_path);
		con1.set_sample_size(sample_size).to_fls(thread_specific_fls_dir_path);
	}
	// Method to write a table's data to a thread-specific FLS directory
	void Write(const string_view            file_path,
	           const path&                  thread_specific_fls_dir_path,
	           const vector<OperatorToken>& operator_tokens) const {
		const path dir_path = fastlanes_repo_data_path / string(file_path);

		// Ensure the thread-specific directory exists
		create_directories(thread_specific_fls_dir_path);

		// Original rowgroup
		Connection con1;
		con1.reset().read_csv(dir_path);
		con1.force_schema(operator_tokens).to_fls(thread_specific_fls_dir_path);
	}

	// Method to get the footer for the thread-specific directory
	[[nodiscard]] up<TableDescriptor> GetTableDescriptor(const path& thread_specific_fls_dir_path) const {
		return make_table_descriptor(thread_specific_fls_dir_path / TABLE_DESCRIPTOR_FILE_NAME);
	}

	// Benchmarks the compression ratio by writing and returning the file size
	[[nodiscard]] n_t bench(const string_view table_path, const path& thread_specific_fls_dir_path) const {
		Write(table_path, thread_specific_fls_dir_path);
		return file_size(thread_specific_fls_dir_path / "data.fls");
	}

	// Benchmarks the compression ratio by writing and returning the file size
	[[nodiscard]] n_t bench_with_sample_size(const string_view table_path,
	                                         const path&       thread_specific_fls_dir_path,
	                                         n_t               sample_size) const {
		Write(table_path, thread_specific_fls_dir_path, sample_size);
		return file_size(thread_specific_fls_dir_path / "data.fls");
	}

	// Benchmarks the compression ratio by writing and returning the file size
	[[nodiscard]] n_t bench_with_forced_schema(const string_view            table_path,
	                                           const path&                  thread_specific_fls_dir_path,
	                                           const vector<OperatorToken>& operator_tokens) const {
		Write(table_path, thread_specific_fls_dir_path, operator_tokens);
		return file_size(thread_specific_fls_dir_path / "data.fls");
	}
	// Benchmarks the compression ratio by writing and returning the file size
	[[nodiscard]] vector<OperatorToken> get_schema(const string_view table_path,
	                                               const path&       thread_specific_fls_dir_path) const {
		Write(table_path, thread_specific_fls_dir_path);
		vector<OperatorToken> result;
		auto                  table_descriptor    = GetTableDescriptor(thread_specific_fls_dir_path);
		auto                  rowgroup_descriptor = table_descriptor->m_rowgroup_descriptors[0];

		// Store the detailed results (thread-safe)
		{
			for (const auto& column_descriptor : rowgroup_descriptor.m_column_descriptors) {
				result.emplace_back(column_descriptor.encoding_rpn.operator_tokens[0]);
			}
		}

		return result;
	}
};

} // namespace fastlanes

#endif // BENCHMARKER_HPP
