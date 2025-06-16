#ifndef JSON_UNIQUE_PTR_HPP
#define JSON_UNIQUE_PTR_HPP

#include <fls/json/nlohmann/json.hpp> // must come first
#include <memory>                     // std::unique_ptr

// ──────────────────────────────────────────────────────────────────────────────
// ADL serializer for std::unique_ptr<T>
//   * Works for any T that is already serialisable on its own.
//   * JSON null   ↔  empty unique_ptr
//   * Allocates with std::make_unique<T>.
// ──────────────────────────────────────────────────────────────────────────────
namespace nlohmann {

template <typename T>
struct adl_serializer<std::unique_ptr<T>> {
	// json → std::unique_ptr<T>
	static void from_json(const json& j, std::unique_ptr<T>& ptr) {
		if (j.is_null()) {
			ptr.reset();
			return;
		}

		// allocate destination object if the pointer is currently empty
		if (!ptr)
			ptr = std::make_unique<T>();

		// delegate field-wise parsing to T’s own deserialiser
		j.get_to(*ptr);
	}

	// std::unique_ptr<T> → json
	static void to_json(json& j, const std::unique_ptr<T>& ptr) {
		if (ptr)
			j = *ptr; // serialise object pointed to
		else
			j = nullptr; // empty → JSON null
	}
};

} // namespace nlohmann
#endif // JSON_UNIQUE_PTR_HPP
