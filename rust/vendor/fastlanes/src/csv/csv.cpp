#include "fls/csv/csv.hpp"
#include "fls/common/common.hpp"
#include "fls/connection.hpp"
#include "fls/io/file.hpp"
#include "fls/reader/segment.hpp"
#include "fls/table/attribute.hpp"
#include "fls/table/chunk.hpp"
#include <sstream>

namespace fastlanes {

constexpr string_view DELIMINATOR = "|";
constexpr string_view NEW_LINE    = "\n";

void CSV::to_csv(const path& file_path, const Rowgroup& rowgroup) {
	auto file = FileSystem::opend_app(file_path);

	if (!file.is_open()) {
		throw std::runtime_error("Could not open file for writing");
	}

	const n_t n_col {rowgroup.internal_rowgroup.size()};
	for (n_t row_idx {0}; row_idx < rowgroup.n_tup; row_idx++) {

		for (n_t last_idx {n_col - 1}, col_idx {0}; col_idx < rowgroup.internal_rowgroup.size(); col_idx++) {
			const auto& col = rowgroup.internal_rowgroup[col_idx];

			string val = Attribute::ToStr(col, row_idx);

			file << val;
			if (col_idx != last_idx) {
				file << DELIMINATOR; // Newline after each row
			}
		}

		file << NEW_LINE;
	}

	file.close();
}
} // namespace fastlanes