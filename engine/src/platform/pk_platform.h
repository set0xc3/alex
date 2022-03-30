#ifndef PK_PLATFORM_H
#define PK_PLATFORM_H

#include "..\pk_defines.h"

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

// Window
b8 platform_poll_message();
b8 platform_create_window(
    platform_state* platform,
    const char* title,
    i32 pos_x,
    i32 pos_y,
    i32 width,
    i32 height);

// Memory
void* platform_allocate(u64 size);
void platform_free(void* block);
void* platform_zero_memory(void* block, u64 size);
void* platform_copy_memory(void* dest, const void* source, u64 size);
void* platform_set_memory(void* dest, i32 value, u64 size);

// Logger
void platform_console_write(const char* msg, u8 colour);
void platform_console_write_error(const char* msg, u8 colour);

// Time
f64 platform_get_absolute_time();

void platform_sleep(u64 ms);

#endif // PK_PLATFORM_H
