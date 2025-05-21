#include "benchmarker.hpp"

using namespace fastlanes; // NOLINT

class DecompressionTimeBenchmarker : public CompressionRatioBenchmarker {
public:
	explicit DecompressionTimeBenchmarker(const n_t n_repetitions)
	    : n_repetitions(n_repetitions) {
	}

	double bench_random_access(const path& dir_path) const {
		Connection conn;
		auto       fls_reader            = conn.reset().read_fls(dir_path);
		auto       first_rowgroup_reader = fls_reader->get_rowgroup_reader(0);

		const auto rowgroup_up = std::make_unique<Rowgroup>(first_rowgroup_reader->get_descriptor(), conn);
		// RandomAccessor random_accessor {*rowgroup_up};

		auto start = std::chrono::high_resolution_clock::now();
		for (n_t repetition_idx {0}; repetition_idx < n_repetitions; repetition_idx++) {
			[[maybe_unused]] auto& expressions = first_rowgroup_reader->get_chunk(0);
		}
		const auto                                      end     = std::chrono::high_resolution_clock::now();
		const std::chrono::duration<double, std::milli> elapsed = end - start; // in milliseconds

		return elapsed.count();
	}

public:
	n_t n_repetitions {0};
};

void benchmark_random_access(dataset_view_t dataset_view) {
	const std::string result_file_path =
	    std::string(FLS_CMAKE_SOURCE_DIR) + "/benchmark/result/random_access/public_bi/fastlanes.csv";

	// Ensure the output directory exists
	create_directories(std::filesystem::path(result_file_path).parent_path());

	// Containers for results to be sorted later
	std::vector<std::pair<std::string, double>> main_results;

	const n_t n_repetition {1000};

	// Generate a thread-specific directory path
	std::ostringstream thread_id_stream;
	thread_id_stream << std::this_thread::get_id();
	path thread_specific_fls_dir_path = fastlanes_repo_data_path / "data" / "fls" / thread_id_stream.str();

	// Iterate over all tables in the dataset and process them in parallel
	for (const auto& [table_name, file_path] : dataset_view) {
		DecompressionTimeBenchmarker benchmarker {n_repetition};

		benchmarker.Write(file_path, thread_specific_fls_dir_path);
		auto        random_access_ms = benchmarker.bench_random_access(thread_specific_fls_dir_path);
		const auto& footer_up        = benchmarker.GetTableDescriptor(thread_specific_fls_dir_path);

		az_printer::green_cout << "-- Table " << table_name << " is benchmarked with time(ms): " << random_access_ms
		                       << std::endl;

		main_results.emplace_back(table_name, random_access_ms);
	}

	// Sort main results by table name
	std::ranges::sort(main_results, [](const auto& a, const auto& b) { return a.first < b.first; });

	// Write results to the CSV files
	std::ofstream csv_file(result_file_path);
	if (!csv_file.is_open()) {
		throw std::runtime_error("Failed to open the CSV file for writing.");
	}
	csv_file << "table_name,version,random_access_ms,n_repetition\n";
	for (const auto& [table_name, random_access_ms] : main_results) {
		csv_file << table_name << "," << Info::get_version() << "," << random_access_ms << "," << n_repetition << "\n";
	}
	csv_file.close();

	remove_all(thread_specific_fls_dir_path);

	az_printer::green_cout << "-- Decompression times written to " << result_file_path << '\n';
}

int main() {
	benchmark_random_access(public_bi::dataset);
	return EXIT_SUCCESS;
}
