#include "fls/expression/physical_expression.hpp"
#include "fls/cor/lyt/buf.hpp"

namespace fastlanes {
void PhysicalExpr::PointTo(n_t vec_n) {}

void PhysicalExpr::EnableVectorizedStore(Buf& buf) {
	operators.emplace_back(make_unique<store_vectorized_store_op>(*this, buf));
}

} // namespace fastlanes