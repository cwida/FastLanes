#include "data/fastlanes_data.hpp"
#include "fastlanes.hpp"
#include "fls/connection.hpp"
#include "fls/printer/az_printer.hpp"

using namespace fastlanes; // NOLINT

int main() {

	try {
		Connection con1;
		const path example_dir_path = string(GENERATED::SINGLE_COLUMN_I64PT);
		const path fls_dir_path     = path {FLS_CMAKE_SOURCE_DIR} / "data" / "fls";

		// Step 1: Read the CSV file from the specified directory path
		con1.read(example_dir_path);

		// Step 2: Write the data to the FastLanes file format in the specified directory
		con1.set_n_vectors_per_rowgroup(1).to_fls(fls_dir_path);

		// Step 3: Get a FastLanes reader for the previously stored data
		Connection con2;
		auto&      fls_reader = con2.reset().read_fls(fls_dir_path);

		// Step 4: Write data to CSV
		fls_reader.to_csv(fls_dir_path);

		exit(EXIT_SUCCESS);
	} catch (std::exception& ex) {
		az_printer::bold_red_cout << "-- Error: " << ex.what() << std::endl;
		return EXIT_FAILURE;
	}
}
