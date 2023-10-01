cmake_minimum_required(VERSION 3.14.0)

set(CMAKE_TOOLCHAIN_FILE "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "Vcpkg toolchain file")

project(MMPSLab1 VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

message("C++ compiler: ${CMAKE_CXX_COMPILER}")

enable_testing()
find_package(GTest)

add_subdirectory(source)
