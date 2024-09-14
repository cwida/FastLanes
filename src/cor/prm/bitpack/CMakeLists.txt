add_library(fls_bitpack
            OBJECT
            bitpack_decompress.cpp
            bitpack_compress.cpp)

target_compile_definitions(fls_bitpack PRIVATE IS_SCALAR)
target_compile_options(fls_bitpack PRIVATE "")
if (ENABLE_IWYU)
    set_target_properties(fls_bitpack PROPERTIES CXX_INCLUDE_WHAT_YOU_USE ${iwyu_path})
endif ()
set_target_properties(fls_bitpack PROPERTIES CXX_CLANG_TIDY "")

set(FASTLANES_OBJECT_FILES
        ${FASTLANES_OBJECT_FILES} $<TARGET_OBJECTS:fls_bitpack>
        PARENT_SCOPE)