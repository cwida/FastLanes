#include "benchmarker.hpp"

using namespace fastlanes; // NOLINT

struct BenchmarkCase {
	dataset_view_t dataset;
	std::string    result_file_path;
	std::string    detailed_result_file_path;
};

BenchmarkCase public_bi_case {
    public_bi::dataset,
    std::string(FLS_CMAKE_SOURCE_DIR) + "/benchmark/result/compression_ratio/public_bi/fastlanes.csv",
    std::string(FLS_CMAKE_SOURCE_DIR) + "/benchmark/result/compression_ratio/public_bi/fastlanes_detailed.csv"};

BenchmarkCase fannie_mae_case {
    fannie_mae::dataset,
    std::string(FLS_CMAKE_SOURCE_DIR) + "/benchmark/result/compression_ratio/fannie_mae/fastlanes.csv",
    std::string(FLS_CMAKE_SOURCE_DIR) + "/benchmark/result/compression_ratio/fannie_mae/fastlanes_detailed.csv"};

BenchmarkCase sdrbnech_case {
    sdrbnech::dataset,
    std::string(FLS_CMAKE_SOURCE_DIR) + "/benchmark/result/compression_ratio/sdrbnech/fastlanes.csv",
    std::string(FLS_CMAKE_SOURCE_DIR) + "/benchmark/result/compression_ratio/sdrbnech/fastlanes_detailed.csv"};

BenchmarkCase fc_bench_case {
    fc_bench::dataset,
    std::string(FLS_CMAKE_SOURCE_DIR) + "/benchmark/result/compression_ratio/fc_bench/fastlanes.csv",
    std::string(FLS_CMAKE_SOURCE_DIR) + "/benchmark/result/compression_ratio/fc_bench/fastlanes_detailed.csv"};

BenchmarkCase nextia_jd_case {
    NextiaJD::dataset,
    std::string(FLS_CMAKE_SOURCE_DIR) + "/benchmark/result/compression_ratio/nextia_jd/fastlanes.csv",
    std::string(FLS_CMAKE_SOURCE_DIR) + "/benchmark/result/compression_ratio/nextia_jd/fastlanes_detailed.csv"};

