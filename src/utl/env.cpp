#include "fls/utl/env.hpp"

namespace fastlanes {

std::string Env::GetEnvVariable(const char* key) {
	const char* dataset_dir_path = std::getenv(key);
	if (dataset_dir_path == nullptr) {
		throw std::runtime_error(std::string("Environment variable ") + key + " IS NOT SET.");
	}

	return {dataset_dir_path};
}
} // namespace fastlanes
