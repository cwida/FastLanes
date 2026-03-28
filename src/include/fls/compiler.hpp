// ────────────────────────────────────────────────────────
// |                      FastLanes                       |
// ────────────────────────────────────────────────────────
// src/include/fls/compiler.hpp
// ────────────────────────────────────────────────────────
// Compiler-portability macros for Clang, GCC, and MSVC.
// ────────────────────────────────────────────────────────
#ifndef FLS_COMPILER_HPP
#define FLS_COMPILER_HPP

#include <cstdint>

// ── Vectorize-loop pragmas ──────────────────────────────
// Clang's auto-vectorizer hint. MSVC has no direct equivalent;
// its auto-vectorizer runs unconditionally at /O2.
#if defined(__clang__)
#define FLS_PRAGMA_VECTORIZE _Pragma("clang loop vectorize(enable)")
#else
#define FLS_PRAGMA_VECTORIZE
#endif

// Clang vectorize-width hint (e.g. FLS_PRAGMA_VECTORIZE_WIDTH(64)).
#if defined(__clang__)
#define FLS_PRAGMA_VECTORIZE_WIDTH_IMPL(s) _Pragma(#s)
#define FLS_PRAGMA_VECTORIZE_WIDTH(n)      FLS_PRAGMA_VECTORIZE_WIDTH_IMPL(clang loop vectorize_width(n))
#else
#define FLS_PRAGMA_VECTORIZE_WIDTH(n)
#endif

// ── MSVC compat for __restrict__ and __builtin_ctzl ─────
#if defined(_MSC_VER) && !defined(__clang__)
#include <intrin.h>
// MSVC strips __restrict/__restrict__ from the mangling of explicit template
// instantiations but keeps them in call-site references, causing LNK2019.
// Define both to nothing so mangling is consistent.
#define __restrict
#define __restrict__
#ifndef __BYTE_ORDER__
#define __BYTE_ORDER__          __ORDER_LITTLE_ENDIAN__
#define __ORDER_LITTLE_ENDIAN__ 2
#endif
static __forceinline int __builtin_ctzl(unsigned long long x) {
	unsigned long ret;
	_BitScanForward64(&ret, x);
	return (int)ret;
}
#elif defined(_MSC_VER) && defined(__clang__)
#include <intrin.h>
#endif

// ── Count Leading Zeros ─────────────────────────────────
#if defined(_MSC_VER)
static inline int fls_clzll(uint64_t x) {
	unsigned long idx;
	_BitScanReverse64(&idx, x);
	return 63 - static_cast<int>(idx);
}
static inline int fls_clz(uint32_t x) {
	unsigned long idx;
	_BitScanReverse(&idx, x);
	return 31 - static_cast<int>(idx);
}
#else
static inline int fls_clzll(uint64_t x) {
	return __builtin_clzll(x);
}
static inline int fls_clz(uint32_t x) {
	return __builtin_clz(x);
}
#endif

// ── Diagnostic push / pop / ignore ──────────────────────
// Check __clang__ before _MSC_VER because clang-cl defines both,
// but uses clang-style diagnostics, not MSVC warning numbers.
#if defined(__clang__)
#define FLS_DIAG_PUSH                  _Pragma("clang diagnostic push")
#define FLS_DIAG_POP                   _Pragma("clang diagnostic pop")
#define FLS_DIAG_IGNORE_SIGN_CONV      _Pragma("clang diagnostic ignored \"-Wsign-conversion\"")
#define FLS_DIAG_IGNORE_FLOAT_CONV     _Pragma("clang diagnostic ignored \"-Wfloat-conversion\"")
#define FLS_DIAG_IGNORE_CONVERSION     _Pragma("clang diagnostic ignored \"-Wconversion\"")
#define FLS_DIAG_IGNORE_SHORTEN_64_32  _Pragma("clang diagnostic ignored \"-Wshorten-64-to-32\"")
#define FLS_DIAG_IGNORE_INT_FLOAT_CONV _Pragma("clang diagnostic ignored \"-Wimplicit-int-float-conversion\"")
#define FLS_DIAG_IGNORE_INT_CONV       _Pragma("clang diagnostic ignored \"-Wimplicit-int-conversion\"")
#elif defined(_MSC_VER)
#define FLS_DIAG_PUSH              __pragma(warning(push))
#define FLS_DIAG_POP               __pragma(warning(pop))
#define FLS_DIAG_IGNORE_SIGN_CONV  __pragma(warning(disable : 4245 4365))
#define FLS_DIAG_IGNORE_FLOAT_CONV __pragma(warning(disable : 4244))
#define FLS_DIAG_IGNORE_CONVERSION __pragma(warning(disable : 4244 4267))
#define FLS_DIAG_IGNORE_SHORTEN_64_32
#define FLS_DIAG_IGNORE_INT_FLOAT_CONV __pragma(warning(disable : 4244))
#define FLS_DIAG_IGNORE_INT_CONV       __pragma(warning(disable : 4244 4267))
#elif defined(__GNUC__)
#define FLS_DIAG_PUSH              _Pragma("GCC diagnostic push")
#define FLS_DIAG_POP               _Pragma("GCC diagnostic pop")
#define FLS_DIAG_IGNORE_SIGN_CONV  _Pragma("GCC diagnostic ignored \"-Wsign-conversion\"")
#define FLS_DIAG_IGNORE_FLOAT_CONV _Pragma("GCC diagnostic ignored \"-Wfloat-conversion\"")
#define FLS_DIAG_IGNORE_CONVERSION _Pragma("GCC diagnostic ignored \"-Wconversion\"")
#define FLS_DIAG_IGNORE_SHORTEN_64_32
#define FLS_DIAG_IGNORE_INT_FLOAT_CONV _Pragma("GCC diagnostic ignored \"-Wimplicit-int-float-conversion\"")
#define FLS_DIAG_IGNORE_INT_CONV       _Pragma("GCC diagnostic ignored \"-Wimplicit-int-conversion\"")
#endif

#endif // FLS_COMPILER_HPP
