#ifndef FLS_NEW_ENCODER_NEW_ENCODER_HPP
#define FLS_NEW_ENCODER_NEW_ENCODER_HPP

namespace fastlanes {
/*--------------------------------------------------------------------------------------------------------------------*/
class Connection;
class Buf;
/*--------------------------------------------------------------------------------------------------------------------*/

class NewEncoder {
public:
	static void encode(const Connection& fls, Buf& buf);
};
} // namespace fastlanes

#endif // FLS_NEW_ENCODER_NEW_ENCODER_HPP
