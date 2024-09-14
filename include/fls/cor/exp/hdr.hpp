#ifndef FLS_COR_EXP_HDR_HPP
#define FLS_COR_EXP_HDR_HPP

#include <cstddef> // for byte
#include <cstdint> // for uint16_t, uint8_t
#include <iosfwd>  // for string

namespace fastlanes { namespace exp {
struct Hdr {
public:
	uint16_t fun_c; /**/
	uint16_t val_o; /**/
	uint16_t col_o; /**/
	uint16_t fun_o; /**/
public:
	static Hdr                Load(uint8_t* p);             /**/
	static Hdr                Load(std::byte* p);           /**/
	std::string&              operator<<(std::string& lhs); /**/
	[[nodiscard]] std::string ToString() const;             /**/
};
}}     // namespace fastlanes::exp
#endif // FLS_COR_EXP_HDR_HPP
