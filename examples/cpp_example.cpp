#include "data/fastlanes_data.hpp"
#include "fastlanes.hpp"
#include "fls/connection.hpp"
#include "fls/printer/az_printer.hpp"

using namespace fastlanes; // NOLINT

int main() {

	try {
		Connection con1;
		const path example_dir_path = string(issue::ISSUE_000);
		const path fls_file_path    = path {FLS_CMAKE_SOURCE_DIR} / "data" / "fls" / "data.fls";
		const path csv_file_path    = fls_file_path.parent_path() / "fastlanes.csv";

		// Remove only data.fls file
		if (exists(fls_file_path)) {
			std::error_code ec;
			fs::remove(fls_file_path, ec);
			if (ec) {
				std::cerr << "Failed to remove data.fls: " << ec.message() << std::endl;
			}
		}

		// Step 1: Read the CSV file from the specified directory path
		con1.set_n_vectors_per_rowgroup(64).read_csv(example_dir_path);

		// Step 2: Write the data to the FastLanes file format in the specified directory
		con1.to_fls(fls_file_path);

		// Step 3: Get a FastLanes reader for the previously stored data
		Connection con2;
		const auto fls_reader = con2.reset().read_fls(fls_file_path);

		// Step 4: Write data to CSV
		if (exists(csv_file_path)) {
			std::filesystem::remove(csv_file_path);
		}
		fls_reader->to_csv(csv_file_path);

		exit(EXIT_SUCCESS);
	} catch (std::exception& ex) {
		az_printer::bold_red_cout << "-- Error: " << ex.what() << std::endl;
		return EXIT_FAILURE;
	}
}
