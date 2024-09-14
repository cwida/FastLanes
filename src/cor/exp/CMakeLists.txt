add_subdirectory(alp)
add_subdirectory(byte_arr)
add_subdirectory(delta)
add_subdirectory(dict)
add_subdirectory(dict_rle)
add_subdirectory(rle)
add_subdirectory(ffor)
add_subdirectory(fsst)
add_subdirectory(fsst12)
add_subdirectory(uncompressed)

add_library(fls_all_exp
        OBJECT
        exp.cpp
        hdr.cpp
        exp_fac.cpp)

set(FASTLANES_OBJECT_FILES
        ${FASTLANES_OBJECT_FILES} $<TARGET_OBJECTS:fls_all_exp>
        PARENT_SCOPE)

if (ENABLE_IWYU)
    set_property(TARGET fls_all_exp PROPERTY CXX_INCLUDE_WHAT_YOU_USE ${iwyu_path})
endif ()


