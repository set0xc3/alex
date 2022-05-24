#ifndef ALEX_H
#define ALEX_H

// Standard headers
#include <stdint.h> 
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <errno.h>
#include <time.h>

typedef uint8_t  u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef int8_t  i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;

typedef float  f32;
typedef double f64;
typedef bool   b8;

#define internal        static
#define local_variable  static
#define global_variable static

#if 0
#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)
#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))

#define MAX_STR_LEN (4095)

// Memory
#define ZERO_MEMORY(s) (memset(s, 0, sizeof(*s)))
#define ZERO_STRUCT(s) (memset(s, 0, sizeof(*s)))

// Math
#define PI (3.14159f)

// Time
#define UTC (3) // Europe/Moscow

struct Color
{
    u8 r;
    u8 g;
    u8 b;
    u8 a;
};

internal char *get_data_from_file(const char *path);
#endif

#endif // ALEX_H