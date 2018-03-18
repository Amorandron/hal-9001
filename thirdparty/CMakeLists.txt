include(external)

# Google test
if(NOT EXISTS ${CMAKE_BINARY_DIR}/thirdparty/gtest-src AND NOT EXISTS ${CMAKE_BINARY_DIR}/thirdparty/gtest-build)
    add_dl_project(
        PROJ gtest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG master
        EXCLUDE_FROM_ALL
        INCLUDE_DIRS googlemock/include googletest/include
        )
else()
    add_subdirectory(${CMAKE_BINARY_DIR}/thirdparty/gtest-src
        ${CMAKE_BINARY_DIR}/thirdparty/gtest-build
        EXCLUDE_FROM_ALL
    )
endif()