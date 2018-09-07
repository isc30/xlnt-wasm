cmake_minimum_required (VERSION 3.5)
project(xlnt-wasm VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_VERBOSE_MAKEFILE OFF)

if(DEFINED ENV{EMSCRIPTEN})
    set(CMAKE_TOOLCHAIN_FILE "$ENV{EMSCRIPTEN}/cmake/Modules/Platform/Emscripten.cmake"
        CACHE PATH "emscripten toolchain" FORCE)
else()
    message(FATAL_ERROR "Emscripten not found. Set EMSCRIPTEN environment variable to point to the emscripten root directory")
endif()

add_subdirectory(dependencies)

add_executable(bindings ${PROJECT_SOURCE_DIR}/src/bindings.cpp)
target_link_libraries(bindings PRIVATE -O3)
target_include_directories(bindings
    PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_compile_options(bindings
    PRIVATE
        -O3
        -Wall
        $<$<COMPILE_LANGUAGE:CXX>:-std=c++14>)

set_target_properties(bindings PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
    CMAKE_CXX_EXTENSIONS OFF
    OUTPUT_NAME "xlnt"
    SUFFIX ".js"
    LINK_FLAGS "--bind -s WASM=1 -s DEMANGLE_SUPPORT=1")

add_dependencies(bindings xlnt)
target_link_libraries(bindings PRIVATE xlnt)
