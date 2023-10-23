add_library(adams_bashfort_2 SHARED adams_bashfort_2.cpp)
target_link_libraries(adams_bashfort_2 PRIVATE IntervalMath)
target_include_directories(adams_bashfort_2 PRIVATE "${PLUGIN_HEADERS_DIR}")

install(TARGETS adams_bashfort_2 DESTINATION "bin/plugins")
