cmake_minimum_required(VERSION 3.8)
project(slfmt_unit_tests CXX)

find_package(Catch2 3 QUIET)
if (Catch2_FOUND)
    message(STATUS "Packaged version of Catch will be used.")
else ()
    message(STATUS "Downloading Catch.")
    include(FetchContent)
    FetchContent_Declare(
            Catch2
            GIT_REPOSITORY https://github.com/catchorg/Catch2.git
            GIT_TAG v3.3.2
    )
    FetchContent_MakeAvailable(Catch2)
endif ()

set(SLFMT_TEST_SOURCES test.cpp)
add_executable(slfmt_unit_tests ${SLFMT_TEST_SOURCES})

target_link_libraries(slfmt_unit_tests PRIVATE Catch2::Catch2WithMain fmt::fmt)

enable_testing()
