#ifndef FLS_ENCODER_SINGLE_COL_ENCODER_HPP
#define FLS_ENCODER_SINGLE_COL_ENCODER_HPP

#include "fls/io/io.hpp"

namespace fastlanes {
/*--------------------------------------------------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------------------------------------------------*\
 * SingleColEncoder
\*--------------------------------------------------------------------------------------------------------------------*/
class SingleColEncoder {
public:
	///
	explicit SingleColEncoder(const io& input_io, io& encoded_io, const DataType& data_type, n_t exp_id);

public:
	///
	void encode() const;

private:
	/// input_io
	[[maybe_unused]] const io& m_input_io;
	/// encoded_io;
	[[maybe_unused]] io& m_encoded_io;
	///		DataType data_type;
	DataType m_data_type;
	/// exp_id
	n_t m_exp_id;
};
} // namespace fastlanes

#endif // FLS_ENCODER_SINGLE_COL_ENCODER_HPP
