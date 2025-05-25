#ifndef FLS_BASES_HPP
#define FLS_BASES_HPP

namespace fastlanes {
class uncopyable {
public:
	uncopyable(const uncopyable& other)            = delete; // disable copy constructor
	uncopyable& operator=(const uncopyable& other) = delete; // disable assignment operator
};
} // namespace fastlanes

#endif // FLS_BASES_HPP
