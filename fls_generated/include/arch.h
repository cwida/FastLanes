#pragma once

#ifdef X86_64
#define MULTI_NAMESPACE(...) \
  namespace scalar {         \
  __VA_ARGS__                \
  }                          \
  namespace avx2 {           \
  __VA_ARGS__                \
  }                          \
  namespace avx512f {        \
  __VA_ARGS__                \
  }
#elif FALLBACK
#define MULTI_NAMESPACE(...) \
  namespace scalar {         \
  __VA_ARGS__                \
  }
#elif ARM
#define MULTI_NAMESPACE(...) \
  namespace scalar {         \
  __VA_ARGS__                \
  }                          \
  namespace arm64 {          \
  __VA_ARGS__                \
  }
#endif

#ifdef IS_AVX2
#define SINGLE_NAMESPACE(...) \
  namespace avx2 {            \
  __VA_ARGS__                 \
  }
#define GET_NAME "AVX2"
#elif IS_AVX512f
#define SINGLE_NAMESPACE(...) \
  namespace avx512f {         \
  __VA_ARGS__                 \
  }
#define GET_NAME "AVX512f"
#elif IS_ARM64
#define SINGLE_NAMESPACE(...) \
  namespace arm64 {           \
  __VA_ARGS__                 \
  }
#define GET_NAME "ARM64"
#elif IS_SCALAR
#define SINGLE_NAMESPACE(...) \
  namespace scalar {          \
  __VA_ARGS__                 \
  }
#define GET_NAME "SCALAR"
#endif
