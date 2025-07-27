// ────────────────────────────────────────────────────────
// |                      FastLanes                       |
// ────────────────────────────────────────────────────────
// benchmark/bench_shared_schema.cpp
// ────────────────────────────────────────────────────────
#include "bench_shared_schema.hpp"
#include "benchmarker.hpp"

using namespace fastlanes; // NOLINT

// This function runs the benchmarks on each row group in parallel,
// collects the results in a shared container, and then writes the CSV file once after all tasks complete.
void bench_share_schema() {
	// Total number of row groups to process
	constexpr n_t total_rowgroups = 10;

	// Aggregated container for results.
	// Each tuple stores: (rowgroup_id, benchmark type ("shared" or "non_shared"), size)
	std::vector<std::tuple<n_t, std::string, n_t>> aggregated_results;
	std::mutex                                     aggregated_mutex;

	// Vector to store futures for each row group.
	std::vector<std::future<void>> rowgroup_futures;
	rowgroup_futures.reserve(total_rowgroups);

	CompressionRatioBenchmarker benchmarker;
	// Create a thread-specific directory path.
	std::ostringstream thread_id_stream;
	thread_id_stream << std::this_thread::get_id();
	std::filesystem::path thread_specific_fls_dir_path =
	    fastlanes_repo_data_path / "data" / "fls" / thread_id_stream.str();

	const std::string base_file_path =
	    std::string(FLS_CMAKE_SOURCE_DIR) + "/benchmark/accuracy_over_rowgroups/rowgroup_" + std::to_string(0);
	auto result = benchmarker.get_schema(base_file_path, thread_specific_fls_dir_path);

	for (n_t col_idx {0}; col_idx < result.size(); col_idx++) {
		az_printer::bold_blue_cout << col_idx << " | " << token_to_string(result[col_idx]) << "\n";
	}

	// Launch asynchronous tasks for each row group.
	for (n_t rowgroup_idx = 3; rowgroup_idx < 5; ++rowgroup_idx) {
		rowgroup_futures.emplace_back(
		    std::async(std::launch::async, [rowgroup_idx, &aggregated_results, &aggregated_mutex, result]() {
			    az_printer::bold_green_cout << "- RowGroup index " << rowgroup_idx << " started.\n";

			    // Local container for results from this row group.
			    std::vector<std::pair<std::string, n_t>> local_results;

			    // Container for table-level tasks (if more than one table, adjust accordingly).
			    std::vector<std::future<void>> table_futures;
			    table_futures.reserve(1);

			    // Container and mutex for thread-specific directory cleanup.
			    std::vector<std::filesystem::path> thread_specific_dirs;
			    std::mutex                         dirs_mutex;

			    // Build the directory path for this row group.
			    const std::string file_path = std::string(FLS_CMAKE_SOURCE_DIR) +
			                                  "/benchmark/accuracy_over_rowgroups/rowgroup_" +
			                                  std::to_string(rowgroup_idx);

			    // Launch the table-level async task.
			    table_futures.emplace_back(std::async(
			        std::launch::async, [&local_results, &dirs_mutex, &thread_specific_dirs, file_path, result]() {
				        CompressionRatioBenchmarker benchmarker;

				        // Create a thread-specific directory path.
				        std::ostringstream thread_id_stream;
				        thread_id_stream << std::this_thread::get_id();
				        std::filesystem::path thread_specific_fls_dir_path =
				            fastlanes_repo_data_path / "data" / "fls" / thread_id_stream.str();

				        {
					        std::lock_guard<std::mutex> lock(dirs_mutex);
					        thread_specific_dirs.push_back(thread_specific_fls_dir_path);
				        }

				        // Run the normal benchmark.
				        auto size = benchmarker.bench(file_path, thread_specific_fls_dir_path);
				        // Run the shared-schema benchmark (using bracket_values from bench_shared_schema.hpp).
				        auto shared_size =
				            benchmarker.bench_with_forced_schema(file_path, thread_specific_fls_dir_path, result);

				        // Store the results locally.
				        local_results.emplace_back("non_shared", size);
				        local_results.emplace_back("shared", shared_size);

				        // Cleanup thread-specific directories.
				        for (const auto& dir : thread_specific_dirs) {
					        std::filesystem::remove_all(dir);
					        az_printer::green_cout << "-- Removed directory: " << dir << std::endl;
				        }
			        }));

			    // Wait for table-level tasks to finish.
			    for (auto& fut : table_futures) {
				    fut.get();
			    }

			    // Optionally sort the local results (e.g., by label).
			    std::sort(local_results.begin(), local_results.end(), [](const auto& a, const auto& b) {
				    return a.first < b.first;
			    });

			    // Append local results to the aggregated results, tagging each with the current rowgroup index.
			    {
				    std::lock_guard<std::mutex> lock(aggregated_mutex);
				    for (const auto& res : local_results) {
					    aggregated_results.emplace_back(rowgroup_idx, res.first, res.second);
				    }
			    }
		    }));
	}

	// Wait for all row group tasks to complete.
	for (auto& fut : rowgroup_futures) {
		fut.get();
	}

	// Now that all row groups have been processed, write the aggregated results to one CSV file.
	std::string result_file_path =
	    std::string(FLS_CMAKE_SOURCE_DIR) + "/benchmark/result/shared_schema/public_bi/fastlanes.csv";
	create_directories(std::filesystem::path(result_file_path).parent_path());

	std::ofstream detailed_csv_file(result_file_path);
	if (!detailed_csv_file.is_open()) {
		throw std::runtime_error("Failed to open CSV file for writing: " + result_file_path);
	}
	// Write CSV header.
	detailed_csv_file << "rowgroup_id,total_size,is_shared\n";

	// Write each aggregated result as a line in the CSV.
	for (const auto& [rowgroup_id, label, size] : aggregated_results) {
		bool is_shared = (label == "shared");
		detailed_csv_file << rowgroup_id << "," << size << "," << (is_shared ? "true" : "false") << "\n";
	}
	detailed_csv_file.close();

	az_printer::green_cout << "-- Compression benchmark results written to " << result_file_path << '\n';
}

void prepare_dataset() {
	az_printer::yellow_cout << "Executing Python script...\n";

	auto script_path = std::string(FLS_CMAKE_SOURCE_DIR) + "/benchmark/share_schema/download_and_split.py";
	auto command     = std::string("python3 ") + script_path;

	int ret = std::system(command.c_str());
	if (ret != 0) {
		throw std::runtime_error("Failed to run Python script or script returned an error.\n");
	}
	az_printer::yellow_cout << "Python script executed successfully.\n";
}

int main() {
	// prepare_dataset(); // Uncomment if you want to auto-run the dataset preparation part
	az_printer::yellow_cout << "Make sure to disable casting.\n";
	bench_share_schema();
	return EXIT_SUCCESS;
}
