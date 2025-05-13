#include "fastlanes.hpp"
#include "fls/footer/table_descriptor.hpp"
#include "fls/json/fls_json.hpp"
#include "fls/json/json_unique_ptr.hpp"
#include <fls/json/nlohmann/json.hpp>
#include <gtest/gtest.h>

namespace fastlanes {

TEST(TableDescriptorTest, RoundTrip) {
	// Sample JSON fixture for TableDescriptor
	const char* sample = R"({
        "1  [REQUIRED], RowGroup Descriptors": [
            {
                "3  [REQUIRED], Column Descriptors": [],
                "1, [REQUIRED], N VEC": 0,
                "2, [REQUIRED], Rowgroup size": 64,
                "4, [REQUIRED], Rowgroup OFFSET": 0,
                "5, [REQUIRED], N TUPLES": 0
            }
        ],
        "2  [REQUIRED], Table Binary Size": 4096
    })";

	// Parse JSON and deserialize
	nlohmann::json   j  = nlohmann::json::parse(sample);
	TableDescriptorT td = j.get<TableDescriptorT>();

	// Validate deserialization
	EXPECT_EQ(td.m_rowgroup_descriptors.size(), 1u);
	EXPECT_NE(td.m_rowgroup_descriptors[0], nullptr);
	EXPECT_EQ(td.m_table_binary_size, 4096u);

	// Serialize back to JSON and compare
	nlohmann::json roundtrip = td;
	EXPECT_EQ(roundtrip, j);
}

