#ifndef FLS_JSON_FLS_JSON_HPP
#define FLS_JSON_FLS_JSON_HPP

#include "fls/common/alias.hpp"
#include "fls/std/filesystem.hpp"
#include "nlohmann/json.hpp"

namespace fastlanes {
/*--------------------------------------------------------------------------------------------------------------------*/
class RowgroupDescriptor;
class ColumnDescriptor;
class RowgroupEncodingResult;
class Connector;
class LogicalExpr;
class NewRPN;
struct Operand;
class SegmentDescriptor;
class BinaryValue;
class ExprSpace;
class TableDescriptor;
class Connection;
/*--------------------------------------------------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------------------------------------------------*\
 * TableDescriptor
\*--------------------------------------------------------------------------------------------------------------------*/
void to_json(nlohmann::json& j, const TableDescriptor& table_descriptor);
void from_json(const nlohmann::json& j, TableDescriptor& table_descriptor);
/*--------------------------------------------------------------------------------------------------------------------*\
 * RowgroupDescriptor
\*--------------------------------------------------------------------------------------------------------------------*/
void to_json(nlohmann::json& j, const RowgroupDescriptor& rowgroup_descriptor);
void from_json(const nlohmann::json& j, RowgroupDescriptor& rowgroup_descriptor);
/*--------------------------------------------------------------------------------------------------------------------*\
 * ColumnDescriptor
\*--------------------------------------------------------------------------------------------------------------------*/
void to_json(nlohmann::json& j, const ColumnDescriptor& p);
void from_json(const nlohmann::json& j, ColumnDescriptor& p);
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
 * BinaryValue
\*--------------------------------------------------------------------------------------------------------------------*/
void to_json(nlohmann::json& j, const BinaryValue& p);
void from_json(const nlohmann::json& j, BinaryValue& p);

/*--------------------------------------------------------------------------------------------------------------------*\
 * ExprSpace
\*--------------------------------------------------------------------------------------------------------------------*/
void to_json(nlohmann::json& j, const ExprSpace& p);
void from_json(const nlohmann::json& j, ExprSpace& p);

/*--------------------------------------------------------------------------------------------------------------------*\
 * SegmentDescriptor
\*--------------------------------------------------------------------------------------------------------------------*/
void to_json(nlohmann::json& j, const SegmentDescriptor& p);
void from_json(const nlohmann::json& j, SegmentDescriptor& p);

/*--------------------------------------------------------------------------------------------------------------------*\
 * JSON
\*--------------------------------------------------------------------------------------------------------------------*/
class JSON {
public:
	static n_t write(const Connection& connection, const path& dir_path, TableDescriptor& table_descriptor);
};

/// write the footer or profiling as json file

} // namespace fastlanes

#endif // FLS_JSON_FLS_JSON_HPP
