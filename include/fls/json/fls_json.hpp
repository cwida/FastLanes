#ifndef FLS_JSON_FLS_JSON_HPP
#define FLS_JSON_FLS_JSON_HPP

#include "fls/std/filesystem.hpp"
#include "nlohmann/json.hpp"

namespace fastlanes {
/*--------------------------------------------------------------------------------------------------------------------*/
class Schema;
class Footer;
class ColumnMetadata;
class RowgroupEncodingResult;
class Connector;
class LogicalExpr;
class NewRPN;
struct Operand;
/*--------------------------------------------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------------------------------------------*\
 * Schema
\*--------------------------------------------------------------------------------------------------------------------*/
void from_json(const nlohmann::json& j, Schema& p);
/*--------------------------------------------------------------------------------------------------------------------*\
 * RowgroupFooter
\*--------------------------------------------------------------------------------------------------------------------*/
void to_json(nlohmann::json& j, const Footer& p);
void from_json(const nlohmann::json& j, Footer& p);
/*--------------------------------------------------------------------------------------------------------------------*\
 * Field
\*--------------------------------------------------------------------------------------------------------------------*/
void to_json(nlohmann::json& j, const ColumnMetadata& p);
void from_json(const nlohmann::json& j, ColumnMetadata& p);
/*--------------------------------------------------------------------------------------------------------------------*\
 * RowgroupEncodingResult
\*--------------------------------------------------------------------------------------------------------------------*/
void to_json(nlohmann::json& j, const RowgroupEncodingResult& p);
/*--------------------------------------------------------------------------------------------------------------------*\
 * LogicalExpr
\*--------------------------------------------------------------------------------------------------------------------*/
void to_json(nlohmann::json& j, const LogicalExpr& p);
void from_json(const nlohmann::json& j, LogicalExpr& p);
/*--------------------------------------------------------------------------------------------------------------------*\
 * NewRpn
\*--------------------------------------------------------------------------------------------------------------------*/
void to_json(nlohmann::json& j, const NewRPN& p);
void from_json(const nlohmann::json& j, NewRPN& p);
/*--------------------------------------------------------------------------------------------------------------------*\
 * Operand
\*--------------------------------------------------------------------------------------------------------------------*/
void to_json(nlohmann::json& j, const Operand& p);
void from_json(const nlohmann::json& j, Operand& p);

/*--------------------------------------------------------------------------------------------------------------------*\
 * JSON
\*--------------------------------------------------------------------------------------------------------------------*/
class JSON {
public:
	template <typename DATA>
	static void write(const path& dir_path, const DATA& data);
};
/// write the footer or profiling as json file

} // namespace fastlanes

#endif // FLS_JSON_FLS_JSON_HPP