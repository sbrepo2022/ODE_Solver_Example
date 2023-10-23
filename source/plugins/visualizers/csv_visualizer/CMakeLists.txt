add_library(csv_visualizer SHARED csv_visualizer.cpp)
target_link_libraries(csv_visualizer PRIVATE IntervalMath)
target_include_directories(csv_visualizer PRIVATE "${PLUGIN_HEADERS_DIR}")

install(TARGETS csv_visualizer DESTINATION "bin/plugins")