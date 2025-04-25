#include "fls/encoder/single_col_encoder.hpp"
#include "fls/encoder/exp_col_encoder.hpp"

namespace fastlanes {
SingleColEncoder::SingleColEncoder(const io& input_io, io& encoded_io, const DataType& data_type, n_t exp_id)
    : m_input_io(input_io)
    , m_encoded_io(encoded_io)
    , m_data_type(data_type)
    , m_exp_id(exp_id) {
}

void SingleColEncoder::encode() const {
	ExpEncodedCol res;
	switch (m_data_type) {
	case DataType::INT64: {
		ExpColEncoder<i64_pt> i64_encoder(false);
		const auto            expression = ExpPool<i64_pt>::get_expression(m_exp_id);
		const auto            span       = IO::read<i64_pt>(m_input_io);

		res = i64_encoder.encode_span(span, expression);

	} break;
	case DataType::DOUBLE: {
		ExpColEncoder<double> double_encoder(false);
		const auto            expression = ExpPool<double>::get_expression(m_exp_id);
		const auto            span       = IO::read<double>(m_input_io);

		res = double_encoder.encode_span(span, expression);

	} break;
	case DataType::INVALID:
	default:
		throw std::runtime_error("Invalid data type");
	}

	IO::flush(m_encoded_io, res);
}
} // namespace fastlanes