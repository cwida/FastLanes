#include "fls/encoder/encoder.hpp"
#include "fls/common/alias.hpp" // for up, n_t
#include "fls/connection.hpp"   // for Connector
#include "fls/cor/lyt/buf.hpp"  // for Buf
#include "fls/expression/encoding_operator.hpp"
#include "fls/expression/expression_executor.hpp" // for ExprExecutor
#include "fls/expression/interpreter.hpp"         // for Interpreter
#include "fls/expression/physical_expression.hpp" // for PhysicalExpr
#include "fls/std/vector.hpp"     // for vector
#include "fls/table/rowgroup.hpp" // for Rowgroup
#include <memory> // for unique_ptr

namespace fastlanes {

void Encoder::encode_rowgroup(Buf& buf, const rowgroup_pt& rowgroup, RowgroupDescriptorT& footer) {
	for (auto& column_descriptor : footer.m_column_descriptors) {
		uint8_t helper_buffer[sizeof(entry_point_t) * (CFG::N_VEC_PER_RG)]; // todo [fix me]

		// interpret
		InterpreterState state;
		auto             physical_expr_up = Interpreter::Encoding::Interpret(*column_descriptor, rowgroup, state);
		// execute the expression for each vector
		for (n_t vec_idx {0}; vec_idx < footer.m_n_vec; ++vec_idx) {
			physical_expr_up->PointTo(vec_idx);
			ExprExecutor::execute(*physical_expr_up, vec_idx);
		}
		physical_expr_up->Finalize();
		physical_expr_up->Flush(buf, *column_descriptor, helper_buffer);
	}
	footer.m_size = buf.Size();
}

} // namespace fastlanes
