#include "fls/table/chunk.hpp"
#include "fls/cfg/cfg.hpp"
#include "fls/common/macros.hpp"
#include "fls/expression/physical_expression.hpp"
#include "fls/reader/segment.hpp"
#include "fls/table/rowgroup.hpp"

namespace fastlanes {

template <typename PT>
TypedVector<PT>::TypedVector(const col_pt& col_pt)
    : m_data(nullptr)
    , m_vec_idx(0) {

	visit(overloaded {
	          [&](const up<TypedCol<PT>>& col) { m_data = col->data.data(); },
	          [](auto&) { FLS_UNREACHABLE() },
	      },
	      col_pt);

	FLS_ASSERT_NOT_NULL_POINTER(m_data);
}

template <typename PT>
void TypedVector<PT>::point_to(n_t vec_idx) {
	m_vec_idx = vec_idx;
	m_data    = m_data + (m_vec_idx * Size());
}

template <typename PT>
ConstantVector<PT>::ConstantVector(const PT& value)
    : value(value) {
}

FLS_ALL_CTS(TypedVector)
FLS_ALL_CTS(ConstantVector)

} // namespace fastlanes