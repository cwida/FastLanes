add_library(fls_encoder
        OBJECT
        #[[]]
        materializer.cpp
        encoder.cpp
)

set(FASTLANES_OBJECT_FILES
        ${FASTLANES_OBJECT_FILES} $<TARGET_OBJECTS:fls_encoder>
        PARENT_SCOPE)

if (FLS_ENABLE_IWYU)
    set_property(TARGET fls_encoder PROPERTY CXX_INCLUDE_WHAT_YOU_USE ${iwyu_path})
endif ()

if ("${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang")
    target_compile_options(fls_encoder PRIVATE -Wno-macro-redefined)
endif ()

target_link_libraries(fls_encoder
        PUBLIC
        FastLanes::headers
)
