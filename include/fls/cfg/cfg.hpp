#ifndef FLS_CFG_CFG_HPP
#define FLS_CFG_CFG_HPP

#include "fls/common/alias.hpp"         // for hdr_field_t
#include "fls/expression/data_type.hpp" // for u32_pt, dbl_pt, i32_pt, i64_pt, u64_pt
#include <cstdint>                      // for uint64_t, uint8_t, uint32_t

namespace fastlanes {
class CFG {
public:
	explicit CFG(); //
public:
	static constexpr uint64_t ENTRY_POINT_SZ = 4;            //
	static constexpr uint8_t  MAJOR_VERSION  = 0;            //
	static constexpr uint8_t  MINOR_VERSION  = 0;            //
	static constexpr uint8_t  MICRO_VERSION  = 1;            //
	static constexpr uint32_t SPECIAL_CODE   = 1370;         //
	static constexpr uint64_t HDR_SZ         = 8;            //
	static constexpr uint64_t EXP_HDR_SZ     = 8;            //
	static constexpr uint64_t FUNCTION_C     = 10;           //
	static constexpr uint64_t VEC_SZ         = 1024;         //
	static constexpr uint64_t VEC_TUP_C      = 1024;         //
	static constexpr uint64_t ROW_GROUP_SIZE = 256UL * 1024; //

	/* String Config. */
	struct String {
		static constexpr uint64_t MAX_SIZE           = 4294967295; // max 32 bit unsigned integer
		static constexpr uint64_t ADAPTIVE_TRY_C     = 3;          //
		static constexpr double   ADAPTIVE_THRESHOLD = 00.80;      //
	};

	/* Sampler Config. */
	struct SAMPLER {
		static constexpr uint64_t SAMPLE_C           = 16UL * 1024; //
		static constexpr uint64_t ADAPTIVE_TRY_C     = 3;           //
		static constexpr double   ADAPTIVE_THRESHOLD = 00.80;       //
	};

	/* Dictionary Config. */
	struct DIC {
		static constexpr uint64_t SAMPLE_C    = 16;            // start sample c for adaptive dict creation
		static constexpr uint64_t THRESHOLD   = 1024 * 9 / 10; // 90%
		static constexpr uint64_t DIC_PAGE_SZ = 256UL * 1024;  //
	};

	/* Page Config. */
	struct PG {
		static constexpr uint64_t HDR_SZ         = 8;                          //
		static constexpr uint64_t SZ             = 64ULL * 8 * 256 * 1024 * 4; // FIXME
		static constexpr uint64_t ENTRY_POINT_SZ = 4;                          //
		static constexpr uint64_t OFFSET_SZ      = 4;                          //
		static constexpr uint64_t BUF_C          = 6;                          //
	};

	/* Vec Config. */
	struct VEC {
		static constexpr uint64_t MAX_VEC_ARR_C = 6; //
	};

	/* Prm Config. */
	struct PRM {
		static constexpr uint64_t PRM_C = 6; //
	};

	/* CMPR Config. */
	struct CMPR {
		static constexpr uint64_t EXC_LIMIT_C = 100; // between 5 and 10 percent
	};

	/* PQ Config. */
	struct PQ {
		static constexpr uint64_t DATA_PG_SZ = 8 * 64 * 256UL * 1024; // FIXME
		static constexpr uint64_t DICT_PG_SZ = 256UL * 1024;
		static constexpr uint64_t BATCH_C    = 1024;
	};

	/* REC Config. */
	struct REC {
		static constexpr uint8_t SPECIAL_BW = 255;
	};

	struct LOG {
		static constexpr uint64_t MAX = 5;
	};

	struct BIT_MAP {
		static constexpr uint64_t UNIT_BIT = 64;                //
		static constexpr uint64_t SZ       = VEC_SZ / 8;        //
		static constexpr uint64_t UNIT_C   = VEC_SZ / UNIT_BIT; //
	};

	struct FF {
		static constexpr uint64_t    MORSEL_SZ       = VEC_SZ * 128;
		static constexpr hdr_field_t VERSION         = 001;
		static constexpr hdr_field_t NO_WRITTEN_CODE = 999999999;
		static constexpr hdr_field_t FF_SPECIAL_CODE = 1370;
		static constexpr hdr_field_t RG_SPECIAL_CODE = 111111111;
		static constexpr hdr_field_t CC_SPECIAL_CODE = 222222222;
	};

	struct FSST {
		static constexpr int NULL_TERMINATED = 0; //
	};
};

} // namespace fastlanes
#endif // FLS_CFG_CFG_HPP
