#ifndef FLS_COM_EXCEPTION_HPP
#define FLS_COM_EXCEPTION_HPP

#include "fls/common/common.hpp"
#include <sstream>
class Exception : public std::runtime_error {
	std::string msg; /**/
public:
	Exception(const std::string& arg, const char* file, int line)
	    : std::runtime_error(arg) {
		std::ostringstream o;
		o << file << ":" << line << ": " << arg;
		msg = o.str();
	}
	~Exception() throw() override {}
};

#endif // FLS_COM_EXCEPTION_HPP
