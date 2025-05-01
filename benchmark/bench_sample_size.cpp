#include "benchmarker.hpp"

using namespace fastlanes; // NOLINT

void bench_sampling() {
	for (n_t sample_size {0}; sample_size < 65; sample_size++) {
		az_printer::bold_green_cout << "- Sample benchmark of size " << sample_size << " started." << std::endl;
		const std::string result_file_path = std::string(FLS_CMAKE_SOURCE_DIR) +
		                                     "/benchmark/result/sampling_benchmark/" + std::to_string(sample_size) +
		                                     "/public_bi/fastlanes.csv";

		const std::string detailed_result_file_path = std::string(FLS_CMAKE_SOURCE_DIR) +
		                                              "/benchmark/result/sampling_benchmark/" +
		                                              std::to_string(sample_size) + "/public_bi/fastlanes_detailed.csv";

		// Ensure the output directory exists
		create_directories(std::filesystem::path(result_file_path).parent_path());

		// Containers for results to be sorted later
		std::vector<std::pair<std::string, n_t>>                                                      main_results;
		std::vector<std::tuple<std::string, n_t, std::string, DataType, n_t, NewRPN, double, double>> detailed_results;

		// Mutex for thread-safe access to the results containers
		std::mutex results_mutex;

		// Vector to store futures for asynchronous processing
		std::vector<std::future<void>> futures;
		futures.reserve(public_bi::dataset.size());

		// Vector to store thread-specific directories for cleanup
		std::vector<path> thread_specific_dirs;
		std::mutex        dirs_mutex;

		// Iterate over all tables in the dataset and process them in parallel
		for (const auto& [table_name, file_path] : public_bi::dataset) {
			futures.emplace_back(std::async(
			    std::launch::async,
			    [&results_mutex,
			     &dirs_mutex,
			     &thread_specific_dirs,
			     &main_results,
			     &detailed_results,
			     table_name,
			     file_path,
			     sample_size]() {
				    CompressionRatioBenchmarker benchmarker;

				    // Generate a thread-specific directory path
				    std::ostringstream thread_id_stream;
				    thread_id_stream << std::this_thread::get_id();
				    path thread_specific_fls_dir_path =
				        fastlanes_repo_data_path / "data" / "fls" / thread_id_stream.str();

				    // Store the directory for cleanup (thread-safe)
				    {
					    std::lock_guard<std::mutex> lock(dirs_mutex);
					    thread_specific_dirs.push_back(thread_specific_fls_dir_path);
				    }

				    auto size =
				        benchmarker.bench_with_sample_size(file_path, thread_specific_fls_dir_path, sample_size);
				    const auto& table_descriptor = benchmarker.GetTableDescriptor(thread_specific_fls_dir_path);
				    const auto& first_rowgroup_descriptor = table_descriptor->m_rowgroup_descriptors[0];

				    // Store the main result (thread-safe)
				    {
					    std::lock_guard<std::mutex> lock(results_mutex);
					    main_results.emplace_back(table_name, size);
				    }

				    // Store the detailed results (thread-safe)
				    {
					    std::lock_guard<std::mutex> lock(results_mutex);
					    for (const auto& column_descriptor : first_rowgroup_descriptor.GetColumnDescriptors()) {
						    double bpt = static_cast<double>(column_descriptor.total_size) /
						                 (static_cast<double>(first_rowgroup_descriptor.m_n_vec * CFG::VEC_SZ));
						    double Bpt = bpt / 8;

						    detailed_results.emplace_back(table_name,
						                                  column_descriptor.idx,
						                                  column_descriptor.name,
						                                  column_descriptor.data_type,
						                                  column_descriptor.total_size,
						                                  column_descriptor.encoding_rpn,
						                                  bpt,
						                                  Bpt);
					    }
				    }

				    az_printer::green_cout << "-- Table " << table_name << " is benchmarked.! Size: " << size
				                           << std::endl;
			    }));
		}

		// Wait for all futures to complete
		for (auto& future : futures) {
			future.get();
		}

		// Sort main results by table name
		std::sort(
		    main_results.begin(), main_results.end(), [](const auto& a, const auto& b) { return a.first < b.first; });

		// Sort detailed results by table name, then by column index
		std::sort(detailed_results.begin(), detailed_results.end(), [](const auto& a, const auto& b) {
			if (std::get<0>(a) == std::get<0>(b)) {
				return std::get<1>(a) < std::get<1>(b); // Sort by column index if table names are equal
			}
			return std::get<0>(a) < std::get<0>(b); // Sort by table name
		});

		// Compute and print the total size across all tables
		n_t total_size = 0;
		for (const auto& [table_name, size] : main_results) {
			total_size += size;
		}
		az_printer::bold_blue_cout << "-- Total compressed size across all tables: " << total_size << " bytes\n";

		// Write results to the CSV files
		std::ofstream csv_file(result_file_path);
		if (!csv_file.is_open()) {
			throw std::runtime_error("Failed to open the CSV file for writing.");
		}
		csv_file << "table_name,version,file_size\n";
		for (const auto& [table_name, size] : main_results) {
			csv_file << table_name << "," << Info::get_version() << "," << size << "\n";
		}
		csv_file.close();

		std::ofstream detailed_csv_file(detailed_result_file_path);
		if (!detailed_csv_file.is_open()) {
			throw std::runtime_error("Failed to open the detailed CSV file for writing.");
		}
		detailed_csv_file << "compression,version,name,id,name,data_type,size(bytes),bpt,Bpt\n";
		for (const auto& [table_name, id, name, data_type, size, encoding_rpn, bpt, Bpt] : detailed_results) {
			detailed_csv_file << Info::get_name() << "," << Info::get_version() << "," << table_name << "," << id << ","
			                  << name << "," << data_type << "," << size << "," << encoding_rpn << "," << std::fixed
			                  << std::setprecision(2) << bpt << "," << std::fixed << std::setprecision(2) << Bpt
			                  << "\n";
		}
		detailed_csv_file.close();

		// Cleanup: Remove all thread-specific directories
		for (const auto& dir : thread_specific_dirs) {
			std::filesystem::remove_all(dir);
			az_printer::green_cout << "-- Removed directory: " << dir << std::endl;
		}

		az_printer::green_cout << "-- Compression benchmark results written to " << result_file_path << '\n';
		az_printer::green_cout << "-- Detailed compression benchmark results written to " << detailed_result_file_path
		                       << '\n';
	}
}

int main() {
	bench_sampling();
	return EXIT_SUCCESS;
}
