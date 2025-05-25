add_subdirectory(bitpack)
add_subdirectory(copy)
add_subdirectory(fls_memset)
add_subdirectory(fsst)
add_subdirectory(fsst12)
add_subdirectory(predicate)
add_subdirectory(rle)
add_subdirectory(unffor)
add_subdirectory(untraspose)


add_library(fls_primitive
        OBJECT
        #
        primitive.cpp
)

set(FASTLANES_OBJECT_FILES
        ${FASTLANES_OBJECT_FILES} $<TARGET_OBJECTS:fls_primitive>
        PARENT_SCOPE)

if (FLS_ENABLE_IWYU)
    set_property(TARGET fls_primitive PROPERTY CXX_INCLUDE_WHAT_YOU_USE ${iwyu_path})
endif ()

target_link_libraries(fls_primitive
        PUBLIC
        FastLanes::headers
)