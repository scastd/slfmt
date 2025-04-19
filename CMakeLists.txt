cmake_minimum_required(VERSION 3.25)
project(slfmt LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_POLICY_VERSION_MINIMUM 3.5)

include(cmake/CPM.cmake)

# Include all the source headers of the library
include_directories("${PROJECT_SOURCE_DIR}/include")

# Add the external dependencies
#add_subdirectory(external/fmt)
#add_subdirectory(external/miniz)
CPMAddPackage("gh:fmtlib/fmt#11.1.4")
CPMAddPackage("gh:richgel999/miniz#3.0.2")

# Add the testing subdirectories
option(SLFMT_BUILD_TESTS "Build the tests" OFF)

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
        include/slfmt/CombinedLogger.h
        include/slfmt/Files.h
        include/slfmt/RollingFileLogger.h
        include/slfmt/LogFormat.h
)

add_library(slfmt STATIC src/slfmt.cpp ${SLFMT_SOURCES})
set_target_properties(slfmt PROPERTIES LINKER_LANGUAGE CXX)

target_link_libraries(slfmt fmt::fmt miniz)
target_include_directories(
        slfmt
        PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        PUBLIC $<INSTALL_INTERFACE:include>
)

option(SLFMT_BUILD_EXAMPLES "Build the examples" ON)

if (SLFMT_BUILD_EXAMPLES)
    message("Adding slfmt examples")
    add_subdirectory(examples)
endif ()
