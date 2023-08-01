cmake_minimum_required(VERSION 3.8)
project(slfmt_bench CXX)

find_package(Threads REQUIRED)
find_package(benchmark CONFIG)
if (NOT benchmark_FOUND)
    message(STATUS "Using CMake Version ${CMAKE_VERSION}")
    if (${CMAKE_VERSION} VERSION_GREATER_EQUAL "3.11.0")
        # User can fetch google_benchmark
        message(STATUS "Downloading GoogleBenchmark")
        include(FetchContent)

        # Disable tests
        set(BENCHMARK_ENABLE_TESTING OFF CACHE INTERNAL "")
        # Do not build and run google_benchmark tests
        FetchContent_Declare(
                google_benchmark
                GIT_REPOSITORY https://github.com/google/benchmark.git
                GIT_TAG v1.6.0
        )
        FetchContent_MakeAvailable(google_benchmark)
    else ()
        message(FATAL_ERROR "GoogleBenchmark is missing. Use CMake >= 3.11 or download it")
    endif ()
endif ()

add_executable(bench bench.cpp)
target_link_libraries(bench PRIVATE benchmark::benchmark)
