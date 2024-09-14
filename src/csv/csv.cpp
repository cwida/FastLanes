#include "fls/csv/csv.hpp"
#include "fls/common/common.hpp"
#include "fls/connection.hpp"
#include "fls/io/file.hpp"
#include "fls/table/chunk.hpp"
#include "sstream"

namespace fastlanes {

void CSV::write(const path& dir_path, const Chunk& chunk) {
	path file_path = dir_path / "extracted_from_fls.csv";

	std::stringstream stream;
	for (n_t row_id {0}; row_id < CFG::VEC_SZ; ++row_id) {
		for (n_t col_id {0}; col_id < chunk.vecs.size(); ++col_id) {
			const auto& vec = chunk.vecs[col_id].get();
			visit(overloaded {[&]<typename PT>(const up<TypedVector<PT>>& typed_vector) {
				                  stream << typed_vector->m_data[row_id];
			                  },
			                  [](auto&) {
				                  FLS_UNREACHABLE();
			                  }},
			      vec);

			if (col_id < chunk.vecs.size() - 1) { stream << "|"; };
			if (col_id == chunk.vecs.size() - 1) { stream << "\n"; };
		};
	}
	File::write(file_path, stream.str());
}
} // namespace fastlanes