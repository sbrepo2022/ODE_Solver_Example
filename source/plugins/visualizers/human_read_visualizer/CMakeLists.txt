add_library(human_read_visualizer SHARED human_read_visualizer.cpp)
target_link_libraries(human_read_visualizer PRIVATE IntervalMath)
target_include_directories(human_read_visualizer PRIVATE "${PLUGIN_HEADERS_DIR}")

install(TARGETS human_read_visualizer DESTINATION "bin/plugins")