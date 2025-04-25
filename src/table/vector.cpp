#include "fls/table/vector.hpp"
#include "fls/reader/segment.hpp"

namespace fastlanes {

Vector::Vector(const fls_vec& vector)
    : internal_vector(vector) {
}

} // namespace fastlanes