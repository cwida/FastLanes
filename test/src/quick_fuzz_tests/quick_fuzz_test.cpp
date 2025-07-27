// ────────────────────────────────────────────────────────
// |                      FastLanes                       |
// ────────────────────────────────────────────────────────
// test/src/quick_fuzz_tests/quick_fuzz_test.cpp
// ────────────────────────────────────────────────────────
#include "fls/connection.hpp"
#include "fls/csv/csv-parser/parser.hpp"
#include "fls/json/nlohmann/json.hpp"
#include "fls/std/filesystem.hpp"
#include <fstream>
#include <gtest/gtest.h>
#include <iostream>
#include <random>
#include <sstream>
#include <string>
#include <vector>

namespace fs = fastlanes::fs; // from fls/std/filesystem.hpp

// ------------------------------------------------------------------
// Minimal Base64 encoder for embedding JPEG bytes in CSV
// ------------------------------------------------------------------
static const std::string b64_chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                                     "abcdefghijklmnopqrstuvwxyz"
                                     "0123456789+/";

static std::string base64_encode(const std::vector<uint8_t>& buf) {
	std::string out;
	int         val  = 0;
	int         valb = -6;
	for (uint8_t c : buf) {
		val = (val << 8) + c;
		valb += 8;
		while (valb >= 0) {
			out.push_back(b64_chars[(val >> valb) & 0x3F]);
			valb -= 6;
		}
	}
	if (valb > -6) {
		out.push_back(b64_chars[((val << 8) >> (valb + 8)) & 0x3F]);
	}
	while (out.size() % 4) {
		out.push_back('=');
	}
	return out;
}

// ------------------------------------------------------------------
// Read fuzz settings from fuzz_config.json
// ------------------------------------------------------------------
namespace fastlanes { namespace cfg {

struct Settings {
	int  num_cases = 10;  // number of TEST cases to spawn
	int  base_seed = 42;  // starting seed, incremented per‑case
	char delim     = '|'; // CSV delimiter

	// OPTIONAL: ranges for generated data dimensions
	int min_cols = 1;   // inclusive lower bound for #columns
	int max_cols = 6;   // inclusive upper bound for #columns
	int min_rows = 100; // inclusive lower bound for #rows
	int max_rows = 100; // inclusive upper bound for #rows (defaults to 100 as before)
};

inline Settings load() {
	Settings s;
	using fs::path;
	try {
		path          cfg_path = path(FLS_CMAKE_SOURCE_DIR) / "test" / "src" / "quick_fuzz_tests" / "fuzz_config.json";
		std::ifstream in(cfg_path);
		if (in) {
			nlohmann::json j;
			in >> j;
			if (j.contains("num_cases"))
				s.num_cases = j["num_cases"];
			if (j.contains("base_seed"))
				s.base_seed = j["base_seed"];
			if (j.contains("delimiter")) {
				auto d = j["delimiter"].get<std::string>();
				if (!d.empty())
					s.delim = d[0];
			}
			if (j.contains("min_cols"))
				s.min_cols = j["min_cols"];
			if (j.contains("max_cols"))
				s.max_cols = j["max_cols"];
			if (j.contains("min_rows"))
				s.min_rows = j["min_rows"];
			if (j.contains("max_rows"))
				s.max_rows = j["max_rows"];
		} else {
			std::cerr << "[cfg] Warning: cannot open " << cfg_path << "; using defaults.\n";
		}
	} catch (const std::exception& ex) {
		std::cerr << "[cfg] Error parsing fuzz_config.json: " << ex.what() << "; using defaults.\n";
	}
	// clamp ranges if swapped in JSON
	if (s.min_cols > s.max_cols)
		std::swap(s.min_cols, s.max_cols);
	if (s.min_rows > s.max_rows)
		std::swap(s.min_rows, s.max_rows);
	return s;
}

}} // namespace fastlanes::cfg

// ------------------------------------------------------------------
// Global settings (loaded once)
// ------------------------------------------------------------------
static const auto SETTINGS = fastlanes::cfg::load();

// Print settings at startup
static struct SettingsPrinter {
	SettingsPrinter() {
		std::cout << "Settings:"
		          << " num_cases=" << SETTINGS.num_cases << ", base_seed=" << SETTINGS.base_seed << ", delim='"
		          << SETTINGS.delim << "'"
		          << ", min_cols=" << SETTINGS.min_cols << ", max_cols=" << SETTINGS.max_cols
		          << ", min_rows=" << SETTINGS.min_rows << ", max_rows=" << SETTINGS.max_rows << std::endl;
	}
} settings_printer;

