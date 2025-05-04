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

target_compile_options(fls_encoder PRIVATE -Wno-macro-redefined)
