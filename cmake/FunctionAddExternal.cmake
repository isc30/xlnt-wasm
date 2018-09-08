function(add_external libraryname sourcedir bindir)

    configure_file(
        ${libraryname}.cmake
        ${CMAKE_BINARY_DIR}/${libraryname}-download/CMakeLists.txt)

    execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
        RESULT_VARIABLE result
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/${libraryname}-download)

    if(result)
        message(FATAL_ERROR "CMake step for ${libraryname} failed: ${result}")
    endif()

    execute_process(COMMAND ${CMAKE_COMMAND} --build .
        RESULT_VARIABLE result
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/${libraryname}-download)

    if(result)
        message(FATAL_ERROR "Build step for ${libraryname} failed: ${result}")
    endif()

    add_subdirectory(
        ${sourcedir}
        ${bindir}
        EXCLUDE_FROM_ALL)

    foreach(expected_target ${ARGN})
        if (NOT TARGET ${expected_target})
            message(FATAL_ERROR "external target ${expected_target} not found")
        endif()
    endforeach(expected_target)

endfunction()