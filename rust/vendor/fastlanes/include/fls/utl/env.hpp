#ifndef FLS_UTL_ENV_HPP
#define FLS_UTL_ENV_HPP

#include "fls/common/common.hpp"
namespace fastlanes {
class Env {
public:
	static std::string GetEnvVariable(const char* key);
};
} // namespace fastlanes

#endif // FLS_UTL_ENV_HPP
