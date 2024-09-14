#ifndef FLS_ENCODER_EXP_COL_DECODER_HPP
#define FLS_ENCODER_EXP_COL_DECODER_HPP

#include "fls/std/span.hpp"

namespace fastlanes {

template <typename PT>
class ExpColDecoder {
public:
	explicit ExpColDecoder();

	void full_decode(span<std::byte> input_data, span<PT> output_data);
};

} // namespace fastlanes
#endif // FLS_ENCODER_EXP_COL_DECODER_HPP
