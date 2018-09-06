configure_file(
    xlnt-CMakeLists.txt
    ${CMAKE_BINARY_DIR}/xlnt-download/CMakeLists.txt)

execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/xlnt-download)

if(result)
  message(FATAL_ERROR "CMake step for xlnt failed: ${result}")
endif()

execute_process(COMMAND ${CMAKE_COMMAND} --build .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/xlnt-download)

if(result)
  message(FATAL_ERROR "Build step for xlnt failed: ${result}")
endif()

# Add xlnt directly to our build.
set(STATIC ON)
add_subdirectory(
    ${CMAKE_BINARY_DIR}/xlnt-src
    ${CMAKE_BINARY_DIR}/xlnt-build
    EXCLUDE_FROM_ALL)