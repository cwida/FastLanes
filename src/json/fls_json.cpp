#include "fls/json/fls_json.hpp"
#include "fls/common/magic_enum.hpp"
#include "fls/connection.hpp"
#include "fls/encoder/rowgroup_encoder.hpp"
#include "fls/expression/logical_expression.hpp"
#include "fls/expression/new_rpn.hpp"
#include "fls/footer/rowgroup_footer.hpp"
#include "fls/io/file.hpp"

namespace fastlanes {
vector<string> to_string(const vector<Operator>& v) {
	vector<string> result;
	result.reserve(v.size());

	for (const auto& e : v) {
		result.emplace_back(magic_enum::enum_name(e.operator_type));
		result.emplace_back(magic_enum::enum_name(e.data_type));
	}

	return result;
}

/*--------------------------------------------------------------------------------------------------------------------*\
 * Schema
\*--------------------------------------------------------------------------------------------------------------------*/
void from_json(const nlohmann::json& j, Schema& p) {}
/*--------------------------------------------------------------------------------------------------------------------*\
 * RowgroupFooter
\*--------------------------------------------------------------------------------------------------------------------*/
constexpr const auto* N_VEC         = "1: N VEC";
constexpr const auto* ROWGROUP_SIZE = "2: Rowgroup size";
constexpr const auto* COLUMN_MTDS   = "3: Column Metadatas";

void to_json(nlohmann::json& j, const Footer& p) {
	j = nlohmann::json {
	    //
	    {N_VEC, p.n_vec},                  //
	    {ROWGROUP_SIZE, p.rowgroup_size},  //
	    {COLUMN_MTDS, p.column_metadatas}, //
	};
}
void from_json(const nlohmann::json& j, Footer& p) {
	j.at(COLUMN_MTDS).get_to(p.column_metadatas);
	j.at(N_VEC).get_to(p.n_vec);
	j.at(ROWGROUP_SIZE).get_to(p.rowgroup_size);
}
/*--------------------------------------------------------------------------------------------------------------------*\
 * ColumnMetadata
\*--------------------------------------------------------------------------------------------------------------------*/
constexpr const auto* ENCODING_RPN_STR = "Encoding RPN";

void to_json(nlohmann::json& j, const ColumnMetadata& p) {
	j = nlohmann::json {{"logical_type", p.data_type},                            //
	                    {"logical_type_str", magic_enum::enum_name(p.data_type)}, //
	                    {ENCODING_RPN_STR, p.encoding_rpn},
	                    {"col_ofs", p.offset}, //
	                    {"is_determined", p.m_is_determined}};
}
void from_json(const nlohmann::json& j, ColumnMetadata& p) {
	j.at("col_ofs").get_to(p.offset); //
};
/*--------------------------------------------------------------------------------------------------------------------*\
 * RowgroupEncodingResult
\*--------------------------------------------------------------------------------------------------------------------*/
void to_json(nlohmann::json& j, const RowgroupEncodingResult& p) {
	//
}
/*--------------------------------------------------------------------------------------------------------------------*\
 * LogicalExpr
\*--------------------------------------------------------------------------------------------------------------------*/
void to_json(nlohmann::json& j, const LogicalExpr& p) { j = nlohmann::json {{"string", p.to_string()}}; }
void from_json(const nlohmann::json& j, LogicalExpr& p) {
	//
}

/*--------------------------------------------------------------------------------------------------------------------*\
 * NewRpn
\*--------------------------------------------------------------------------------------------------------------------*/
void to_json(nlohmann::json& j, const NewRPN& p) {
	j = nlohmann::json {{"operators", to_string(p.operators)}, {"operands", p.operands}};
}
void from_json(const nlohmann::json& j, NewRPN& p) {}

/*--------------------------------------------------------------------------------------------------------------------*\
 * Operand
\*--------------------------------------------------------------------------------------------------------------------*/
constexpr const auto* OPERAND_COL_IDX = "col idx";

void to_json(nlohmann::json& j, const Operand& p) {
	//
	j = nlohmann::json {{OPERAND_COL_IDX, p.col_idx}};
}
void from_json(const nlohmann::json& j, Operand& p) {
	j.at(OPERAND_COL_IDX).get_to(p.col_idx); //
}

/*--------------------------------------------------------------------------------------------------------------------*\
 * JSON
\*--------------------------------------------------------------------------------------------------------------------*/
template <typename DATA>
void JSON::write(const path& dir_path, const DATA& data) {
	path file_path;
	if constexpr (std::is_same_v<DATA, RowgroupEncodingResult>) {
		file_path = dir_path / PROFILING_FILE_NAME;
	} else if constexpr (std::is_same_v<DATA, Footer>) {
		file_path = dir_path / FOOTER_FILE_NAME;
	}
	const nlohmann::json j = data;
	File::write(file_path, j.dump());
}

template void JSON::write(const path& path, const Footer& data_up);
template void JSON::write(const path& path, const RowgroupEncodingResult& data_up);

} // namespace fastlanes