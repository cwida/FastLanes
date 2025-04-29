#include "fls_tester.hpp"

namespace fastlanes {

// Public BI
TEST_F(FastLanesReaderTester, Arade) {
	const vector<n_t> constant_cols                 = {5, 6, 9};
	const vector<n_t> equal_cols                    = {5, 6};
	const vector<n_t> one_to_one_mapped_col_indexes = {}; // No one-to-one mapped columns found
	AllTest(public_bi::Arade, constant_cols, equal_cols, one_to_one_mapped_col_indexes);
}

TEST_F(FastLanesReaderTester, Bimbo) {
	const vector<n_t>     constant_cols                 = {6};
	constexpr vector<n_t> equal_cols                    = {}; // No equal columns found
	const vector<n_t>     one_to_one_mapped_col_indexes = {}; // No one-to-one mapped columns found
	AllTest(public_bi::Bimbo, constant_cols, equal_cols, one_to_one_mapped_col_indexes);
}

TEST_F(FastLanesReaderTester, CMSprovider) {
	const vector<n_t>     constant_cols                 = {20};
	constexpr vector<n_t> equal_cols                    = {}; // No equal columns found
	const vector<n_t>     one_to_one_mapped_col_indexes = {}; // No one-to-one mapped columns found
	AllTest(public_bi::CMSprovider, constant_cols, equal_cols, one_to_one_mapped_col_indexes);
}

TEST_F(FastLanesReaderTester, CityMaxCapita) {
	const vector<n_t>     constant_cols                 = {10, 19};
	constexpr vector<n_t> equal_cols                    = {}; // No equal columns found
	const vector<n_t>     one_to_one_mapped_col_indexes = {}; // No one-to-one mapped columns found
	AllTest(public_bi::CityMaxCapita, constant_cols, equal_cols, one_to_one_mapped_col_indexes);
}

TEST_F(FastLanesReaderTester, CommonGovernment) {
	const vector<n_t> constant_cols = {0, 25, 46, 51};
	// Groups: [[0, 46], [7, 13], [18, 50], [20, 21], [41, 43]]
	// removed [18, 50] almost the same but not completely 2009-10-01 00:00:00 |2009-10-01 00:00:00. one more space
	const vector<n_t> equal_cols = {46, 13, 21, 43};
	// one-to-one mapped columns:
	// [(3, 4), (6, 8), (12, 19), (16, 22), (16, 27), (16, 49), (18, 50), (22, 27), (22, 49), (27, 49), (44, 45)]
	const vector<n_t> one_to_one_mapped_col_indexes = {4, 8, 19, 22, 27, 49, 50, 27, 49, 45};
	AllTest(public_bi::CommonGovernment, constant_cols, equal_cols, one_to_one_mapped_col_indexes);
}

TEST_F(FastLanesReaderTester, Corporations) {
	// check 4, 7, 10, 12, 16, 17, 22, 25: should be equal
	// check 2, 4, 7, 10, 12, 13, 16, 17, 22, 25: should be constant
	const vector<n_t> constant_cols                 = {1, 3, 5, 9, 14, 20, 23, 24};
	const vector<n_t> equal_cols                    = {3, 5, 9, 14, 20, 23}; // equal columns: [2, 3, 4, 5, ...]
	const vector<n_t> one_to_one_mapped_col_indexes = {};                    // No one-to-one mapped columns found
	AllTest(public_bi::Corporations, constant_cols, equal_cols, one_to_one_mapped_col_indexes);
}

TEST_F(FastLanesReaderTester, Eixo) {
	const vector<n_t> constant_cols = {6, 23, 32, 59};
	const vector<n_t> equal_cols    = {60, 61, 47}; // Groups: [[7, 11], [19, 60, 61], [45, 47]]
	// 11 is removed from list. column 7 is string and 11 is integer, but 7 contains only numbers
	// todo detect that 7 is int and add 11 to list of equal col later.
	//-- one-to-one mapped columns: [(0, 17), (10, 12), (58, 67)]
	const vector<n_t> one_to_one_mapped_col_indexes = {17, 12, 67};
	AllTest(public_bi::Eixo, constant_cols, equal_cols, one_to_one_mapped_col_indexes);
}

TEST_F(FastLanesReaderTester, Euro2016) {
	const vector<n_t>     constant_cols = {0};
	constexpr vector<n_t> equal_cols    = {};
	// -- one-to-one mapped columns: [(3, 4)]
	const vector<n_t> one_to_one_mapped_col_indexes = {4};
	AllTest(public_bi::Euro2016, constant_cols, equal_cols, one_to_one_mapped_col_indexes);
}

TEST_F(FastLanesReaderTester, Food) {
	const vector<n_t>     constant_cols                 = {0};
	constexpr vector<n_t> equal_cols                    = {}; // No equal columns found
	const vector<n_t>     one_to_one_mapped_col_indexes = {}; // No one-to-one mapped columns found
	AllTest(public_bi::Food, constant_cols, equal_cols, one_to_one_mapped_col_indexes);
}

TEST_F(FastLanesReaderTester, Generico) {
	const vector<n_t> constant_cols = {2, 19, 25, 26, 27};
	const vector<n_t> equal_cols    = {5, 37, 27}; // Groups: [[3, 5], [8, 37], [26, 27]]
	// -- one-to-one mapped columns: [(24, 40), (24, 42), (40, 42)]
	const vector<n_t> one_to_one_mapped_col_indexes = {40, 42};
	AllTest(public_bi::Generico, constant_cols, equal_cols, one_to_one_mapped_col_indexes);
}

TEST_F(FastLanesReaderTester, HashTags) {
	const vector<n_t> constant_cols = {0, 18, 20};
	const vector<n_t> equal_cols = {59, 53, 55, 58, 61, 46, 21, 25, 26, 27, 35, 36}; // Multiple groups of equal columns
	// -- One-to-one mapped columns (low cardinality, indices): [(39, 40), (39, 43), (40, 43)]
	// -- One-to-one mapped columns (high cardinality, indices): [(13, 14)]
	const vector<n_t> one_to_one_mapped_col_indexes = {40, 43};
	AllTest(public_bi::HashTags, constant_cols, equal_cols, one_to_one_mapped_col_indexes);
}

TEST_F(FastLanesReaderTester, Hatred) {
	const vector<n_t> constant_cols                 = {0, 18, 21};
	const vector<n_t> equal_cols                    = {25}; // Group: [[24, 25]]
	const vector<n_t> one_to_one_mapped_col_indexes = {};   // No one-to-one mapped columns found
	AllTest(public_bi::Hatred, constant_cols, equal_cols, one_to_one_mapped_col_indexes);
}

TEST_F(FastLanesReaderTester, IGlocations1) {
	const vector<n_t> constant_cols = {6, 7};
	const vector<n_t> equal_cols    = {}; // No equal columns found
	// one-to-one mapped columns: [(16, 17)]
	const vector<n_t> one_to_one_mapped_col_indexes = {17};
	AllTest(public_bi::IGlocations1, constant_cols, equal_cols, one_to_one_mapped_col_indexes);
}

TEST_F(FastLanesReaderTester, MLB) {
	const vector<n_t> constant_cols                 = {3, 4, 11, 18, 35};
	const vector<n_t> equal_cols                    = {4, 11, 35}; // Group: [[3, 4, 11, 35]]
	const vector<n_t> one_to_one_mapped_col_indexes = {};          // No one-to-one mapped columns found
	AllTest(public_bi::MLB, constant_cols, equal_cols, one_to_one_mapped_col_indexes);
}

TEST_F(FastLanesReaderTester, MedPayment1) {
	const vector<n_t> constant_cols                 = {0};
	const vector<n_t> equal_cols                    = {}; // No equal columns found
	const vector<n_t> one_to_one_mapped_col_indexes = {}; // No one-to-one mapped columns found
	AllTest(public_bi::MedPayment1, constant_cols, equal_cols, one_to_one_mapped_col_indexes);
}

TEST_F(FastLanesReaderTester, Medicare1) {
	const vector<n_t> constant_cols                 = {2, 7, 9, 16};
	const vector<n_t> equal_cols                    = {9}; // Group: [[2, 9]]
	const vector<n_t> one_to_one_mapped_col_indexes = {};  // No one-to-one mapped columns found
	AllTest(public_bi::Medicare1, constant_cols, equal_cols, one_to_one_mapped_col_indexes);
}

TEST_F(FastLanesReaderTester, Motos) {
	const vector<n_t> constant_cols = {2, 19, 25, 26, 27};
	const vector<n_t> equal_cols    = {5, 37, 27}; // Groups: [[3, 5], [8, 37], [26, 27]]
	//-- one-to-one mapped columns: [(24, 40), (24, 42), (40, 42)]
	const vector<n_t> one_to_one_mapped_col_indexes = {40, 42};
	AllTest(public_bi::Motos, constant_cols, equal_cols, one_to_one_mapped_col_indexes);
}

TEST_F(FastLanesReaderTester, MulheresMil) {
	const vector<n_t> constant_cols = {6, 23, 32, 59};
	// fixme removed 11
	const vector<n_t> equal_cols = {60, 61, 47}; // Groups: [[7, 11], [19, 60, 61], [45, 47]]
	// -- one-to-one mapped columns: [(0, 17), (10, 12), (58, 67)]
	const vector<n_t> one_to_one_mapped_col_indexes = {12, 17, 67};
	AllTest(public_bi::MulheresMil, constant_cols, equal_cols, one_to_one_mapped_col_indexes);
}

TEST_F(FastLanesReaderTester, NYC) {
	// check 43: should be constant
	const vector<n_t> constant_cols = {4, 5, 6, 17, 19, 29, 34, 48, 49, 51};
	const vector<n_t> equal_cols    = {5, 6, 17, 19, 34, 48, 49, 51}; // Group: [[4, 5, 6, 17, 19, 34, 48, 49, 51]]
	// -- one-to-one mapped columns: [(25, 27), (25, 28), (27, 28)]
	const vector<n_t> one_to_one_mapped_col_indexes = {27, 28};
	AllTest(public_bi::NYC, constant_cols, equal_cols, one_to_one_mapped_col_indexes);
}

TEST_F(FastLanesReaderTester, PanCreactomy1) {
	// check 7: should be constant
	const vector<n_t> constant_cols                 = {23};
	const vector<n_t> equal_cols                    = {}; // No equal columns found
	const vector<n_t> one_to_one_mapped_col_indexes = {}; // No one-to-one mapped columns found
	AllTest(public_bi::PanCreactomy1, constant_cols, equal_cols, one_to_one_mapped_col_indexes);
}

TEST_F(FastLanesReaderTester, Physicians) {
	const vector<n_t> constant_cols                 = {0};
	const vector<n_t> equal_cols                    = {}; // No equal columns found
	const vector<n_t> one_to_one_mapped_col_indexes = {}; // No one-to-one mapped columns found
	AllTest(public_bi::Physicians, constant_cols, equal_cols, one_to_one_mapped_col_indexes);
}

TEST_F(FastLanesReaderTester, Provider) {
	const vector<n_t> constant_cols                 = {0}; // todo add and check 14
	const vector<n_t> equal_cols                    = {};  // No equal columns found
	const vector<n_t> one_to_one_mapped_col_indexes = {};  // No one-to-one mapped columns found
	AllTest(public_bi::Provider, constant_cols, equal_cols, one_to_one_mapped_col_indexes);
}

TEST_F(FastLanesReaderTester, RealEstate1) {
	const vector<n_t> constant_cols = {10, 23, 26};
	const vector<n_t> equal_cols    = {21}; // Group: [[20, 21]]
	// -- one-to-one mapped columns: [(25, 27)]
	const vector<n_t> one_to_one_mapped_col_indexes = {27};
	AllTest(public_bi::RealEstate1, constant_cols, equal_cols, one_to_one_mapped_col_indexes);
}

TEST_F(FastLanesReaderTester, Redfin1) {
	const vector<n_t> constant_cols = {0, 30};
	const vector<n_t> equal_cols    = {}; // No equal columns found
	// -- one-to-one mapped columns: [(29, 31), (41, 42)]
	const vector<n_t> one_to_one_mapped_col_indexes = {31, 42};
	AllTest(public_bi::Redfin1, constant_cols, equal_cols, one_to_one_mapped_col_indexes);
}

TEST_F(FastLanesReaderTester, Rentabilidad) {
	const vector<n_t> constant_cols = {0,  1,  2,  3,  4,   5,   6,   7,   9,   10,  11,  12,  20,  23, 26, 28,
	                                   31, 33, 35, 37, 40,  42,  48,  50,  58,  67,  70,  72,  73,  74, 75, 76,
	                                   77, 83, 94, 95, 100, 102, 104, 108, 110, 113, 114, 115, 134, 138};
	const vector<n_t>
	    equal_cols = {1,  2,  3,   4,   5,   6,   7,   9,   11,  42,  72, 73, 75,  76, 77,
	                  94, 95, 113, 134, 138, 120, 12,  20,  23,  26,  28, 33, 35,  37, 40,
	                  48, 50, 58,  67,  100, 102, 104, 108, 114, 115, 55, 80, 135, 123}; // Multiple groups
	// -- One-to-one mapped columns (low cardinality, indices): [(18, 127), (63, 133)]
	// -- One-to-one mapped columns (high cardinality, indices): [(13, 15), (46, 128)]
	const vector<n_t> one_to_one_mapped_col_indexes = {127, 133};
	AllTest(public_bi::Rentabilidad, constant_cols, equal_cols, one_to_one_mapped_col_indexes);
}

TEST_F(FastLanesReaderTester, Romance) {
	const vector<n_t> constant_cols                 = {1};
	const vector<n_t> equal_cols                    = {}; // No equal columns found
	const vector<n_t> one_to_one_mapped_col_indexes = {}; // No one-to-one mapped columns found
	AllTest(public_bi::Romance, constant_cols, equal_cols, one_to_one_mapped_col_indexes);
}

TEST_F(FastLanesReaderTester, SalariesFrance) {
	const vector<n_t> constant_cols = {21, 44, 47};
	const vector<n_t> equal_cols    = {44, 47}; // Group: [[21, 44, 47]]
	// -- one-to-one mapped columns: [(0, 1), (0, 3), (0, 56), (1, 3), (1, 56), (3, 56), (4, 5), (19, 43), (19, 54),
	// (19, 55), (37, 38), (37, 48), (37, 49), (38, 48), (38, 49), (43, 54), (43, 55), (48, 49), (54, 55)]
	const vector<n_t> one_to_one_mapped_col_indexes = {1, 3, 56, 5, 43, 54, 55, 38, 48, 49, 54, 55};
	AllTest(public_bi::SalariesFrance, constant_cols, equal_cols, one_to_one_mapped_col_indexes);
}

TEST_F(FastLanesReaderTester, TableroSistemaPenal) {
	const vector<n_t> constant_cols = {15, 16, 20, 21, 25};
	const vector<n_t> equal_cols    = {9, 14}; // Groups: [[8, 9], [10, 14]]
	// -- one-to-one mapped columns: [(4, 22), (11, 26)]
	const vector<n_t> one_to_one_mapped_col_indexes = {22, 26}; // No one-to-one mapped columns found
	AllTest(public_bi::TableroSistemaPenal, constant_cols, equal_cols, one_to_one_mapped_col_indexes);
}

TEST_F(FastLanesReaderTester, Taxpayer) {
	const vector<n_t> constant_cols                 = {0}; // todo add and check 14
	const vector<n_t> equal_cols                    = {};  // No equal columns found
	const vector<n_t> one_to_one_mapped_col_indexes = {};  // No one-to-one mapped columns found
	AllTest(public_bi::Taxpayer, constant_cols, equal_cols, one_to_one_mapped_col_indexes);
}

TEST_F(FastLanesReaderTester, Telco) {
	const vector<n_t> constant_cols = {27, 72};
	const vector<n_t> equal_cols    = {
	       136, 137, 138, 139, 140, 174}; // Groups: [[22, 136], [23, 137], [24, 138], [25, 139], [26, 140], [171, 174]]

	/*
	* -- One-to-one mapped columns (low cardinality, indices): [(13, 16), (18, 21), (29, 32), (34, 37), (44, 47), (49,
52), (54, 57), (74, 77), (79, 82), (84, 87), (89, 92), (94, 97), (99, 102), (132, 135)]
-- One-to-one mapped columns (high cardinality, indices): [(152, 155)]
	 */
	const vector<n_t> one_to_one_mapped_col_indexes = {16, 21, 32, 37, 47, 52, 57, 77, 82, 87, 92, 97, 102, 135};
	AllTest(public_bi::Telco, constant_cols, equal_cols, one_to_one_mapped_col_indexes);
}

TEST_F(FastLanesReaderTester, TrainsUK1) {
	const vector<n_t> constant_cols                 = {};
	const vector<n_t> equal_cols                    = {}; // No equal columns
	const vector<n_t> one_to_one_mapped_col_indexes = {}; // No one-to-one mapped columns found
	AllTest(public_bi::TrainsUK1, constant_cols, equal_cols, one_to_one_mapped_col_indexes);
}

TEST_F(FastLanesReaderTester, TrainsUK2) {
	const vector<n_t> constant_cols = {3, 36};
	const vector<n_t> equal_cols    = {33}; // Group: [[30, 33]]
	//-- one-to-one mapped columns: [(16, 17)]
	const vector<n_t> one_to_one_mapped_col_indexes = {17};
	AllTest(public_bi::TrainsUK2, constant_cols, equal_cols, one_to_one_mapped_col_indexes);
}

TEST_F(FastLanesReaderTester, USCensus) {
	const vector<n_t> constant_cols = {
	    0,   1,   2,   3,   4,   6,   10,  11,  12,  13,  14,  17,  18,  19,  24,  32,  33,  34,  36,  38,  39,
	    41,  42,  43,  44,  45,  46,  47,  50,  51,  52,  56,  63,  64,  68,  70,  71,  74,  75,  77,  78,  79,
	    80,  81,  82,  94,  95,  96,  97,  99,  100, 101, 102, 103, 106, 113, 118, 119, 120, 121, 122, 124, 128,
	    130, 133, 135, 139, 140, 142, 143, 144, 145, 146, 147, 152, 153, 154, 155, 156, 157, 160, 162, 163, 164,
	    165, 166, 167, 168, 169, 171, 172, 174, 175, 176, 177, 178, 182, 183, 184, 185, 186, 187, 189, 198, 199,
	    200, 201, 202, 203, 205, 206, 207, 208, 209, 210, 213, 214, 221, 235, 236, 237, 238, 239, 241, 242, 243,
	    245, 246, 247, 248, 249, 250, 251, 257, 258, 259, 260, 262, 263, 265, 268, 271, 272, 274, 280, 281, 282,
	    294, 295, 298, 300, 301, 302, 303, 304, 305, 306, 307, 317, 318, 319, 320, 321, 322, 323, 324, 325, 327,
	    330, 332, 333, 334, 335, 336, 338, 339, 340, 341, 342, 346, 347, 348, 349, 350, 352, 353, 355, 437, 438,
	    439, 440, 441, 442, 443, 444, 445, 446, 447, 448, 449, 450, 451, 452, 453, 454, 455, 456, 457, 458, 459,
	    460, 461, 462, 463, 464, 465, 466, 467, 468, 469, 470, 471, 472, 473, 474, 475, 476, 477, 478, 479, 480,
	    481, 482, 483, 484, 485, 486, 487, 488, 489, 490, 491, 492, 493, 494, 495, 496, 497, 498, 499, 500, 501,
	    502, 503, 504, 505, 506, 507, 508, 509, 510, 511, 512, 513, 514, 515, 516};
	const vector<n_t> equal_cols = {1, 6, 11, 14, 42, 52, 77, 96, 135}; // equal columns based on groups
	const vector<n_t> one_to_one_mapped_col_indexes = {};               // No one-to-one mapped columns found
	AllTest(public_bi::USCensus, constant_cols, equal_cols, one_to_one_mapped_col_indexes);
}

TEST_F(FastLanesReaderTester, Uberlandia) {
	const vector<n_t> constant_cols = {6, 23, 32, 59};
	const vector<n_t> equal_cols    = {11, 60, 61, 47}; // Groups: [[7, 11], [19, 60, 61], [45, 47]]
	// -- one-to-one mapped columns: [(0, 17), (10, 12), (58, 67)]
	const vector<n_t> one_to_one_mapped_col_indexes = {17, 12, 67}; // No one-to-one mapped columns found
	AllTest(public_bi::Uberlandia, constant_cols, equal_cols, one_to_one_mapped_col_indexes);
}

TEST_F(FastLanesReaderTester, Wins) {
	// check 254: should be constant
	const vector<n_t> constant_cols                 = {1, 73};
	const vector<n_t> equal_cols                    = {136, 178, 136}; // Group: [[80, 178], [83, 136], [215, 224]]
	const vector<n_t> one_to_one_mapped_col_indexes = {};              // No one-to-one mapped columns found
	AllTest(public_bi::Wins, constant_cols, equal_cols, one_to_one_mapped_col_indexes);
}

TEST_F(FastLanesReaderTester, YaleLanguages) {
	const vector<n_t> constant_cols = {15, 19};
	const vector<n_t> equal_cols    = {9, 23}; // Groups: [[0, 9], [22, 23]]
	// -- one-to-one mapped columns: [(5, 29), (20, 21), (20, 24), (21, 24)]
	// todo 5 null
	const vector<n_t> one_to_one_mapped_col_indexes = {21, 24};
	AllTest(public_bi::YaleLanguages, constant_cols, equal_cols, one_to_one_mapped_col_indexes);
}

} // namespace fastlanes
