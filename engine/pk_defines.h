#ifndef PK_DEFINES_H
#define PK_DEFINES_H

#include <cstdint>

// Unsigned int types.
typedef std::uint8_t u8;
typedef std::uint16_t u16;
typedef std::uint32_t u32;
typedef std::uint64_t u64;

typedef std::int8_t i8;
typedef std::int16_t i16;
typedef std::int32_t i32;
typedef std::int64_t i64;

// Floating point types
typedef float f32;
typedef double f64;

// Properly define static assertions.
#if defined(__clang__) || defined(__gcc__)
#define STATIC_ASSERT _Static_assert
#else

#define STATIC_ASSERT static_assert
#endif

// Ensure all types are of the correct size.
STATIC_ASSERT(sizeof(u8) == 1, "Expected u8 to be 1 byte.");
STATIC_ASSERT(sizeof(u16) == 2, "Expected u16 to be 2 bytes.");
STATIC_ASSERT(sizeof(u32) == 4, "Expected u32 to be 4 bytes.");
STATIC_ASSERT(sizeof(u64) == 8, "Expected u64 to be 8 bytes.");
STATIC_ASSERT(sizeof(i8) == 1, "Expected i8 to be 1 byte.");
STATIC_ASSERT(sizeof(i16) == 2, "Expected i16 to be 2 bytes.");
STATIC_ASSERT(sizeof(i32) == 4, "Expected i32 to be 4 bytes.");
STATIC_ASSERT(sizeof(i64) == 8, "Expected i64 to be 8 bytes.");
STATIC_ASSERT(sizeof(f32) == 4, "Expected f32 to be 4 bytes.");
STATIC_ASSERT(sizeof(f64) == 8, "Expected f64 to be 8 bytes.");

#define INVALID_ID 4294967295U
#define INVALID_ID_U16 65535U
#define INVALID_ID_U8 255U

#define internal static
#define local static
#define global static

// Platform detection
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__)
#define PK_PLATFORM_WINDOWS 1
#ifndef _WIN64
#error "64-bit is required on Windows!"
#endif
#elif defined(__linux__) || defined(__gnu_linux__)
// Linux OS
#define PK_PLATFORM_LINUX 1
#if defined(__ANDROID__)
#define PK_PLATFORM_ANDROID 1
#endif
#else
#error "Unknown platform!"
#endif

#ifdef PK_EXPORT
// Exports
#ifdef _MSC_VER
#define PK_API __declspec(dllexport)
#else
#define PK_API __attribute__ ((visibility ("default")))
#endif
#else
// Imports
#ifdef _MSC_VER
#define PK_API __declspec(dllimport)
#else
#define PK_API
#endif
#endif

#endif