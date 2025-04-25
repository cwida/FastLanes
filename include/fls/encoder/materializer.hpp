#ifndef FLS_ENCODER_MATERIALIZER_HPP
#define FLS_ENCODER_MATERIALIZER_HPP

#include "fls/std/vector.hpp"

namespace fastlanes {
class Rowgroup;
class PhysicalExpr;

class Materializer {
public:
	explicit Materializer(Rowgroup& rowgroup);
	void Materialize(const vector<sp<PhysicalExpr>>& expressions, n_t vec_idx) const;

public:
	Rowgroup& rowgroup;
};

} // namespace fastlanes
#endif // FLS_ENCODER_MATERIALIZER_HPP
