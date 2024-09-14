#include "fls/new_encoder/new_encoder.hpp"
#include "fls/common/alias.hpp"                   // for up, n_t
#include "fls/connection.hpp"                     // for Connector
#include "fls/cor/lyt/buf.hpp"                    // for Buf
#include "fls/expression/expression_executor.hpp" // for ExprExecutor
#include "fls/expression/interpreter.hpp"         // for Interpreter
#include "fls/expression/physical_expression.hpp" // for PhysicalExpr
#include "fls/footer/rowgroup_footer.hpp"         // for ColumnMetadata
#include "fls/std/vector.hpp"                     // for vector
#include "fls/table/rowgroup.hpp"                 // for Rowgroup
#include <memory>                                 // for unique_ptr

namespace fastlanes {

void NewEncoder::encode(const Connection& fls, Buf& buf) {
	[[maybe_unused]] auto&       footer   = *fls.m_rowgroup_footer;
	[[maybe_unused]] const auto& rowgroup = *fls.m_rowgroup;

	// write each column
	for (auto& col_mtd : footer.column_metadatas) {
		// set the offset
		col_mtd.offset = buf.Size();

		// interpret
		auto physical_expr_up = Interpreter::Encoding::Interpret(col_mtd.encoding_rpn, rowgroup);

		// enable vectorized store
		physical_expr_up->EnableVectorizedStore(buf);

		// execute the expression for each vector
		for (n_t vec_idx {0}; vec_idx < footer.n_vec; ++vec_idx) {
			physical_expr_up->PointTo(vec_idx);
			ExprExecutor::execute(*physical_expr_up);
		}
	}

	// final size of rowgroup;
	footer.rowgroup_size = buf.Size();
}

} // namespace fastlanes