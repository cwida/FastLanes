#include "fls/common/bimap_frequency.hpp"
#include "fls/expression/data_type.hpp"
#include <stdexcept>

namespace fastlanes {

// Constructor
template <typename PT>
BiMapFrequency<PT>::BiMapFrequency()
    : max_freq(0)
    , most_frequent_key(0) {
}

// Insert or update an entry
template <typename PT>
void BiMapFrequency<PT>::insert(n_t key, PT value) {
	if (key_to_value.find(key) != key_to_value.end()) {
		// Key already exists, update frequency
		key_to_value[key].frequency++;
	} else {
		// New key-value pair
		key_to_value[key]   = {value, 1};
		value_to_key[value] = key;
	}

	// Update most frequent key if necessary
	if (key_to_value[key].frequency > max_freq) {
		max_freq          = key_to_value[key].frequency;
		most_frequent_key = key;
	}
}

// Get the most frequent key (O(1))
template <typename PT>
n_t BiMapFrequency<PT>::get_most_frequent_key() const {
	if (max_freq == 0) {
		throw std::runtime_error("No elements exist in BiMapFrequency.");
	}
	return most_frequent_key;
}

// Get the most frequent value (O(1))
template <typename PT>
PT BiMapFrequency<PT>::get_most_frequent_value() const {
	if (max_freq == 0) {
		throw std::runtime_error("No elements exist in BiMapFrequency.");
	}
	return key_to_value.at(most_frequent_key).value;
}

// Get the value associated with a key (O(1))
template <typename PT>
PT BiMapFrequency<PT>::get_value(n_t key) const {
	auto it = key_to_value.find(key);
	if (it == key_to_value.end()) {
		throw std::runtime_error("Key not found in BiMapFrequency.");
	}
	return it->second.value;
}

// Get the key associated with a value (O(1))
template <typename PT>
n_t BiMapFrequency<PT>::get_key(PT value) const {
	auto it = value_to_key.find(value);
	if (it == value_to_key.end()) {
		throw std::runtime_error("Value not found in BiMapFrequency.");
	}
	return it->second;
}

// Check if a key exists
template <typename PT>
bool BiMapFrequency<PT>::contains_key(n_t key) const {
	return key_to_value.find(key) != key_to_value.end();
}

// Check if a value exists
template <typename PT>
bool BiMapFrequency<PT>::contains_value(PT value) const {
	return value_to_key.find(value) != value_to_key.end();
}

template <typename PT>
n_t BiMapFrequency<PT>::size() const {
	return key_to_value.size();
}

template <typename PT>
bool BiMapFrequency<PT>::empty() const {
	return key_to_value.empty();
}

template class BiMapFrequency<u64_pt>;
template class BiMapFrequency<u32_pt>;
template class BiMapFrequency<u16_pt>;
template class BiMapFrequency<u08_pt>;
template class BiMapFrequency<i64_pt>;
template class BiMapFrequency<i32_pt>;
template class BiMapFrequency<i16_pt>;
template class BiMapFrequency<i08_pt>;
template class BiMapFrequency<str_pt>;
template class BiMapFrequency<dbl_pt>;
template class BiMapFrequency<flt_pt>;

} // namespace fastlanes
