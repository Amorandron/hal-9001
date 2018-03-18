set(HAL_LIB_SRC
    hallib.h
    hallib.cpp
    )

set(HAL_SRC
    hal.cpp
    )

if(MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

set(HAL_LIBRARY_NAME libhal-9001)

add_library(libhal-9001 ${HAL_SRC})

target_compile_features(libhal-9001
    PRIVATE
        cxx_std_17
    )

add_executable(${PROJECT_NAME} ${HAL_EXEC_SRC})

target_link_libraries(${PROJECT_NAME} ${HAL_LIBRARY_NAME})

if(CMAKE_BUILD_TYPE STREQUAL Release)
    include(release)
endif()