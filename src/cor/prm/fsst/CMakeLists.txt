add_library(fls_fsst_prm
        OBJECT
        fsst_prm.cpp
        libfsst.cpp
        fsst_avx512.cpp)

target_compile_definitions(fls_fsst_prm PRIVATE IS_SCALAR)
target_compile_options(fls_fsst_prm PRIVATE "")
if (ENABLE_IWYU)
    set_target_properties(fls_fsst_prm PROPERTIES CXX_INCLUDE_WHAT_YOU_USE ${iwyu_path})
endif ()
set_target_properties(fls_fsst_prm PROPERTIES CXX_CLANG_TIDY "")

set(FASTLANES_OBJECT_FILES
        ${FASTLANES_OBJECT_FILES} $<TARGET_OBJECTS:fls_fsst_prm>
        PARENT_SCOPE)


target_compile_options(fls_fsst_prm PRIVATE -Wno-macro-redefined)
