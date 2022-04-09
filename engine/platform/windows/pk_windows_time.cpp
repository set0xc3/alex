#include "core/pk_time.h"

#if PK_PLATFORM_WINDOWS

#include <windows.h>
#include <windowsx.h>

global f64 clock_frequency;
global LARGE_INTEGER start_time;

internal void
clock_setup ()
{
  LARGE_INTEGER frequency;
  QueryPerformanceCounter (&frequency);
  clock_frequency = 1.0 / (f64)frequency.QuadPart;
  QueryPerformanceCounter (&start_time);
}

internal f64
get_absolute_time ()
{
  if (!clock_frequency)
    {
      clock_setup ();
    }

  LARGE_INTEGER now_time;
  QueryPerformanceCounter (&now_time);
  return (f64)now_time.QuadPart * clock_frequency;
}

#endif