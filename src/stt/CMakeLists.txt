add_library(fls_stt
        OBJECT
        #[[]]
        histogram.cpp
        minmax.cpp
        stt_fac.cpp)

set(FASTLANES_OBJECT_FILES
        ${FASTLANES_OBJECT_FILES} $<TARGET_OBJECTS:fls_stt>
        PARENT_SCOPE)

if (ENABLE_IWYU)
    set_property(TARGET fls_stt PROPERTY CXX_INCLUDE_WHAT_YOU_USE ${iwyu_path})
endif ()

