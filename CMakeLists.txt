cmake_minimum_required(VERSION 3.9 FATAL_ERROR)

project(hal-9001 CXX)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

add_subdirectory(src)
add_subdirectory(thirdparty)

if(CMAKE_BUILD_TYPE STREQUAL Debug)
    enable_testing()
    add_subdirectory(tests)
endif()