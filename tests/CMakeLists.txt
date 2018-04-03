macro(add_hal_test HAL_TEST_EXECUTABLE HAL_TEST_SOURCE)
    add_executable(${HAL_TEST_EXECUTABLE} ${HAL_TEST_SOURCE})
    add_test(${HAL_TEST_EXECUTABLE} ${HAL_TEST_EXECUTABLE})
    include_directories(../src)
    target_link_libraries(${HAL_TEST_EXECUTABLE} gtest gtest_main libhal-9001)
endmacro()

set(HS_TESTS
    halstring_tests.cpp
    )

add_hal_test(HalStringTests ${HS_TESTS})

set(RANDOM_TESTS
    random_tests.cpp
    )

add_hal_test(RandomTests ${RANDOM_TESTS})

set(FIELD_TESTS
    field_tests.cpp
    )

add_hal_test(FieldTests ${FIELD_TESTS})

set(RB_TESTS
    rulebased_tests.cpp
    )

add_hal_test(RulebasedTests ${RB_TESTS})

set(NODE_TESTS
    node_tests.cpp
    )

add_hal_test(NodeTests ${NODE_TESTS})
