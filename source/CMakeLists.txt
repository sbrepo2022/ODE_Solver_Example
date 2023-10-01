add_subdirectory(IntervalMath)

add_executable(mmps_lab1 main.cpp)
target_link_libraries(mmps_lab1 PRIVATE IntervalMath)
target_include_directories(mmps_lab1 PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}")

add_library(adams_bashfort_2 SHARED adams_bashfort_2.cpp)
target_link_libraries(adams_bashfort_2 PRIVATE IntervalMath)
target_include_directories(adams_bashfort_2 PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}")

add_library(runge_kutta_4 SHARED runge_kutta_4.cpp)
target_link_libraries(runge_kutta_4 PRIVATE IntervalMath)
target_include_directories(runge_kutta_4 PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}")

install(TARGETS mmps_lab1 adams_bashfort_2 runge_kutta_4 DESTINATION "bin")