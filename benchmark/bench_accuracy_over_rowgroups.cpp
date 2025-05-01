#include "benchmarker.hpp"

using namespace fastlanes; // NOLINT

void bench_accuracy_over_rowgroups() {
	// We'll create one future per row group
	constexpr n_t                  total_rowgroups = 47;
	std::vector<std::future<void>> rowgroup_futures;
	rowgroup_futures.reserve(total_rowgroups);

	for (n_t rowgroup_idx {0}; rowgroup_idx < total_rowgroups; rowgroup_idx++) {
		// Launch each row group as an asynchronous task
		rowgroup_futures.emplace_back(std::async(std::launch::async, [rowgroup_idx]() {
			az_printer::bold_green_cout << "- RowGroup index " << rowgroup_idx << " started.\n";

			// Build file paths specific to this rowgroup
			const std::string result_file_path = std::string(FLS_CMAKE_SOURCE_DIR) +
			                                     "/benchmark/result/accuracy_over_rowgroup/" +
			                                     std::to_string(rowgroup_idx) + "/public_bi/fastlanes.csv";

			const std::string detailed_result_file_path =
			    std::string(FLS_CMAKE_SOURCE_DIR) + "/benchmark/result/accuracy_over_rowgroup/" +
			    std::to_string(rowgroup_idx) + "/public_bi/fastlanes_detailed.csv";

			// Ensure output directory exists
			create_directories(std::filesystem::path(result_file_path).parent_path());

			// Containers for results
			std::vector<std::pair<std::string, n_t>> main_results;
			std::vector<std::tuple<std::string, n_t, std::string, DataType, n_t, NewRPN, double, double>>
			    detailed_results;

			// Shared mutex to protect result containers within this rowgroup
			std::mutex results_mutex;

			// Vector of futures for table-level parallelism (if you have multiple tables)
			std::vector<std::future<void>> futures;
			futures.reserve(public_bi::dataset.size());

			// Vector to store thread-specific directories for cleanup
			std::vector<std::filesystem::path> thread_specific_dirs;
			std::mutex                         dirs_mutex;

			// Directory that holds rowgroup files
			const auto uscensus_table_name = "USCensus";
			const auto file_path = std::string(FLS_CMAKE_SOURCE_DIR) + "/benchmark/accuracy_over_rowgroups/rowgroup_" +
			                       std::to_string(rowgroup_idx);

			// --------------------------------------------------------------------
			// If you have multiple tables, you'd do something like:
			//
			// for (auto & table_info : public_bi::dataset) {
			//     futures.emplace_back(std::async(std::launch::async, [...](){
			//         ... do the benchmark for that table ...
			//     }));
			// }
			//
			// But if you truly have just a single table to process, you can leave it as one task.
			// --------------------------------------------------------------------

			// For now, let's assume just one table (as in your code snippet):
			futures.emplace_back(std::async(
			    std::launch::async,
			    [&results_mutex,
			     &dirs_mutex,
			     &thread_specific_dirs,
			     &main_results,
			     &detailed_results,
			     uscensus_table_name,
			     file_path]() {
				    CompressionRatioBenchmarker benchmarker;

				    // Generate a thread-specific directory path
				    std::ostringstream thread_id_stream;
				    thread_id_stream << std::this_thread::get_id();
				    std::filesystem::path thread_specific_fls_dir_path =
				        fastlanes_repo_data_path / "data" / "fls" / thread_id_stream.str();

				    // Store the directory for cleanup
				    {
					    std::lock_guard<std::mutex> lock(dirs_mutex);
					    thread_specific_dirs.push_back(thread_specific_fls_dir_path);
				    }

				    // Run the benchmark
				    auto        size      = benchmarker.bench(file_path, thread_specific_fls_dir_path);
				    const auto& footer_up = benchmarker.GetTableDescriptor(thread_specific_fls_dir_path);
				    const auto& first_rowgroup_descriptor = footer_up->m_rowgroup_descriptors[0];

				    {
					    // Lock and store the main result
					    std::lock_guard<std::mutex> lock(results_mutex);
					    main_results.emplace_back(uscensus_table_name, size);
				    }

				    {
					    // Lock and store the detailed results
					    std::lock_guard<std::mutex> lock(results_mutex);
					    for (const auto& column_descriptor : first_rowgroup_descriptor.GetColumnDescriptors()) {
						    double bpt = static_cast<double>(column_descriptor.total_size) /
						                 (static_cast<double>(first_rowgroup_descriptor.m_n_vec * CFG::VEC_SZ));
						    double Bpt = bpt / 8.0;

						    detailed_results.emplace_back(uscensus_table_name,
						                                  column_descriptor.idx,
						                                  column_descriptor.name,
						                                  column_descriptor.data_type,
						                                  column_descriptor.total_size,
						                                  column_descriptor.encoding_rpn,
						                                  bpt,
						                                  Bpt);
					    }
				    }

				    az_printer::green_cout << "-- Table " << uscensus_table_name << " is benchmarked. "
				                           << "Size: " << size << std::endl;
			    }));

			// Wait for all table-specific futures in this row group
			for (auto& future : futures) {
				future.get();
			}

			// Sort the results (within this row group) before writing
			std::sort(main_results.begin(), main_results.end(), [](const auto& a, const auto& b) {
				return a.first < b.first;
			});

			std::sort(detailed_results.begin(), detailed_results.end(), [](const auto& a, const auto& b) {
				// Sort by table name, then column index
				if (std::get<0>(a) == std::get<0>(b)) {
					return std::get<1>(a) < std::get<1>(b);
				}
				return std::get<0>(a) < std::get<0>(b);
			});

			// Write the detailed results
			std::ofstream detailed_csv_file(detailed_result_file_path);
			if (!detailed_csv_file.is_open()) {
				throw std::runtime_error("Failed to open the detailed CSV file for writing.");
			}
			detailed_csv_file << "compression,version,name,id,name,data_type,size(bytes),expression,bpt,Bpt\n";
			for (const auto& [table_name, id, name, data_type, size, encoding_rpn, bpt, Bpt] : detailed_results) {
				detailed_csv_file << Info::get_name() << "," << Info::get_version() << "," << table_name << "," << id
				                  << "," << name << "," << data_type << "," << size << "," << '"' << encoding_rpn << '"'
				                  << "," << std::fixed << std::setprecision(2) << bpt << "," << std::fixed
				                  << std::setprecision(2) << Bpt << "\n";
			}
			detailed_csv_file.close();

			// Cleanup: remove all thread-specific directories for this row group
			for (const auto& dir : thread_specific_dirs) {
				std::filesystem::remove_all(dir);
				az_printer::green_cout << "-- Removed directory: " << dir << std::endl;
			}

			az_printer::green_cout << "-- Compression benchmark results written to " << result_file_path << '\n';
			az_printer::green_cout << "-- Detailed compression benchmark results written to "
			                       << detailed_result_file_path << '\n';
		})); // end of async
	}

	// Now wait for all row-group tasks to finish
	for (auto& rg_future : rowgroup_futures) {
		rg_future.get();
	}
}

void prepare_dataset() {
	az_printer::yellow_cout << "Executing Python script...\n";

	auto script_path = std::string(FLS_CMAKE_SOURCE_DIR) + "/benchmark/accuracy_over_rowgroups/download_and_split.py";
	auto command     = std::string("python3 ") + script_path; // Properly concatenated command

	int ret = std::system(command.c_str());
	if (ret != 0) {
		throw std::runtime_error("Failed to run Python script or script returned an error.\n");
	}
	az_printer::yellow_cout << "Python script executed successfully.\n";
}

int main() {
	// prepare_dataset(); // Un-comment if you want to auto-run prepartin part
	bench_accuracy_over_rowgroups();
	return EXIT_SUCCESS;
}
