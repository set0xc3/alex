#ifndef PK_CLOCK_H
#define PK_CLOCK_H

#include "pk_defines.h"

typedef struct clock
{
    f64 start_time;
    f64 elapsed;
} clock;

PK_API void clock_update (clock *clock);
PK_API void clock_start (clock *clock);
PK_API void clock_stop (clock *clock);

#endif
