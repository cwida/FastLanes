add_library(fls_new_encoder
        OBJECT
        #
        new_decoder.cpp
        new_encoder.cpp

)

set(FASTLANES_OBJECT_FILES
        ${FASTLANES_OBJECT_FILES} $<TARGET_OBJECTS:fls_new_encoder>
        PARENT_SCOPE)

if (FLS_ENABLE_IWYU)
    set_property(TARGET fls_new_encoder PROPERTY CXX_INCLUDE_WHAT_YOU_USE ${iwyu_path})
endif ()