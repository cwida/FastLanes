#include "benchmarker.hpp"
#include "cycle_counter.hpp"

using namespace fastlanes; // NOLINT

class DecompressionTimeBenchmarker : public CompressionRatioBenchmarker {
public:
	explicit DecompressionTimeBenchmarker(const n_t n_repetitions)
	    : n_repetitions(n_repetitions) {
	}

	double bench(const path& dir_path) const {
		Connection conn;

		auto fls_reader      = conn.reset().read_fls(dir_path);
		auto rowgroup_reader = fls_reader->get_rowgroup_reader(0);

		auto start = benchmark::cycleclock::Now();
		for (n_t repetition_idx {0}; repetition_idx < n_repetitions; repetition_idx++) {
			for (n_t vec_idx {0}; vec_idx < rowgroup_reader->get_descriptor().m_n_vec; vec_idx++) {
				rowgroup_reader->get_chunk(vec_idx);
			};
		}
		const auto end            = benchmark::cycleclock::Now();
		auto       elapsed_cycles = end - start;

		return static_cast<double>(elapsed_cycles) /
		       (static_cast<double>(rowgroup_reader->get_descriptor().GetNVectors() * CFG::VEC_SZ * n_repetitions));
	}

public:
	n_t n_repetitions {0};
};

void micro_benchmark_decompression(detailed_dataset_view_t dataset_view, const std::string& result_file_path) {
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
	for (const auto& [table_name, file_path, idxs] : dataset_view) {
		DecompressionTimeBenchmarker benchmarker {n_repetition};

		benchmarker.Write(file_path, thread_specific_fls_dir_path, idxs);
		auto        cycles_per_value = benchmarker.bench(thread_specific_fls_dir_path);
		const auto& footer_up        = benchmarker.GetTableDescriptor(thread_specific_fls_dir_path);

		az_printer::result_cout << "--- Table " << table_name << "  with cycles per value: " << cycles_per_value
		                        << std::endl;

		main_results.emplace_back(table_name, cycles_per_value);
	}

	// Sort main results by table name
	std::ranges::sort(main_results, [](const auto& a, const auto& b) { return a.first < b.first; });

	// Write results to the CSV files
	std::ofstream csv_file(result_file_path);
	if (!csv_file.is_open()) {
		throw std::runtime_error("Failed to open the CSV file for writing.");
	}
	csv_file << "table_name,version,cycles_per_value,n_repetition\n";
	for (const auto& [table_name, decompression_time_ms] : main_results) {
		csv_file << table_name << "," << Info::get_version() << "," << decompression_time_ms << "," << n_repetition
		         << "\n";
	}
	csv_file.close();

	// Cleanup: Remove the thread-specific directory
	remove_all(thread_specific_fls_dir_path);
	az_printer::yellow_cout << "-- Removed directory: " << thread_specific_fls_dir_path << std::endl;
	az_printer::yellow_cout << "-- Cycles per value are written to " << result_file_path << '\n';
}

static std::array<DetailedTableView, 36> my_dataset = {
    {//
     {"Arade", public_bi::Arade, {0}},
     {"Bimbo", public_bi::Bimbo, {0}},
     {"CMSprovider", public_bi::CMSprovider, {0}},
     {"CityMaxCapita", public_bi::CityMaxCapita, {0}},
     {"CommonGovernment", public_bi::CommonGovernment, {0}},
     {"Corporations", public_bi::Corporations, {0}},
     {"Eixo", public_bi::Eixo, {0}},
     {"Euro2016", public_bi::Euro2016, {0}},
     {"Food", public_bi::Food, {0}},
     {"Generico", public_bi::Generico, {0}},
     {"HashTags", public_bi::HashTags, {0}},
     {"Hatred", public_bi::Hatred, {0}},
     {"IGlocations1", public_bi::IGlocations1, {0}},
     {"MLB", public_bi::MLB, {0}},
     {"MedPayment1", public_bi::MedPayment1, {0}},
     {"Medicare1", public_bi::Medicare1, {0}},
     {"Motos", public_bi::Motos, {0}},
     {"MulheresMil", public_bi::MulheresMil, {0}},
     {"NYC", public_bi::NYC, {0}},
     {"PanCreactomy1", public_bi::PanCreactomy1, {0}},
     {"Physicians", public_bi::Physicians, {0}},
     {"Provider", public_bi::Provider, {0}},
     {"RealEstate1", public_bi::RealEstate1, {0}},
     {"Redfin1", public_bi::Redfin1, {0}},
     {"Rentabilidad", public_bi::Rentabilidad, {0}},
     {"Romance", public_bi::Romance, {0}},
     {"SalariesFrance", public_bi::SalariesFrance, {0}},
     {"TableroSistemaPenal", public_bi::TableroSistemaPenal, {0}},
     {"Taxpayer", public_bi::Taxpayer, {0}},
     {"Telco", public_bi::Telco, {0}},
     {"TrainsUK1", public_bi::TrainsUK1, {0}},
     {"TrainsUK2", public_bi::TrainsUK2, {0}},
     {"USCensus", public_bi::USCensus, {0}},
     {"Uberlandia", public_bi::Uberlandia, {0}},
     {"Wins", public_bi::Wins, {0}},
     {"YaleLanguages", public_bi::YaleLanguages, {0}}}
    //
};

int main() {
	az_printer::bold_green_cout << "- Micro benchmark decompression started!" << std::endl;

	benchmark::cycleclock::Init();
	const std::string result_file_path =
	    std::string(FLS_CMAKE_SOURCE_DIR) + "/benchmark/result/decompression_time/my_dataset/fastlanes.csv";
	micro_benchmark_decompression(my_dataset, result_file_path);

	az_printer::bold_green_cout << "- Micro benchmark decompression ended successfully!" << std::endl;
	return EXIT_SUCCESS;
}
