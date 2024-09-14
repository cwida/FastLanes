#ifndef FLS_STT_STT_FAC_HPP
#define FLS_STT_STT_FAC_HPP

#include "fls/common/common.hpp"
#include "fls/stt/type.hpp"

// clang-format off
namespace fastlanes { template <typename T> class Statistic; } // namespace fastlanes
// clang-format on

namespace fastlanes {
template <typename T>
class stt_fac {
public:
	stt_fac() = delete; //
public:
	static up<Statistic<T>> Create(uint8_t* data_p, n_t c, SttT type); //
};
} // namespace fastlanes
#endif // FLS_STT_STT_FAC_HPP
