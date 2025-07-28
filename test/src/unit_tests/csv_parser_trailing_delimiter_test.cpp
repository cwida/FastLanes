// ────────────────────────────────────────────────────────
// |                      FastLanes                       |
// ────────────────────────────────────────────────────────
// test/src/unit_tests/csv_parser_trailing_delimiter_test.cpp
// ────────────────────────────────────────────────────────
#include "fls/common/alias.hpp"
#include "fls/common/assert.hpp"
#include "fls/csv/csv-parser/parser.hpp"
#include "fls/csv/csv.hpp"
#include "gtest/gtest.h"
#include <sstream>

namespace fastlanes {

std::vector<std::string> scanTokens(aria::csv::CsvParser& p, size_t safety_limit = 10000) {
	std::vector<std::string> out;
	size_t                   steps = 0;
	for (;;) {
		if (++steps > safety_limit) {
			// If we ever hit this, the parser is stuck (buggy behavior).
			// This makes the test fail fast instead of hanging.
			out.push_back("<SAFETY_LIMIT_HIT>");
			break;
		}
		aria::csv::Field f = p.next_field();
		if (f.type == aria::csv::FieldType::CSV_END) {
			out.emplace_back("CSV_END");
			break;
		} else if (f.type == aria::csv::FieldType::ROW_END) {
			out.emplace_back("ROW_END");
		} else {
			out.emplace_back(*f.data);
		}
	}
	return out;
}

} // namespace fastlanes

// Bring types & helper into global scope for the TESTs:
using aria::csv::CsvParser;
using fastlanes::scanTokens;

TEST(CsvParserBug, TrailingDelimiterLF) {
	// A single row that ends with a delimiter before '\n' → last field is empty.
	const std::string csv = "001|2014-08-24 18:00:00|3|0|21|19|0|\n";

	std::istringstream iss(csv);
	CsvParser          parser(iss);
	parser.delimiter('|'); // important for this dataset

	auto tokens = scanTokens(parser);

	// With the bug: tokens ends with many "ROW_END" and finally "<SAFETY_LIMIT_HIT>"
	// With the fix: we should see fields, then one empty field (""), one ROW_END, then CSV_END.
	std::vector<std::string> expected = {
	    "001", "2014-08-24 18:00:00", "3", "0", "21", "19", "0", "", "ROW_END", "CSV_END"};

	// If the parser is stuck, the sentinel appears and this assertion helps diagnose.
	ASSERT_EQ(tokens.back(), "CSV_END") << "Parser did not reach CSV_END; tokens: " << tokens.back();

	// Compare full sequence.
	EXPECT_EQ(tokens, expected);
}

TEST(CsvParserBug, TrailingDelimiterCRLF) {
	// Same scenario, but with Windows line ending to ensure CRLF handling works.
	const std::string csv = "A|B|C|\r\n";

	std::istringstream iss(csv);
	CsvParser          parser(iss);
	parser.delimiter('|'); // default terminator is CRLF

	auto tokens = scanTokens(parser);

	std::vector<std::string> expected = {"A", "B", "C", "", "ROW_END", "CSV_END"};

	ASSERT_EQ(tokens.back(), "CSV_END") << "Parser did not reach CSV_END; tokens: " << tokens.back();
	EXPECT_EQ(tokens, expected);
}
