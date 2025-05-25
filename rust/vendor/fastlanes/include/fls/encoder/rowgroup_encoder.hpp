#ifndef FLS_ENCODER_ROWGROUP_ENCODER_HPP
#define FLS_ENCODER_ROWGROUP_ENCODER_HPP

#include "fls/common/alias.hpp"             // for up
#include "fls/encoder/exp_col_encoder.hpp"  // for AllExpEncodedCol, ExpColE...
#include "fls/expression/data_type.hpp"     // for dbl_pt, i64_pt, str_pt
#include "fls/footer/column_descriptor.hpp" // for ColDescription (ptr only)
#include "fls/std/vector.hpp"               // for vector
#include "fls/table/rowgroup.hpp"           // for Rowgroup (ptr only), col_pt

namespace fastlanes {
/*--------------------------------------------------------------------------------------------------------------------*/
class Connection;
class Footer;
/*--------------------------------------------------------------------------------------------------------------------*/

class RowgroupEncodingResult {
public:
	RowgroupEncodingResult() = default;

public:
	vector<AllExpEncodedCol> col_result_vec;
};

constexpr bool WITHOUT_VERIFICATION = false;
constexpr bool WITH_VERIFICATION    = true;
constexpr bool PERMANENT            = true;
constexpr bool TEMPORARY            = false;

class RowgroupEncoder {
public:
	explicit RowgroupEncoder(bool save);

public:
	///! Encode
	void Encode(Connection& fls) const;

private:
	///!
	[[nodiscard]] RowgroupEncodingResult encode(const rowgroup_pt& table, const ColumnDescriptors& descriptions) const;
	///!
	[[nodiscard]] RowgroupEncodingResult encode(const Rowgroup& rowgroup, const Footer& footer) const;
	///!
	[[nodiscard]] AllExpEncodedCol encode_all(const col_pt& fff, const ColumnDescriptor& col_descriptor) const;

public:
	up<ExpColEncoder<i64_pt>> i64_tester_up;
	up<ExpColEncoder<str_pt>> str_tester_up;
	up<ExpColEncoder<dbl_pt>> dbl_tester_up;

private:
	const bool m_verify;
};

} // namespace fastlanes
#endif // FLS_ENCODER_ROWGROUP_ENCODER_HPP
