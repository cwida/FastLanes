#ifndef FLS_COMMON_BIMAP_FREQUENCY_HPP
#define FLS_COMMON_BIMAP_FREQUENCY_HPP

#include "fls/common/alias.hpp"
#include "fls/std/unordered_map.hpp"

namespace fastlanes {

// Struct to hold value and frequency
template <typename PT>
struct FrequencyEntry {
	PT  value;     // Associated value (e.g., index)
	n_t frequency; // Frequency count
};

// Template class for bidirectional map with frequency tracking
template <typename PT>
class BiMapFrequency {
public:
	// n_t → {PT, frequency}
	unordered_map<n_t, FrequencyEntry<PT>> key_to_value;
	unordered_map<PT, n_t>                 value_to_key;      // PT → n_t (reverse lookup)
	n_t                                    max_freq;          // Highest frequency recorded
	n_t                                    most_frequent_key; // Key with the highest frequency

public:
	BiMapFrequency();

public:
	//
	void insert(n_t key, PT value);
	//
	n_t get_most_frequent_key() const;
	//
	PT get_most_frequent_value() const;
	//
	PT get_value(n_t key) const;
	//
	n_t get_key(PT value) const;
	//
	bool contains_key(n_t key) const;
	//
	bool contains_value(PT value) const;
	//
	n_t size() const;
	//
	bool empty() const;
};

} // namespace fastlanes
#endif // FLS_COMMON_BIMAP_FREQUENCY_HPP
