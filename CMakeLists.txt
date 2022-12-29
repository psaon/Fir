cmake_minimum_required(VERSION 3.22 FATAL_ERROR)

project(Fir VERSION 0.1.0 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 11)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

set(FIR_SOURCE_FILES

    # Include Files
    include/Fir/Core/CharTraits.h
    include/Fir/Core/Exception.h
    include/Fir/Core/String.h
    include/Fir/Core/Typedefs.h
    
    # Source Files
    source/Fir/Core/CharTraits.cpp
    source/Fir/Core/String.cpp
)

# Add the option to build the library's examples.
option(FIR_BUILD_EXAMPLES "Build the examples." ON)

# Add some flags for MSVC.
if (MSVC)
    string(APPEND CMAKE_CXX_FLAGS " /Zc:__cplusplus")   # Get MSVC to report the correct C++ version.
    string(APPEND CMAKE_CXX_FLAGS " /W4")               # Set the warning level to level 4.
endif()

# Macros for build types.
if (${CMAKE_BUILD_TYPE} STREQUAL "Debug")
    add_definitions("-DFIR_CONFIG_DEBUG")
endif()

include_directories(include)
add_library(Fir ${FIR_SOURCE_FILES})

if (FIR_BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()