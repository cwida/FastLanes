#ifndef FLS_PRINTER_TO_STR_HPP
#define FLS_PRINTER_TO_STR_HPP

#include "fls/common/common.hpp"
#include "fls/std/string.hpp"

namespace fastlanes {
class ExpEncodedCol;
class Expression;
class Buf;
class ep_arr;
class off_arr;
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
	static string to_str(ep_arr& ep_arr);
	///!
	static string to_str(off_arr& off_arr);
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
#endif // FLS_PRINTER_TO_STR_HPP
