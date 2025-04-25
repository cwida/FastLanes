#include "fls/cor/exp/exp.hpp"
#include "fls/cor/lyt/page/page.hpp"

namespace fastlanes {
Exp::Exp(enum ExpT exp_t, uint8_t var_t)
    : variant {var_t}
    , exp_t {exp_t} {
}

template <typename T>
TExp<T>::TExp(enum ExpT exp_t, uint8_t variant)
    : Exp(exp_t, variant) {
}

template <typename T>
PageHdr TExp<T>::page_hdr() {
	return {exp_t, variant, 0, 0, 0};
}

/*---------------------------------------------------------------------------------------------------------------------\
 * Specialization
\---------------------------------------------------------------------------------------------------------------------*/
FLS_ALL_CTS(TExp)
// CHECK
//{
// template class TExp<parquet::FixedLenByteArray>;
// template class TExp<parquet::Int96>;
// template class TExp<parquet::ByteArray>;
// }
} // namespace fastlanes