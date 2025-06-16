#ifndef FLS_COR_ENG_RESOLVER_HPP
#define FLS_COR_ENG_RESOLVER_HPP

#include "fls/common/common.hpp"
#include "fls/cor/exp/exp.hpp"
#include "fls/cor/fls_data_type.hpp"
#include "fls/cor/fun.hpp"
#include "fls/cor/prm/prm_type.hpp"

namespace fastlanes {
template <typename T>
class resolver { // NOLINT
public:
	static cmpr_fun_t    resolve_cmpr(prm_t pmr_type, fls_t fls_type, sp<TExp<T>>& exp);
	static de_cmpr_fun_t resolve_de_cmpr(prm_t pmr_type, fls_t fls_type, sp<TExp<T>>& exp);
};
} // namespace fastlanes
#endif // FLS_COR_ENG_RESOLVER_HPP
