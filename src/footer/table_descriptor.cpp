// ────────────────────────────────────────────────────────
// |                      FastLanes                       |
// ────────────────────────────────────────────────────────
// src/footer/table_descriptor.cpp
// ────────────────────────────────────────────────────────
#include "fls/footer/table_descriptor.hpp"
#include "flatbuffers/flatbuffer_builder.h"
#include "flatbuffers/verifier.h" // flatbuffers::Verifier
#include "fls/common/alias.hpp"
#include "fls/cor/lyt/buf.hpp"
#include "fls/footer/rowgroup_descriptor.hpp"
#include "fls/footer/table_descriptor_generated.h"
#include "fls/io/file.hpp"
#include "fls/std/filesystem.hpp"
#include "fls/std/vector.hpp"
#include "fls/table/table.hpp"
#include <cstddef> // std::size_t
#include <cstdint> // uint8_t
#include <cstring> // std::memcpy
#include <fstream>
#include <ios>
#include <memory> // std::shared_ptr, std::make_shared
#include <stdexcept>
#include <utility> // std::move
#include <vector>

namespace fastlanes {

const TableDescriptor& get_table_descriptor(const uint8_t* data, std::size_t size) {
	if (!data || size == 0) {
		throw std::invalid_argument("get_table_descriptor: null data or zero size");
	}
#if defined(DEBUG)
	{
		flatbuffers::Verifier v(data, size);
		if (!VerifyTableDescriptorBuffer(v)) {
			throw std::runtime_error("get_table_descriptor: invalid TableDescriptor FlatBuffer");
		}
	}
#endif
	return *GetTableDescriptor(data);
}

const TableDescriptor& make_table_descriptor(const path& file_path, std::vector<uint8_t>& storage) {
	std::ifstream in {file_path, std::ios::binary | std::ios::ate};
	if (!in) {
		throw std::runtime_error("make_table_descriptor: failed to open footer: " + file_path.string());
	}

	const auto sz = static_cast<std::size_t>(in.tellg());
	if (sz == 0) {
		throw std::runtime_error("make_table_descriptor: empty footer file: " + file_path.string());
	}

	storage.resize(sz);
	in.seekg(0, std::ios::beg);
	if (!in.read(reinterpret_cast<char*>(storage.data()), static_cast<std::streamsize>(sz))) {
		throw std::runtime_error("make_table_descriptor: failed to read footer: " + file_path.string());
	}

	return get_table_descriptor(storage.data(), storage.size());
}

const TableDescriptor&
make_table_descriptor(const path& file_path, n_t offset, n_t size, std::vector<uint8_t>& storage) {
	File f(file_path);
	Buf  buf;

	f.ReadRange(buf, offset, size);

	const auto* p = reinterpret_cast<const uint8_t*>(buf.data());
	storage.assign(p, p + buf.Size());

	return get_table_descriptor(storage.data(), storage.size());
}

const TableDescriptor* TableDescriptorHandle::MakePtr(const std::shared_ptr<vector<uint8_t>>& bytes, bool verify) {
	if (!bytes || bytes->empty()) {
		throw std::runtime_error("TableDescriptorHandle: empty buffer");
	}

	const uint8_t*    data = bytes->data();
	const std::size_t sz   = bytes->size();

#if defined(DEBUG)
	(void)verify; // always verify in DEBUG
	flatbuffers::Verifier v(data, sz);
	if (!VerifyTableDescriptorBuffer(v)) {
		throw std::runtime_error("TableDescriptorHandle: verification failed (DEBUG)");
	}
#else
	if (verify) {
		flatbuffers::Verifier v(data, sz);
		if (!VerifyTableDescriptorBuffer(v)) {
			throw std::runtime_error("TableDescriptorHandle: verification failed");
		}
	}
#endif

	return GetTableDescriptor(data);
}

TableDescriptorHandle TableDescriptorHandle::FromBytes(vector<uint8_t> bytes, bool verify) {
	auto sp  = std::make_shared<vector<uint8_t>>(std::move(bytes));
	auto ptr = MakePtr(sp, verify);
	return {std::move(sp), ptr};
}

TableDescriptorHandle TableDescriptorHandle::FromFile(const path& file_path, bool verify) {
	std::ifstream in {file_path, std::ios::binary | std::ios::ate};
	if (!in) {
		throw std::runtime_error("TableDescriptorHandle::FromFile: failed to open: " + file_path.string());
	}

	const auto sz = static_cast<std::size_t>(in.tellg());
	if (sz == 0) {
		throw std::runtime_error("TableDescriptorHandle::FromFile: empty file: " + file_path.string());
	}

	vector<uint8_t> storage(sz);
	in.seekg(0, std::ios::beg);
	if (!in.read(reinterpret_cast<char*>(storage.data()), static_cast<std::streamsize>(sz))) {
		throw std::runtime_error("TableDescriptorHandle::FromFile: failed to read: " + file_path.string());
	}

	return FromBytes(std::move(storage), verify);
}

TableDescriptorHandle TableDescriptorHandle::FromFileSlice(const path& file_path, n_t offset, n_t size, bool verify) {
	File f(file_path);
	Buf  buf;
	f.ReadRange(buf, offset, size);

	const auto*     p = reinterpret_cast<const uint8_t*>(buf.data());
	vector<uint8_t> storage;
	storage.assign(p, p + size);

	return FromBytes(std::move(storage), verify);
}

TableDescriptorHandle TableDescriptorHandle::FromNative(const TableDescriptorT& native) {
	flatbuffers::FlatBufferBuilder fbb;
	auto                           off = TableDescriptor::Pack(fbb, &native);
	fbb.Finish(off);

	auto            det = fbb.Release();
	vector<uint8_t> bytes(det.size());
	if (det.size() > 0) {
		std::memcpy(bytes.data(), det.data(), det.size());
	}

	return FromBytes(std::move(bytes), /*verify=*/false);
}

up<TableDescriptorT> make_table_descriptor(const Table& table) {
	auto table_descriptor = make_unique<TableDescriptorT>();

	for (n_t rowgroup_idx = 0; rowgroup_idx < table.get_n_rowgroups(); ++rowgroup_idx) {
		table_descriptor->m_rowgroup_descriptors.push_back(make_rowgroup_descriptor(*table.m_rowgroups[rowgroup_idx]));
	}
	table_descriptor->m_table_binary_size = 0;

	return table_descriptor;
}

} // namespace fastlanes
