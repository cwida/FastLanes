// ────────────────────────────────────────────────────────
// |                      FastLanes                       |
// ────────────────────────────────────────────────────────
// src/include/fls/reader/rowgroup_reader.hpp
// ────────────────────────────────────────────────────────
#ifndef FLS_READER_ROWGROUP_READER_HPP
#define FLS_READER_ROWGROUP_READER_HPP

#include "fls/api/api.hpp"
#include "fls/common/alias.hpp"                   // for up, n_t
#include "fls/cor/lyt/buf.hpp"                    // for Buf
#include "fls/expression/physical_expression.hpp" // for PhysicalExpr
#include "fls/reader/rowgroup_reader.hpp"
#include "fls/reader/rowgroup_view.hpp"           // for RowgroupView (complete type needed for dllexport)
#include "fls/std/filesystem.hpp"                 // for path
#include "fls/std/vector.hpp"                     // for vector
#include "fls/table/chunk.hpp"                    // for Chunk

namespace fastlanes {
/*--------------------------------------------------------------------------------------------------------------------*/
class Connection;
class Rowgroup;
/*--------------------------------------------------------------------------------------------------------------------*/
class FLS_API RowgroupReader {
public:
	explicit RowgroupReader(const path& file_path, const RowgroupDescriptor& rowgroup_descriptor, Connection& fls);

	~RowgroupReader();
	RowgroupReader(const RowgroupReader&)            = delete;
	RowgroupReader& operator=(const RowgroupReader&) = delete;
	RowgroupReader(RowgroupReader&&)                 = delete;
	RowgroupReader& operator=(RowgroupReader&&)      = delete;

public:
	vector<sp<PhysicalExpr>>& get_chunk(n_t vec_idx);
	///
	void reset();
	///!
	up<Rowgroup> materialize();
	///
	void to_csv(const path& dir_path);
	///
	[[nodiscard]] const RowgroupDescriptor& get_descriptor() const;
	///!
	[[nodiscard]] vector<string> get_column_names() const;
	///
	[[nodiscard]] vector<DataType> get_data_types() const;

public:
	vector<sp<PhysicalExpr>> m_expressions;

private:
	Connection&               m_connection;
	const RowgroupDescriptor& m_rowgroup_descriptor;
	up<Buf>                   m_buf;
	up<RowgroupView>          m_rowgroup_view;
};

} // namespace fastlanes

#endif
