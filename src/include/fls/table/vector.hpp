// ────────────────────────────────────────────────────────
// |                      FastLanes                       |
// ────────────────────────────────────────────────────────
// src/include/fls/table/vector.hpp
// ────────────────────────────────────────────────────────
#ifndef FLS_TABLE_VECTOR_HPP
#define FLS_TABLE_VECTOR_HPP
#include "fls/api/api.hpp"
#include "chunk.hpp"

namespace fastlanes {
class FLS_API Vector {
public:
	explicit Vector(const fls_vec& vector);
	const fls_vec& internal_vector;
};
} // namespace fastlanes
#endif
