#ifndef FASTLANES_STATIC_TEST_HPP
#define FASTLANES_STATIC_TEST_HPP

#define STATIC_ASSERT(expr)                    static_assert(expr, #expr)
#define STATIC_ASSERT_EQUALS(expected, actual) static_assert(expected == actual, #expected " == " #actual)

#endif // FASTLANES_STATIC_TEST_HPP