TEST(TableDescriptorTest, ComplexFixture) {
	// 1) Embed the exact JSON you provided
	static constexpr char const* sample = R"json({
      "1  [REQUIRED], RowGroup Descriptors": [
        {
          "1, [REQUIRED], N VEC": 1,
          "2, [REQUIRED], Rowgroup size": 262,
          "3  [REQUIRED], Column Descriptors": [
            {
              "": 0,
              "0, [REQUIRED], LOGICAL TYPE": 2,
              "1, [OPTIONAL], LOGICAL TYPE STRING": "INT8",
              "2, [OPTIONAL], COLUMN NAME": "COLUMN_0",
              "3, [REQUIRED], SEGMENTS": [
                {"1, [REQUIRED], ENTRY POINT OFFSET":0,   "2, [REQUIRED], ENTRY POINT SIZE":1, "3, [REQUIRED], DATA OFFSET":1,   "4, [REQUIRED], DATA SIZE":128, "5, [REQUIRED], ENTRY_POINT_TYPE":0},
                {"1, [REQUIRED], ENTRY POINT OFFSET":129, "2, [REQUIRED], ENTRY POINT SIZE":1, "3, [REQUIRED], DATA OFFSET":130, "4, [REQUIRED], DATA SIZE":128, "5, [REQUIRED], ENTRY_POINT_TYPE":0},
                {"1, [REQUIRED], ENTRY POINT OFFSET":258, "2, [REQUIRED], ENTRY POINT SIZE":1, "3, [REQUIRED], DATA OFFSET":259, "4, [REQUIRED], DATA SIZE":1,   "5, [REQUIRED], ENTRY_POINT_TYPE":0},
                {"1, [REQUIRED], ENTRY POINT OFFSET":260, "2, [REQUIRED], ENTRY POINT SIZE":1, "3, [REQUIRED], DATA OFFSET":261, "4, [REQUIRED], DATA SIZE":1,   "5, [REQUIRED], ENTRY_POINT_TYPE":0}
              ],
              "6, [REQUIRED], COLUMN OFFSET(B)": 0,
              "7, [REQUIRED], COLUMN SIZE(B)": 262,
              "8, [REQUIRED], RPN": {
                "1, [REQUIRED], OPERATOR KEY": [112],
                "2, [OPTIONAL], OPERAND KEY": [0,1,2,3]
              },
              "9, [OPTIONAL], N NULL": 0,
              "B, [REQUIRED], MAX": { "1, [REQUIRED], BINARY DATA": [127] },
              "C, [REQUIRED], CHILDREN": [],
              "D, [REQUIRED], EXPR SPACE": [
                {"1  [REQUIRED], OPERATOR_TOKEN":108, "2  [REQUIRED], SIZE":1042},
                {"1  [REQUIRED], OPERATOR_TOKEN":115, "2  [REQUIRED], SIZE":1056},
                {"1  [REQUIRED], OPERATOR_TOKEN":114, "2  [REQUIRED], SIZE":1317},
                {"1  [REQUIRED], OPERATOR_TOKEN":113, "2  [REQUIRED], SIZE":3996},
                {"1  [REQUIRED], OPERATOR_TOKEN":112, "2  [REQUIRED], SIZE":274},
                {"1  [REQUIRED], OPERATOR_TOKEN":111, "2  [REQUIRED], SIZE":1303},
                {"1  [REQUIRED], OPERATOR_TOKEN":105, "2  [REQUIRED], SIZE":1028},
                {"1  [REQUIRED], OPERATOR_TOKEN":109, "2  [REQUIRED], SIZE":910},
                {"1  [REQUIRED], OPERATOR_TOKEN":117, "2  [REQUIRED], SIZE":3067},
                {"1  [REQUIRED], OPERATOR_TOKEN":122, "2  [REQUIRED], SIZE":5128}
              ],
              "D, [REQUIRED], EXPR SPACE STRING": "{[EXP_DICT_I08_FFOR_U08,1042],[EXP_DICT_I08_FFOR_SLPATCH_U08,1056],[EXP_RLE_I08_SLPATCH_U16,1317],[EXP_FFOR_SLPATCH_I08,3996],[EXP_DELTA_I08,274],[EXP_RLE_I08_U16,1303],[EXP_UNCOMPRESSED_I08,1028],[EXP_FFOR_I08,910],[EXP_FREQUENCY_I08,3067],[EXP_CROSS_RLE_I08,5128]}"
            }
          ],
          "4, [REQUIRED], Rowgroup OFFSET": 24,
          "5, [REQUIRED], N TUPLES": 1024
        }
      ],
      "2  [REQUIRED], Table Binary Size": 286
    })json";

	// 1) Parse
	nlohmann::json j;
	ASSERT_NO_THROW(j = nlohmann::json::parse(sample)) << "Raw JSON failed to parse:\n" << sample;

	// 2) Deserialize with full error reporting
	try {
		TableDescriptorT tdx = j.get<TableDescriptorT>();
		// ← if that throws, we’ll catch below
	} catch (const nlohmann::json::exception& ex) {
		// FAIL() will stop the test and print our message + ex.what()
		FAIL() << "Deserialization threw: " << ex.what() << "\n"
		       << "Look at the dumped JSON above for mismatched keys/types.";
	}

	TableDescriptorT td = j.get<TableDescriptorT>();

	// 3) Top-level checks
	EXPECT_EQ(td.m_rowgroup_descriptors.size(), 1u);
	EXPECT_EQ(td.m_table_binary_size, 286u);

	// 4) Inspect the first (and only) RowgroupDescriptor
	auto& rg = td.m_rowgroup_descriptors[0];
	ASSERT_TRUE(rg) << "RowgroupDescriptor ptr must be non-null";
	EXPECT_EQ(rg->m_n_vec, 1u);
	EXPECT_EQ(rg->m_size, 262u);
	EXPECT_EQ(rg->m_offset, 24u);
	EXPECT_EQ(rg->m_n_tuples, 1024u);

	// 5) Inspect its ColumnDescriptors
	EXPECT_EQ(rg->m_column_descriptors.size(), 1u);
	auto& col = rg->m_column_descriptors[0];
	ASSERT_TRUE(col) << "ColumnDescriptor ptr must be non-null";
	EXPECT_EQ(col->idx, 0);
	EXPECT_EQ(col->data_type, DataType::INT8);
	EXPECT_EQ(col->name, "COLUMN_0");
	EXPECT_EQ(col->segment_descriptors.size(), 4u);
	EXPECT_EQ(col->encoding_rpn->operator_tokens.size(), 1u);
	EXPECT_EQ(col->encoding_rpn->operand_tokens.size(), 4u);

	// 6) And finally check that nothing in the vector is ever a nullptr
	for (size_t i = 0; i < td.m_rowgroup_descriptors.size(); ++i) {
		EXPECT_NE(td.m_rowgroup_descriptors[i], nullptr) << "Null ptr at rowgroup index " << i;
	}
}

} // namespace fastlanes
