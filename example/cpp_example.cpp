#include "data/fastlanes_data.hpp"
#include "fastlanes.hpp"
#include "fls/connection.hpp"
#include <iostream>

using namespace fastlanes; // NOLINT
int main() {

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
			if (output_arr[i] != input_arr[i]) { throw std::runtime_error("decoding failed"); }
		}
	}
	return 0;
}
