#ifndef FLS_UTL_TO_STR_HPP
#define FLS_UTL_TO_STR_HPP

#include "fls/common/common.hpp"
#include "fls/std/string.hpp"

namespace fastlanes {
class ExpEncodedCol;
class Expression;
class Buf;
class EpArr;
class OffArr;
class Page;
enum class ExpT : uint8_t;

class ToStr {
public:
	///!
	static string to_str(const Expression& expression_hdr);
	///!
	static string to_str(var_t var_t, ExpT exp_t);
	///!
	static string to_str(ExpT exp_t);
	///!
	static string to_str(Buf& buffer_builder);
	///!
	static string to_str(EpArr& ep_arr);
	///!
	static string to_str(OffArr& off_arr);
	///!
	static string to_str(Page& page);
	///!
	template <typename T>
	static string to_str(T* p);
	///!
	template <typename T>
	static string to_str(T* p, n_t c);
	///!
	static string to_hex(uint8_t* p, n_t c);
	///!
	template <typename T>
	static string to_str(T val);
	///!
	static string to_str(const ExpEncodedCol& expression_hdr);
};

} // namespace fastlanes
#endif // FLS_UTL_TO_STR_HPP
