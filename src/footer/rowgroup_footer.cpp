#include "fls/footer/rowgroup_footer.hpp"
#include "fls/expression/logical_expression.hpp"
#include "fls/printer/output.hpp"
#include "fls/table/schema.hpp"
#include <fls/table/rowgroup.hpp>
#include <math.h>

namespace fastlanes {

ColumnMetadata::ColumnMetadata()
    : data_type(DataType::INVALID)
    , offset {INVALID_OFFSET}
    , encoding_rpn {}
    , m_is_determined {false} {};

ColumnMetadata::ColumnMetadata(const DataType& logical_type)
    : data_type(logical_type)
    , offset(INVALID_OFFSET)
    , encoding_rpn()
    , m_is_determined(false) {}

bool ColumnMetadata::IsDetermined() const { return this->m_is_determined; }

Footer::Footer()
    : n_vec(0) {};

n_t GetNVector(const n_t n_tup) {
	return static_cast<n_t>(ceil(static_cast<double>(n_tup) / static_cast<double>(CFG::VEC_SZ)));
}

Footer::Footer(const Rowgroup& rowgroup)
    : n_vec(GetNVector(rowgroup.n_tup)) {
	column_metadatas.reserve(rowgroup.m_schema.size());
	for (const auto& col : rowgroup.m_schema.col_descriptions()) {
		column_metadatas.emplace_back(col.type);
	}
};

void Footer::push_back(ColumnMetadata&& scheme) {
	/**/
	column_metadatas.push_back(scheme);
}

ColumnMetadata& Footer::operator[](const size_t idx) { return column_metadatas[idx]; }

const ColumnMetadata& Footer::operator[](const size_t idx) const { return column_metadatas[idx]; }

size_t Footer::size() const { return column_metadatas.size(); }

} // namespace fastlanes