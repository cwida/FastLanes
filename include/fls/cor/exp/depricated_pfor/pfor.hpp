#ifndef FLS_EXP_PFOR_PFOR_HPP
#define FLS_EXP_PFOR_PFOR_HPP

#include "fls/cor/col.hpp"
#include "fls/cor/compression_plan.hpp"
#include "fls/exp/pfor/cfg.hpp"
#include "fls/exp/pfor/seg.hpp"
#include "fls/exp/typ.hpp"
#include "fls/utl/util.hpp"

namespace fast_lanes { namespace pfor {
using std::vector;
template <typename T>
struct Setting {
	uint64_t bit_c; /**/
	T        base;  /**/
	uint64_t exc_c; /**/
	byte_c   Size(count_t c) {
		  return byte_c {(c * bit_c / CHAR_BIT) + exc_c * sizeof(T)};
	}
};

template <typename T>
class PFor {
public:
	static bool                   TryFill(sp<Scanner<T>> scanner_sp, sp<Seg<T>> seg_sp);                           /**/
	static sp<Seg<T>>             ExtractSeg(sp<Scanner<T>> scanner_sp);                                           /**/
	static sp<CompressionPlan<T>> ColAnalyse(sp<Scanner<T>> scanner_sp);                                           /**/
	static Setting<T>             FindBestSetting(sp<pfor::Seg<T>> seg_sp);                                        /**/
	static Setting<T>             FindBestSetting(sp<pfor::Seg<T>> seg_sp, count_t idx);                           /**/
	static count_t CountExc(const T lwr_bnd, const T upr_bnd, const vector<T>& val_vec, const vector<T>& rep_vec); /**/
};
/*---------------------------------------------------------------------------------------------------------------------|
 * Implementation
|---------------------------------------------------------------------------------------------------------------------*/
template <typename T>
bool IsExc(T lower_bound, T upper_bound, T val) {
	FLS_ASSERT(upper_bound > lower_bound, " upperbound is less than lowerbound", " ");

	if (val <= upper_bound && val >= lower_bound) {
		return false;
	}
	return true;
}

template <typename T>
count_t PFor<T>::CountExc(const T               lower_bound,
                          const T               upper_bound,
                          const std::vector<T>& val_vec,
                          const std::vector<T>& rep_vec) {
	FLS_ASSERT(upper_bound > lower_bound, " upperbound is less than lower-bound", " ");
	FLS_ASSERT(!val_vec.empty(), "an empty vec", " ");
	FLS_ASSERT(!rep_vec.empty(), "an empty vec", " ");

	count_t result {0};
	bool    is_exc {false};

	for (count_t i = 0; i < val_vec.size(); ++i) {
		is_exc = IsExc(lower_bound, upper_bound, val_vec[i]);
		if (!is_exc) {
			continue;
		}
		/* It is an exception.
		 * Increase the number of exception by the repetition of this value.
		 */
		result += rep_vec[i];
	}

	return result;
}

template <typename T>
byte_c BulkLoad(count_t remained_c) {
	FLS_ASSERT_CORRECT_SIZE(remained_c)

	byte_c remained_sz {remained_c * sizeof(T)};
	byte_c bulk_size {25 * fast_lanes::Cfg::VECTOR_SIZE * pfor::Cfg::BULK_RATIO * sizeof(T)};
	byte_c size = (remained_sz >= bulk_size) ? bulk_size : remained_sz;

	return size;
}

template <typename T>
Setting<T> PFor<T>::FindBestSetting(sp<Seg<T>> seg_sp, count_t idx) {
	FLS_ASSERT(seg_sp != nullptr, "a nullptr.", " ");
	FLS_ASSERT(idx >= 0, "negative idx.", " ");
	FLS_ASSERT(idx < seg_sp->histogram.val_vec.size(), "idx out of bound.", " ");

	/* Initialize */
	Setting<T> best, next;
	auto&      val_vec     = seg_sp->histogram.val_vec;
	auto&      rep_vec     = seg_sp->histogram.rep_vec;
	const T    lower_bound = val_vec[idx];
	T          upper_bound = lower_bound + Max<1>::VALUE;

	/* best = fist */
	best = {1, lower_bound, CountExc(lower_bound, upper_bound, val_vec, rep_vec)};

	// The rest
	for (count_t i = 2; i < TYPE_BIT<T>::VALUE; ++i) {
		/* Compute the upperbound*/
		upper_bound = SafeUpperBound(lower_bound, i);

		/* Compute the next setting*/
		next = {i, lower_bound, CountExc(lower_bound, upper_bound, val_vec, rep_vec)};

		/* Check to see if there is a better setting. */
		if (next.Size(seg_sp->Count()) < best.Size(seg_sp->Count())) {
			best = next;
		}
	}

	return best;
}

template <typename T>
Setting<T> PFor<T>::FindBestSetting(sp<pfor::Seg<T>> seg_sp) {
	FLS_ASSERT(seg_sp != nullptr, "seg_sp should not be a nullptr!", " ");

	/* Init values.*/
	Setting<T> best, next;
	count_t    base_c = seg_sp->histogram.rep_vec.size();

	best = FindBestSetting(seg_sp, 0);
	for (count_t i = 1; i < base_c; ++i) {
		next = FindBestSetting(seg_sp, i);

		if (next.Size(seg_sp->Count()) < best.Size(seg_sp->Count())) {
			best = next;
		}
	}

	return best;
}

template <typename T>
sp<Seg<T>> PFor<T>::ExtractSeg(sp<Scanner<T>> scanner_sp) {
	FLS_ASSERT_NOT_NULL_POINTER(scanner_sp)
	FLS_ASSERT_NOT_ZERO_SIZE(scanner_sp->remained_c)

	/* Initialize. */
	Setting<T> best_setting;
	auto       seg_sp      = std::make_shared<pfor::Seg<T>>(scanner_sp->col.m_segment_sz);
	seg_sp->fls_hdr.expr_t = exp::Typ::PFOR;
	seg_sp->exp.hdr        = Cfg::EXPR_HDR;

	/* First bulk try. */
	seg_sp->uncompressed_sz = BulkLoad<T>(scanner_sp->remained_c);

	/* Update the segment metadata. */
	seg_sp->histogram.Cal(scanner_sp->GetVec(), scanner_sp->cur_off, seg_sp->Count());
	seg_sp->min_max.Cal(scanner_sp->GetVec(), scanner_sp->cur_off, seg_sp->Count());
	best_setting          = FindBestSetting(seg_sp);
	seg_sp->exp.pyl.bit_c = best_setting.bit_c;
	/*Fixme maybe set  to 0;*/
	memcpy(seg_sp->exp.pyl.base, &best_setting.base, sizeof(T));
	seg_sp->compressed_sz = best_setting.Size(seg_sp->Count());
	seg_sp->exc_c         = best_setting.exc_c;
	scanner_sp->cur_off += seg_sp->Count();
	scanner_sp->remained_c -= seg_sp->Count();

	/* Try to push vectors into the segment as much as possible. */
	while (PFor<T>::TryFill(scanner_sp, seg_sp)) {
		continue;
	}

	/* Find Offsets.*/
	if (seg_sp->Occupancy() < fast_lanes::Cfg::SQUEEZE_RATIO) {
		seg_sp->Squeeze();
	}
	seg_sp->exp.pyl.bitpacked_col = Cfg::START;
	seg_sp->exp.pyl.exception_col = seg_sp->End() - seg_sp->exc_c * sizeof(T);

	return seg_sp;
}

template <typename T>
bool PFor<T>::TryFill(sp<Scanner<T>> scanner_sp, sp<Seg<T>> seg_sp) {
	FLS_ASSERT_CORRECT_SIZE(scanner_sp->remained_c)

	if (scanner_sp->remained_c == 0) {
		return false;
	}

	/* Initialize.*/
	auto    vec_scanner_sp = scanner_sp->GetVecScanner();
	byte_c  new_size {0};
	count_t exc_c {0};
	T       lower_bound;
	memcpy(&lower_bound, seg_sp->exp.pyl.base, sizeof(T));
	T upper_bound = SafeUpperBound(lower_bound, seg_sp->exp.pyl.bit_c);

	/* Calculate new stats. */
	vec_scanner_sp->histogram.Cal(vec_scanner_sp->GetVec(), vec_scanner_sp->cur_off, fast_lanes::Cfg::VECTOR_SIZE);
	vec_scanner_sp->min_max.Cal(vec_scanner_sp->GetVec(), vec_scanner_sp->cur_off, fast_lanes::Cfg::VECTOR_SIZE);
	exc_c = CountExc(lower_bound, upper_bound, vec_scanner_sp->histogram.val_vec, vec_scanner_sp->histogram.rep_vec);
	FLS_ASSERT(exc_c <= fast_lanes::Cfg::VECTOR_SIZE, "A vector cannot have more exceptions than its size.", " ");
	vec_scanner_sp->compressed_sz =
	    byte_c {(fast_lanes::Cfg::VECTOR_SIZE * seg_sp->exp.pyl.bit_c / CHAR_BIT) + (sizeof(T) * exc_c)};
	vec_scanner_sp->uncompressed_sz = byte_c {fast_lanes::Cfg::VECTOR_SIZE * sizeof(T)};

	/* Update stats. */
	new_size = byte_c {vec_scanner_sp->compressed_sz + seg_sp->compressed_sz};

	/* Was not successful. Go to next segment*/
	if (new_size > seg_sp->cap) {
		return false;
	}

	/* Was successful, 1)Absorb the vector, 2)Update the segment. */
	seg_sp->uncompressed_sz = byte_c {seg_sp->uncompressed_sz + vec_scanner_sp->uncompressed_sz};
	seg_sp->compressed_sz   = new_size;
	scanner_sp->cur_off += vec_scanner_sp->Count();
	scanner_sp->remained_c -= vec_scanner_sp->Count();
	seg_sp->min_max.min = std::min(vec_scanner_sp->Min(), seg_sp->Min());
	seg_sp->min_max.max = std::max(vec_scanner_sp->Max(), seg_sp->Max());
	seg_sp->exc_c += exc_c;
	return true;
}

template <typename T>
sp<CompressionPlan<T>> PFor<T>::ColAnalyse(sp<Scanner<T>> scanner_sp) {
	FLS_ASSERT_NOT_ZERO_SIZE(scanner_sp->remained_c)

	/* Initialize. */
	auto compression_plan = std::make_shared<CompressionPlan<T>>();
	/* Analyse. */
	while (!scanner_sp->IsFinished()) {
		compression_plan->AddSeg(PFor<T>::ExtractSeg(scanner_sp));
	}
	/* finalize */
	return compression_plan;
}
}}     // namespace fast_lanes::pfor
#endif // FLS_EXP_PFOR_PFOR_HPP
