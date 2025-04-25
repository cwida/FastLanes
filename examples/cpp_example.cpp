#include "data/fastlanes_data.hpp"
#include "fastlanes.hpp"
#include "fls/connection.hpp"
#include <iostream>

using namespace fastlanes; // NOLINT

int main() {
	{
		try {
			Connection con1;
			Connection con2;
			path       example_dir_path = string(fc_bench::fc_bench_sample);

			const path fastlanes_repo_data_path {FLS_CMAKE_SOURCE_DIR};
			const path fls_dir_path = fastlanes_repo_data_path / "data" / "fls";
			// Example 2: [WIP] Process a CSV file
			// Step 1: Reset the connection and read the CSV file from the specified directory path
			con1.reset().read(example_dir_path).project({7, 8});

			// Step 2: Write the data to the FastLanes file format in the specified directory
			con1.to_fls(fls_dir_path);
			[[maybe_unused]] auto& original_rowgroup = con1.rowgroup();

			// Step 3: Reset the connection again and obtain a FastLanes reader for the previously stored data
			auto& fls_reader = con2.reset().read_fls(fls_dir_path);

			fls_reader.to_csv(fls_dir_path);

			// Step 4: Write the data from the FastLanes format back to a CSV file in the specified directory
			// [[maybe_unused]] auto& res = fls_reader.get_chunk(0);
			//
			// [[maybe_unused]] auto decoded_rowgroup = fls_reader.materialize();
			//
			// if (original_rowgroup != *decoded_rowgroup) { std::cout << "not successful \n"; }

			exit(EXIT_SUCCESS);
		} catch (std::exception& ex) {
			std::cerr << "-- Error: " << ex.what() << std::endl;
			return EXIT_FAILURE;
		}
	}
	{
		// example 1: single column encoding from memory:
		constexpr int64_t             N_TUP {64 * 1024};
		array<double, N_TUP>          input_arr {};
		array<uint8_t, N_TUP * 8 * 2> encoded_arr {};
		array<double, N_TUP>          output_arr {};
		bsz_t                         encoded_bsz = 0;

		for (size_t i = 0; i < N_TUP; ++i) {
			input_arr[i] = 1370.1;
		}

		Connection::encode_from_memory(input_arr.data(), //
		                               N_TUP,
		                               encoded_arr.size() * 8,
		                               encoded_arr.data(),
		                               &encoded_bsz,
		                               DataType::DOUBLE,
		                               1);
		Connection::decode_to_memory(encoded_arr.data(), output_arr.data(), DataType::DOUBLE);

		for (size_t i = 0; i < N_TUP; ++i) {
			if (output_arr[i] != input_arr[i]) {
				throw std::runtime_error("decoding failed");
			}
		}
	}

	exit(EXIT_SUCCESS);
}
