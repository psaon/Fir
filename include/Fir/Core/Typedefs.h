#ifndef __FIR_INCLUDE_TYPEDEFS_H__
#define __FIR_INCLUDE_TYPEDEFS_H__

#include <stddef.h>                 // For the size_t type and the NULL macro.
#include <stdint.h>                 // For int8_t -> int64_t and uint8_t -> uint64_t.

#include "Fir/Core/Exception.h"

/**
 * Identify the Operating System.
*/
#if defined(_WIN32)
#   define FIR_SYSTEM_WINDOWS
#elif defined(__linux__)
#    define FIR_SYSTEM_LINUX
#else
#   define FIR_SYSTEM_UNKNOWN
#   error System unsupported.
#endif

/**
 * Identify the compiler.
*/
#if defined(_MSC_VER)
#   define FIR_COMPILER_MSVC
#elif defined(__GNUC__)
#    define FIR_COMPILER_GCC
#else
#   define FIR_COMPILER_UNKNOWN
#   error Compiler unsupported.
#endif

/**
 * Define some compiler specific macros.
*/
#if defined(FIR_COMPILER_MSVC)
#   define _CRT_SECURE_NO_WARNINGS          // Turn off deprecation warnings for unsafe CRT functions.

#    define FIR_ENABLE_MSVC_WARNING(code)  __pragma(warning(default: ##code))
#    define FIR_DISABLE_MSVC_WARNING(code) __pragma(warning(disable: ##code))
#else
#    define FIR_ENABLE_MSVC_WARNING(code)
#    define FIR_DISABLE_MSVC_WARNING(code)
#endif

/**
 * Undefine some macros for Windows.
*/
#if defined(FIR_SYSTEM_WINDOWS)
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
 * Macro for force inlining.
*/
#if defined(FIR_COMPILER_MSVC)
#    define FIR_FORCEINLINE __forceinline
#elif defined(FIR_COMPILER_GCC)
#    define FIR_FORCEINLINE __attribute__((always_inline))
#else
#    define FIR_FORCEINLINE inline
#endif

/**
 * Macro for compiling as a shared library. (DLL in Windows)
*/
#if defined(FIR_BUILD_STATIC)
#    define FIR_API
#else
#    if defined(FIR_COMPILER_MSVC)
#        if defined(FIR_BUILD_SHARED)
#            define FIR_API __declspec(dllexport)
#        else
#            define FIR_API __declspec(dllimport)
#        endif
#    elif defined(FIR_COMPILER_GCC)
#        if defined(FIR_BUILD_SHARED)
#            define FIR_API __attribute__((visibility("default")))
#        else
#            define FIR_API
#        endif
#    endif
#endif

#if !defined(FIR_BUILD_STATIC)
#    if defined(FIR_BUILD_SHARED)
#        define FIR_API __declspec(dllexport)
#    else
#        define FIR_API __declspec(dllimport)
#    endif
#else
#    define FIR_API
#endif

/**
 * Macros for maths.
 * Use the <math.h> header for actual mathematical operations.
 * Some macros like abs() can result in -0 for floating point numbers.
*/
#define FIR_MAX(x, y) ((x > y) ? x : y)
#define FIR_MIN(x, y) ((x > y) ? y : x)
#define FIR_ABS(x)    ((x > 0) ? x : -x)
#define FIR_SIGN(x)   ((x < 0) ? -1 : (x == 0) ? 0 : 1)

#endif      // Typedefs.h