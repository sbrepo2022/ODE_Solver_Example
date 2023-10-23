add_library(adams_bashfort_moulton_4 SHARED adams_bashfort_moulton_4.cpp)
target_link_libraries(adams_bashfort_moulton_4 PRIVATE IntervalMath)
target_include_directories(adams_bashfort_moulton_4 PRIVATE "${PLUGIN_HEADERS_DIR}")

install(TARGETS adams_bashfort_moulton_4 DESTINATION "bin/plugins")
