#ifndef FLS_ENCODER_EXP_COL_ENCODER_HPP
#define FLS_ENCODER_EXP_COL_ENCODER_HPP

#include "fls/cor/exp/exp_pool.hpp"
#include "fls/std/span.hpp"
#include "fls/std/vector.hpp"

namespace fastlanes {

class Buf;

class ExpEncodedCol {
public:
	ExpEncodedCol();
	ExpEncodedCol(Expression new_exp, bsz_t bsz);

public:
	friend std::ostream& operator<<(std::ostream& stream, const ExpEncodedCol& result);

public:
	Expression expression;
	bsz_t      bsz;
	sp<Buf>    data_buf;
	sp<Buf>    dictionary_buf;
};

class AllExpEncodedCol {
public:
	AllExpEncodedCol();

public:
	///!
	friend std::ostream& operator<<(std::ostream& stream, const AllExpEncodedCol& result);
	///!
	[[nodiscard]] const ExpEncodedCol& GetBest() const;
	///!
	AllExpEncodedCol& GetAll();

public:
	vector<ExpEncodedCol> exp_result_vec;
	n_t                   col_idx;
	n_t                   n_tup;
};

template <typename PT>
class ExpColEncoder {
public:
	explicit ExpColEncoder(bool verify);

public:
	AllExpEncodedCol Encode(const std::string& csv_file, const scheme_pool_t& m_scheme_pool);
	AllExpEncodedCol Encode(const std::vector<PT>& vec, const scheme_pool_t& m_scheme_pool);
	AllExpEncodedCol EncodeDict(const std::string& csv_file);
	AllExpEncodedCol EncodeDict(const std::vector<PT>& vec);
	AllExpEncodedCol Encode(const std::string& csv_file);
	AllExpEncodedCol Encode(const std::vector<PT>& vec);
	ExpEncodedCol    encode(vector<PT> data_col, const Expression& exp);
	ExpEncodedCol    encode_span(span<PT> data_col, const Expression& exp);
	ExpEncodedCol    encode_pointer(PT* data_p, n_t n_tup, const Expression& exp);

private:
	AllExpEncodedCol encode_all(const std::vector<PT>& data_col, const scheme_pool_t& m_scheme_pool);

private:
	const bool m_verify;
};

} // namespace fastlanes
#endif // FLS_ENCODER_EXP_COL_ENCODER_HPP
