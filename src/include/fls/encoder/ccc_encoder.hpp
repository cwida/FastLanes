#ifndef FLS_ENCODER_CCC_ENCODER_HPP
#define FLS_ENCODER_CCC_ENCODER_HPP

#include "fls/common/common.hpp"
#include "fls/encoder/rowgroup_encoder.hpp"

namespace fastlanes {
/*--------------------------------------------------------------------------------------------------------------------*/
class RowgroupEncoder;
class Schema;
class MultiColEncoder;
/*--------------------------------------------------------------------------------------------------------------------*/
class CCCEncoder {
public:
	CCCEncoder();

public:
	RowgroupEncodingResult Encode(Schema& schema, const std::string& csv_file);

public:
	up<RowgroupEncoder> tab_encoder;
	up<MultiColEncoder> multi_col_encoder;
};

} // namespace fastlanes
#endif // FLS_ENCODER_CCC_ENCODER_HPP
