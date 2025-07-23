// ────────────────────────────────────────────────────────
// |                      FastLanes                       |
// ────────────────────────────────────────────────────────
// galp/src/include/alp/alp-bindings.cuh
// ────────────────────────────────────────────────────────
#ifndef ALP_BINDINGS_CUH
#define ALP_BINDINGS_CUH

#include "alp.hpp"
#include "flsgpu/flsgpu-api.cuh"
#include <cstddef>
#include <cstdint>
#include <exception>
#include <type_traits>

namespace alp {

class EncodingException : public std::exception {
public:
	using std::exception::what;
	const char* what() {
		return "Could not encode data with desired encoding.";
	}
};

// Test if data can be decoded in specified type
template <typename T>
bool is_compressable(const T* input_array, const size_t n_elements);

template <typename T>
flsgpu::host::ALPColumn<T>
encode(const T* input_array, const size_t n_elements, const bool print_compression_info = false);

template <typename T>
T* decode(const flsgpu::host::ALPColumn<T> column, T* output_array);

template <typename T>
T* decode(const flsgpu::host::ALPExtendedColumn<T> column, T* output_array);

} // namespace alp

#endif // ALP_BINDINGS_CUH
