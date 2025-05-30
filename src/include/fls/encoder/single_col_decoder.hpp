#ifndef FLS_ENCODER_SINGLE_COL_DECODER_HPP
#define FLS_ENCODER_SINGLE_COL_DECODER_HPP

#include "fls/io/io.hpp"

namespace fastlanes {
/*--------------------------------------------------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------------------------------------------------*\
 * SingleColDecoder
\*--------------------------------------------------------------------------------------------------------------------*/
class SingleColDecoder {
public:
	///
	explicit SingleColDecoder(const io& encoded_io, io& output_io, const DataType& data_type);

public:
	///
	void full_decode() const;

private:
	/// encoded_io
	[[maybe_unused]] const io& m_encoded_io;
	/// output_io
	[[maybe_unused]] const io& m_output_io;
	///		DataType data_type;
	DataType m_data_type;
};
} // namespace fastlanes

#endif // FLS_ENCODER_SINGLE_COL_DECODER_HPP
