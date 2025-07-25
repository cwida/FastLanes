// ────────────────────────────────────────────────────────
// |                      FastLanes                       |
// ────────────────────────────────────────────────────────
// src/utl/env.cpp
// ────────────────────────────────────────────────────────
#include "fls/utl/env.hpp"
#include "fls/std/string.hpp"
#include <cstdlib>
#include <stdexcept>

namespace fastlanes {

string Env::GetEnvVariable(const char* key) {
#ifdef _WIN32
	char*  buffer = nullptr;
	size_t size   = 0;
	if (_dupenv_s(&buffer, &size, key) != 0 || buffer == nullptr) {
		throw std::runtime_error(string("Environment variable ") + key + " IS NOT SET.");
	}
	string value(buffer);
	free(buffer);
	return value;
#else
	const char* dataset_dir_path = std::getenv(key);
	if (dataset_dir_path == nullptr) {
		throw std::runtime_error(string("Environment variable ") + key + " IS NOT SET.");
	}
	return {dataset_dir_path};
#endif
}

} // namespace fastlanes
