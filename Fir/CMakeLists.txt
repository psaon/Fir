project(Fir VERSION 0.1.0 LANGUAGES CXX)
include_directories(../)

set(FIR_SOURCE_FILES 

    # Include Files
    Core/Config.h
    Core/Core.h
    Core/Macros.h

    Memory/Allocator.h

    # Source Files
    Memory/Allocator.cpp
)

if (${FIR_BUILD_SHARED})
    add_library(Fir SHARED ${FIR_SOURCE_FILES})
    target_compile_definitions(Fir PUBLIC FIR_BUILD_SHARED=1)
else()
    add_library(Fir STATIC ${FIR_SOURCE_FILES})
    target_compile_definitions(Fir PUBLIC FIR_BUILD_STATIC=1)
endif()
