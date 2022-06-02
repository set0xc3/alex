/* date = June 2nd 2022 1:41 pm */

#ifndef ALEX_BASE_DEF_H
#define ALEX_BASE_DEF_H

// Standard headers
#include <stdint.h> 
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <cstdlib>
#include <errno.h>
#include <time.h>
#include <unistd.h>

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

#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)

// Memory
#define ZERO_MEMORY(s) (memset(s, 0, sizeof(*s)))
#define ZERO_STRUCT(s) (memset(s, 0, sizeof(*s)))

#endif //ALEX_BASE_DEF_H
