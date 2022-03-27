#if !defined(PEKORA_PLATFORM_H)
#define PEKORA_PLATFORM_H

#include "pekora_defines.h"

typedef struct platform_state {
    void* internal_state;
} platform_state;

void clock_setup();

b8 platform_startup(
    platform_state* platform,
    const char* title,
    i32 pos_x,
    i32 pos_y,
    i32 width,
    i32 height);
b8 platform_shutdown(platform_state* platform);
b8 platform_poll_message(platform_state* platform);

void* platform_allocate(u64 size, b8 aligned);
void platform_free(void* block, b8 aligned);
void* platform_zero_memory(void* block, u64 size);
void* platform_copy_memory(void* dest, const void* source, u64 size);
void* platform_set_memory(void* dest, i32 value, u64 size);

void platform_console_write(const char* msg, u8 colour);
void platform_console_write_error(const char* msg, u8 colour);

f64 platform_get_absolute_time();
void platform_sleep(u64 ms);

#endif  // PEKORA_PLATFORM_H