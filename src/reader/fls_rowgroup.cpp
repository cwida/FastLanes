#include "fls/reader/fls_rowgroup.hpp"
#include "fls/footer/rowgroup_footer.hpp"
#include "fls/reader/horizontal_column.hpp"

namespace fastlanes {

FLSRowgroup::FLSRowgroup(span<std::byte> ptr, const Footer& footer) {

	for (const auto& col_mtd : footer.column_metadatas) {
		const auto ofs  = col_mtd.offset;
		const auto size = col_mtd.size;

		const span<std::byte> sub_span = ptr.subspan(ofs, size);
		columns.emplace_back(sub_span);
	}
}
} // namespace fastlanes