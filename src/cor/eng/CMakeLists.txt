add_library(fls_eng
        OBJECT
        analyzer.cpp
        #[[]]
        compressor.cpp
        decompressor.cpp
        engine.cpp
        executor.cpp
        hzl_cmp.cpp
        hzl_cmp_fac.cpp
        hzl_de_cmp.cpp
        hzl_de_cmp_fac.cpp
        resolver.cpp
        sampler.cpp)

set(FASTLANES_OBJECT_FILES
        ${FASTLANES_OBJECT_FILES} $<TARGET_OBJECTS:fls_eng>
        PARENT_SCOPE)

if (ENABLE_IWYU)
    set_property(TARGET fls_eng PROPERTY CXX_INCLUDE_WHAT_YOU_USE ${iwyu_path})
endif ()
