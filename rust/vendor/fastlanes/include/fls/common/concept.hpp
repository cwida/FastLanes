#ifndef FLS_COMMON_CONCEPT_HPP
#define FLS_COMMON_CONCEPT_HPP

#include <cstddef>
#include <cstdint>
#include <memory>

namespace fastlanes {
template <typename PT1, typename PT2>
concept SAME_SIZE_TYPE = (sizeof(PT1) == sizeof(PT2));

}

#endif // FLS_COMMON_CONCEPT_HPP
