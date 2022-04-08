#include "pk_clock.h"

#include "core/pk_time.h"

void
clock_update (clock *clock)
{
  if (clock->start_time != 0)
    {
      clock->elapsed = get_absolute_time () - clock->start_time;
    }
}

void
clock_start (clock *clock)
{
  clock->start_time = get_absolute_time ();
  clock->elapsed = 0;
}

void
clock_stop (clock *clock)
{
  clock->start_time = 0;
}