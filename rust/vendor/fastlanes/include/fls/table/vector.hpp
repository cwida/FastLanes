#ifndef FLS_TABLE_VECTOR_HPP
#define FLS_TABLE_VECTOR_HPP
#include "chunk.hpp"

namespace fastlanes {
class Vector {
public:
	explicit Vector(const fls_vec& vector);
	const fls_vec& internal_vector;
};
} // namespace fastlanes
#endif