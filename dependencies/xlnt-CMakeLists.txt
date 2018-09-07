cmake_minimum_required(VERSION 3.5.0)

project(xlnt-download NONE)

include(ExternalProject)
ExternalProject_Add(xlnt-remote
  GIT_REPOSITORY    https://github.com/tfussell/xlnt
  GIT_TAG           master
  SOURCE_DIR        "${CMAKE_BINARY_DIR}/xlnt-src"
  BINARY_DIR        "${CMAKE_BINARY_DIR}/xlnt-build"
  CONFIGURE_COMMAND ""
  BUILD_COMMAND     ""
  INSTALL_COMMAND   ""
  TEST_COMMAND      ""
)