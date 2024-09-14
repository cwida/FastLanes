#ifndef FLS_COMMON_BYTE_C_HPP
#define FLS_COMMON_BYTE_C_HPP

#include "fls/common/alias.hpp" // for n_t
#include <stdint.h>             // for uint64_t
#include <type_traits>          // for is_standard_layout

namespace fastlanes {
class ByteCount {
public:
	explicit ByteCount(n_t c); //

public:
	ByteCount(ByteCount& byte_c); //
	ByteCount() = default;        //

public:
	template <typename T>
	n_t              Count() const;
	void             reset();                                            //
	friend double    operator/(const ByteCount& l, const ByteCount& r);  //
	friend n_t       operator-(const ByteCount& l, const ByteCount& r);  //
	friend bool      operator>=(const ByteCount& l, const ByteCount& r); //
	friend bool      operator<(const ByteCount& l, const ByteCount& r);  //
	friend bool      operator>(const ByteCount& l, const ByteCount& r);  //
	friend ByteCount operator+(const ByteCount& l, const ByteCount& r);  //
	friend ByteCount operator*(const ByteCount& l, const ByteCount& r);  //
	void             operator=(ByteCount&& r) noexcept;                  //
	n_t              Val() const;                                        //
private:
	uint64_t m_c; //
};

/*---------------------------------------------------------------------------------------------------------------------\
 * Implementation
\---------------------------------------------------------------------------------------------------------------------*/
template <typename T>
n_t ByteCount::Count() const {
	return m_c / sizeof(T);
}

/*---------------------------------------------------------------------------------------------------------------------\
 * Static assert and Helper
\---------------------------------------------------------------------------------------------------------------------*/
static_assert(std::is_standard_layout<ByteCount>(), "");
using byte_c = ByteCount;
} // namespace fastlanes
#endif // FLS_COMMON_BYTE_C_HPP
