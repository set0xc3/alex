#ifndef ALEX_H
#define ALEX_H

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

#define internal static
#define local_variable static
#define global_variable static

#endif /* PEKORA_H */