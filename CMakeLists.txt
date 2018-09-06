cmake_minimum_required (VERSION 3.5)
project(xlnt-wasm VERSION 1.0.0 LANGUAGES CXX)

message("$ENV{EMSCRIPTEN}")
set(CMAKE_VERBOSE_MAKEFILE OFF)

if(DEFINED ENV{EMSCRIPTEN})
    set(CMAKE_TOOLCHAIN_FILE "$ENV{EMSCRIPTEN}/cmake/Modules/Platform/Emscripten.cmake"
        CACHE PATH "emscripten toolchain" FORCE)
else()
    message(FATAL_ERROR "Emscripten not found. Set EMSCRIPTEN environment variable to point to the emscripten root directory")
endif()

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(dependencies)

add_executable(bindings ${PROJECT_SOURCE_DIR}/src/bindings.cpp)
target_link_libraries(bindings PRIVATE "--bind")
set_target_properties(bindings PROPERTIES OUTPUT_NAME "xlnt.js")

add_dependencies(bindings xlnt)
target_link_libraries(bindings PRIVATE xlnt)

target_compile_options(bindings PRIVATE "-Wall")

target_include_directories(bindings
    PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)
