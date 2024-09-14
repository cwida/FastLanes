add_library(fls_encoder
        OBJECT
        ccc_encoder.cpp
        #[[]]
        col_encoder.cpp
        exp_col_decoder.cpp
        exp_col_encoder.cpp
        materializer.cpp
        multi_col_encoder.cpp
        rowgroup_encoder.cpp
        single_col_decoder.cpp
        single_col_encoder.cpp
        verifier.cpp)

set(FASTLANES_OBJECT_FILES
        ${FASTLANES_OBJECT_FILES} $<TARGET_OBJECTS:fls_encoder>
        PARENT_SCOPE)

if (FLS_ENABLE_IWYU)
    set_property(TARGET fls_encoder PROPERTY CXX_INCLUDE_WHAT_YOU_USE ${iwyu_path})
endif ()