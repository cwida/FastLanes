#ifndef FLS_JSON_FLS_JSON_HPP
#define FLS_JSON_FLS_JSON_HPP

#include "fls/common/alias.hpp"
#include "fls/json/nlohmann/json.hpp"
#include "fls/std/filesystem.hpp"

namespace fastlanes {
/*--------------------------------------------------------------------------------------------------------------------*/
class RowgroupDescriptor;
struct ColumnDescriptorT;
class RowgroupEncodingResult;
class Connector;
class LogicalExpr;
struct RPNT;
struct Operand;
struct SegmentDescriptorT;
struct BinaryValueT;
class ExprSpace;
class TableDescriptor;
class Connection;
struct ExpressionResultT;
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
void to_json(nlohmann::json& j, const ColumnDescriptorT& p);
void from_json(const nlohmann::json& j, ColumnDescriptorT& p);
/*--------------------------------------------------------------------------------------------------------------------*\
 * LogicalExpr
\*--------------------------------------------------------------------------------------------------------------------*/
void to_json(nlohmann::json& j, const LogicalExpr& p);
void from_json(const nlohmann::json& j, LogicalExpr& p);
/*--------------------------------------------------------------------------------------------------------------------*\
 * NewRpn
\*--------------------------------------------------------------------------------------------------------------------*/
void to_json(nlohmann::json& j, const RPNT& p);
void from_json(const nlohmann::json& j, RPNT& p);

/*--------------------------------------------------------------------------------------------------------------------*\
 * BinaryValue
\*--------------------------------------------------------------------------------------------------------------------*/
void to_json(nlohmann::json& j, const BinaryValueT& p);
void from_json(const nlohmann::json& j, BinaryValueT& p);

/*--------------------------------------------------------------------------------------------------------------------*\
 * ExprSpace
\*--------------------------------------------------------------------------------------------------------------------*/
void to_json(nlohmann::json& j, const ExprSpace& p);
void from_json(const nlohmann::json& j, ExprSpace& p);

/*--------------------------------------------------------------------------------------------------------------------*\
 * SegmentDescriptor
\*--------------------------------------------------------------------------------------------------------------------*/
void to_json(nlohmann::json& j, const SegmentDescriptorT& p);
void from_json(const nlohmann::json& j, SegmentDescriptorT& p);

/*--------------------------------------------------------------------------------------------------------------------*\
 * ExpressionResult
\*--------------------------------------------------------------------------------------------------------------------*/
void to_json(nlohmann::json& j, const ExpressionResultT& p);
void from_json(const nlohmann::json& j, ExpressionResultT& p);

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
