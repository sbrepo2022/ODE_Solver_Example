cmake_minimum_required(VERSION 3.14.0)

project(MMPSLab1 VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

message("C++ compiler: ${CMAKE_CXX_COMPILER}")

add_executable(mmps_lab1 main.cpp)
target_include_directories(mmps_lab1 PRIVATE "${CMAKE_SOURCE_DIR}")

add_library(adams_bashfort_2 SHARED adams_bashfort_2.cpp)
target_include_directories(adams_bashfort_2 PRIVATE "${CMAKE_SOURCE_DIR}")

add_library(runge_kutta_4 SHARED runge_kutta_4.cpp)
target_include_directories(runge_kutta_4 PRIVATE "${CMAKE_SOURCE_DIR}")

install(TARGETS mmps_lab1 adams_bashfort_2 runge_kutta_4 DESTINATION "bin")