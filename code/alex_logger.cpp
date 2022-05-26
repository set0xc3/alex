#include "alex_logger.h"

internal void 
logger_print(const char *type_str, 
             const char *file_name, const i32 line,
             const char *fmt, ...)
{
    const local_variable i32 str_len = 256;
    
    // Time
    char time_buff[str_len] = "";
    time_t rawtime;
    struct tm *ptm;
    time(&rawtime);
    ptm = gmtime(&rawtime);
    sprintf(time_buff, "%02d:%02d", (ptm->tm_hour+UTC)%24, ptm->tm_min);
    
    // Header
    char header_buff[str_len] = "";
    sprintf(header_buff, "[%s][%s][%s:%i] ", time_buff, type_str, file_name, line); 
    
    va_list arg_list;
    va_start(arg_list, fmt);
    
    // End string
    char end_buff[str_len] = "";
    vsprintf(end_buff, fmt, arg_list);
    strcat(header_buff, end_buff);
    
    fprintf(stderr, "%s\n", header_buff);
    
    va_end(arg_list);
}