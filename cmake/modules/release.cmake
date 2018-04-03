file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/release)

add_custom_target(
    zip-files
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/src
    COMMAND ${CMAKE_COMMAND} -E tar cvf ${CMAKE_BINARY_DIR}/release/${PROJECT_NAME}.zip --format=zip
        ${HAL_LIB_SRC}
        ${HAL_SRC}
    )

add_dependencies(${PROJECT_NAME} zip-files)