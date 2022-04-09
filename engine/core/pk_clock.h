#ifndef PK_CLOCK_H
#define PK_CLOCK_H

#include "pk_defines.h"

struct Clock
{
    f64 start_time;
    f64 elapsed;
};

PK_API void clock_update(Clock *clock);
PK_API void clock_start(Clock *clock);
PK_API void clock_stop(Clock *clock);

#endif
