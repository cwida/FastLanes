#ifndef FLS_UTL_MATH_HPP
#define FLS_UTL_MATH_HPP

namespace fastlanes {

class Math {
public:
	template <typename T>
	static T UnsignedSubtract(T a, T b) {
		return a < b ? 0 : a - b;
	}

	template <typename T>
	static T AbsSubtract(T a, T b) {
		return a < b ? b - a : a - b;
	}
};

} // namespace fastlanes

#endif