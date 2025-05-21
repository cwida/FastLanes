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
#include "fls/file/file_header.hpp"
#include "fls/footer/rowgroup_descriptor.hpp" // for ColumnMetadata
#include "fls/reader/segment.hpp"
#include "fls/std/vector.hpp"     // for vector
#include "fls/table/rowgroup.hpp" // for Rowgroup
#include <fls/io/io.hpp>
#include <memory> // for unique_ptr

namespace fastlanes {

void Encoder::encode(const Connection& connection, const path& file_path) {
	// init
	Buf buf; // TODO[memory pool]

	n_t cur_rowgroup_offset {sizeof(FileHeader)};
	io  file_io = make_unique<File>(file_path); // TODO[io]

	for (n_t rowgroup_idx {0}; rowgroup_idx < connection.m_table->get_n_rowgroups(); ++rowgroup_idx) {
		[[maybe_unused]] auto& rowgroup_descriptor =
		    connection.m_table_descriptor->m_rowgroup_descriptors[rowgroup_idx];
		[[maybe_unused]] const auto& rowgroup = *connection.m_table->m_rowgroups[rowgroup_idx];

		// write each column
		for (auto& column_descriptor : rowgroup_descriptor->m_column_descriptors) {
			uint8_t helper_buffer[sizeof(entry_point_t) * (CFG::N_VEC_PER_RG)]; // todo [fix me]

			// interpret
			InterpreterState state;
			auto             physical_expr_up =
			    Interpreter::Encoding::Interpret(*column_descriptor, rowgroup.internal_rowgroup, state);

			// execute the expression for each vector
			for (n_t vec_idx {0}; vec_idx < rowgroup_descriptor->m_n_vec; ++vec_idx) {
				physical_expr_up->PointTo(vec_idx);
				ExprExecutor::execute(*physical_expr_up, vec_idx);
			}

			physical_expr_up->Finalize();
			physical_expr_up->Flush(buf, *column_descriptor, helper_buffer);
		}

		IO::append(file_io, buf);
		rowgroup_descriptor->m_size   = buf.Size();
		rowgroup_descriptor->m_offset = cur_rowgroup_offset;
		cur_rowgroup_offset           = cur_rowgroup_offset + buf.Size();
		buf.Reset();
	}
	connection.m_table_descriptor->m_table_binary_size = cur_rowgroup_offset;
}

} // namespace fastlanes