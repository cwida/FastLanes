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
#include <algorithm>
#include <cctype>
#include <fls/json/nlohmann/json.hpp>
#include <regex>
#include <sstream>
#include <stdexcept>
#include <string>
#include <unordered_map>

namespace fastlanes {

DataType TypeLookUp(const string& str) {
	// 1) Normalize to uppercase
	std::string s = str;
	std::ranges::transform(s, s.begin(), [](unsigned char c) { return std::toupper(c); });

	// 2) Regex for DECIMAL(p,s)
	static const std::regex decimal_re(R"(DECIMAL\(\d+,\s*\d+\))");

	if (std::regex_match(s, decimal_re)) {
		return DataType::DECIMAL;
	}

	// 3) Regex for VARCHAR(n)
	static const std::regex varchar_re(R"(^VARCHAR(?:\(\d+\))?$)");
	if (std::regex_match(s, varchar_re)) {
		return DataType::FLS_STR;
	}

	// 4) Static table of all the remaining fixed names (also all uppercase)
	static const std::unordered_map<string, DataType> TABLE {
	    // FLS types
	    {"FLS_I64", DataType::INT64},       {"FLS_I32", DataType::INT32},   {"INT", DataType::INT32},
	    {"FLS_I16", DataType::INT16},       {"FLS_I08", DataType::INT8},    {"FLS_U08", DataType::UINT8},
	    {"FLS_DBL", DataType::DOUBLE},      {"FLS_STR", DataType::FLS_STR}, {"BIGINT", DataType::INT64},
	    {"STRING", DataType::FLS_STR},      {"DOUBLE", DataType::DOUBLE},   {"LIST", DataType::LIST},
	    {"STRUCT", DataType::STRUCT},       {"MAP", DataType::MAP},         {"FLOAT", DataType::FLOAT},
	    {"BOOLEAN", DataType::FLS_STR},     {"INTEGER", DataType::INT64},   {"CHAR", DataType::FLS_STR},
	    {"BIGINT", DataType::INT64},        {"TIME", DataType::FLS_STR},    {"DATE", DataType::DATE},
	    {"TIMESTAMP", DataType::TIMESTAMP}, {"SMALLINT", DataType::INT16},  {"BYTE_ARRAY", DataType::BYTE_ARRAY},
	    {"JPEG", DataType::JPEG},

	    // …add any other fixed names here…
	};

	const auto it = TABLE.find(s);
	if (it == TABLE.end()) {
		throw std::runtime_error("type “" + str + "” not found");
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
constexpr const auto* OPERATORS_KEY     = "OPERATOR KEY";
constexpr const auto* OPERATORS_KEY_STR = "OPERATOR KEY STRINGS";
constexpr const auto* OPERANDS_KEY      = "OPERAND KEY";

void to_json(nlohmann::json& j, const RPNT& p) {
	std::vector<std::string> op_strs(p.operator_tokens.size());
	std::transform(p.operator_tokens.begin(), p.operator_tokens.end(), op_strs.begin(), [](OperatorToken tok) {
		return token_to_string(tok);
	});
	j = nlohmann::json {
	    {OPERATORS_KEY, p.operator_tokens}, {OPERATORS_KEY_STR, op_strs}, {OPERANDS_KEY, p.operand_tokens}};
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
n_t JSON::write(const Connection& connection, const path& file_path, TableDescriptorT& table_descriptor) {
	const nlohmann::json table_descriptor_json      = table_descriptor;
	const auto           table_descriptor_json_dump = table_descriptor_json.dump();

	File::write(file_path, table_descriptor_json_dump);

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
