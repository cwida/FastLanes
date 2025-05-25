add_library(fls_detail
        OBJECT
        #[[]]
        parse_fp.cpp
)

set(FASTLANES_OBJECT_FILES
        ${FASTLANES_OBJECT_FILES} $<TARGET_OBJECTS:fls_detail>
        PARENT_SCOPE)

if (FLS_ENABLE_IWYU)
    set_property(TARGET fls_detail PROPERTY CXX_INCLUDE_WHAT_YOU_USE ${iwyu_path})
endif ()

target_compile_options(fls_detail PRIVATE -Wno-macro-redefined)

target_link_libraries(fls_detail
        PUBLIC
        FastLanes::headers
)