#ifndef ALEX_LOGGER_H
#define ALEX_LOGGER_H

#include "alex.h"

enum Log_Type
{
    LogType_Info = 0,
    LogType_Warn,
    LogType_Debug,
    LogType_Trace,
    LogType_Error,
    LogType_Fatal,
    LogType_Count
};

internal void logger_print(const char *type_str, 
                           const char *file_name, const i32 line,
                           const char *fmt, ...);

#if 0
#define LOG_INFO(...)  logger_print("Info",  __FILENAME__, __LINE__, __VA_ARGS__)
#else
#define LOG_INFO(...)  logger_print("Info",  "", 0, __VA_ARGS__)
#endif

#define LOG_WARN(...)  logger_print("Warn",  __FILENAME__, __LINE__, __VA_ARGS__)

#if 0
#define LOG_DEBUG(...) logger_print("Debug", __FILENAME__, __LINE__, __VA_ARGS__)
#else
#define LOG_DEBUG(...) logger_print("Debug", "", 0, __VA_ARGS__)
#endif

#define LOG_TRACE(...) logger_print("Trace", __FILENAME__, __LINE__, __VA_ARGS__)
#define LOG_ERROR(...) logger_print("Error", __FILENAME__, __LINE__, __VA_ARGS__)
#define LOG_FATAL(...) logger_print("Fatal", __FILENAME__, __LINE__, __VA_ARGS__)

#endif // ALEX_LOGGER_H
