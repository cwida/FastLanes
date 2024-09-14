#ifndef FLS_PRIMITIVE_ALP_MTD_HPP
#define FLS_PRIMITIVE_ALP_MTD_HPP

// NOLINTBEGIN

#include <cstdint>
#include <iostream>
namespace alp {
struct metadata {
	void print_dict() const { std::cout << "size: " << size << " | unq_c: " << unq_c << std::endl; }

	/* Deprecated :
	 *
	    dict_size : air_sensor_f : 50.0769
	    cnst_size : air_sensor_f : 54.3325
	    skew_size : air_sensor_f : 49.4082
	    dict_size : poi_lat : 56.5047
	    cnst_size : poi_lat : 55.2395
	    skew_size : poi_lat : 53.7731
	    dict_size : poi_lon : 57.329
	    cnst_size : poi_lon : 65
	    skew_size : poi_lon : 55.0901
	*/
	double cnst_vec_size() {
		double result = 1                                                        // bitmap
		                + (64.0 / 1024)                                          // on value
		                + (static_cast<double>(exc_c) * (64 + 16) / (1024 * 64)) //
		                + 64 - l_bw                                              // bitpacked
		    ;
		return result;
	}

	double dict_vec_size() {
		double result = log2(unq_c) + 64 - l_bw + ((static_cast<double>(unq_c * 64) / (1024)));
		return result;
	}

	double skew_vec_size() {
		double result = log2(unq_c)                                              //
		                + 64 - l_bw                                              //
		                + (static_cast<double>(exc_c) * (64 + 16) / (1024 * 64)) //
		                + ((static_cast<double>(unq_c * 64) / (1024)));
		return result;
	}

	double get_size() {
		double result = r_bw + l_bw + static_cast<double>(exc_c * (16 + 16)) / SMP_C;
		return result;
	}

	std::string to_string() {
		std::string res = "r_bw : " + std::to_string(r_bw) +     //
		                  "| l_bw : " + std::to_string(l_bw) +   //
		                  "| unq_c : " + std::to_string(unq_c) + //
		                  //		                  "| size :" + std::to_string(get_size()) + //
		                  //		                  "| exc_c : " + std::to_string(exc_c) +    //
		                  "| "; //

		for (auto x : repetition_vec) {
			res = res.append(std::to_string(static_cast<double>(x.first) / SMP_C) + " | ");
		}
		res = res.append("\n");
		return res;
	}

	bool exceeds() { return (unq_c > 26); }

	uint8_t                                    bw {0};
	uint16_t                                   exc_c {0};
	uint64_t                                   unq_c {0};
	uint16_t                                   freq {0};
	double                                     size {0};
	uint64_t                                   r_bw {0};
	uint64_t                                   l_bw {0};
	uint64_t                                   c {0};
	std::vector<std::pair<uint16_t, uint64_t>> repetition_vec;
};
} // namespace alp

#endif

// NOLINTEND
