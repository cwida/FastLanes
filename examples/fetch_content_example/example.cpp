// ────────────────────────────────────────────────────────
// |                      FastLanes                       |
// ────────────────────────────────────────────────────────
// examples/fetch_content_example/example.cpp
// ────────────────────────────────────────────────────────
#include "fastlanes.hpp"
#include <iostream>

int main() {
	try {
		// Define input and output file paths using
		const std::filesystem::path data_dir   = EXAMPLE_CMAKE_SOURCE_DIR "/data";
		const std::filesystem::path fls_file   = EXAMPLE_CMAKE_SOURCE_DIR "/data.fls";
		const std::filesystem::path output_csv = EXAMPLE_CMAKE_SOURCE_DIR "/decoded_by_fastlanes.csv";

		// Establish connection to FastLanes
		std::cout << std::string(fastlanes::Info::get_version()) << std::endl;
		auto connection = fastlanes::connect();

		// STEP 1: Read the CSV from the specified directory
		connection->inline_footer().read_csv(data_dir);

		// STEP 2: Write data to the FastLanes .fls file
		connection->to_fls(fls_file);

		// STEP 3: read the .fls file
		const auto fls_reader = connection->read_fls(fls_file);

		// STEP 4: Export the decoded .fls data back to CSV format
		fls_reader->to_csv(output_csv);

		return EXIT_SUCCESS;
	} catch (const std::exception& ex) {
		std::cerr << "Error: " << ex.what() << std::endl;
		return EXIT_FAILURE;
	}
}
