#include "fls/common/string.hpp"
#include "fls/cfg/cfg.hpp"
#include "fls/common/assert.hpp" // for FLS_ASSERT_CORRECT_SZ, FLS_ASSERT_N...
#include "fls/std/vector.hpp"    // for vector
#include "fls/table/rowgroup.hpp"
#include <cstring>
#include <memory> // for make_unique, unique_ptr

namespace fastlanes {

FlsString::FlsString()
    : p(nullptr)
    , length(INVALID_LENGTH) {
}

std::string FlsString::to_string() const {
	FLS_ASSERT_NOT_NULL_POINTER(p)

	return {reinterpret_cast<const char*>(p), length};
}

std::ostream& operator<<(std::ostream& os, const FlsString& fls_string) {
	os.write(reinterpret_cast<const char*>(fls_string.p), static_cast<std::streamsize>(fls_string.length));
	return os;
}

bool FlsString::operator==(const FlsString& other) const {
	FLS_ASSERT_NOT_NULL_POINTER(p)
	FLS_ASSERT_NOT_NULL_POINTER(other.p)

	if (length != other.length) {
		return false;
	}
	return std::memcmp(p, other.p, length) == 0;
}

FlsString::FlsString(const FlsString& other)
    : p(other.p)
    , length(other.length) {
	FLS_ASSERT_NOT_NULL_POINTER(other.p);
}

FlsString& FlsString::operator=(const FlsString& other) {
	FLS_ASSERT_NOT_NULL_POINTER(other.p);

	if (this == &other) {
		return *this; // Handle self-assignment
	}

	// Copy new resource
	length = other.length;
	p      = other.p;
	if (other.p) {
		std::memcpy(const_cast<uint8_t*>(p), other.p, length);
	}

	return *this;
}

FlsString::FlsString(const uint8_t* data, len_t len)
    : p(data)
    , length(len) {
}

decoupled_str_vec Str::decouple(n_t n, std::string* str_arr) {
	decoupled_str_vec result;
	auto&             len_vec = result.first;
	auto&             ptr_vec = result.second;

	for (n_t idx {0}; idx < n; ++idx) {

		auto& cur_str = str_arr[idx];

		FLS_ASSERT_LESS(cur_str.size(), CFG::String::MAX_SIZE)
		len_vec.push_back(static_cast<len_t>(cur_str.size()));
		ptr_vec.push_back(reinterpret_cast<uint8_t*>(cur_str.data()));
	}

	return result;
}

up<bsz_vec_t> Str::get_bsz_vec(const ofs_t* ofs_arr, sz_t size) {
	FLS_ASSERT_NOT_NULL_POINTER(ofs_arr)
	FLS_ASSERT_CORRECT_SZ(size)

	auto bsz_res_vec = std::make_unique<bsz_vec_t>();

	for (idx_t idx {0}, start {0}, end {0}; idx < size; ++idx) {
		end = ofs_arr[idx] - start;
		bsz_res_vec->push_back(end);
		start = ofs_arr[idx];
	}
	return bsz_res_vec;
}

up<ofs_vec_t> Str::to_normal_offset(const ofs_t* ofs_arr, sz_t size) {
	FLS_ASSERT_NOT_NULL_POINTER(ofs_arr)
	FLS_ASSERT_CORRECT_SZ(size)

	auto bsz_res_vec = std::make_unique<ofs_vec_t>();

	for (idx_t idx {0}, start {0}; idx < size; ++idx) {
		bsz_res_vec->push_back(start);
		start = ofs_arr[idx];
	}
	return bsz_res_vec;
}

up<vector<uint8_t*>> Str::smart_offset_to_pointer(n_t c, ofs_t offset_arr[], uint8_t str_arr[]) {

	auto tmp = std::make_unique<vector<uint8_t*>>();

	for (n_t i {0}, cur_ofs {0}; i < c; ++i) {
		tmp->push_back(&str_arr[cur_ofs]);
		cur_ofs = offset_arr[i];
	}
	return tmp;
}

bool Str::Equal(const FLSStrColumn& left_column, const FLSStrColumn& right_column, n_t left_idx, n_t right_idx) {
	const auto* left_p     = left_column.str_p_arr[left_idx];
	const auto* right_p    = right_column.str_p_arr[right_idx];
	const auto& left_size  = left_column.length_arr[left_idx];
	const auto& right_size = right_column.length_arr[right_idx];

	if (left_size != right_size) {
		return false;
	}

	return std::memcmp(left_p, right_p, left_size) == 0;
}

} // namespace fastlanes

namespace std {

// Define the specialization of std::hash for fastlanes::FlsString
size_t hash<fastlanes::FlsString>::operator()(const fastlanes::FlsString& key) const noexcept {
	const uint8_t* ptr  = key.p;
	size_t         len  = key.length;
	size_t         hash = 0;
	for (size_t i = 0; i < len; ++i) {
		hash = hash * 31 + ptr[i]; // Example hash function
	}
	return hash;
}

} // namespace std