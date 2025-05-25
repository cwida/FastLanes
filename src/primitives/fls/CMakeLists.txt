add_library(fls_manual
        OBJECT
        double_scalar_transpose.cpp
        double_scalar_untranspose.cpp)

set(FASTLANES_OBJECT_FILES
        ${FASTLANES_OBJECT_FILES} $<TARGET_OBJECTS:fls_manual>
        PARENT_SCOPE)

target_link_libraries(fls_manual
        PUBLIC
        FastLanes::headers
)