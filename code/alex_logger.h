#ifndef ALEX_LOGGER_H
#define ALEX_LOGGER_H

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

internal void logger_print(const Log_Type type, 
                           const char *file_name, const i32 line,
                           const char *fmt, ...);

#define LOG_INFO(...)  logger_print (LogType_Info,  __FILENAME__, __LINE__, __VA_ARGS__)
#define LOG_WARN(...)  logger_print (LogType_Warn,  __FILENAME__, __LINE__, __VA_ARGS__)
#define LOG_DEBUG(...) logger_print (LogType_Debug, __FILENAME__, __LINE__, __VA_ARGS__)
#define LOG_TRACE(...) logger_print (LogType_Trace, __FILENAME__, __LINE__, __VA_ARGS__)
#define LOG_ERROR(...) logger_print (LogType_Error, __FILENAME__, __LINE__, __VA_ARGS__)
#define LOG_FATAL(...) logger_print (LogType_Fatal, __FILENAME__, __LINE__, __VA_ARGS__)

#endif // ALEX_LOGGER_H
