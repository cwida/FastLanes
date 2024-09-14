#include "fls/table/vector.hpp"

namespace fastlanes {

Vector::Vector(const fls_vec& vector)
    : internal_vector(vector) {}

} // namespace fastlanes