project(FirCore VERSION 0.1.0 LANGUAGES CXX)
include_directories(${CMAKE_SOURCE_DIR}/include)

set(FIR_CORE_SOURCE_FILES 
    # Include Files
    #Array.h
    CharTraits.h
    Exception.h
    String.h
    #StringUtils.h
    Typedefs.h
    
    # Source Files
    ${CMAKE_SOURCE_DIR}/source/Fir/Core/CharTraits.cpp
    ${CMAKE_SOURCE_DIR}/source/Fir/Core/String.cpp
    #${CMAKE_SOURCE_DIR}/source/Fir/Core/StringUtils.cpp
)

if (${FIR_BUILD_SHARED})
    add_library(FirCore SHARED ${FIR_CORE_SOURCE_FILES})
    target_compile_definitions(FirCore PUBLIC FIR_BUILD_SHARED=1)
else()
    add_library(FirCore STATIC ${FIR_CORE_SOURCE_FILES})
    target_compile_definitions(FirCore PUBLIC FIR_BUILD_STATIC=1)
endif()