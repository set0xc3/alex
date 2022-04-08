#ifndef PK_ASSERT_H
#define PK_ASSERT_H

#include "pk_defines.h"

#define ASSERTIONS_ENABLED

#ifdef ASSERTIONS_ENABLED
#if _MSC_VER
#include <intrin.h>
#define DEBUGBREAK() __debugbreak ()
#else
#define DEBUGBREAK() __buildtin_trap ()
#endif

PK_API void report_assertion_failed (const char *expr, const char *msg,
                                     const char *file, i32 line);

#define ASSERT(expr)                                                          \
  {                                                                           \
    if (expr)                                                                 \
      {                                                                       \
      }                                                                       \
    else                                                                      \
      {                                                                       \
        report_assertion_failed (#expr, "", __FILE__, __LINE__);              \
        DEBUGBREAK ();                                                        \
      }                                                                       \
  }

#define ASSERT_MSG(expr, msg)                                                 \
  {                                                                           \
    if (expr)                                                                 \
      {                                                                       \
      }                                                                       \
    else                                                                      \
      {                                                                       \
        report_assertion_failed (#expr, msg, __FILE__, __LINE__);             \
        DEBUGBREAK ();                                                        \
      }                                                                       \
  }

#ifdef _DEBUG
#define ASSERT_DEBUG(expr)                                                    \
  {                                                                           \
    if (expr)                                                                 \
      {                                                                       \
      }                                                                       \
    else                                                                      \
      {                                                                       \
        report_assertion_failed (#expr, "", __FILE__, __LINE__);              \
        DEBUGBREAK ();                                                        \
      }                                                                       \
  }
#else
#define ASSERT_DEBUG(expr)
#endif

#else
#define ASSERT(expr)
#define ASSERT_MSG(expr, msg)
#define ASSERT_DEBUG(expr)
#endif

#endif /* PK_ASSERT_H */
