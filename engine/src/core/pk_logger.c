#include <stdarg.h>
#include <stdio.h>
#include <string.h>

#include "core/pk_memory.h"
#include "pk_assert.h"
#include "pk_logger.h"
#include "platform/pk_platform.h"

internal b8
initialize_logging() {
    return true;
}

internal void
shutdown_logging() {
}

internal void
log_output(log_level level, const char* message, ...) {
    const char* level_strings[6] = {"[FATAL]: ", "[ERROR]: ", "[WARN]: ", "[INFO]: ", "[DEBUG]: ", "[TRACE]: "};
    b8 is_error = level < LOG_LEVEL_WARN;

    // NOTE(parsecffo): переделать!.
    const i32 msg_length = 32000;
    char out_message[msg_length];
    pk_zero_memory(out_message, sizeof(out_message));

    __builtin_va_list arg_ptr;
    va_start(arg_ptr, message);
    vsnprintf(out_message, msg_length, message, arg_ptr);
    va_end(arg_ptr);

    char out_message2[msg_length];
    sprintf(out_message2, "%s%s\n", level_strings[level], out_message);

    // Print accordingly
    if (is_error) {
        platform_console_write_error(out_message2, level);
    } else {
        platform_console_write(out_message2, level);
    }
}

void report_assertion_failed(const char* expr, const char* msg, const char* file, i32 line) {
    log_output(LOG_LEVEL_FATAL, "Assertion Failed: %s, msg: '%s', in file: %s, line: %d\n", expr, msg, file, line);
}
