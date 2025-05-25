#ifndef FLS_ARCH_HPP
#define FLS_ARCH_HPP

#ifdef DUCKDB_X86_64
#define MULTI_ARCH(...)                                                                                                \
	namespace fallback {                                                                                               \
	__VA_ARGS__                                                                                                        \
	}                                                                                                                  \
	namespace avx2 {                                                                                                   \
	__VA_ARGS__                                                                                                        \
	}                                                                                                                  \
	namespace avx512f {                                                                                                \
	__VA_ARGS__                                                                                                        \
	}
#elif DUCKDB_FALLBACK
#define MULTI_ARCH(...)                                                                                                \
	namespace fallback {                                                                                               \
	__VA_ARGS__                                                                                                        \
	}
#elif DUCKDB_ARM
#define MULTI_ARCH(...)                                                                                                \
	namespace fallback {                                                                                               \
	__VA_ARGS__                                                                                                        \
	}                                                                                                                  \
	namespace arm64 {                                                                                                  \
	__VA_ARGS__                                                                                                        \
	}
#endif

#ifdef IS_AVX2
#define AUTO_SET_ARCH(...)                                                                                             \
	namespace avx2 {                                                                                                   \
	__VA_ARGS__                                                                                                        \
	}
#define GET_NAME "AVX2"
#elif IS_AVX512f
#define AUTO_SET_ARCH(...)                                                                                             \
	namespace avx512f {                                                                                                \
	__VA_ARGS__                                                                                                        \
	}
#define GET_NAME "AVX512f"
#elif IS_arm64
#define AUTO_SET_ARCH(...)                                                                                             \
	namespace arm64 {                                                                                                  \
	__VA_ARGS__                                                                                                        \
	}
#define GET_NAME "ARM64"
#elif IS_FALLBACK
#define AUTO_SET_ARCH(...)                                                                                             \
	namespace fallback {                                                                                               \
	__VA_ARGS__                                                                                                        \
	}
#define GET_NAME "FALLBACK"
#endif

#endif // FLS_ARCH_HPP
