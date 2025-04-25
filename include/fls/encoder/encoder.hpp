#ifndef FLS_ENCODER_ENCODER_HPP
#define FLS_ENCODER_ENCODER_HPP

namespace fastlanes {
/*--------------------------------------------------------------------------------------------------------------------*/
class Connection;
class Buf;
/*--------------------------------------------------------------------------------------------------------------------*/

class Encoder {
public:
	static void encode(const Connection& fls, Buf& buf);
};
} // namespace fastlanes

#endif // FLS_ENCODER_ENCODER_HPP
