#include "benchmarker.hpp"

using namespace fastlanes; // NOLINT

class DecompressionTimeBenchmarker : public CompressionRatioBenchmarker {
public:
	explicit DecompressionTimeBenchmarker(const n_t n_repetitions)
	    : n_repetitions(n_repetitions) {
	}

	[[nodiscard]] double bench(const path& dir_path) const {
		Connection conn;

		auto fls_reader            = conn.reset().read_fls(dir_path);
		auto first_rowgroup_reader = fls_reader->get_rowgroup_reader(0);

		auto start = std::chrono::high_resolution_clock::now();
		for (n_t repetition_idx {0}; repetition_idx < n_repetitions; repetition_idx++) {
			for (n_t vec_idx {0}; vec_idx < first_rowgroup_reader->get_descriptor().m_n_vec; vec_idx++) {
				first_rowgroup_reader->get_chunk(vec_idx);
			};
		}
		const auto                                      end     = std::chrono::high_resolution_clock::now();
		const std::chrono::duration<double, std::milli> elapsed = end - start; // in milliseconds

		return elapsed.count();
	}

public:
	n_t n_repetitions {0};
};

void bench_decompression(dataset_view_t dataset_view) {
	const std::string result_file_path =
	    std::string(FLS_CMAKE_SOURCE_DIR) + "/benchmark/result/decompression_time/public_bi/fastlanes.csv";

	// Ensure the output directory exists
	create_directories(std::filesystem::path(result_file_path).parent_path());

	// Containers for results to be sorted later
	std::vector<std::pair<std::string, double>> main_results;

	// Vector to store thread-specific directories for cleanup
	const n_t n_repetition {1000};

	// Generate a thread-specific directory path
	std::ostringstream thread_id_stream;
	thread_id_stream << std::this_thread::get_id();
	path thread_specific_fls_dir_path = fastlanes_repo_data_path / "data" / "fls" / thread_id_stream.str();

	// Iterate over all tables in the dataset and process them in parallel
	for (const auto& [table_name, file_path] : dataset_view) {
		DecompressionTimeBenchmarker benchmarker {n_repetition};

		benchmarker.Write(file_path, thread_specific_fls_dir_path);
		auto        decompression_time_ms = benchmarker.bench(thread_specific_fls_dir_path);
		const auto& footer_up             = benchmarker.GetTableDescriptor(thread_specific_fls_dir_path);

		az_printer::green_cout << "-- Table " << table_name
		                       << " is benchmarked with time(ms): " << decompression_time_ms << std::endl;

		main_results.emplace_back(table_name, decompression_time_ms);
	}

	// Sort main results by table name
	std::ranges::sort(main_results, [](const auto& a, const auto& b) { return a.first < b.first; });

	// Compute the sum of decompression times
	double total_decompression_time_ms = 0;
	for (const auto& [_, decompression_time_ms] : main_results) {
		total_decompression_time_ms += decompression_time_ms;
	}

	// Write results to the CSV files
	std::ofstream csv_file(result_file_path);
	if (!csv_file.is_open()) {
		throw std::runtime_error("Failed to open the CSV file for writing.");
	}
	csv_file << "table_name,version,decompression_time_ms,n_repetition\n";
	for (const auto& [table_name, decompression_time_ms] : main_results) {
		csv_file << table_name << "," << Info::get_version() << "," << decompression_time_ms << "," << n_repetition
		         << "\n";
	}
	csv_file.close();

	// Print the total sum to the console
	az_printer::bold_magenta_cout << "-- Total decompression time (ms): " << total_decompression_time_ms << std::endl;

	// Cleanup: Remove the thread-specific directory
	remove_all(thread_specific_fls_dir_path);
	az_printer::green_cout << "-- Removed directory: " << thread_specific_fls_dir_path << std::endl;
	az_printer::green_cout << "-- Decompression times written to " << result_file_path << '\n';
}

int main() {
	const auto start = std::chrono::high_resolution_clock::now();
	bench_decompression(public_bi::dataset);
	auto                                            end     = std::chrono::high_resolution_clock::now();
	const std::chrono::duration<double, std::milli> elapsed = end - start; // in milliseconds
	az_printer::bold_magenta_cout << "-- The whole benchmark time (ms): " << elapsed.count() << '\n';
	return EXIT_SUCCESS;
}
