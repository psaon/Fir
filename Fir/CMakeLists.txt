project(Fir VERSION 0.1.0 LANGUAGES CXX)

set(FIR_SOURCE_FILES 

    # Include Files
    Containers/Array.h

    Core/Config.h
    Core/Core.h
    Core/Macros.h

    Memory/Allocator.h
    Memory/ScopedPtr.h

    Strings/CharTraits.h
    Strings/String.h

    # Source Files
    Memory/Allocator.cpp

    Strings/CharTraits.cpp
    Strings/String.cpp
)

if (${FIR_BUILD_SHARED})
    add_library(Fir SHARED ${FIR_SOURCE_FILES})
    target_compile_definitions(Fir PUBLIC FIR_BUILD_SHARED=1)
else()
    add_library(Fir STATIC ${FIR_SOURCE_FILES})
    target_compile_definitions(Fir PUBLIC FIR_BUILD_STATIC=1)
endif()

target_include_directories(Fir PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../)
