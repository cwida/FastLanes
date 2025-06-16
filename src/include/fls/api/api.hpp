#ifndef API_HPP
#define API_HPP

#pragma once
/*========================================================================
  fastlanes :: export.hpp   ──  symbol visibility helpers
  Pull this in from every public header that needs FLS_API.
========================================================================*/

#if defined(FLS_STATIC) // ──— static build, no decorations
#define FLS_API
#define FLS_NO_EXPORT
#elif defined(_WIN32) || defined(_WIN64) // ──— Windows / MSVC / Clang-CL
#ifdef FLS_BUILD_DLL                     // building the DLL itself
#define FLS_API __declspec(dllexport)
#else // using the DLL
#define FLS_API __declspec(dllimport)
#endif
#define FLS_NO_EXPORT // nothing extra for hidden symbols
#else                 // ──— GCC / Clang / AppleClang
#if __GNUC__ >= 4     // visibility only in GCC ≥ 4
#define FLS_API       __attribute__((visibility("default")))
#define FLS_NO_EXPORT __attribute__((visibility("hidden")))
#else
#define FLS_API
#define FLS_NO_EXPORT
#endif
#endif

/* Optional extras that many projects add */
#define FLS_DEPRECATED     [[deprecated]]
#define FLS_DEPRECATED_API FLS_API FLS_DEPRECATED

#endif // API_HPP
