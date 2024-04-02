add_executable(basic_usage basic_usage.cpp)
add_executable(rolling_usage rolling_usage.cpp)

target_link_libraries(basic_usage fmt::fmt miniz)
target_link_libraries(rolling_usage fmt::fmt miniz)
