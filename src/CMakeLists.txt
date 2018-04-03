set(HAL_LIB_SRC
    mc/montecarlo.h
    mc/montecarlo.cpp
    mcts/mcts.h
    mcts/mcts.cpp
    mcts/node.h
    mcts/node.cpp
    rulebased/rulebased.h
    rulebased/rulebased.cpp
    util/halstring.h
    util/halstring.cpp
    util/random.h
    util/timer.h
    util/timer.cpp
    algorithm.h
    bot.h
    bot.cpp
    disc.h
    disc.cpp
    field.h
    field.cpp
    setting_manager.h
    setting_manager.cpp
    )

set(HAL_SRC
    main.cpp
    )

if(MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

set(HAL_LIBRARY_NAME libhal-9001)

add_library(libhal-9001 ${HAL_LIB_SRC})

target_compile_features(libhal-9001
    PRIVATE
        cxx_std_14
    )

add_executable(${PROJECT_NAME} ${HAL_SRC})

target_link_libraries(${PROJECT_NAME} ${HAL_LIBRARY_NAME})

if(CMAKE_BUILD_TYPE STREQUAL Release)
    include(release)
endif()