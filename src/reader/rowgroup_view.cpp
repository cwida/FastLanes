#include "fls/reader/rowgroup_view.hpp"
#include "fls/common/assert.hpp"
#include "fls/connection.hpp"
#include "fls/footer/rowgroup_descriptor.hpp"
#include "fls/reader/column_view.hpp"
#include "fls/reader/segment.hpp"

namespace fastlanes {

RowgroupView::RowgroupView(span<std::byte> ptr, const RowgroupDescriptorT& footer) {

	for (const auto& column_descriptor : footer.m_column_descriptors) {
		const span<std::byte> column_span = ptr;
		columns.emplace_back(make_unique<ColumnView>(column_span, *column_descriptor, footer));
	}
}

ColumnView& RowgroupView::operator[](const n_t col_idx) {
	FLS_ASSERT_NOT_EMPTY_VEC(columns)

	return *columns[col_idx];
}

const ColumnView& RowgroupView::operator[](const n_t col_idx) const {
	FLS_ASSERT_NOT_EMPTY_VEC(columns)

	return *columns[col_idx];
}
} // namespace fastlanes