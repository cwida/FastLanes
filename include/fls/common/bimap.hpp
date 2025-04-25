#ifndef FLS_COMMON_BIMAP_HPP
#define FLS_COMMON_BIMAP_HPP

#include "fls/common/alias.hpp"
#include "fls/common/assert.hpp"
#include "fls/common/string.hpp"
#include "fls/std/unordered_map.hpp"
#include <stdexcept>

namespace fastlanes {

class BiMapFrequencyStr {
public:
	struct FrequencyEntry {
		n_t value;     ///< The mapped numeric value
		n_t frequency; ///< Number of times this key has been inserted
	};

public:
	BiMapFrequencyStr()
	    : max_freq_(0) {
	}

	void insert(const fls_string_t& key, n_t value) {
		auto it = forward_map_.find(key);
		if (it != forward_map_.end()) {
			FrequencyEntry& entry = it->second;
			if (entry.value != value) {
				throw std::runtime_error(
				    "BiMapFrequency<fls_string_t>::insert: Key already exists with a different value.");
			}
			++entry.frequency;

			if (entry.frequency > max_freq_) {
				max_freq_          = entry.frequency;
				most_frequent_key_ = key;
			}
		} else {
			FrequencyEntry new_entry {value, 1};
			forward_map_.emplace(key, new_entry);

			auto rev_it = reverse_map_.find(value);
			if (rev_it != reverse_map_.end()) {
				throw std::runtime_error(
				    "BiMapFrequency<fls_string_t>::insert: Value already associated with another key.");
			}
			reverse_map_[value] = key;

			// Update the frequency trackers
			if (new_entry.frequency > max_freq_) {
				max_freq_          = new_entry.frequency;
				most_frequent_key_ = key;
			}
		}
	}

	n_t get_value(const fls_string_t& key) const {
		auto it = forward_map_.find(key);
		if (it == forward_map_.end()) {
			throw std::runtime_error("BiMapFrequency<fls_string_t>::get_value: Key not found.");
		}
		return it->second.value;
	}

	fls_string_t get_key(n_t value) const {
		auto it = reverse_map_.find(value);
		if (it == reverse_map_.end()) {
			throw std::runtime_error("BiMapFrequency<fls_string_t>::get_key: Value not found.");
		}
		return it->second;
	}

	bool contains_key(const fls_string_t& key) const {
		return (forward_map_.find(key) != forward_map_.end());
	}

	bool contains_value(n_t value) const {
		return (reverse_map_.find(value) != reverse_map_.end());
	}

	std::size_t size() const {
		FLS_ASSERT_EQUALITY(forward_map_.size(), reverse_map_.size());
		return forward_map_.size();
	}

	bool empty() const {
		return forward_map_.empty();
	}

	fls_string_t get_most_frequent_key() const {
		if (empty()) {
			throw std::runtime_error("BiMapFrequency<fls_string_t>::get_most_frequent_key: Map is empty.");
		}
		return most_frequent_key_;
	}

	n_t get_most_frequent_value() const {
		if (empty()) {
			throw std::runtime_error("BiMapFrequency<fls_string_t>::get_most_frequent_value: Map is empty.");
		}
		// safe to call at() because we know most_frequent_key_ must exist
		return forward_map_.at(most_frequent_key_).value;
	}

	n_t get_key_frequency(const fls_string_t& key) const {
		auto it = forward_map_.find(key);
		if (it == forward_map_.end()) {
			return 0;
		}
		return it->second.frequency;
	}

private:
	/// fls_string_t → FrequencyEntry (value + frequency)
	unordered_map<fls_string_t, FrequencyEntry> forward_map_;

	/// n_t → fls_string_t (reverse lookup)
	unordered_map<n_t, fls_string_t> reverse_map_;

	/// The highest frequency so far
	n_t max_freq_;

	/// The key having the highest frequency
	fls_string_t most_frequent_key_;
};

} // namespace fastlanes

#endif // FLS_COMMON_BIMAP_HPP
