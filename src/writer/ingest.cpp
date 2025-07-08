#include "fls/writer/ingest.hpp"

namespace fastlanes {

static bool isValidUint64(const std::string& str) {
	if (str.empty()) {
		return false;
	}

	// Check if the string contains only digits
	for (char c : str) {
		if (!std::isdigit(c)) {
			return false;
		}
	}

	try {
		// Convert to unsigned long long and check if it's within uint64_t range
		uint64_t value = std::stoull(str);
		return value <= std::numeric_limits<uint64_t>::max();
	} catch (const std::exception&) {
		return false; // Overflow or invalid conversion
	}
}

static bool IsNumeric(const string& val_str) {
	if (val_str.empty()) {
		return false; // Empty string is not an integer
	}

	const size_t startIndex = (val_str[0] == '+' || val_str[0] == '-') ? 1 : 0;

	for (size_t i = startIndex; i < val_str.size(); ++i) {
		if (!std::isdigit(val_str[i])) {
			return false;
		}
	}

	return true;
}

void Ingest::FLSStringIngest(FLSStrColumn& fls_str_column, std::span<const str_pt> src_column) {
		const auto count = src_column.size();

		auto& byte_arr            = fls_str_column.byte_arr;
		auto& ofs_arr             = fls_str_column.ofs_arr;
		auto& max_n_bytes_p_value = fls_str_column.m_stats.maximum_n_bytes_p_value;
		auto& length_arr          = fls_str_column.length_arr;
		auto& is_numeric          = fls_str_column.m_stats.is_numeric;

		auto& fsst_byte_arr   = fls_str_column.fsst_byte_arr;
		auto& fsst_length_arr = fls_str_column.fsst_length_arr;

		if (length_arr.empty()) {
			is_numeric = true;
		}

		for (idx_t i = 0; i < count; i++) {
			const str_pt& value = src_column[i];
			if (value.size() > CFG::String::max_bytes_per_string) {
				throw std::runtime_error("String of size " + std::to_string(value.size()) +
				                         " exceeds the maximum allowed size of " +
				                         std::to_string(CFG::String::max_bytes_per_string) + " bytes.");
			}
			const bool is_null = value == TypedNull<str_pt>();

			fls_str_column.null_map_arr.push_back(is_null);
			string current_val;
			if (!is_null) {
				current_val                          = value;
				fls_str_column.m_stats.last_seen_val = current_val;
			} else {
				current_val = fls_str_column.m_stats.last_seen_val;
			}

			if (is_numeric && !is_null && !isValidUint64(current_val)) {
				is_numeric = false;
			}

			const size_t old_size = byte_arr.size(); // Save the current size
			ofs_arr.push_back(static_cast<ofs_t>(byte_arr.size()));
			byte_arr.resize(byte_arr.size() + current_val.size());
			std::memcpy(byte_arr.data() + old_size, current_val.data(), current_val.size());
			length_arr.push_back(static_cast<len_t>(current_val.size()));

			// calculate maximum size of a value
			max_n_bytes_p_value = (max_n_bytes_p_value > current_val.size()) ? max_n_bytes_p_value : current_val.size();
			is_numeric          = is_numeric && IsNumeric(value);

			// FSST
			{
				// check if it NULL
				if (!is_null) {
					current_val                          = value;
					fls_str_column.m_stats.last_seen_val = current_val;
				} else {
					current_val = "";
				}

				// push
				const size_t fsst_old_size = fsst_byte_arr.size(); // Save the current size
				fsst_byte_arr.resize(fsst_byte_arr.size() + current_val.size());
				std::memcpy(fsst_byte_arr.data() + fsst_old_size, current_val.data(), current_val.size());
				fsst_length_arr.push_back(static_cast<len_t>(current_val.size()));
			}
		}
	}

} // namespace fastlanes