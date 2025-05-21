#include "fls/footer/column_descriptor.hpp"

namespace fastlanes {

void set_index(vector<up<ColumnDescriptorT>>& column_descriptors) {
	for (n_t col_idx = 0; col_idx < column_descriptors.size(); ++col_idx) {
		auto& column_descriptor = column_descriptors[col_idx];
		column_descriptor->idx  = col_idx;
		if (!column_descriptor->children.empty()) {
			set_index(column_descriptor->children);
		}
	}
}

} // namespace fastlanes
