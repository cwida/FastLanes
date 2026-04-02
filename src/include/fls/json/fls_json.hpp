// ────────────────────────────────────────────────────────
// |                      FastLanes                       |
// ────────────────────────────────────────────────────────
// src/include/fls/json/fls_json.hpp
// ────────────────────────────────────────────────────────
#ifndef FLS_JSON_FLS_JSON_HPP
#define FLS_JSON_FLS_JSON_HPP

#include "fls/api/api.hpp"
#include "fls/common/alias.hpp"
#include "fls/json/nlohmann/json.hpp"
#include "fls/std/filesystem.hpp"

namespace fastlanes {
/*--------------------------------------------------------------------------------------------------------------------*/
struct RowgroupDescriptorT;
struct ColumnDescriptorT;
class RowgroupEncodingResult;
class Connector;
class LogicalExpr;
struct RPNT;
struct Operand;
struct SegmentDescriptorT;
struct BinaryValueT;
class ExprSpace;
struct TableDescriptorT;
class Connection;
struct ExpressionResultT;
/*--------------------------------------------------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------------------------------------------------*\
 * TableDescriptorT
\*--------------------------------------------------------------------------------------------------------------------*/
FLS_API void to_json(nlohmann::json& j, const TableDescriptorT& table_descriptor);
FLS_API void from_json(const nlohmann::json& j, TableDescriptorT& table_descriptor);
/*--------------------------------------------------------------------------------------------------------------------*\
 * RowgroupDescriptor
\*--------------------------------------------------------------------------------------------------------------------*/
FLS_API void to_json(nlohmann::json& j, const RowgroupDescriptorT& rowgroup_descriptor);
FLS_API void from_json(const nlohmann::json& j, RowgroupDescriptorT& rowgroup_descriptor);
/*--------------------------------------------------------------------------------------------------------------------*\
 * ColumnDescriptor
\*--------------------------------------------------------------------------------------------------------------------*/
FLS_API void to_json(nlohmann::json& j, const ColumnDescriptorT& p);
FLS_API void from_json(const nlohmann::json& j, ColumnDescriptorT& p);
/*--------------------------------------------------------------------------------------------------------------------*\
 * LogicalExpr
\*--------------------------------------------------------------------------------------------------------------------*/
FLS_API void to_json(nlohmann::json& j, const LogicalExpr& p);
FLS_API void from_json(const nlohmann::json& j, LogicalExpr& p);
/*--------------------------------------------------------------------------------------------------------------------*\
 * NewRpn
\*--------------------------------------------------------------------------------------------------------------------*/
FLS_API void to_json(nlohmann::json& j, const RPNT& p);
FLS_API void from_json(const nlohmann::json& j, RPNT& p);

/*--------------------------------------------------------------------------------------------------------------------*\
 * BinaryValue
\*--------------------------------------------------------------------------------------------------------------------*/
FLS_API void to_json(nlohmann::json& j, const BinaryValueT& p);
FLS_API void from_json(const nlohmann::json& j, BinaryValueT& p);

/*--------------------------------------------------------------------------------------------------------------------*\
 * ExprSpace
\*--------------------------------------------------------------------------------------------------------------------*/
FLS_API void to_json(nlohmann::json& j, const ExprSpace& p);
FLS_API void from_json(const nlohmann::json& j, ExprSpace& p);

/*--------------------------------------------------------------------------------------------------------------------*\
 * SegmentDescriptor
\*--------------------------------------------------------------------------------------------------------------------*/
FLS_API void to_json(nlohmann::json& j, const SegmentDescriptorT& p);
FLS_API void from_json(const nlohmann::json& j, SegmentDescriptorT& p);

/*--------------------------------------------------------------------------------------------------------------------*\
 * ExpressionResult
\*--------------------------------------------------------------------------------------------------------------------*/
FLS_API void to_json(nlohmann::json& j, const ExpressionResultT& p);
FLS_API void from_json(const nlohmann::json& j, ExpressionResultT& p);

/*--------------------------------------------------------------------------------------------------------------------*\
 * JSON
\*--------------------------------------------------------------------------------------------------------------------*/
class FLS_API JSON {
public:
	static n_t write(const Connection& connection, const path& file_path, TableDescriptorT& table_descriptor);
};

/// write the footer or profiling as json file

} // namespace fastlanes

#endif // FLS_JSON_FLS_JSON_HPP
