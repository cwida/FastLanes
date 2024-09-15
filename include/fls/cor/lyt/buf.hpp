#ifndef FLS_COR_LYT_BUF_HPP
#define FLS_COR_LYT_BUF_HPP

#include "fls/common/common.hpp"
#include "fls/std/span.hpp"

namespace fastlanes {
class Buf {
public:
	// fixed size buffer;
	explicit Buf();
	// variable size buffer;
	explicit Buf(sz_t capacity); //
	~Buf();                      //
public:
	/// pointer to data
	[[nodiscard]] uint8_t* data() const;
	/// size of buf
	[[nodiscard]] sz_t Size() const;
	/// give a span of {m_active_p, size}
	[[nodiscard]] span<std::byte> Span() const;
	///
	void                   Rewind();                                 //
	static void            Reserve();                                //
	void                   Rewind(n_t a_off);                        //
	[[nodiscard]] uint8_t* mutable_data() const;                     //
	[[nodiscard]] uint8_t* data_at(n_t a_off) const;                 //
	[[nodiscard]] uint8_t* end() const;                              //
	void                   UnsafeAppend(const void* data_p, n_t sz); //
	void                   Append(const void* data_p, n_t sz);       //
	void                   Swap(const Buf& a_buf);                   //
	void                   Swap(uint8_t* p);                         //
	n_t                    length() const;                           //
	void                   Advance(n_t byte_c);                      //
	void                   UnsafeAdvance(n_t byte_c);                //
	void                   Reset();                                  //
	void                   Resize(sz_t new_sz);                      //
	sz_t                   Capacity() const;                         //
	void                   Clone(const Buf& a_buf);                  //

	template <typename PT>
	const PT* data(); //
	template <typename PT>
	PT* mutable_data(); //

private:
	void init();

private:
	/// capacity
	sz_t m_capacity;
	/// offset to end of data
	n_t      m_off;      //
	uint8_t* m_owned_p;  //
	uint8_t* m_active_p; //
};
} // namespace fastlanes

#endif // FLS_COR_LYT_BUF_HPP
