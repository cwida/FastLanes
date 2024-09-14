#ifndef FLS_ENCODER_MATERIALIZER_HPP
#define FLS_ENCODER_MATERIALIZER_HPP

#include "fls/std/span.hpp"

namespace fastlanes {
class Vec;

template <typename PT>
class Materializer {
public:
	explicit Materializer(span<PT> output_span);

public:
	void Materialize(const Vec& vec);

public:
	span<PT> output_span;
};

} // namespace fastlanes
#endif // FLS_ENCODER_MATERIALIZER_HPP
