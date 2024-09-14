#ifndef FLS_READER_READER_HPP
#define FLS_READER_READER_HPP

#include "fls/common/alias.hpp"                   // for up, n_t
#include "fls/cor/lyt/buf.hpp"                    // for Buf
#include "fls/expression/physical_expression.hpp" // for PhysicalExpr
#include "fls/reader/fls_rowgroup.hpp"
#include "fls/std/filesystem.hpp" // for path
#include "fls/std/vector.hpp"     // for vector
#include "fls/table/chunk.hpp"    // for Chunk

namespace fastlanes {
/*--------------------------------------------------------------------------------------------------------------------*/
class Connection;
class FLSRowgroup;
/*--------------------------------------------------------------------------------------------------------------------*/
class Reader {
public:
	explicit Reader(const path& dir_path, Connection& fls);

public:
	///!  get chunk
	Chunk& get_chunk(n_t vec_idx);
	///
	void reset();
	///!
	void to_csv(const path& dir_path);

private:
	up<Footer>               m_footer;
	up<Chunk>                m_chunk;
	up<Buf>                  m_buf;
	vector<up<PhysicalExpr>> m_expressions;
	up<FLSRowgroup>          m_fls_rg;
};

} // namespace fastlanes

#endif
