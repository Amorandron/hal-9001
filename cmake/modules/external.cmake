include(CMakeParseArguments)

set(DIR_HAL_DL_PROJECT ${CMAKE_CURRENT_LIST_DIR})

function(add_dl_project)
    set(ONE_VAL_ARGS PROJ URL URL_HASH GIT_REPOSITORY GIT_TAG)
    set(MULTIPLE_VAL_ARGS INCLUDE_DIRS PATCH_COMMAND)
    cmake_parse_arguments(HALDL_ARGS "${OPTIONS}" "${ONE_VAL_ARGS}" "${MULTIPLE_VAL_ARGS}" ${ARGN})

    configure_file(${DIR_HAL_DL_PROJECT}/external.cmake.in ${HALDL_ARGS_PROJ}-download/CMakeLists.txt)
    execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/thirdparty/${HALDL_ARGS_PROJ}-download
        )
    execute_process(COMMAND ${CMAKE_COMMAND} --build .
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/thirdparty/${HALDL_ARGS_PROJ}-download
        )

    file(RENAME ${CMAKE_BINARY_DIR}/${HALDL_ARGS_PROJ}-src ${CMAKE_BINARY_DIR}/thirdparty/${HALDL_ARGS_PROJ}-src)
    file(RENAME ${CMAKE_BINARY_DIR}/${HALDL_ARGS_PROJ}-build ${CMAKE_BINARY_DIR}/thirdparty/${HALDL_ARGS_PROJ}-build)

    add_subdirectory(${CMAKE_BINARY_DIR}/thirdparty/${HALDL_ARGS_PROJ}-src
        ${CMAKE_BINARY_DIR}/thirdparty/${HALDL_ARGS_PROJ}-build
        EXCLUDE_FROM_ALL
        )
endfunction()