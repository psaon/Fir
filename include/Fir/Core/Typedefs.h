#ifndef __FIR_INCLUDE_TYPEDEFS_H__
#define __FIR_INCLUDE_TYPEDEFS_H__

#include <stddef.h>                 // For the size_t type and the NULL macro.
#include <stdint.h>                 // For int8_t -> int64_t and uint8_t -> uint64_t.

/**
 * Identify the Operating System.
*/
#if defined(_WIN32)
#   define FIR_SYSTEM_WINDOWS
#else
#   define FIR_SYSTEM_UNKNOWN
#   error System unsupported.
#endif

/**
 * Identify the compiler.
*/
#if defined(_MSC_VER)
#   define FIR_COMPILER_MSVC
#else
#   define FIR_COMPILER_UNKNOWN
#   error Compiler unsupported.
#endif

/**
 * Undefine some macros for Windows.
*/
#if defined(_WIN32)
#   undef min               // Undefine the min macro.
#   undef max               // Undefine the max macro.
#   undef CreateWindow      // Undefine the CreateWindow macro, clashes with the CreateWindow function.
#endif

/**
 * Macro to turn the argument to a string.
*/
#define FIR_STRINGIFY(arg) #arg

/**
 * Macro for unreferenced variables.
*/
#define FIR_UNREF(var) (void)var

/**
 * Macros for maths.
 * Use the <math.h> header for actual usage.
*/
#define FIR_MAX(x, y) ((x > y) ? x : y)

#endif      // Typedefs.h