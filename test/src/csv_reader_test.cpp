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
} // namespace fastlanes
