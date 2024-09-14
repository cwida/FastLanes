#include "fls/encoder/exp_col_encoder.hpp"
#include "fls/api/engine.hpp"
#include "fls/cor/exp/exp_pool.hpp"
#include "fls/cor/lyt/buf.hpp"
#include "fls/encoder/col_encoder.hpp"
#include "fls/encoder/verifier.hpp"
#include "fls/table/rowgroup.hpp"

namespace fastlanes {

ExpEncodedCol::ExpEncodedCol(Expression new_exp, bsz_t bsz)
    : expression(new_exp)
    , bsz(bsz) {
	data_buf       = std::make_shared<Buf>();
	dictionary_buf = std::make_shared<Buf>();
}

template <typename PT>
AllExpEncodedCol ExpColEncoder<PT>::encode_all(const std::vector<PT>& data_col, const scheme_pool_t& m_scheme_pool) {
	AllExpEncodedCol result;

	result.n_tup = data_col.size();
	for (const auto& exp : m_scheme_pool) {
		auto exp_result = encode(data_col, exp.second);
		result.exp_result_vec.push_back(exp_result);
	}
	return result;
}

template <typename PT>
ExpEncodedCol ExpColEncoder<PT>::encode(vector<PT> data_col, const Expression& exp) {
	return encode_pointer(data_col.data(), data_col.size(), exp);
}

template <typename PT>
ExpEncodedCol ExpColEncoder<PT>::encode_span(span<PT> data_col, const Expression& exp) {
	return encode_pointer(data_col.data(), data_col.size(), exp);
}
template <typename PT>
ExpEncodedCol ExpColEncoder<PT>::encode_pointer(PT* data_p, n_t n_tup, const Expression& exp) {
	TColEncoder<PT> col_encoder {};

	ExpEncodedCol exp_encoded_col {exp, 0};

	col_encoder.Reset();
	col_encoder.ExtInitCompress(exp.exp, exp.var);
	col_encoder.ExtAnalyze(data_p, n_tup);
	col_encoder.ExtCompress(data_p, n_tup / 1024);
	col_encoder.ExtFlush(*exp_encoded_col.data_buf);
	col_encoder.ExtDicFlush(*exp_encoded_col.dictionary_buf);

	if (m_verify) {
		TColDecoder<PT> col_decoder;
		if (exp_encoded_col.dictionary_buf->Size() > 0) {
			col_decoder.ExtInitDict(exp_encoded_col.dictionary_buf->data());
		}
		col_decoder.InitDecompress(exp_encoded_col.data_buf->data());
		Verifier::decode_verify_print_save<PT>(col_decoder, data_p, n_tup / 1024, &assert_eq<PT>, exp.exp);
	}

	exp_encoded_col.bsz = exp_encoded_col.dictionary_buf->Size();

	return exp_encoded_col;
}

template <typename PT>
AllExpEncodedCol ExpColEncoder<PT>::EncodeDict(const std::vector<PT>& vec) {
	return Encode(vec, ExpPool<PT>::get_dict_pool());
}

template <typename PT>
AllExpEncodedCol ExpColEncoder<PT>::EncodeDict(const std::string& csv_file) {
	return Encode(csv_file, ExpPool<PT>::get_dict_pool());
}

template <typename PT>
ExpColEncoder<PT>::ExpColEncoder(const bool verify)
    : m_verify(verify) {};

template <typename PT>
AllExpEncodedCol ExpColEncoder<PT>::Encode(const std::string& csv_file) {
	return Encode(csv_file, ExpPool<PT>::get_pool());
}

template <typename PT>
AllExpEncodedCol ExpColEncoder<PT>::Encode(const std::vector<PT>& data_col, const scheme_pool_t& m_scheme_pool) {
	AllExpEncodedCol result = encode_all(data_col, m_scheme_pool);

	return result;
}

std::ostream& operator<<(std::ostream& stream, const ExpEncodedCol& result) {

	stream << ToStr::to_str(result);

	return stream;
}

ExpEncodedCol::ExpEncodedCol()
    : expression(INVALID_EXPRESSION())
    , bsz(0) {};

std::ostream& operator<<(std::ostream& stream, const AllExpEncodedCol& result) {
	for (const auto& exp_result : result.exp_result_vec) {
		stream << exp_result << "\n";
	}

	return stream;
}

AllExpEncodedCol::AllExpEncodedCol()
    : col_idx {0}
    , n_tup {0} {

      };

const ExpEncodedCol& AllExpEncodedCol::GetBest() const {
	FLS_ASSERT_NOT_EMPTY_VEC(exp_result_vec)

	idx_t best_idx = 0;
	for (idx_t idx {0}; idx < exp_result_vec.size(); ++idx) {
		const auto& cur_exp_res  = exp_result_vec[idx];
		const auto& best_exp_res = exp_result_vec[best_idx];

		if (cur_exp_res.bsz < best_exp_res.bsz) { best_idx = idx; }
	}

	return exp_result_vec[best_idx];
}

AllExpEncodedCol& AllExpEncodedCol::GetAll() {
	auto& best = GetBest();

	exp_result_vec.clear();
	exp_result_vec.push_back(best);

	return *this;
}

template <typename PT>
AllExpEncodedCol ExpColEncoder<PT>::Encode(const std::string& csv_file, const scheme_pool_t& m_scheme_pool) {
	Schema           schema {};
	AllExpEncodedCol result;

	if constexpr (std::is_same_v<PT, str_pt>) {
		ColDescription col_mtd_0 = {0, "col_0", fastlanes::DataType::STR};
		schema.AddCol(col_mtd_0);
	} else if constexpr (std::is_same_v<PT, i64_pt>) {
		ColDescription col_mtd_0 = {0, "col_0", fastlanes::DataType::INT64};
		schema.AddCol(col_mtd_0);
	} else if constexpr (std::is_same_v<PT, dbl_pt>) {
		ColDescription col_mtd_0 = {0, "col_0", fastlanes::DataType::DOUBLE};
		schema.AddCol(col_mtd_0);
	} else {
		FLS_ABORT("NOT IMPLEMENTED!")
	}

	Rowgroup bff_1(schema);
	bff_1.ReadCsv(csv_file);

	auto& data_col = std::get<up<TypedCol<PT>>>(bff_1.internal_rowgroup[0])->data;
	result         = Encode(data_col, m_scheme_pool);

	return result;
}

template <typename PT>
AllExpEncodedCol ExpColEncoder<PT>::Encode(const std::vector<PT>& vec) {
	return Encode(vec, ExpPool<PT>::get_pool());
}

template class ExpColEncoder<i64_pt>;
template class ExpColEncoder<str_pt>;
template class ExpColEncoder<dbl_pt>;

} // namespace fastlanes