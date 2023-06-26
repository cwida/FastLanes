#include <cstdint>

namespace defs{

#if HASH_SIZE == 32
  using hash_t = uint32_t;
#else
  using hash_t = uint64_t;
#endif

};
