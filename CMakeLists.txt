cmake_minimum_required(VERSION 3.22 FATAL_ERROR)

set(CMAKE_CXX_STANDARD 17)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

# Add the option to build the library's examples.
option(FIR_BUILD_EXAMPLES "Build the examples." ON)

# Add an option to build as a shared library or a static library.
option(FIR_BUILD_SHARED "Build as a shared library." ON)

# Add some flags for MSVC.
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    string(APPEND CMAKE_CXX_FLAGS " /Zc:__cplusplus")   # Get MSVC to report the correct C++ version.
    string(APPEND CMAKE_CXX_FLAGS " /W4")               # Set the warning level to level 4.
elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    string(APPEND CMAKE_CXX_FLAGS " -Wall")             # Get G++ to report all warnings.
endif()

# Macros for build types.
if ("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
    add_definitions("-DFIR_CONFIG_DEBUG")
endif()

add_subdirectory(Fir)

if (${FIR_BUILD_EXAMPLES})
    add_subdirectory(Examples)
endif()