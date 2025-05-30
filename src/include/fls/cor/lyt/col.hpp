#ifndef FLS_COR_LYT_COL_HPP
#define FLS_COR_LYT_COL_HPP

#include "fls/common/byte_c.hpp"
#include "fls/common/common.hpp"
#include <vector>

namespace fastlanes {
template <typename T>
class Col {
public:
	Col(); //
public:
	void   Insert(T* data, n_t c); //
	void   Share(T* data, n_t c);  //
	n_t    Count() const;          //
	byte_c Size() const;           //
	virtual ~Col() = default;      //
	T* Data();                     //
	T* operator[](n_t i);          //
private:
	n_t            m_count;  //
	std::vector<T> m_buffer; //
};
} // namespace fastlanes
#endif // FLS_COR_LYT_COL_HPP
