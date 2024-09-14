#include "fls/printer/to_str.hpp"
#include "fls/cfg/cfg.hpp"
#include "fls/cor/exp/exp_pool.hpp"
#include "fls/cor/exp/exp_type.hpp"
#include "fls/cor/lyt/page/entry_point.hpp"
#include "fls/cor/lyt/page/offset.hpp"
#include "fls/cor/lyt/page/page.hpp"
#include <fls/encoder/exp_col_encoder.hpp>
#include <iomanip>
#include <sstream>

namespace fastlanes {

template <typename T>
std::string print_arr(const T* p, n_t c) {
	if constexpr (std::is_same<T, bool>()) {
		FLS_ABORT("Not Supported")
	} else {
		std::stringstream ss;
		ss << "[";
		for (size_t i {0}; i < c; ++i) {
			ss << std::to_string(p[i]);
			if (i != c - 1) { ss << " "; };
		}
		ss << "]";
		return ss.str();
	}
	return {};
}

std::string ToStr::to_str(Buf& buffer_builder) {
	return print_arr<uint32_t>(reinterpret_cast<const uint32_t*>(buffer_builder.data()), CFG::LOG::MAX);
}
std::string ToStr::to_str(ep_arr& ep_arr) { return print_arr<uint32_t>(ep_arr.arr, ep_arr.m_arr_c); }

std::string ToStr::to_str(off_arr& off_arr) { return print_arr<uint32_t>(off_arr.arr, off_arr.arr_c()); }

std::string ToStr::to_str(Page& page) {
	return print_arr<uint32_t>(reinterpret_cast<const uint32_t*>(page.start_p), CFG::LOG::MAX);
}

template <typename T>
std::string ToStr::to_str(T* p) {
	return print_arr<T>(reinterpret_cast<T*>(p), CFG::LOG::MAX);
}

template <typename T>
std::string ToStr::to_str(T* p, n_t c) {
	return print_arr<T>(reinterpret_cast<T*>(p), c);
}

template <>
std::string ToStr::to_str(void* p) {
	auto              typed_p = reinterpret_cast<uint64_t*>(p);
	std::stringstream ss;
	ss << "0x ";
	for (size_t i {0}; i < 16; ++i) {
		ss << std::uppercase << std::hex << std::setw(2) << std::setfill('0') << typed_p[i] << " ";
	}
	return ss.str();
}

std::string ToStr::to_hex(uint8_t* p, n_t c) {
	std::stringstream ss;
	ss << "0x ";
	for (size_t i {0}; i < c; ++i) {
		ss << std::uppercase << std::hex << std::setw(2) << std::setfill('0') << +p[i] << " ";
	}
	return ss.str();
}

string ToStr::to_str(const ExpEncodedCol& expression_hdr) {
	std::stringstream result;

	result << to_str(expression_hdr.expression);
	result << ",";
	result << expression_hdr.bsz;

	return result.str();
}

template <typename T>
std::string ToStr::to_str(T val) {
	std::stringstream ss;
	ss << val;
	return ss.str();
}

std::string ToStr::to_str(ExpT exp_t) {
	switch (exp_t) {
	case ExpT::INVALID:
		return {"INVALID"};
	case ExpT::UNDECIDED:
		return {"UNDECIDED"};
	case ExpT::UNCOMPRESSED:
		return {"UNCOMPRESSED"};
	case ExpT::BYTE_ARR:
		return {"BYTE_ARR"};
	case ExpT::FFOR:
		return {"FFOR"};
	case ExpT::DELTA:
		return {"DELTA"};
	case ExpT::RLE:
		return {"RLE"};
	case ExpT::DICT:
		return {"DICT"};
	case ExpT::FSST:
		return {"FSST"};
	case ExpT::DICT_RLE:
		return {"DICT_RLE"};
	case ExpT::DICT_FRQ:
		return {"DICT_FRQ"};
	case ExpT::DICT_VAL:
		return {"DICT_VAL"};
	case ExpT::TGT_EQUALITY:
		return {"TARGET_EQUALITY"};
	case ExpT::TGT_1T1:
		return {"TARGET_1T1"};
	case ExpT::TGT_1TN:
		return {"TARGET_1TN"};
	case ExpT::SRC_1T1:
		return {"SRC_1T1"};
	case ExpT::SRC_1TN:
		return {"SRC_1TN"};
	case ExpT::ALP:
		return {"ALP"};
	case ExpT::ALP_RD:
		return {"ALP_RD"};
	case ExpT::FSST12:
		return {"FSST12"};
	default:
		FLS_ABORT("NOT IMPLEMENTED!")
	}
	FLS_ABORT(" NOT IMPLEMENTED! ")
	return "";
}

string ToStr::to_str(const Expression& expression_hdr) {
	string res_str = "[ " + to_str(expression_hdr.exp) + ", " + to_str(expression_hdr.var, expression_hdr.exp) + " ]";
	return res_str;
}

std::string ToStr::to_str(var_t var_t, ExpT exp_t) {
	switch (exp_t) {
	case ExpT::INVALID:
		return {"INVALID"};
	case ExpT::UNDECIDED:
		return {"UNDECIDED"};
	case ExpT::UNCOMPRESSED:
		switch (var_t) {
		case 0:
			return "INVALID";
		case 1:
			return "UNCOMPRESSED";
		}
	case ExpT::BYTE_ARR:
		switch (var_t) {
		case 0:
			return "INVALID";
		case 1:
			return "UNCOMPRESSED";
		case 2:
			return "DELTA_NO_PATCH";
		}
	case ExpT::FFOR:
		switch (var_t) {
		case 0:
			return "INVALID";
		case 1:
			return "NO_PATCH";
		case 2:
			return "LL_PATCH";
		case 3:
			return "S_PATCH";
		case 4:
			return "B_PATCH";
		case 5:
			return "S_PATCH_REC";
		}
	case ExpT::DELTA:
		switch (var_t) {
		case 0:
			return "INVALID";
		case 1:
			return "NO_PATCH";
		case 2:
			return "LL_PATCH";
		case 3:
			return "S_PATCH";
		case 4:
			return "B_PATCH";
		case 5:
			return "B_PATCH_REC";
		}
	case ExpT::RLE:
		switch (var_t) {
		case 0:
			return "INVALID";
		case 1:
			return "UNCOMPRESSED";
		case 2:
			return "DELTA_NO_PATCH";
		case 3:
			return "SIMPLE_REC";
		case 4:
			return "WITH_DELTA_NO_PATCH_REC";
		case 5:
			return "WITH_DELTA_NO_PATCH_REC2";
		}
	case ExpT::DICT_RLE:
		switch (var_t) {
		case 0:
			return "INVALID";
		case 1:
			return "SIMPLE";
		case 2:
			return "WITH_DELTA_NO_PATCH";
		case 3:
			return "SIMPLE_REC";
		case 4:
			return "WITH_DELTA_NO_PATCH_REC";
		case 5:
			return "WITH_DELTA_NO_PATCH_REC2";
		}
	case ExpT::DICT_VAL:
	case ExpT::DICT_FRQ:
	case ExpT::DICT:
		switch (var_t) {
		case 0:
			return "INVALID";
		case 1:
			return "UNCOMPRESSED";
		case 2:
			return "FFOR_NO_PATCH";
		case 3:
			return "FFOR_LL_PATCH";
		case 4:
			return "FFOR_S_PATCH";
		case 5:
			return "FFOR_B_PATCH";
		case 6:
			return "FFOR_S_PATCH_REC";
		case 7:
			return "DELTA_NO_PATCH";
		case 8:
			return "DELTA_LL_PATCH";
		case 9:
			return "DELTA_S_PATCH";
		case 10:
			return "DELTA_B_PATCH";
		case 11:
			return "DELTA_B_PATCH_REC";
		}
	case ExpT::FSST:
		switch (var_t) {
		case 0:
			return "INVALID";
		case 1:
			return "UNCOMPRESSED";
		case 2:
			return "DELTA_NO_PATCH";
		}

	case ExpT::FSST12:
		switch (var_t) {
		case 0:
			return "INVALID";
		case 1:
			return "UNCOMPRESSED";
		case 2:
			return "DELTA_NO_PATCH";
		}

	case ExpT::TGT_EQUALITY: {
		return "";
	}
	case ExpT::TGT_1T1: {
		return "";
	}
	case ExpT::TGT_1TN: {
		return "";
	}
	case ExpT::SRC_1T1: {
		return "";
	}
	case ExpT::SRC_1TN: {
		return "";
	}
	case ExpT::ALP: {
		switch (var_t) {
		case 1:
			return "ALP_PDE";
		}
	}
	case ExpT::ALP_RD: {
		return " ";
	}
	default:
		FLS_ABORT("NOT IMPLEMENTED!")
	}

	FLS_ABORT("NOT IMPLEMENTED")
	return "";
}

/*---------------------------------------------------------------------------------------------------------------------\
 * Specialization
\---------------------------------------------------------------------------------------------------------------------*/
// clang-format off
template std::string ToStr::to_str<uint8_t>(uint8_t *p);
template std::string ToStr::to_str<uint16_t>(uint16_t *p);
template std::string ToStr::to_str<uint32_t>(uint32_t *p);
template std::string ToStr::to_str<uint64_t>(uint64_t *p);
template std::string ToStr::to_str<int8_t>(int8_t *p);
template std::string ToStr::to_str<int16_t>(int16_t *p);
template std::string ToStr::to_str<int32_t>(int32_t *p);
template std::string ToStr::to_str<int64_t>(int64_t *p);
template std::string ToStr::to_str<float>(float *p);
template std::string ToStr::to_str<double>(double *p);
template std::string ToStr::to_str<bool>(bool *p);


template std::string ToStr::to_str<uint8_t>(uint8_t *p, n_t c);
template std::string ToStr::to_str<uint16_t>(uint16_t *p, n_t c);
template std::string ToStr::to_str<uint32_t>(uint32_t *p, n_t c);
template std::string ToStr::to_str<uint64_t>(uint64_t *p, n_t c);
template std::string ToStr::to_str<int8_t>(int8_t *p, n_t c);
template std::string ToStr::to_str<int16_t>(int16_t *p, n_t c);
template std::string ToStr::to_str<int32_t>(int32_t *p, n_t c);
template std::string ToStr::to_str<int64_t>(int64_t *p, n_t c);
template std::string ToStr::to_str<float>(float *p, n_t c);
template std::string ToStr::to_str<double>(double *p, n_t c);
template std::string ToStr::to_str<bool>(bool *p, n_t c);

template std::string ToStr::to_str<uint16_t>(uint16_t val);


} // namespace fastlanes