#ifndef FLS_COMMON_STRING_HPP
#define FLS_COMMON_STRING_HPP

#include "fls/common/alias.hpp" // for ofs_t, up, n_t, sz_t, len_t
#include "fls/std/string.hpp"   // for string
#include "fls/std/vector.hpp"   // for bsz_vec_t, ofs_vec_t
#include <cstdint>              // for uint8_t

namespace fastlanes {
/*--------------------------------------------------------------------------------------------------------------------*/
class FLSStrColumn;
/*--------------------------------------------------------------------------------------------------------------------*/
struct FlsString {
	const uint8_t* p;      // Pointer to the data
	len_t          length; // Length of the data

	FlsString();

	std::string to_string() const;

	friend std::ostream& operator<<(std::ostream& os, const FlsString& fls_string);

	bool operator==(const FlsString& other) const;
	FlsString(const FlsString& other);

	FlsString& operator=(const FlsString& other);
	FlsString(const uint8_t* data, len_t len);
};

using fls_string_t      = FlsString;
using decoupled_str_vec = std::pair<vector<len_t>, vector<uint8_t*>>;

class Str {
public:
	static decoupled_str_vec    decouple(n_t n, string* str_arr);                  //
	static up<bsz_vec_t>        get_bsz_vec(const ofs_t* ofs_arr, sz_t size);      //
	static up<ofs_vec_t>        to_normal_offset(const ofs_t* ofs_arr, sz_t size); //
	static up<vector<uint8_t*>> smart_offset_to_pointer(n_t c, ofs_t offset_arr[], uint8_t str_arr[]);
	static bool Equal(const FLSStrColumn& left_column, const FLSStrColumn& right_column, n_t left_idx, n_t right_idx);
};
} // namespace fastlanes

namespace std {
template <>
struct hash<fastlanes::FlsString> {
	size_t operator()(const fastlanes::FlsString& key) const noexcept;
};
} // namespace std

#endif // FLS_COMMON_STRING_HPP
