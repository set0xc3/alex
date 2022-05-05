#include "alex_logger.h"

internal void
logger_init()
{
    LOG_INFO("PI: %f", PI);
    LOG_WARN("PI: %f", PI);
    LOG_DEBUG("PI: %f", PI);
    LOG_TRACE("PI: %f", PI);
    LOG_ERROR("PI: %f", PI);
    LOG_FATAL("PI: %f", PI);
}

internal void 
logger_print(const Log_Type type, 
             const char *file_name, const i32 line,
             const char *fmt, ...)
{
    local_variable const char *type_str[LogType_Count] = 
    { 
        "Info", 
        "Warn", 
        "Debug", 
        "Trace", 
        "Error", 
        "Fatal" 
    };
    
    // Time
    char time_buff[MAX_STR_LEN] = "";
    time_t rawtime;
    struct tm *ptm;
    time(&rawtime);
    ptm = gmtime(&rawtime);
    sprintf(time_buff, "%02d:%02d", (ptm->tm_hour+UTC)%24, ptm->tm_min);
    
    // Header
    char header_buff[MAX_STR_LEN] = "";
    sprintf(header_buff, "[%s][%s][%s:%i] ", time_buff, type_str[type], file_name, line); 
    
    va_list arg_list;
    va_start(arg_list, fmt);
    
    // End string
    char end_buff[MAX_STR_LEN] = "";
    vsprintf(end_buff, fmt, arg_list);
    strcat(header_buff, end_buff);
    
    fprintf(stderr, "%s\n", header_buff);
    
    va_end(arg_list);
}