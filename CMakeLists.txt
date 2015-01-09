cmake_minimum_required(VERSION 2.8)
project(libfbc)
enable_testing()
include(CTest)

set(CMAKE_BUILD_TYPE "Release" CACHE PATH "" FORCE)
set(LIBFBC_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/CMake")
option(WITH_PYTHON "" ON)

if(NOT WIN32)
  option(FBC_GENERATE_DOXYGEN "Build the Doxygen documentation" ON)
else()
  option(FBC_GENERATE_DOXYGEN "Build the Doxygen documentation" OFF)
endif()

add_subdirectory(src)
add_subdirectory(testing)

if (FBC_GENERATE_DOXYGEN)
  add_subdirectory(doxygen)
endif()
