#include "fls/cor/lyt/page/page.hpp"
#include "fls/cor/eng/hzl_cmp.hpp"
#include "fls/cor/exp/exp.hpp"
#include "fls/cor/exp/rpn.hpp"
#include "fls/cor/lyt/rec_hdr.hpp"
#include "fls/cor/lyt/vec.hpp"
#include "fls/logger/logger.hpp"
#include "fls/utl/to_str.hpp"
#include <memory>

#pragma clang diagnostic ignored "-Wconversion"

namespace fastlanes {
Page::Page()
    : m_ttl_sz {0} {
}

void Page::Reset() {
	for (auto& buf : buf_arr) {
		buf.Reset();
	}
	tup_c    = 0;
	arr_c    = 0;
	m_ttl_sz = 0;
	pg_hdr.Reset();
	ep_arr.Reset();
}

void Page::InitCompress(const sp<Exp>& exp_sp) {
	for (auto& buff : buf_arr) {
		FLS_UNUSED(buff.Rewind(0));
	}
	ep_arr_buf.Rewind(0);

	/* Page hdr.*/
	pg_hdr = exp_sp->page_hdr();

	/* Arr offsets: */
	arr_c = exp_sp->arw_c();
	off_arr.InitCompress(arr_c);

	/* Entry Point: */
	ep_arr.InitCompress(*this);

	/* Current size.*/
	m_ttl_sz = 0;
	m_ttl_sz += CFG::PG::HDR_SZ;
	m_ttl_sz += arr_c * CFG::PG::OFFSET_SZ;

	/* Add rec buff hdrs*/
	auto* rpn = exp_sp->cmpr_rpn();
	for (n_t i {0}; i < rpn->des_buf_c; ++i) {
		if (!rpn->is_compressed[i]) {
			continue;
		}

		m_ttl_sz += sizeof(rec_hdr);
	}

	/* Start pointer*/
	start_p = nullptr;

	FLS_PLOG_KEY_VALUE("initial_sz", std::to_string(m_ttl_sz))
}

void Page::InitDecompress(const uint8_t* p, const sp<Exp>& exp_up) {
	FLS_ASSERT_NOT_NULL_POINTER(p)

	/* Start pointer*/
	start_p = const_cast<uint8_t*>(p);

	/* Page hdr.*/
	pg_hdr.Load(p);

	/* Arr offsets: */
	arr_c = exp_up->arw_c();
	off_arr.InitDecompress(*this);

	/* Init Params: */
	params.Init(*this);

	/* Init EP: */
	ep_arr.InitDecompress(*this);

	tup_c = 0;

	FLS_PLOG_KEY_VALUE("pg", ToStr::to_str(*this));
}

PageHdr Page::hdr() {
	return pg_hdr;
}

void Page::Absorb(Vec& vec) {
	if (vec_c() >= 1) {
		ep_arr_buf.UnsafeAppend(ep_arr.arr, ep_arr.sz());
		m_ttl_sz += ep_arr.sz();
	}

	n_t vec_ttl_sz {0};
	for (size_t i {0}; i < arr_c; ++i) {
		auto added_sz = vec.buf_arr[i].length();
		buf_arr[i].UnsafeAppend(vec.buf_arr[i].data(), added_sz);
		ep_arr.arr[i] = ep_arr.arr[i] + added_sz;
		vec_ttl_sz += added_sz;
	}

	m_ttl_sz += vec_ttl_sz;
	pg_hdr.vec_c++;

	FLS_PLOG_KEY_VALUE("ep", ToStr::to_str(ep_arr))
	FLS_PLOG_KEY_VALUE("ep_arr",
	                   ToStr::to_str<uint32_t>(reinterpret_cast<uint32_t*>(ep_arr_buf.mutable_data()), pg_hdr.vec_c))
	FLS_PLOG_KEY_VALUE("ttl_sz", std::to_string(m_ttl_sz));
	FLS_PLOG_KEY_VALUE("vec_ttl_sz", std::to_string(vec_ttl_sz));
	FLS_PLOG_KEY_VALUE("vec_c", std::to_string(vec_c()));

	vec.Reset();
}

void Page::vec_c_inc() {
	pg_hdr.vec_c++;
}

uint16_t Page::vec_c() {
	return pg_hdr.vec_c;
}

void Page::OffsetToSink(Buf& sink) {
	/* First one
	 * Rest follow each other.*/
	off_arr.arr[0] = CFG::PG::HDR_SZ + off_arr.ttl_sz() + ep_arr_buf.length();
	for (size_t i {1}; i < arr_c; ++i) {
		off_arr.arr[i] = off_arr.arr[i - 1] + buf_arr[i - 1].length();
	}

	sink.UnsafeAppend(off_arr.arr, off_arr.ttl_sz());
	FLS_PLOG_KEY_VALUE("OFF_arr", ToStr::to_str(off_arr))
}

PageParam Page::page_params() {
	PageParam res;
	ep_arr.load_and_next();
	for (size_t i {0}; i < arr_c; ++i) {
		res.arr[i] = params.arr[i] + ep_arr.arr[i];
	}

	return res;
}

n_t Page::size_of(Vec& vec) {
	n_t vec_ttl_sz {0};

	if (vec_c() >= 1) {
		vec_ttl_sz = ep_arr.sz();
	}

	for (size_t i {0}; i < arr_c; ++i) {
		auto added_sz = vec.buf_arr[i].length();
		vec_ttl_sz += added_sz;
	}

	return vec_ttl_sz;
}

n_t Page::get_total_sz() {
	n_t ttl_sz {0};
	for (auto& buf : buf_arr) {
		ttl_sz += buf.length();
	}

	return ttl_sz;
}

bool Page::Verify() {
	auto ttl_sz = get_total_sz();
	return ttl_sz <= CFG::PG::SZ;
}

Page::~Page() = default;
} // namespace fastlanes