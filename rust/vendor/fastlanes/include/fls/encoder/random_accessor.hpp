#ifndef FLS_ENCODER_RANDOM_ACCESSOR_HPP
#define FLS_ENCODER_RANDOM_ACCESSOR_HPP

#include "fls/std/vector.hpp"

namespace fastlanes {
class PhysicalExpr;
class Buf;

class RandomAccessor {
public:
	explicit RandomAccessor();
	void RandomAccess(const vector<sp<PhysicalExpr>>& expressions, n_t val_idx);

public:
	up<Buf> data_1_buf;
	up<Buf> data_2_buf;
};

} // namespace fastlanes
#endif // FLS_ENCODER_RANDOM_ACCESSOR_HPP
