#include "fls/encoder/encoder.hpp"
#include "fls/common/alias.hpp" // for up, n_t
#include "fls/connection.hpp"   // for Connector
#include "fls/cor/lyt/buf.hpp"  // for Buf
#include "fls/expression/decoding_operator.hpp"
#include "fls/expression/encoding_operator.hpp"
#include "fls/expression/expression_executor.hpp" // for ExprExecutor
#include "fls/expression/interpreter.hpp"         // for Interpreter
#include "fls/expression/physical_expression.hpp" // for PhysicalExpr
#include "fls/expression/predicate_operator.hpp"
#include "fls/footer/rowgroup_descriptor.hpp" // for ColumnMetadata
#include "fls/reader/segment.hpp"
#include "fls/std/vector.hpp"     // for vector
#include "fls/table/rowgroup.hpp" // for Rowgroup
#include <memory>                 // for unique_ptr

namespace fastlanes {

void Encoder::encode(const Connection& fls, Buf& buf) {

	[[maybe_unused]] auto&       rowgroup_descriptor = *fls.m_rowgroup_descriptor;
	[[maybe_unused]] const auto& rowgroup            = *fls.m_rowgroup;

	// write each column
	for (auto& column_descriptor : rowgroup_descriptor.m_column_descriptors) {
		uint8_t helper_buffer[sizeof(entry_point_t) * (CFG::N_VEC_PER_RG)]; // todo [fix me]

		// interpret
		InterpreterState state;
		auto physical_expr_up = Interpreter::Encoding::Interpret(column_descriptor, rowgroup.internal_rowgroup, state);

		// execute the expression for each vector
		for (n_t vec_idx {0}; vec_idx < rowgroup_descriptor.m_n_vec; ++vec_idx) {
			physical_expr_up->PointTo(vec_idx);
			ExprExecutor::execute(*physical_expr_up, vec_idx);
		}

		physical_expr_up->Finalize();
		physical_expr_up->Flush(buf, column_descriptor, helper_buffer);
	}

	// final size of rowgroup;
	rowgroup_descriptor.m_rowgroup_size = buf.Size();
}

} // namespace fastlanes