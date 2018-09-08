SET(STATIC ON CACHE BOOL "" FORCE)

add_external(
    xlnt
    ${CMAKE_BINARY_DIR}/xlnt-src
    ${CMAKE_BINARY_DIR}/xlnt-build
    xlnt)

target_compile_options(xlnt
  PRIVATE
    -O3
    $<$<COMPILE_LANGUAGE:CXX>:-std=c++14>)