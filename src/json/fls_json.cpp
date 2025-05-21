#include "fls/json/fls_json.hpp"
#include "fls/common/decimal.hpp"
#include "fls/common/magic_enum.hpp"
#include "fls/connection.hpp"
#include "fls/expression/logical_expression.hpp"
#include "fls/expression/rpn.hpp"
#include "fls/footer/column_descriptor.hpp"
#include "fls/footer/rowgroup_descriptor.hpp"
#include "fls/footer/table_descriptor.hpp"
#include "fls/io/file.hpp"
#include "fls/json/json_unique_ptr.hpp" // <─ must appear before you call get_to(...)
#include <fls/json/nlohmann/json.hpp>
#include <sstream>

namespace fastlanes {
DataType TypeLookUp(const std::string& str) {
	static std::unordered_map<std::string, DataType> const TABLE {
	    // FLS types
	    {"FLS_I64", DataType::INT64},   //
	    {"FLS_I32", DataType::INT32},   //
	    {"FLS_I16", DataType::INT16},   //
	    {"FLS_I08", DataType::INT8},    //
	    {"FLS_U08", DataType::UINT8},   //
	    {"FLS_DBL", DataType::DOUBLE},  //
	    {"FLS_STR", DataType::FLS_STR}, //
	    {"BIGINT", DataType::INT64},    //
	    {"string", DataType::FLS_STR},  //
	    {"varchar", DataType::FLS_STR}, //
	    {"VARCHAR", DataType::FLS_STR}, //
	    {"double", DataType::DOUBLE},   //
	    {"DOUBLE", DataType::DOUBLE},   //
	    {"list", DataType::LIST},       //
	    {"struct", DataType::STRUCT},   //
	    {"map", DataType::MAP},         //
	    {"float", DataType::FLOAT},     //
	    {"FLOAT", DataType::FLOAT},     //

	    // CLickHouse
	    {"SMALLINT", DataType::INT64},
	    {"INTEGER", DataType::INT64},
	    {"VARCHAR(255)", DataType::FLS_STR},
	    {"CHAR", DataType::FLS_STR},

	    // Public Bi
	    {"varchar(1)", DataType::FLS_STR}, // {"varchar(1)", DataType::FLS_STR},
	    {"bigint", DataType::INT64},
	    {"boolean", DataType::FLS_STR},
	    {"date", DataType::FLS_STR},
	    {"integer", DataType::INT32},
	    {"smallint", DataType::INT16},
	    {"decimal(1, 0)", DataType::DECIMAL},
	    {"decimal(10, 4)", DataType::DECIMAL},
	    {"decimal(10, 5)", DataType::DECIMAL},
	    {"decimal(10, 6)", DataType::DECIMAL},
	    {"decimal(10, 8)", DataType::DECIMAL},
	    {"decimal(11, 6)", DataType::DECIMAL},
	    {"decimal(11, 8)", DataType::DECIMAL},
	    {"decimal(11, 9)", DataType::DECIMAL},
	    {"decimal(12, 6)", DataType::DECIMAL},
	    {"decimal(15, 10)", DataType::DECIMAL},
	    {"decimal(15, 11)", DataType::DECIMAL},
	    {"decimal(15, 13)", DataType::DECIMAL},
	    {"decimal(16, 10)", DataType::DECIMAL},
	    {"decimal(16, 12)", DataType::DECIMAL},
	    {"decimal(16, 14)", DataType::DECIMAL},
	    {"decimal(16, 15)", DataType::DECIMAL},
	    {"decimal(17, 11)", DataType::DECIMAL},
	    {"decimal(17, 14)", DataType::DECIMAL},
	    {"decimal(17, 16)", DataType::DECIMAL},
	    {"decimal(18, 11)", DataType::DECIMAL},
	    {"decimal(18, 12)", DataType::DECIMAL},
	    {"decimal(18, 13)", DataType::DECIMAL},
	    {"decimal(18, 14)", DataType::DECIMAL},
	    {"decimal(18, 15)", DataType::DECIMAL},
	    {"decimal(18, 17)", DataType::DECIMAL},
	    {"decimal(2, 0)", DataType::DECIMAL},
	    {"decimal(2, 1)", DataType::DECIMAL},
	    {"decimal(3, 0)", DataType::DECIMAL},
	    {"decimal(3, 1)", DataType::DECIMAL},
	    {"decimal(3, 2)", DataType::DECIMAL},
	    {"decimal(4, 0)", DataType::DECIMAL},
	    {"decimal(4, 1)", DataType::DECIMAL},
	    {"decimal(4, 2)", DataType::DECIMAL},
	    {"decimal(4, 3)", DataType::DECIMAL},
	    {"decimal(5, 0)", DataType::DECIMAL},
	    {"decimal(5, 1)", DataType::DECIMAL},
	    {"decimal(5, 2)", DataType::DECIMAL},
	    {"decimal(5, 4)", DataType::DECIMAL},
	    {"decimal(6, 1)", DataType::DECIMAL},
	    {"decimal(6, 2)", DataType::DECIMAL},
	    {"decimal(6, 4)", DataType::DECIMAL},
	    {"decimal(7, 2)", DataType::DECIMAL},
	    {"decimal(7, 4)", DataType::DECIMAL},
	    {"decimal(8, 4)", DataType::DECIMAL},
	    {"decimal(8, 6)", DataType::DECIMAL},
	    {"decimal(9, 3)", DataType::DECIMAL},
	    {"decimal(9, 4)", DataType::DECIMAL},
	    {"decimal(9, 6)", DataType::DECIMAL},
	    {"double", DataType::DOUBLE},
	    {"time", DataType::FLS_STR},
	    {"timestamp", DataType::FLS_STR},
	    {"varchar(10)", DataType::FLS_STR},
	    {"varchar(100)", DataType::FLS_STR},
	    {"varchar(102)", DataType::FLS_STR},
	    {"varchar(104)", DataType::FLS_STR},
	    {"varchar(108)", DataType::FLS_STR},
	    {"varchar(11)", DataType::FLS_STR},
	    {"varchar(113)", DataType::FLS_STR},
	    {"varchar(116)", DataType::FLS_STR},
	    {"varchar(117)", DataType::FLS_STR},
	    {"varchar(118)", DataType::FLS_STR},
	    {"varchar(12)", DataType::FLS_STR},
	    {"varchar(120)", DataType::FLS_STR},
	    {"varchar(121)", DataType::FLS_STR},
	    {"varchar(126)", DataType::FLS_STR},
	    {"varchar(129)", DataType::FLS_STR},
	    {"varchar(13)", DataType::FLS_STR},
	    {"varchar(137)", DataType::FLS_STR},
	    {"varchar(138)", DataType::FLS_STR},
	    {"varchar(14)", DataType::FLS_STR},
	    {"varchar(140)", DataType::FLS_STR},
	    {"varchar(141)", DataType::FLS_STR},
	    {"varchar(15)", DataType::FLS_STR},
	    {"varchar(151)", DataType::FLS_STR},
	    {"varchar(153)", DataType::FLS_STR},
	    {"varchar(154)", DataType::FLS_STR},
	    {"varchar(156)", DataType::FLS_STR},
	    {"varchar(16)", DataType::FLS_STR},
	    {"varchar(160)", DataType::FLS_STR},
	    {"varchar(162)", DataType::FLS_STR},
	    {"varchar(17)", DataType::FLS_STR},
	    {"varchar(173)", DataType::FLS_STR},
	    {"varchar(18)", DataType::FLS_STR},
	    {"varchar(187)", DataType::FLS_STR},
	    {"varchar(19)", DataType::FLS_STR},
	    {"varchar(194)", DataType::FLS_STR},
	    {"varchar(2)", DataType::FLS_STR},
	    {"varchar(20)", DataType::FLS_STR},
	    {"varchar(21)", DataType::FLS_STR},
	    {"varchar(213)", DataType::FLS_STR},
	    {"varchar(22)", DataType::FLS_STR},
	    {"varchar(228)", DataType::FLS_STR},
	    {"varchar(229)", DataType::FLS_STR},
	    {"varchar(23)", DataType::FLS_STR},
	    {"varchar(230)", DataType::FLS_STR},
	    {"varchar(24)", DataType::FLS_STR},
	    {"varchar(25)", DataType::FLS_STR},
	    {"varchar(255)", DataType::FLS_STR},
	    {"varchar(256)", DataType::FLS_STR},
	    {"varchar(259)", DataType::FLS_STR},
	    {"varchar(26)", DataType::FLS_STR},
	    {"varchar(27)", DataType::FLS_STR},
	    {"varchar(28)", DataType::FLS_STR},
	    {"varchar(29)", DataType::FLS_STR},
	    {"varchar(293)", DataType::FLS_STR},
	    {"varchar(3)", DataType::FLS_STR},
	    {"varchar(30)", DataType::FLS_STR},
	    {"varchar(31)", DataType::FLS_STR},
	    {"varchar(32)", DataType::FLS_STR},
	    {"varchar(324)", DataType::FLS_STR},
	    {"varchar(33)", DataType::FLS_STR},
	    {"varchar(338)", DataType::FLS_STR},
	    {"varchar(34)", DataType::FLS_STR},
	    {"varchar(35)", DataType::FLS_STR},
	    {"varchar(36)", DataType::FLS_STR},
	    {"varchar(3688)", DataType::FLS_STR},
	    {"varchar(37)", DataType::FLS_STR},
	    {"varchar(38)", DataType::FLS_STR},
	    {"varchar(39)", DataType::FLS_STR},
	    {"varchar(4)", DataType::FLS_STR},
	    {"varchar(40)", DataType::FLS_STR},
	    {"varchar(402)", DataType::FLS_STR},
	    {"varchar(41)", DataType::FLS_STR},
	    {"varchar(42)", DataType::FLS_STR},
	    {"varchar(43)", DataType::FLS_STR},
	    {"varchar(44)", DataType::FLS_STR},
	    {"varchar(45)", DataType::FLS_STR},
	    {"varchar(46)", DataType::FLS_STR},
	    {"varchar(47)", DataType::FLS_STR},
	    {"varchar(48)", DataType::FLS_STR},
	    {"varchar(480)", DataType::FLS_STR},
	    {"varchar(49)", DataType::FLS_STR},
	    {"varchar(5)", DataType::FLS_STR},
	    {"varchar(50)", DataType::FLS_STR},
	    {"varchar(500)", DataType::FLS_STR},
	    {"varchar(505)", DataType::FLS_STR},
	    {"varchar(51)", DataType::FLS_STR},
	    {"varchar(53)", DataType::FLS_STR},
	    {"varchar(54)", DataType::FLS_STR},
	    {"varchar(55)", DataType::FLS_STR},
	    {"varchar(56)", DataType::FLS_STR},
	    {"varchar(562)", DataType::FLS_STR},
	    {"varchar(57)", DataType::FLS_STR},
	    {"varchar(58)", DataType::FLS_STR},
	    {"varchar(59)", DataType::FLS_STR},
	    {"varchar(6)", DataType::FLS_STR},
	    {"varchar(60)", DataType::FLS_STR},
	    {"varchar(61)", DataType::FLS_STR},
	    {"varchar(62)", DataType::FLS_STR},
	    {"varchar(620)", DataType::FLS_STR},
	    {"varchar(63)", DataType::FLS_STR},
	    {"varchar(64)", DataType::FLS_STR},
	    {"varchar(65)", DataType::FLS_STR},
	    {"varchar(67)", DataType::FLS_STR},
	    {"varchar(69)", DataType::FLS_STR},
	    {"varchar(7)", DataType::FLS_STR},
	    {"varchar(70)", DataType::FLS_STR},
	    {"varchar(71)", DataType::FLS_STR},
	    {"varchar(74)", DataType::FLS_STR},
	    {"varchar(75)", DataType::FLS_STR},
	    {"varchar(76)", DataType::FLS_STR},
	    {"varchar(77)", DataType::FLS_STR},
	    {"varchar(776)", DataType::FLS_STR},
	    {"varchar(78)", DataType::FLS_STR},
	    {"varchar(8)", DataType::FLS_STR},
	    {"varchar(80)", DataType::FLS_STR},
	    {"varchar(800)", DataType::FLS_STR},
	    {"varchar(8160)", DataType::FLS_STR},
	    {"varchar(82)", DataType::FLS_STR},
	    {"varchar(83)", DataType::FLS_STR},
	    {"varchar(84)", DataType::FLS_STR},
	    {"varchar(89)", DataType::FLS_STR},
	    {"varchar(9)", DataType::FLS_STR},
	    {"varchar(90)", DataType::FLS_STR},
	    {"varchar(91)", DataType::FLS_STR},
	    {"varchar(92)", DataType::FLS_STR},
	    {"varchar(94)", DataType::FLS_STR},
	    {"varchar(95)", DataType::FLS_STR},
	    {"varchar(950)", DataType::FLS_STR},
	    {"varchar(96)", DataType::FLS_STR},
	    {"varchar(99)", DataType::FLS_STR},
	};

	const auto it = TABLE.find(str);
	if (it == TABLE.end()) {
		throw std::runtime_error("type " + str + " not found");
	}

	return it->second;
}

/*--------------------------------------------------------------------------------------------------------------------*\
 * RowgroupDescriptor
\*--------------------------------------------------------------------------------------------------------------------*/
constexpr const auto* N_VEC              = "1, [REQUIRED], N VEC";
constexpr const auto* ROWGROUP_SIZE      = "2, [REQUIRED], Rowgroup size";
constexpr const auto* COLUMN_DESCRIPTORS = "3  [REQUIRED], Column Descriptors";
constexpr const auto* ROWGROUP_OFFSET    = "4, [REQUIRED], Rowgroup OFFSET";
constexpr const auto* N_TUPLES           = "5, [REQUIRED], N TUPLES";

void to_json(nlohmann::json& j, const RowgroupDescriptorT& rowgroup_descriptor) {
	j = nlohmann::json {
	    //
	    {N_VEC, rowgroup_descriptor.m_n_vec},                           //
	    {ROWGROUP_SIZE, rowgroup_descriptor.m_size},                    //
	    {COLUMN_DESCRIPTORS, rowgroup_descriptor.m_column_descriptors}, //
	    {ROWGROUP_OFFSET, rowgroup_descriptor.m_offset},                //
	    {N_TUPLES, rowgroup_descriptor.m_n_tuples},                     //

	};
}
void from_json(const nlohmann::json& j, RowgroupDescriptorT& rowgroup_descriptor) {
	if (j.contains(COLUMN_DESCRIPTORS)) {
		j.at(COLUMN_DESCRIPTORS).get_to(rowgroup_descriptor.m_column_descriptors);
		j.at(N_VEC).get_to(rowgroup_descriptor.m_n_vec);
		j.at(ROWGROUP_SIZE).get_to(rowgroup_descriptor.m_size);
		j.at(ROWGROUP_OFFSET).get_to(rowgroup_descriptor.m_offset);
		j.at(N_TUPLES).get_to(rowgroup_descriptor.m_n_tuples);

	} else {
		j.at("columns").get_to(rowgroup_descriptor.m_column_descriptors);
	}
}
/*--------------------------------------------------------------------------------------------------------------------*\
 * ColumnDescriptorT
\*--------------------------------------------------------------------------------------------------------------------*/
constexpr const auto* LOGICAL_TYPE_KEY      = "0, [REQUIRED], LOGICAL TYPE";
constexpr const auto* LOGICAL_TYPE_STR_KEY  = "1, [OPTIONAL], LOGICAL TYPE STRING";
constexpr const auto* NAME_KEY              = "2, [OPTIONAL], COLUMN NAME";
constexpr const auto* SEGMENTS_KEY          = "3, [REQUIRED], SEGMENTS";
constexpr const auto* COLUMN_OFFSET_KEY     = "6, [REQUIRED], COLUMN OFFSET(B)";
constexpr const auto* COLUMN_SIZE_KEY       = "7, [REQUIRED], COLUMN SIZE(B)";
constexpr const auto* RPN_KEY               = "8, [REQUIRED], RPN";
constexpr const auto* N_NULLS_KEY           = "9, [OPTIONAL], N NULL";
constexpr const auto* IDX_KEY               = "";
constexpr const auto* MAX_KEY               = "B, [REQUIRED], MAX";
constexpr const auto* CHILDREN_KEY          = "C, [REQUIRED], CHILDREN";
constexpr const auto* EXPR_SPACE_KEY        = "D, [REQUIRED], EXPR SPACE";
constexpr const auto* EXPR_SPACE_STRING_KEY = "D, [REQUIRED], EXPR SPACE STRING";

#include <memory>
#include <sstream>
#include <string>
#include <vector>

template <typename ExpressionResultT>
std::string to_string(const std::vector<std::unique_ptr<ExpressionResultT>>& pairs) {
	std::ostringstream results;
	results << '{';

	bool first = true;
	for (const auto& ptr : pairs) {
		if (!ptr) {
			continue;
		}                                          // defensive: skip nulls
		const auto& [operator_token, size] = *ptr; // structured-bind the pointed-to pair

		if (!first) {
			results << ','; // comma-separate each element
		}
		first = false;

		results << '[' << token_to_string(operator_token) << ',' << size << ']';
	}

	results << '}';
	return results.str();
}

void to_json(nlohmann::json& j, const ColumnDescriptorT& p) {
	j = nlohmann::json {
	    {IDX_KEY, p.idx},                                           // A
	    {LOGICAL_TYPE_KEY, p.data_type},                            // 0
	    {LOGICAL_TYPE_STR_KEY, magic_enum::enum_name(p.data_type)}, // 1
	    {NAME_KEY, p.name},                                         // 2
	    {SEGMENTS_KEY, p.segment_descriptors},                      // 3
	    {COLUMN_OFFSET_KEY, p.column_offset},                       // 6
	    {COLUMN_SIZE_KEY, p.total_size},                            // 7
	    {RPN_KEY, p.encoding_rpn},                                  // 8
	    {MAX_KEY, p.max},                                           // B
	    {CHILDREN_KEY, p.children},                                 // C
	    {EXPR_SPACE_KEY, p.expr_space},                             // D
	    {EXPR_SPACE_STRING_KEY, to_string(p.expr_space)},           // D
	    {N_NULLS_KEY, p.n_null}                                     // D
	};
}
void from_json(const nlohmann::json& j, ColumnDescriptorT& p) {
	p.encoding_rpn = std::make_unique<RPNT>();
	p.max          = std::make_unique<BinaryValueT>();

	if (j.contains(LOGICAL_TYPE_KEY)) {
		j.at(SEGMENTS_KEY).get_to(p.segment_descriptors); //
		j.at(RPN_KEY).get_to(*p.encoding_rpn);            //
		j.at(NAME_KEY).get_to(p.name);                    //
		j.at(LOGICAL_TYPE_KEY).get_to(p.data_type);       //
		j.at(COLUMN_SIZE_KEY).get_to(p.total_size);       //
		j.at(COLUMN_OFFSET_KEY).get_to(p.column_offset);  //
		j.at(IDX_KEY).get_to(p.idx);                      //
		j.at(MAX_KEY).get_to(*p.max);                     //
		j.at(CHILDREN_KEY).get_to(p.children);            //
		j.at(EXPR_SPACE_KEY).get_to(p.expr_space);        //
		j.at(N_NULLS_KEY).get_to(p.n_null);               //
	}

	else {
		string data_type_string;
		j.at("type").get_to(data_type_string);
		p.data_type = TypeLookUp(data_type_string);
		if (p.data_type == DataType::DECIMAL) {
			p.fix_me_decimal_type = make_decimal_t(data_type_string);
		}
		j.at("name").get_to(p.name);
		if (j.contains("children")) {
			j.at("children").get_to(p.children);
		}
	}
}

/*--------------------------------------------------------------------------------------------------------------------*\
 * RowgroupEncodingResult
\*--------------------------------------------------------------------------------------------------------------------*/
void to_json(nlohmann::json& j, const RowgroupEncodingResult& p) {
	//
}

/*--------------------------------------------------------------------------------------------------------------------*\
 * NewRpn
\*--------------------------------------------------------------------------------------------------------------------*/
constexpr const auto* OPERATORS_KEY = "1, [REQUIRED], OPERATOR KEY";
constexpr const auto* OPERANDS_KEY  = "2, [OPTIONAL], OPERAND KEY";

void to_json(nlohmann::json& j, const RPNT& p) {
	j = nlohmann::json {{OPERATORS_KEY, p.operator_tokens}, {OPERANDS_KEY, p.operand_tokens}};
}
void from_json(const nlohmann::json& j, RPNT& p) {
	j.at(OPERATORS_KEY).get_to(p.operator_tokens); //
	j.at(OPERANDS_KEY).get_to(p.operand_tokens);   //
}

/*--------------------------------------------------------------------------------------------------------------------*\
 * BinaryValue
\*--------------------------------------------------------------------------------------------------------------------*/
constexpr const auto* BINARY_DATA_KEY = "1, [REQUIRED], BINARY DATA";

void to_json(nlohmann::json& j, const BinaryValueT& p) {
	j = nlohmann::json {
	    {BINARY_DATA_KEY, p.binary_data},
	};
}

void from_json(const nlohmann::json& j, BinaryValueT& p) {
	j.at(BINARY_DATA_KEY).get_to(p.binary_data); //
}

/*--------------------------------------------------------------------------------------------------------------------*\
 * SegmentDescriptorT
\*--------------------------------------------------------------------------------------------------------------------*/
constexpr const auto* ENTRY_POINT_OFFSET = "1, [REQUIRED], ENTRY POINT OFFSET";
constexpr const auto* ENTRY_POINT_SIZE   = "2, [REQUIRED], ENTRY POINT SIZE";
constexpr const auto* DATA_OFFSET        = "3, [REQUIRED], DATA OFFSET";
constexpr const auto* DATA_SIZE          = "4, [REQUIRED], DATA SIZE";
constexpr const auto* ENTRY_POINT_TYPE   = "5, [REQUIRED], ENTRY_POINT_TYPE";

void to_json(nlohmann::json& j, const SegmentDescriptorT& p) {
	j = nlohmann::json {
	    {ENTRY_POINT_OFFSET, p.entrypoint_offset},
	    {ENTRY_POINT_SIZE, p.entrypoint_size},
	    {DATA_OFFSET, p.data_offset},
	    {DATA_SIZE, p.data_size},
	    {ENTRY_POINT_TYPE, p.entry_point_t},
	    //
	};
}
void from_json(const nlohmann::json& j, SegmentDescriptorT& p) {
	j.at(ENTRY_POINT_OFFSET).get_to(p.entrypoint_offset);
	j.at(ENTRY_POINT_SIZE).get_to(p.entrypoint_size);
	j.at(DATA_OFFSET).get_to(p.data_offset);
	j.at(DATA_SIZE).get_to(p.data_size);
	j.at(ENTRY_POINT_TYPE).get_to(p.entry_point_t);
}

/*--------------------------------------------------------------------------------------------------------------------*\
 * JSON
\*--------------------------------------------------------------------------------------------------------------------*/
n_t JSON::write(const Connection& connection, const path& dir_path, TableDescriptorT& table_descriptor) {

	const nlohmann::json table_descriptor_json      = table_descriptor;
	const auto           table_descriptor_json_dump = table_descriptor_json.dump();

	if (connection.is_footer_inlined()) {
		const path fls_path = dir_path / FASTLANES_FILE_NAME;
		File::append(fls_path, table_descriptor_json_dump);

		return table_descriptor_json_dump.size();
	}

	const path table_descriptor_path = dir_path / TABLE_DESCRIPTOR_FILE_NAME;
	File::write(table_descriptor_path, table_descriptor_json_dump);

	return table_descriptor_json_dump.size();
}

/*--------------------------------------------------------------------------------------------------------------------*\
 * TableDescriptor
\*--------------------------------------------------------------------------------------------------------------------*/
constexpr const auto* ROWGROUP_DESCRIPTORS = "1  [REQUIRED], RowGroup Descriptors";
constexpr const auto* TABLE_BINARY_SIZE    = "2  [REQUIRED], Table Binary Size";

void to_json(nlohmann::json& j, const TableDescriptorT& table_descriptor) {
	j = nlohmann::json {
	    //
	    {ROWGROUP_DESCRIPTORS, table_descriptor.m_rowgroup_descriptors}, //
	    {TABLE_BINARY_SIZE, table_descriptor.m_table_binary_size},       //
	};
}
void from_json(const nlohmann::json& j, TableDescriptorT& table_descriptor) {
	j.at(ROWGROUP_DESCRIPTORS).get_to(table_descriptor.m_rowgroup_descriptors);
	j.at(TABLE_BINARY_SIZE).get_to(table_descriptor.m_table_binary_size);
}

/*--------------------------------------------------------------------------------------------------------------------*\
 * ExpressionResult
\*--------------------------------------------------------------------------------------------------------------------*/
constexpr const auto* OPERATOR_TOKEN = "1  [REQUIRED], OPERATOR_TOKEN";
constexpr const auto* SIZE           = "2  [REQUIRED], SIZE";
void                  to_json(nlohmann::json& j, const ExpressionResultT& expression_result) {
	                 j = nlohmann::json {
        //
        {OPERATOR_TOKEN, expression_result.operator_token}, //
        {SIZE, expression_result.size},                     //
    };
}
void from_json(const nlohmann::json& j, ExpressionResultT& expression_result) {
	j.at(OPERATOR_TOKEN).get_to(expression_result.operator_token);
	j.at(SIZE).get_to(expression_result.size);
}

} // namespace fastlanes