#include "fls/common/alias.hpp"
#include "fls/common/assert.hpp"
#include "fls/csv/csv-parser/parser.hpp"
#include "fls/csv/csv.hpp"
#include "gtest/gtest.h"

namespace fastlanes {
class Dir;

class CsvTester : public ::testing::Test {};

TEST_F(CsvTester, TEST_LAST_COLUMN_EMPTY) {
	std::istringstream   csv_stream {"|||\n"};
	constexpr char       DELIMITER  = '|';
	constexpr char       TERMINATOR = '\n';
	aria::csv::CsvParser parser     = aria::csv::CsvParser(csv_stream).delimiter(DELIMITER).terminator(TERMINATOR);

	for (auto& tuple : parser) {
		ASSERT_EQ(tuple.size(), 4);
	}
}

// Test case for reading CSV data from a file.
// Disable csv reader test for now
// TODO fix this
// TEST_F(CsvTester, read) {
// 	const std::string file_path = FLS_CMAKE_SOURCE_DIR "/test/csv/extracted_columns_subarrays.csv";
// 	std::ifstream     file_stream(file_path);
//
// 	constexpr char DELIMITER  = '|';
// 	constexpr char TERMINATOR = '\n';
//
// 	aria::csv::CsvParser parser = aria::csv::CsvParser(file_stream).delimiter(DELIMITER).terminator(TERMINATOR);
//
// 	// Iterate through parsed rows and verify the column count.
// 	n_t n_lines {0};
// 	for (auto& tuple : parser) {
// 		std::cout << n_lines << "|";
// 		for (auto& val : tuple) {
// 			std::cout << val << "|";
// 		}
// 		std::cout << std::endl;
// 		ASSERT_LE(n_lines, 1024) << n_lines; // Adjust this as per your test data expectations.
// 		n_lines++;
// 	}
//
// 	std::cout << n_lines;
//
// 	file_stream.close(); // Close the file stream after usage.
// }

} // namespace fastlanes