// ------------------------------------------------------------------
// Generate CSV + schema, round‑trip through FastLanes, compare tables
// ------------------------------------------------------------------
static bool run_roundtrip(int seed, int case_idx, char delim) {
	std::mt19937 rng(seed);

	auto uniform = [&](int a, int b) {
		return a + int(rng() % (b - a + 1));
	};

	// dimensions come from JSON config; keeps signature unchanged
	const int cols = uniform(SETTINGS.min_cols, SETTINGS.max_cols);
	const int rows = uniform(SETTINGS.min_rows, SETTINGS.max_rows);

	// column types: 0=int, 1=string, 2=jpeg; ensure ≥1 jpeg
	std::vector<int> col_type(cols);
	bool             saw_jpeg = false;
	for (int c = 0; c < cols; ++c) {
		col_type[c] = rng() % 3;
		if (col_type[c] == 2)
			saw_jpeg = true;
	}
	if (!saw_jpeg) {
		col_type[uniform(0, cols - 1)] = 2;
	}

	// build JSON schema
	nlohmann::json schema;
	schema["columns"] = nlohmann::json::array();
	for (int c = 0; c < cols; ++c) {
		schema["columns"].push_back({{"name", "col" + std::to_string(c)},
		                             {"type",
		                              col_type[c] == 0   ? "integer"
		                              : col_type[c] == 1 ? "string"
		                                                 : "jpeg"}});
	}

	// prepare directories (images dir removed; no image files are produced)
	fs::path root   = FLS_CMAKE_SOURCE_DIR;
	fs::path case_d = root / "tmp" / "fls_quick_fuzz" / ("case_" + std::to_string(case_idx));
	fs::remove_all(case_d);
	fs::create_directories(case_d);

	fs::path csv_p    = case_d / "generated.csv";
	fs::path schema_p = case_d / "schema.json";
	fs::path fls_p    = case_d / "data.fls";

	// write schema.json
	std::ofstream(schema_p) << schema.dump(2);

	// write CSV (JPEG blobs are embedded directly; no files are touched)
	{
		std::ofstream csv(csv_p);
		for (int row = 0; row < rows; ++row) {
			std::ostringstream ss;
			for (int c = 0; c < cols; ++c) {
				if (c)
					ss << delim;

				switch (col_type[c]) {
				case 0: // integer
					ss << (rng() % 10 == 0 ? "NULL" : std::to_string(uniform(0, 1000)));
					break;

				case 1: { // string
					int L = uniform(1, 8);
					for (int i = 0; i < L; ++i)
						ss << char(uniform('a', 'z'));
				} break;

				case 2: { // jpeg (tiny, random) kept fully in memory
					std::vector<uint8_t>     img {0xFF, 0xD8};
					static constexpr uint8_t hdr[] = {0xFF,
					                                  0xE0,
					                                  0x00,
					                                  0x10,
					                                  'J',
					                                  'F',
					                                  'I',
					                                  'F',
					                                  0x00,
					                                  0x01,
					                                  0x02,
					                                  0x00,
					                                  0x00,
					                                  0x01,
					                                  0x00,
					                                  0x01,
					                                  0x00,
					                                  0x00};
					img.insert(img.end(), std::begin(hdr), std::end(hdr));
					int payload = uniform(1, 8) * 4;
					for (int i = 0; i < payload; ++i)
						img.push_back(uint8_t(rng() % 256));
					img.push_back(0xFF);
					img.push_back(0xD9);

					// Embed directly in CSV via Base64; no disk I/O.
					ss << base64_encode(img);
				} break;
				default:;
				}
			}
			csv << ss.str() << '\n';
		}
	}

	// round‑trip
	fastlanes::Connection con1;
	con1.set_n_vectors_per_rowgroup(1).read_csv(case_d).to_fls(fls_p);
	const auto& tbl1 = con1.get_table();

	fastlanes::Connection con2;
	auto                  tbl2 = con2.reset().read_fls(fls_p)->materialize();

	return (tbl1 == *tbl2).is_equal;
}

// ------------------------------------------------------------------
// Spawn the original 10 independent TESTs (interface unchanged)
// ------------------------------------------------------------------
TEST(QuickFuzz_Case0, Random) {
	EXPECT_TRUE(run_roundtrip(SETTINGS.base_seed + 0, 0, SETTINGS.delim));
}
TEST(QuickFuzz_Case1, Random) {
	EXPECT_TRUE(run_roundtrip(SETTINGS.base_seed + 1, 1, SETTINGS.delim));
}
TEST(QuickFuzz_Case2, Random) {
	EXPECT_TRUE(run_roundtrip(SETTINGS.base_seed + 2, 2, SETTINGS.delim));
}
TEST(QuickFuzz_Case3, Random) {
	EXPECT_TRUE(run_roundtrip(SETTINGS.base_seed + 3, 3, SETTINGS.delim));
}
TEST(QuickFuzz_Case4, Random) {
	EXPECT_TRUE(run_roundtrip(SETTINGS.base_seed + 4, 4, SETTINGS.delim));
}
TEST(QuickFuzz_Case5, Random) {
	EXPECT_TRUE(run_roundtrip(SETTINGS.base_seed + 5, 5, SETTINGS.delim));
}
TEST(QuickFuzz_Case6, Random) {
	EXPECT_TRUE(run_roundtrip(SETTINGS.base_seed + 6, 6, SETTINGS.delim));
}
TEST(QuickFuzz_Case7, Random) {
	EXPECT_TRUE(run_roundtrip(SETTINGS.base_seed + 7, 7, SETTINGS.delim));
}
TEST(QuickFuzz_Case8, Random) {
	EXPECT_TRUE(run_roundtrip(SETTINGS.base_seed + 8, 8, SETTINGS.delim));
}
TEST(QuickFuzz_Case9, Random) {
	EXPECT_TRUE(run_roundtrip(SETTINGS.base_seed + 9, 9, SETTINGS.delim));
}
