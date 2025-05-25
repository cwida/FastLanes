#include "fls/encoder/single_col_decoder.hpp"
#include "fls/api/engine.hpp"
#include "fls/encoder/exp_col_decoder.hpp" // for ExpColDecoder
#include "fls/expression/data_type.hpp"    // for DataType, i64_pt
#include "fls/io/io.hpp"                   // for IO, io
#include "fls/table/rowgroup.hpp"
#include <cstddef>   // for byte
#include <stdexcept> // for runtime_error

namespace fastlanes {
SingleColDecoder::SingleColDecoder(const io& encoded_io, io& output_io, const DataType& data_type)
    : m_encoded_io(encoded_io)
    , m_output_io(output_io)
    , m_data_type(data_type) {
}

void SingleColDecoder::full_decode() const {
	switch (m_data_type) {
	case DataType::INT64: {
		ExpColDecoder<i64_pt> exp_i64_decoder;
		const auto            encoded_span = IO::read<std::byte>(m_encoded_io);
		const auto            output_span  = IO::read<i64_pt>(m_output_io);
		exp_i64_decoder.full_decode(encoded_span, output_span);

	} break;
	case DataType::DOUBLE: {
		ExpColDecoder<double> expr_double_decoder;
		const auto            encoded_span = IO::read<std::byte>(m_encoded_io);
		const auto            output_span  = IO::read<double>(m_output_io);
		expr_double_decoder.full_decode(encoded_span, output_span);

	} break;
	case DataType::INVALID:
	default:
		throw std::runtime_error("Invalid data type");
	}
}
} // namespace fastlanes