#ifndef FLS_EXP_PFOR_SEG_HPP
#define FLS_EXP_PFOR_SEG_HPP

#include "fls/cor/seg.hpp"
#include "fls/prm/bitpack.hpp"
#include "fls/prm/patch.hpp"
#include "fls/utl/util.hpp"

namespace fast_lanes { namespace pfor {
template <typename T>
class Seg : public fast_lanes::Seg<T> {
public:
	Seg() = delete;                   //
	explicit Seg(count_t segment_sz); //
	virtual ~Seg() = default;         //
public:
	void Compress(std::byte* des, Scanner<T>& scanner) const override; //
	void ToSvg(std::ostream& out) const override;                      //
	void ToRow(std::ostream& out) const override;                      //
	void ToRow(TxtTab& txt_tab) const override;                        //
	void Reset() override;                                             //
public:
	pfor::Exp exp;   //
	count_t   exc_c; //
};
/*---------------------------------------------------------------------------------------------------------------------|
 * Implementation
|---------------------------------------------------------------------------------------------------------------------*/
template <typename T>
Seg<T>::Seg(count_t segment_sz)
    : fast_lanes::Seg<T> {segment_sz}
    , exc_c {0} {}

template <typename T>
void Seg<T>::Compress(std::byte* des, Scanner<T>& scanner) const {
	FLS_ASSERT_NOT_NULL_POINTER(des)

	/* Init. */
	auto offset = des;

	/* Memcpy exp. */
	memcpy(offset, &this->exp, pfor::Cfg::EXP_SZ);
	offset += pfor::Cfg::EXP_SZ;

	/* Compress Real DATA
	 * 1) Init. */
	uint64_t* bitpacked_col = reinterpret_cast<uint64_t*>(offset + exp.pyl.bitpacked_col);
	T*        exception_col = reinterpret_cast<T*>(offset + exp.pyl.exception_col);
	uint64_t  data_arr[fast_lanes::Cfg::VECTOR_SIZE];
	count_t   miss_arr[fast_lanes::Cfg::VECTOR_SIZE];
	T         base;
	memcpy(&base, exp.pyl.base, sizeof(T));
	count_t bit_c      = exp.pyl.bit_c;
	int     last_patch = 0;

	/* 2) Compress. */
	for (count_t vec_c = 0; vec_c < this->VecCount(); ++vec_c) {
		int j    = 0;
		int prev = last_patch;

		/* LOOP1: find exceptions */
		for (count_t i = 0; i < fast_lanes::Cfg::VECTOR_SIZE; i++) {
			uint64_t val = scanner[i] - base;
			data_arr[i]  = val;
			miss_arr[j]  = i;
			j += (val < 0) && (val > SafeUpperBound(base, bit_c));
		}

		/* LOOP2: create patch-list */
		for (int i = 0; i < j; i++) {
			int cur          = miss_arr[i];
			exception_col[i] = scanner[cur];
			data_arr[prev]   = (cur - prev) - 1;
			prev             = cur;
		}

		/* LOOP3: bitpack. */
		bitpack::Compress(data_arr, bitpacked_col, bit_c); /* bit-pack the values */

		/* Finalize. */
		last_patch = prev;
		exception_col += j; /* #exceptions */
	}
}

template <typename T>
void Seg<T>::ToSvg(std::ostream& out) const {
	fast_lanes::Seg<T>::ToSvg(out);
	std::stringstream str_stream;
	/* exp_hdr(green = a0ffa0). */
	/* Exp Hdr.*/
	str_stream << duckdb_fmt::format("(draw-box \"{}\"", exp.hdr.val_o)
	           << "[:box-first {:span 2, :fill \"#a0ffa0\"}])\n"
	           << duckdb_fmt::format("(draw-box \"{}\"", exp.hdr.col_o)
	           << "[:box-related {:span 2, :fill \"#a0ffa0\"}])"
	           << "\n"
	           << duckdb_fmt::format("(draw-box \"{}\" ", exp.hdr.fun_o)
	           << "[:box-related {:span 2, :fill \"#a0ffa0\"}])"
	           << "\n"
	           << duckdb_fmt::format("(draw-box \"{}\" ", exp.hdr.fun_c) << "[:box-last {:span 2, :fill \"#a0ffa0\"}])"
	           << "\n";
	/* Val Arr. */
	str_stream << duckdb_fmt::format("(draw-box \"CONSTANT_VAL: {}\"", exp.pyl.bit_c)
	           << "[:box-first {:span 8, :fill \"#a0ffa0\"}])"
	           << "\n";
	str_stream << duckdb_fmt::format("(draw-box \"CONSTANT_VAL: {}\"", static_cast<uint64_t>(*exp.pyl.base))
	           << "[:box-first {:span 8, :fill \"#a0ffa0\"}])"
	           << "\n";
	/* Col Arr. */
	str_stream << duckdb_fmt::format("(draw-box \"COL_OFFSET: {}\"", 0) << "[:box-first {:span 8, :fill \"#a0ffa0\"}])"
	           << "\n";
	str_stream << duckdb_fmt::format("(draw-box \"COL_OFFSET: {}\"", 1000)
	           << "[:box-first {:span 8, :fill \"#a0ffa0\"}])"
	           << "\n";
	//	/* Fun Arr*/
	//	for (size_t i = 0; i < config::FUN_O; ++i) {
	//		str_stream << duckdb_fmt::format("(draw-box \"FUN_INDEX: {}\"", fun_arr[i]) << "{:span 8, :fill
	//\"#a0ffa0\"})"
	//		           << "\n";
	//	}

	/* Payload(red = ffa0a0). */
	for (count_t i = 0; i < this->VecCount(); ++i) {
		str_stream << duckdb_fmt::format("(draw-box \"vec_{}\"", i) << "{:span 2, :fill \"#ffa0a0\"})"
		           << "\n";
	}
	/* Unused. */
	str_stream << duckdb_fmt::format("(draw-gap \"unused\")") << "\n"
	           << "(draw-bottom)"
	           << "\n";
	/* Statistics(orange = ffd0a0). */
	str_stream << duckdb_fmt::format("(draw-box \"capacity: {}\"", this->cap.Val()) << "{:span 4, :fill \"#ffd0a0\"})"
	           << "\n";
	str_stream << duckdb_fmt::format("(draw-box \"count: {}\"", this->Count()) << "{:span 4, :fill \"#ffd0a0\"})"
	           << "\n";
	str_stream << duckdb_fmt::format("(draw-box \"uncmpr_sz: {}\"", this->uncompressed_sz.Val())
	           << "{:span 4, :fill \"#ffd0a0\"})"
	           << "\n";
	str_stream << duckdb_fmt::format("(draw-box \"cmpr_sz: {}\"", this->compressed_sz.Val())
	           << "{:span 4, :fill \"#ffd0a0\"})"
	           << "\n";
	str_stream << duckdb_fmt::format("(draw-box \"cmpr_ratio: {:.2f}\"", this->Ratio())
	           << "{:span 4, :fill \"#ffd0a0\"})"
	           << "\n";
	str_stream << duckdb_fmt::format("(draw-box \"unused_sz: {}\"", this->UnusedSize())
	           << "{:span 4, :fill \"#ffd0a0\"})"
	           << "\n";
	str_stream << duckdb_fmt::format("(draw-box \"min: {}\"", this->Min()) << "{:span 4, :fill \"#ffd0a0\"})"
	           << "\n";
	str_stream << duckdb_fmt::format("(draw-box \"max: {}\"", this->Max()) << "{:span 4, :fill \"#ffd0a0\"})"
	           << "\n";

	out << str_stream.str();
}

template <typename T>
void Seg<T>::ToRow(std::ostream& out) const {
	// clang-format off
	// fixme: ToRow(TxtTab &txt_tab)
	out << this->cap.Val() <<  ","
	<< this->size.Val() << ","
	<< this->compressed_sz.Val() <<  ","
	<< this->uncompressed_sz.Val() << ","
	<< this->Count() <<  ","
	<< this->Occupancy() <<  ","
	<< this->Ratio() << ","
	<< "{exe_c: " << exc_c << "}" << '\n';
	// clang-format on
}

template <typename T>
void Seg<T>::ToRow(TxtTab& txt_tab) const {
	txt_tab.Add(std::to_string(this->cap.Val()));
	txt_tab.Add(std::to_string(this->size.Val()));
	txt_tab.Add(std::to_string(this->compressed_sz.Val()));
	txt_tab.Add(std::to_string(this->UnusedSize()));
	txt_tab.Add(std::to_string(this->uncompressed_sz.Val()));
	txt_tab.Add(std::to_string(this->Cardinality()));
	txt_tab.Add(std::to_string(this->Count()));
	txt_tab.Add(std::to_string(this->VecCount()));
	txt_tab.Add(std::to_string(this->Min()));
	txt_tab.Add(std::to_string(this->Max()));
	txt_tab.Add(std::to_string(this->Occupancy()));
	txt_tab.Add(std::to_string(this->Ratio()));
	txt_tab.Add("{exc_c: " + std::to_string(exc_c) + "}");
	txt_tab.EndOfRow();
}
template <typename T>
void Seg<T>::Reset() {}
}}     // namespace fast_lanes::pfor
#endif // FLS_EXP_PFOR_SEG_HPP
