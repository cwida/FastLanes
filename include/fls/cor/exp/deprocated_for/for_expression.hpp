#ifndef FASTLANES_FRAME_OF_REFERENCE_HPP
#define FASTLANES_FRAME_OF_REFERENCE_HPP

#include "fast_lanes/expression/expressions.hpp"
#include "fast_lanes/main/hdr.hpp"
#include "fast_lanes/main/scanner.hpp"
#include "fast_lanes/primitive/for.hpp"

namespace fast_lanes { namespace for_ {
constexpr uint8_t VERSION = 1;
template <typename T, typename R_EXPR, typename L_EXPR>
class Expr {
public:
	/* For Expression class */
	Expr(R_EXPR& r_expr, L_EXPR& l_expr);           /* When des is __NOT__ provided. */
	Expr(T* des_p, R_EXPR& r_expr, L_EXPR& l_expr); /* */
	virtual ~Expr();
	T* operator()();

private:
	bool   m_is_owner;
	T*     m_des_p;
	R_EXPR m_r_expr;
	L_EXPR m_l_expr;
};

template <typename T>
class Expr<T*, T*, T*> {
public:
	/* Partial FORExpr Specialization. */
	Expr(T* data_p, T* reference_p);           /* When des is __NOT__ provided. */
	Expr(T* des_p, T* data_p, T* reference_p); /* When des is provided. */
	T* operator()();                           /* Callable*/

private:
	bool m_is_owner;
	T*   m_des_p;
	T*   m_data_p;
	T*   m_reference_p;
};

//! 64-bit Header
class Header {
public:
	uint8_t     version;   //! For expression version.
	uint8_t     bit_c;     //! Number of bits used to bitpack the current segment.
	uint16_t    empty_1;   //! Empty spot
	uint32_t    empty_2;   //! Empty spot
	uint64_t    reference; //! Reference
	std::string ToString();
};
static_assert(std::is_pod<Header>());

template <typename T>
class SegMD : public BaseSegMD<T> {
public:
	SegMD() = delete;
	explicit SegMD(const size_t segment_sz)
	    : BaseSegMD<T> {segment_sz}
	    , header {VERSION, 0, 0, 0, 0} {};
	virtual ~SegMD() {}

public:
	void  ToSvg(std::ostream& out) const override;
	void* GetHeader() override { return &header; }

public:
	Header header;
};

template <typename T>
class Helper {
public:
	static bool                   TryFill(sp<VecScanner<T>> vec_scanner_sp, sp<SegMD<T>> segment_sp);
	static sp<SegMD<T>>           ExtractSeg(sp<ColScanner<T>> scanner_sp);
	static up<CompressionPlan<T>> ColAnalyse(sp<ColScanner<T>> scanner_sp);
	static void                   Compress(T* des, sp<BaseSegMD<T>> segment_s);
	static void                   LOAD() {};
};
/*---------------------------------------------------------------------------------------------------------------------|
|                                                    Implementation                                                    |
|---------------------------------------------------------------------------------------------------------------------*/
template <typename T, typename R_EXPR, typename L_EXPR>
Expr<T, R_EXPR, L_EXPR>::Expr(R_EXPR& r_expr, L_EXPR& l_expr)
    : m_is_owner {false}
    , m_r_expr {r_expr}
    , m_l_expr {l_expr} {
	m_is_owner = true;
	m_des_p    = new T[constant::VECTOR_SIZE];
}

template <typename T, typename R_EXPR, typename L_EXPR>
T* Expr<T, R_EXPR, L_EXPR>::operator()() {
	FOR(m_des_p, m_r_expr(), m_l_expr());
	return m_des_p;
};

template <typename T, typename R_EXPR, typename L_EXPR>
Expr<T, R_EXPR, L_EXPR>::~Expr() {
	if (m_is_owner) { delete[] m_des_p; }
}

template <typename T, typename R_EXPR, typename L_EXPR>
Expr<T, R_EXPR, L_EXPR>::Expr(T* des_p, R_EXPR& r_expr, L_EXPR& l_expr)
    : m_is_owner {false}
    , m_des_p {des_p}
    , m_r_expr {r_expr}
    , m_l_expr {l_expr} {};

template <typename T>
Expr<T*, T*, T*>::Expr(T* data_p, T* reference_p)
    : m_data_p {data_p}
    , m_reference_p {reference_p} {
	m_is_owner = true;
	m_des_p    = new T[constant::VECTOR_SIZE];
}
template <typename T>
Expr<T*, T*, T*>::Expr(T* des_p, T* data_p, T* reference_p)
    : m_is_owner {false}
    , m_des_p {des_p}
    , m_data_p {data_p}
    , m_reference_p {reference_p} {};

template <typename T>
T* Expr<T*, T*, T*>::operator()() {
	FOR(m_des_p, m_data_p, m_reference_p);
	return m_des_p;
}

template <typename T>
void SegMD<T>::ToSvg(std::ostream& out) const {
	BaseSegMD<T>::ToSvg(out);

	std::stringstream str_stream;

	/* header(green = a0ffa0). */
	/* Fast Lane header.*/
	str_stream << duckdb_fmt::format("(draw-box \"{}\"", header.version) << "[:box-first {:span 1, :fill \"#a0ffa0\"}])"
	           << "\n";
	str_stream << duckdb_fmt::format("(draw-box \"{}\"", header.bit_c) << "[:box-related {:span 1, :fill \"#a0ffa0\"}])"
	           << "\n";
	str_stream << duckdb_fmt::format("(draw-box \"{}\" ", header.empty_1 + header.empty_2)
	           << "[:box-last {:span 6, :fill \"#a0ffa0\"}])"
	           << "\n";
	str_stream << duckdb_fmt::format("(draw-box \"{}\" ", header.reference)
	           << "[:box-last {:span 8, :fill \"#a0ffa0\"}])"
	           << "\n";

	/* Payload(red = ffa0a0). */
	for (size_t i = 0; i < this->vector_c; ++i) {
		str_stream << duckdb_fmt::format("(draw-box \"vec_{}\"", i) << "{:span 2, :fill \"#ffa0a0\"})"
		           << "\n";
	}
	/* Unused. */
	str_stream << duckdb_fmt::format("(draw-gap \"unused\")") << "\n"
	           << "(draw-bottom)"
	           << "\n";

	/* Statistics(orange = ffd0a0). */
	str_stream << duckdb_fmt::format("(draw-box \"segment_sz: {}\"", this->segment_sz)
	           << "{:span 4, :fill \"#ffd0a0\"})"
	           << "\n";
	str_stream << duckdb_fmt::format("(draw-box \"count: {}\"", this->Count()) << "{:span 4, :fill \"#ffd0a0\"})"
	           << "\n";
	str_stream << duckdb_fmt::format("(draw-box \"uncmpr_sz: {}\"", this->uncompressed_sz)
	           << "{:span 4, :fill \"#ffd0a0\"})"
	           << "\n";
	str_stream << duckdb_fmt::format("(draw-box \"cmpr_sz: {}\"", this->compressed_sz)
	           << "{:span 4, :fill \"#ffd0a0\"})"
	           << "\n";
	str_stream << duckdb_fmt::format("(draw-box \"cmpr_ratio: {:.2f}\"", this->Ratio())
	           << "{:span 4, :fill \"#ffd0a0\"})"
	           << "\n";
	str_stream << duckdb_fmt::format("(draw-box \"unused_sz: {}\"", this->UnusedSize())
	           << "{:span 4, :fill \"#ffd0a0\"})"
	           << "\n";
	str_stream << duckdb_fmt::format("(draw-box \"min: {}\"", this->min) << "{:span 4, :fill \"#ffd0a0\"})"
	           << "\n";
	str_stream << duckdb_fmt::format("(draw-box \"max: {}\"", this->max) << "{:span 4, :fill \"#ffd0a0\"})"
	           << "\n";

	out << str_stream.str();
}

template <typename T>
bool Helper<T>::TryFill(sp<VecScanner<T>> vec_scanner_sp, sp<SegMD<T>> segment_sp) {
	if (vec_scanner_sp->offset >= vec_scanner_sp->col.Count()) { return false; }
	/* Initialize.*/
	size_t   new_size {0};
	size_t   new_bit_c {0};
	uint64_t new_reference {0};

	/* Do we have enough data for a full vector?*/
	vec_scanner_sp->uncompressed_sz = (vec_scanner_sp->col_scanner.remained_size >= constant::VECTOR_SIZE * sizeof(T))
	                                      ? constant::VECTOR_SIZE * sizeof(T)
	                                      : vec_scanner_sp->col_scanner.remained_size;

	/* Calculate new stats. */
	for (size_t i = vec_scanner_sp->offset; i < vec_scanner_sp->offset + constant::VECTOR_SIZE; ++i) {
		vec_scanner_sp->min = std::min(vec_scanner_sp->min, (*vec_scanner_sp)[i]);
		vec_scanner_sp->max = std::max(vec_scanner_sp->max, (*vec_scanner_sp)[i]);
	}
	new_bit_c = log2(vec_scanner_sp->max - vec_scanner_sp->min) + 1;

	/* Update stats. */
	new_reference                 = std::min(static_cast<uint64_t>(vec_scanner_sp->min), segment_sp->header.reference);
	new_bit_c                     = (new_bit_c > segment_sp->header.bit_c) ? new_bit_c : segment_sp->header.bit_c;
	vec_scanner_sp->compressed_sz = new_bit_c * constant::VECTOR_SIZE / sizeof(T);
	new_size                      = (new_bit_c * segment_sp->Count() / sizeof(T)) + vec_scanner_sp->compressed_sz;

	/* Was not successful. Go to next segment*/
	if (new_size > segment_sp->segment_sz) { return false; }

	/* Update the segment. */
	segment_sp->header.bit_c     = static_cast<uint8_t>(new_bit_c);
	segment_sp->header.reference = new_reference;
	segment_sp->uncompressed_sz += vec_scanner_sp->uncompressed_sz;
	segment_sp->compressed_sz = new_size;
	// fixme
	vec_scanner_sp->col_scanner.offset += 1024;
	++segment_sp->vector_c;
	segment_sp->min = std::min(vec_scanner_sp->min, segment_sp->min);
	segment_sp->max = std::max(vec_scanner_sp->max, segment_sp->max);

	return true;
}

template <typename T>
sp<SegMD<T>> Helper<T>::ExtractSeg(sp<ColScanner<T>> scanner_sp) {
	/* Initialize. */
	auto segment_sp            = std::make_shared<SegMD<T>>(scanner_sp->segment_sz);
	segment_sp->fls_hdr.expr_t = ExpressionType::FASTLANES_FOR;
	bool was_successful        = false;

	/* First bulk try. */
	/* Do we have enough data for full segment? */
	segment_sp->uncompressed_sz =
	    (scanner_sp->remained_size >= scanner_sp->segment_sz) ? scanner_sp->segment_sz : scanner_sp->remained_size;

	/* Treat the uncompressed size as non-divisible unit consist of constant::VECTOR_SIZE tuples. */
	segment_sp->vector_c        = (segment_sp->uncompressed_sz / sizeof(T)) / constant::VECTOR_SIZE;
	segment_sp->uncompressed_sz = segment_sp->vector_c * sizeof(T) * constant::VECTOR_SIZE;

	/* Update the segment. */
	for (size_t i = scanner_sp->offset; i < scanner_sp->offset + segment_sp->Count(); ++i) {
		segment_sp->min = std::min(segment_sp->min, (*scanner_sp)[i]);
		segment_sp->max = std::max(segment_sp->max, (*scanner_sp)[i]);
	}
	segment_sp->header.bit_c     = static_cast<uint8_t>(log2(segment_sp->max - segment_sp->min)) + 1;
	segment_sp->header.reference = static_cast<uint64_t>(segment_sp->min);
	segment_sp->compressed_sz    = segment_sp->uncompressed_sz * segment_sp->header.bit_c / bit_size_of<T>();
	scanner_sp->offset += segment_sp->Count();

	/* Try to push vectors into the segment as much as possible. */
	auto vec_scanner_sp = scanner_sp->GetVecTraverser();
	while (true) {
		was_successful = Helper<T>::TryFill(vec_scanner_sp, segment_sp);
		if (!was_successful) { break; }
		vec_scanner_sp->Reset();
	}

	scanner_sp->remained_size -= segment_sp->uncompressed_sz;
	return segment_sp;
}
template <typename T>
void Helper<T>::Compress(T* des, sp<BaseSegMD<T>> segment_sp) {
	duckdb_fmt::print(std::cerr, "{}:{}__{} Executed!\n", __FILE__, __LINE__, __func__);
	std::memcpy(des, &segment_sp->fls_hdr, sizeof(fast_lanes::Header));
	// fixme

	std::memcpy(des + 1, segment_sp->GetHeader(), sizeof(for_::Header));
}

template <typename T>
std::unique_ptr<CompressionPlan<T>> Helper<T>::ColAnalyse(sp<ColScanner<T>> scanner_sp) {
	/* Initialize. */
	auto compression_plan     = std::make_unique<CompressionPlan<T>>();
	scanner_sp->remained_size = scanner_sp->col.Size();

	/* Analyse. */
	while (scanner_sp->remained_size > 0) {
		compression_plan->Push(Helper<T>::ExtractSeg(scanner_sp));
	}

	/* Debug. */
	//	duckdb_fmt::print(std::clog, "{}:{}__{} executed!\n", __FILE__, __LINE__, __func__);

	/* finalize */
	compression_plan->uncompressed_sz = scanner_sp->col.Size();

	return std::move(compression_plan);
}

std::string Header::ToString() {
	return duckdb_fmt::format("Version: {}\n"
	                          "Bit_c: {}\n"
	                          "Empty_1: {}\n"
	                          "Empty_2: {}\n"
	                          "Reference: {}",
	                          version,
	                          bit_c,
	                          empty_1,
	                          empty_2,
	                          reference);
}
}}     // namespace fast_lanes::for_
#endif // FASTLANES_FRAME_OF_REFERENCE_HPP
