#include "fls/encoder/exp_col_decoder.hpp"
#include "fls/api/engine.hpp"
#include "fls/encoder/col_encoder.hpp"
#include "fls/encoder/materializer.hpp"
#include "fls/encoder/verifier.hpp"
#include "fls/expression/data_type.hpp" // for i64_pt

namespace fastlanes {
template <typename PT>
ExpColDecoder<PT>::ExpColDecoder() = default;

template <typename PT>
void ExpColDecoder<PT>::full_decode(span<std::byte> input_data, span<PT> output_data) {
	// init
	TColDecoder<PT>              col_decoder;
	SingleColumnMaterializer<PT> materializer {output_data};
	col_decoder.ExtInitDict(reinterpret_cast<uint8_t*>(input_data.data()));
	col_decoder.InitDecompress(reinterpret_cast<uint8_t*>(input_data.data()));

	auto n_vec = col_decoder.NVector();

	for (idx_t vec_idx {0}; vec_idx < n_vec; ++vec_idx) {
		auto* res_fls_vec = col_decoder.Decompress();
		materializer.Materialize(*res_fls_vec);
	}
}

template class ExpColDecoder<i64_pt>;
template class ExpColDecoder<dbl_pt>;

} // namespace fastlanes