function(slfmt_test name)
    add_executable(${name} ${name}.cpp)
    target_link_libraries(${name} fmt::fmt miniz)
endfunction()

slfmt_test(basic_usage)
slfmt_test(rolling_usage)
slfmt_test(combined_logger)
