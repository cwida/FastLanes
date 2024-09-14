add_library(fallback_scalar_aav_1024_uf1_rsum OBJECT
        fallback_scalar_aav_1024_uf1_rsum_src.cpp)
target_compile_definitions(fallback_scalar_aav_1024_uf1_rsum PRIVATE IS_SCALAR)

LIST(APPEND FLS_GENERATED_OBJECT_FILES
        $<TARGET_OBJECTS:fallback_scalar_aav_1024_uf1_rsum>)
#------------------------------------------------------------------------------------------------------
if (FLS_BUILD_TESTING)
#    add_executable(fallback_scalar_aav_1024_uf1_rsum_test fallback_scalar_aav_1024_uf1_rsum_test.cpp)
#    target_link_libraries(fallback_scalar_aav_1024_uf1_rsum_test PRIVATE fallback_scalar_aav_1024_uf1_rsum)
#    target_link_libraries(fallback_scalar_aav_1024_uf1_rsum_test PRIVATE fallback_scalar_aav_1024_uf1_unrsum fallback_scalar_aav_1024_uf1_untranspose)
#    target_link_libraries(fallback_scalar_aav_1024_uf1_rsum_test PRIVATE gtest_main)
#    target_include_directories(fallback_scalar_aav_1024_uf1_rsum_test PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
#    gtest_discover_tests(fallback_scalar_aav_1024_uf1_rsum_test)
endif ()
