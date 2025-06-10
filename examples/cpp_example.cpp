#include "data/fastlanes_data.hpp"
#include "fastlanes.hpp"
#include <iostream>

using namespace fastlanes; // NOLINT

int main() {
	try {
		// 1) Establish a connection and print FastLanes version
		const auto con1 = connect();
		std::cout << "-- FastLanes Version: " << con1->get_version() << std::endl;

		// 2) Define paths
		const path example_dir_path = string(EXAMPLE::N1);
		const path fls_file_path    = path {FLS_CMAKE_SOURCE_DIR} / "data" / "fls" / "data.fls";
		const path csv_file_path    = fls_file_path.parent_path() / "fastlanes.csv";

		// 3) Remove any existing data.fls so we start fresh
		if (exists(fls_file_path)) {
			std::cout << "-- Removing existing FLS file: " << fls_file_path << std::endl;
			std::error_code ec;
			fs::remove(fls_file_path, ec);
			if (ec) {
				std::cerr << "   [Error] Failed to remove data.fls: " << ec.message() << std::endl;
				return EXIT_FAILURE;
			}
			std::cout << "-- Removed old FLS successfully." << std::endl;
		} else {
			std::cout << "-- No existing FLS file found; continuing." << std::endl;
		}

		// 4) Step 1: Read the CSV file from the specified directory path
		std::cout << "-- Step 1: Reading CSV data from directory: " << example_dir_path << std::endl;
		con1->set_n_vectors_per_rowgroup(64).read_csv(example_dir_path);
		std::cout << "-- Step 1 complete: CSV data loaded into memory." << std::endl;

		// 5) Step 2: Write the data to the FastLanes file format
		std::cout << "-- Step 2: Writing data to FLS file: " << fls_file_path << std::endl;
		con1->to_fls(fls_file_path);
		std::cout << "-- Step 2 complete: FLS file created." << std::endl;

		// 6) Step 3: Get a FastLanes reader for the previously stored data
		std::cout << "-- Step 3: Opening FLS reader for file: " << fls_file_path << std::endl;
		Connection con2;
		const auto fls_reader = con2.reset().read_fls(fls_file_path);
		std::cout << "-- Step 3 complete: FLS reader is ready." << std::endl;

		// 7) Step 4: Write data back out to CSV
		if (exists(csv_file_path)) {
			std::cout << "-- Removing existing CSV file: " << csv_file_path << std::endl;
			std::filesystem::remove(csv_file_path);
			std::cout << "-- Removed old CSV successfully." << std::endl;
		}
		std::cout << "-- Step 4: Writing data back to CSV: " << csv_file_path << std::endl;
		fls_reader->to_csv(csv_file_path);
		std::cout << "-- Step 4 complete: CSV file created." << std::endl;

		std::cout << "-- All steps finished successfully. Exiting." << std::endl;
		return EXIT_SUCCESS;
	} catch (const std::exception& ex) {
		std::cerr << "-- Error: " << ex.what() << std::endl;
		return EXIT_FAILURE;
	}
}
