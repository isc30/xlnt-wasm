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

# Add 'xlnt' target

SET(STATIC ON CACHE BOOL "Build libxlnt as static library" FORCE)

add_subdirectory(
    ${CMAKE_BINARY_DIR}/xlnt-src
    ${CMAKE_BINARY_DIR}/xlnt-build
    EXCLUDE_FROM_ALL)

target_compile_options(xlnt
  PRIVATE
    -O3
    $<$<COMPILE_LANGUAGE:CXX>:-std=c++14>)