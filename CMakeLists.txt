cmake_minimum_required(VERSION 3.8)
project(slfmt LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

option(WERROR "Add -Werror flag to build (turns warnings into errors)" ON)

# Configure optimization
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    if (MSVC)
        set(OPTIMIZATION_FLAGS "/Od /D \"_DEBUG\"")
    else ()
        set(OPTIMIZATION_FLAGS "-O0 -DDEBUG")
    endif ()
    message("-- Configuring debug build")
else ()
    if (MSVC)
        set(OPTIMIZATION_FLAGS "/O2 /D \"NDEBUG\"")
    else ()
        set(OPTIMIZATION_FLAGS "-O3 -DNDEBUG")
    endif ()
    message("-- Configuring release build")
endif ()

# Enable extra warnings
set(DESIRED_WARNINGS "-Wall -Wextra -Wconversion -Wunreachable-code -Wno-error=unused-variable -Wshadow -Wfloat-equal")
if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang" OR CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    set(DESIRED_WARNINGS "${DESIRED_WARNINGS} -pedantic-errors -Wold-style-cast -Weffc++ -Wuninitialized")
endif ()
if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    set(DESIRED_WARNINGS "${DESIRED_WARNINGS} -Wmost")
endif ()

if (WERROR)
    if (MSVC)
        set(ERROR_FLAG "/WX")
    else ()
        set(ERROR_FLAG "-Werror")
    endif ()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${ERROR_FLAG}")
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

set(SLFMT_SOURCES
        include/slfmt.h
        include/slfmt/Color.h
        include/slfmt/ConsoleLogger.h
        include/slfmt/FileLogger.h
        include/slfmt/Level.h
        include/slfmt/LoggerBase.h
        include/slfmt/LogManager.h
        include/slfmt/Version.h
)

add_library(slfmt STATIC ${SLFMT_SOURCES})
set_target_properties(slfmt PROPERTIES LINKER_LANGUAGE CXX)

target_link_libraries(slfmt fmt::fmt)
target_include_directories(
        slfmt
        PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        PUBLIC $<INSTALL_INTERFACE:include>
)

option(SLFMT_BUILD_EXAMPLES "Build the examples" OFF)

if (SLFMT_BUILD_EXAMPLES)
    message("Adding slfmt examples")
    add_subdirectory(examples)
endif ()
