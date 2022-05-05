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

// Bool
typedef uint8_t b8;

#define true  1
#define false 0

#define internal        static
#define local_variable  static
#define global_variable static

#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)
#define ARRAY_SIZE(a) sizeof(a) / sizeof(a[0])
#define MAX_STR_LEN (4095)

// Math
#define PI 3.14159f

// Time
#define UTC (3) // Europe/Moscow

#endif // ALEX_H