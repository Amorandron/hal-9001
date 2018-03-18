macro(add_hal_test HAL_TEST_EXECUTABLE HAL_TEST_SOURCE)
    add_executable(${HAL_TEST_EXECUTABLE} ${HAL_TEST_SOURCE})
    add_test(${HAL_TEST_EXECUTABLE} ${HAL_TEST_EXECUTABLE})
    include_directories(../src)
    target_link_libraries(${HAL_TEST_EXECUTABLE} gtest gtest_main libhal-9001)
endmacro()

set(HAL_TEST_TEST_SOURCES
    test.cpp
    )

add_hal_test(Libtest ${HAL_TEST_TEST_SOURCES})