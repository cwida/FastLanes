#include "fls/footer/table_descriptor.hpp"
#include "fls/connection.hpp"
#include "fls/flatbuffers/flatbuffers.hpp"
#include "fls/io/file.hpp"
#include "fls/json/fls_json.hpp"
#include "fls/json/nlohmann/json.hpp"
#include "fls/table/table.hpp"

namespace fastlanes {

// TableDescriptor::TableDescriptor()
//     : m_table_binary_size {0} {
// }
//
// // Deep-copy: clone each RowgroupDescriptor via its copy-ctor
// TableDescriptor::TableDescriptor(const TableDescriptor& o)
//     : m_rowgroup_descriptors {} // start empty
//     , m_table_binary_size(o.m_table_binary_size) {
// 	m_rowgroup_descriptors.reserve(o.m_rowgroup_descriptors.size());
// 	for (auto const& up_rg : o.m_rowgroup_descriptors) {
// 		// invoke RowgroupDescriptor’s own copy-ctor
// 		m_rowgroup_descriptors.emplace_back(std::make_unique<RowgroupDescriptorT>(*up_rg));
// 	}
// }
//
// n_t TableDescriptor::GetNRowgroups() const {
// 	return m_rowgroup_descriptors.size();
// }

//
// template <enum FooterType::JSON>
// up<TableDescriptorT> make_table_descriptor(const path& file_path) {
// 	auto                 json_string      = File::read(file_path);
// 	const nlohmann::json j                = nlohmann::json::parse(json_string);
// 	auto                 table_descriptor = j.get<TableDescriptorT>();
// 	return make_unique<TableDescriptorT>(table_descriptor);
// }

up<TableDescriptorT> make_table_descriptor(const Table& table) {
	auto table_descriptor = make_unique<TableDescriptorT>();

	for (n_t rowgroup_idx = 0; rowgroup_idx < table.get_n_rowgroups(); ++rowgroup_idx) {
		table_descriptor->m_rowgroup_descriptors.push_back(make_rowgroup_descriptor(*table.m_rowgroups[rowgroup_idx]));
	}
	table_descriptor->m_table_binary_size = 0;

	return table_descriptor;
}

std::unique_ptr<TableDescriptorT> make_table_descriptor(const std::filesystem::path& file_path) {
	// init
	std::ifstream in {file_path, std::ios::binary | std::ios::ate};
	if (!in) {
		throw std::runtime_error("Failed to open footer: " + file_path.string());
	}

	//
	auto size = in.tellg();
	in.seekg(0, std::ios::beg);
	std::vector<uint8_t> buffer(static_cast<size_t>(size));
	if (!in.read(reinterpret_cast<char*>(buffer.data()), size)) {
		throw std::runtime_error("Failed to read footer: " + file_path.string());
	}
	in.close();

#ifdef DEBUG
	flatbuffers::Verifier verifier(buffer.data(), buffer.size());
	if (!fastlanes::VerifyTableDescriptorBuffer(verifier)) {
		throw std::runtime_error("Invalid FlatBuffer in file: " + file_path.string());
	}
#endif

	const auto accessor = GetTableDescriptor(buffer.data());

	// (deep copy)
	TableDescriptorT* raw = accessor->UnPack();
	if (!raw) {
		throw std::runtime_error("Failed to unpack TableDescriptor from buffer: " + file_path.string());
	}

	return up<TableDescriptorT>(raw);
}

up<TableDescriptorT> make_table_descriptor(const path& file_path, const n_t offset, const n_t size) {
	// init
	File file(file_path);
	Buf  buf; // OPTIMIZE

	file.ReadRange(buf, offset, size);
	const auto accessor = fastlanes::GetTableDescriptor(buf.data());

	// 4) Deep-copy into a TableDescriptorT and wrap in a unique_ptr
	TableDescriptorT* raw = accessor->UnPack();
	if (!raw) {
		throw std::runtime_error("Failed to unpack TableDescriptor from slice in file: " + file_path.string());
	}

	return up<TableDescriptorT>(raw);
}

} // namespace fastlanes
