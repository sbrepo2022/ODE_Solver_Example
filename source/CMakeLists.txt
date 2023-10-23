add_subdirectory(IntervalMath)

add_executable(mmps_lab1 main.cpp)
target_link_libraries(mmps_lab1 PRIVATE IntervalMath)
target_include_directories(mmps_lab1 PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}")

install(TARGETS mmps_lab1 DESTINATION "bin")

add_subdirectory(plugins)
