cmake_minimum_required(VERSION 3.8)
project(slfmt LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

option(WERROR "Add -Werror flag to build (turns warnings into errors)" ON)

# Configure optimization
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(OPTIMIZATION_FLAGS "-O0 -DDEBUG")
    message("-- Configuring debug build")
else ()
    set(OPTIMIZATION_FLAGS "-O3 -DNDEBUG")
    message("-- Configuring release build")
endif ()

# Enable extra warnings to adhere to https://github.com/mapbox/cpp/issues/37
set(DESIRED_WARNINGS "-Wall -Wextra -Wconversion -Wunreachable-code -Wuninitialized -pedantic-errors -Wold-style-cast -Wno-error=unused-variable -Wshadow -Wfloat-equal -Weffc++")
if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    set(DESIRED_WARNINGS "${DESIRED_WARNINGS} -Wmost")
endif ()

if (WERROR)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror")
endif ()

# Include all the source headers of the library
include_directories("${PROJECT_SOURCE_DIR}/include")

add_subdirectory(external/fmt)

# Add the testing subdirectories
option(SLFMT_BUILD_TESTS "Build the tests" ON)

if (SLFMT_BUILD_TESTS)
    add_subdirectory(test)
    add_subdirectory(bench)
endif ()

# Add the include directory to the project (contains declaration for the library)
add_subdirectory(include)
