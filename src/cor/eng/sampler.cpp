#include "fls/cor/eng/sampler.hpp"
#include "fls/cfg/cfg.hpp"
#include "fls/encoder/col_encoder.hpp"
#include <algorithm>

namespace fastlanes {
#define SAMPLE_CASE(ArrowType, ActualType)                                                                             \
	case arrow::Type::ArrowType:                                                                                       \
		Sample<ActualType>(col_chunk.data().get(), c, sample_state);                                                   \
		break;

// SAMPLE_CASE(arrow::Type::INT8, int8_t)
// SAMPLE_CASE(arrow::Type::UInt8Type, uint8_t)
// SAMPLE_CASE(arrow::Type::Int16Type, int16_t)
// SAMPLE_CASE(arrow::Type::UInt16Type, uint16_t)
// SAMPLE_CASE(arrow::Type::UInt32Type, uint32_t)
// SAMPLE_CASE(arrow::Type::Int32Type, int32_t)

template <typename PT>
double TakeSample(const PT* data_p, std::vector<std::string>& vec, n_t c, n_t sample_c) {
	sample_c = (CFG::SAMPLER::SAMPLE_C <= c) ? CFG::SAMPLER::SAMPLE_C : c;

	for (size_t i = 0; i < sample_c; ++i) {
		// FIX ME
		//		vec.push_back(col_chunk_sp->GetString(i));
	}

	const auto unique_c = std::unique(vec.begin(), vec.end()) - vec.begin();

	return static_cast<double>(unique_c) / static_cast<double>(vec.size());
}

template <typename PT>
void SampleString(const PT* data_p, n_t n, SampleState& sample_state) {
	n_t    adaptive_try = CFG::SAMPLER::ADAPTIVE_TRY_C;
	double uniqueness {0.0};

	for (size_t i = 0; i < adaptive_try; ++i) {
		if (uniqueness >= CFG::SAMPLER::ADAPTIVE_THRESHOLD) {
			break;
		}

		uniqueness = TakeSample<PT>(data_p, sample_state.str_vec, n, CFG::SAMPLER::SAMPLE_C);
	}

	sort(sample_state.str_vec.begin(), sample_state.str_vec.end());
}

template <typename PT>
void SampleArithmetic(const PT* data_p, n_t c, SampleState& sample_state) {
}

template <typename T>
Sampler<T>::Sampler() = default;

template <typename PT>
void Sampler<PT>::Sample(const PT* data_p, n_t c, SampleState& sample_state) {
	if (std::is_same_v<PT, i64_pt>) {
		SampleArithmetic<PT>(data_p, c, sample_state);
	} else {
		SampleString<PT>(data_p, c, sample_state);
	}
}

template <typename PT>
void Sampler<PT>::AdaptiveSample(const PT* data_p, n_t m, SampleState& sample_state) {
}

/*---------------------------------------------------------------------------------------------------------------------\
 * Specialization
\---------------------------------------------------------------------------------------------------------------------*/
FLS_ALL_CTS(Sampler)

/*---------------------------------------------------------------------------------------------------------------------\
 * State
\---------------------------------------------------------------------------------------------------------------------*/
SampleState::SampleState() = default;
} // namespace fastlanes