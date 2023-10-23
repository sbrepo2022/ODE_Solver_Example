add_library(runge_kutta_4 SHARED runge_kutta_4.cpp)
target_link_libraries(runge_kutta_4 PRIVATE IntervalMath)
target_include_directories(runge_kutta_4 PRIVATE "${PLUGIN_HEADERS_DIR}")

install(TARGETS runge_kutta_4 DESTINATION "bin/plugins")
