// ────────────────────────────────────────────────────────
// |                      FastLanes                       |
// ────────────────────────────────────────────────────────
// src/include/fls/footer/table_descriptor.hpp
// ────────────────────────────────────────────────────────
#ifndef FLS_FOOTER_TABLE_DESCRIPTOR_HPP
#define FLS_FOOTER_TABLE_DESCRIPTOR_HPP

#include "fls/common/alias.hpp" // n_t, up
#include "fls/footer/table_descriptor_generated.h"
#include "fls/std/filesystem.hpp" // path
#include "fls/std/vector.hpp"     // fastlanes::vector alias
#include <cstddef>
#include <cstdint>
#include <memory> // shared_ptr, std::make_unique

namespace fastlanes {

class Table;

class TableDescriptorHandle {
public:
	TableDescriptorHandle() = default;

	// Build from already-owned bytes (moves bytes into the handle).
	static TableDescriptorHandle FromBytes(vector<uint8_t> bytes, bool verify = true);

	// Read whole file and own the bytes.
	static TableDescriptorHandle FromFile(const path& file_path, bool verify = true);

	// Read a slice [offset, offset+size) from file and own the bytes.
	static TableDescriptorHandle FromFileSlice(const path& file_path, n_t offset, n_t size, bool verify = true);

	// Pack native T -> bytes and expose a view.
	static TableDescriptorHandle FromNative(const TableDescriptorT& native);

	// View access
	[[nodiscard]] const TableDescriptor* Get() const noexcept {
		return ptr_;
	}
	const TableDescriptor& operator*() const {
		return *ptr_;
	}
	const TableDescriptor* operator->() const {
		return ptr_;
	}
	[[nodiscard]] const uint8_t* data() const noexcept {
		return bytes_ ? bytes_->data() : nullptr;
	}
	[[nodiscard]] std::size_t size() const noexcept {
		return bytes_ ? bytes_->size() : 0;
	}
	explicit operator bool() const noexcept {
		return ptr_ != nullptr;
	}

	// Convert to native (owning) structure when you need mutability / STL containers.
	[[nodiscard]] up<TableDescriptorT> Unpack() const {
		if (!ptr_) {
			return {};
		}
		return up<TableDescriptorT>(ptr_->UnPack());
	}

private:
	// Internal constructor used by factory methods.
	TableDescriptorHandle(sp<vector<uint8_t>> bytes, const TableDescriptor* ptr)
	    : bytes_(std::move(bytes))
	    , ptr_(ptr) {
	}

	// Create a typed view into the owned bytes; may verify if requested.
	static const TableDescriptor* MakePtr(const sp<vector<uint8_t>>& bytes, bool verify);

private:
	sp<vector<uint8_t>>    bytes_;         // owning storage
	const TableDescriptor* ptr_ = nullptr; // view into bytes_->data()
};

/*──────────────────────────────────────────────────────────────────────────────┐
│ By-pointer helpers (return up<...>)                                          │
│ These heap-allocate the handle and return unique ownership (up<>).           │
└──────────────────────────────────────────────────────────────────────────────*/
up<TableDescriptorT> make_table_descriptor(const Table& table);

inline up<TableDescriptorHandle> make_table_descriptor(const path& file_path, bool verify = true) {
	return std::make_unique<TableDescriptorHandle>(TableDescriptorHandle::FromFile(file_path, verify));
}

inline up<TableDescriptorHandle>
make_table_descriptor(const path& file_path, n_t offset, n_t size, bool verify = true) {

	return std::make_unique<TableDescriptorHandle>(
	    TableDescriptorHandle::FromFileSlice(file_path, offset, size, verify));
}

} // namespace fastlanes

#endif // FLS_FOOTER_TABLE_DESCRIPTOR_HPP
