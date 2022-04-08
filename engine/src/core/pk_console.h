#ifndef PK_CONSOLE_H
#define PK_CONSOLE_H

#include "pk_defines.h"

b8 console_init();
void console_write (const char *msg, u8 colour);
void console_write_error (const char *msg, u8 colour);
b8 console_shutdown();

#endif