void run_compression_ratio_benchmark(const BenchmarkCase& benchmark_case) {
	const auto& result_file_path          = benchmark_case.result_file_path;
	const auto  detailed_result_file_path = benchmark_case.detailed_result_file_path;
	const auto& dataset                   = benchmark_case.dataset;

	// Prepare a path for the new summary of compression ratios
	auto ratio_file_path = std::filesystem::path(result_file_path).parent_path() / "compression_summary.csv";

	// Ensure the output directory exists
	create_directories(std::filesystem::path(result_file_path).parent_path());

	// Containers for results to be sorted later
	std::vector<std::tuple<std::string, n_t, uint64_t>>                                         main_results;
	std::vector<std::tuple<std::string, n_t, std::string, DataType, n_t, RPNT, double, double>> detailed_results;

	std::mutex                     results_mutex;
	std::mutex                     dirs_mutex;
	std::vector<path>              thread_specific_dirs;
	std::vector<std::future<void>> futures;
	futures.reserve(dataset.size());

	for (const auto& [table_name, file_path] : dataset) {
		futures.emplace_back(std::async(std::launch::async, [&]() {
			CompressionRatioBenchmarker benchmarker;
			std::ostringstream          tid;
			tid << std::this_thread::get_id();
			path fls_dir = fastlanes_repo_data_path / "data" / "fls" / tid.str();
			{
				std::lock_guard<std::mutex> lk(dirs_mutex);
				thread_specific_dirs.push_back(fls_dir);
			}

			auto fls_size = benchmarker.bench(file_path, fls_dir);
			// Determine CSV file path by scanning the directory for the .csv file
			std::filesystem::path csv_file_path;
			for (auto& entry : std::filesystem::directory_iterator(file_path)) {
				if (entry.path().extension() == ".csv") {
					csv_file_path = entry.path();
					break;
				}
			}
			if (csv_file_path.empty()) {
				throw std::runtime_error("No CSV file found in directory: " + std::string(file_path));
			}
			uint64_t csv_size = std::filesystem::file_size(csv_file_path);

			{
				std::lock_guard<std::mutex> lk(results_mutex);
				main_results.emplace_back(table_name, fls_size, csv_size);
			}

			const auto& tbl_desc = benchmarker.GetTableDescriptor(fls_dir);
			const auto& rg_desc  = tbl_desc->m_rowgroup_descriptors[0];
			{
				std::lock_guard<std::mutex> lk(results_mutex);
				for (const auto& col : rg_desc->m_column_descriptors) {
					double bytes_per_tuple = double(col->total_size) / (double(rg_desc->m_n_vec) * CFG::VEC_SZ);
					double bits_per_tuple  = bytes_per_tuple * 8;
					detailed_results.emplace_back(table_name,
					                              col->idx,
					                              col->name,
					                              col->data_type,
					                              col->total_size,
					                              *col->encoding_rpn,
					                              bytes_per_tuple,
					                              bits_per_tuple);
				}
			}

			az_printer::green_cout << "-- Table " << table_name << " bench in " << fls_dir << ", FLS size=" << fls_size
			                       << ", CSV size=" << csv_size << std::endl;
		}));
	}
	for (auto& f : futures)
		f.get();

	std::sort(
	    main_results.begin(), main_results.end(), [](auto& a, auto& b) { return std::get<0>(a) < std::get<0>(b); });
	std::sort(detailed_results.begin(), detailed_results.end(), [](auto& a, auto& b) {
		if (std::get<0>(a) == std::get<0>(b))
			return std::get<1>(a) < std::get<1>(b);
		return std::get<0>(a) < std::get<0>(b);
	});

	{
		std::ofstream out(result_file_path);
		out << "table_name,version,file_size\n";
		for (auto& [table, fls_sz, csv_sz] : main_results) {
			out << table << "," << Info::get_version() << "," << fls_sz << "\n";
		}
	}

	{
		std::ofstream out(detailed_result_file_path);
		out << "compression,version,table_name,id,name,data_type,size(bytes),expression,bytes_per_value,bits_per_"
		       "value\n";
		for (auto& [table, id, name, dt, size, rpn, bpt, btv] : detailed_results) {
			out << Info::get_name() << "," << Info::get_version() << "," << table << "," << id << "," << name << ","
			    << dt << "," << size << ",\"" << rpn << "\""
			    << "," << std::fixed << std::setprecision(2) << bpt << "," << std::fixed << std::setprecision(2) << btv
			    << "\n";
		}
	}

	{
		std::ofstream out(ratio_file_path);
		if (!out.is_open()) {
			throw std::runtime_error("Failed to open compression summary file");
		}
		out << "table_name,version,csv_size,fls_size,compression_ratio\n";
		for (auto& [table, fls_sz, csv_sz] : main_results) {
			double ratio = double(csv_sz) / double(fls_sz);
			out << table << "," << Info::get_version() << "," << csv_sz << "," << fls_sz << "," << std::fixed
			    << std::setprecision(2) << ratio << "\n";
		}
	}

	for (auto& dir : thread_specific_dirs) {
		std::filesystem::remove_all(dir);
		az_printer::green_cout << "-- Removed " << dir << std::endl;
	}

	az_printer::green_cout << "-- Results written to " << result_file_path << std::endl;
	az_printer::green_cout << "-- Detailed results to " << detailed_result_file_path << std::endl;
	az_printer::green_cout << "-- Summary to " << ratio_file_path << std::endl;
}

int main() {
	run_compression_ratio_benchmark(public_bi_case);
	return EXIT_SUCCESS;
}
