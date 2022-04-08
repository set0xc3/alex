#include "pk_event.h"

#include "containers/pk_array.h"
#include "core/pk_assert.h"
#include "core/pk_memory.h"

typedef struct
{
  void *listener;
  on_event callback;
} registered_event;

typedef struct
{
  registered_event *events;
} event_code_entry;

#define MAX_MESSAGE_CODES 16384

// State structure.
typedef struct
{
  // Lookup table for event codes.
  event_code_entry registered[MAX_MESSAGE_CODES];
} event_system_state;

global b8 g_initialized = false;
global event_system_state *g_state = NULL;

internal void
event_initialize ()
{
  if (g_initialized)
    {
      ASSERT (false);
    }

  g_state
      = memory_allocate (sizeof (event_system_state), MEMORY_TAG_APPLICATION);
  memory_set (g_state, 0, sizeof (g_state));
  g_initialized = true;
}

internal void
event_shutdown ()
{
  if (g_state)
    {
      // Free the events arrays. And objects pointed to should be destroyed on
      // their own.
      for (u16 i = 0; i < MAX_MESSAGE_CODES; ++i)
        {
          if (g_state->registered[i].events != 0)
            {
              ARRAY_DESTROY (g_state->registered[i].events);
              g_state->registered[i].events = 0;
            }
        }
    }
  g_state = (void *)0;
}

b8
event_register (u16 code, void *listener, on_event on_event)
{
  if (!g_state)
    {
      return false;
    }

  if (g_state->registered[code].events == 0)
    {
      g_state->registered[code].events = ARRAY_CREATE (registered_event);
    }

  u64 registered_count = ARRAY_LENGHT (g_state->registered[code].events);
  for (u64 i = 0; i < registered_count; ++i)
    {
      if (g_state->registered[code].events[i].listener == listener)
        {
          // TODO: warn
          return false;
        }
    }

  // If at this point, no duplicate was found. Proceed with registration.
  registered_event event;
  event.listener = listener;
  event.callback = on_event;
  ARRAY_PUSH (g_state->registered[code].events, event);

  return true;
}

b8
event_unregister (u16 code, void *listener, on_event on_event)
{
  if (!g_state)
    {
      return false;
    }

  // On nothing is registered for the code, boot out.
  if (g_state->registered[code].events == 0)
    {
      // TODO: warn
      return false;
    }

  u64 registered_count = ARRAY_LENGHT (g_state->registered[code].events);
  for (u64 i = 0; i < registered_count; ++i)
    {
      registered_event e = g_state->registered[code].events[i];
      if (e.listener == listener && e.callback == on_event)
        {
          // Found one, remove it
          registered_event popped_event;
          ARRAY_POP_AT (g_state->registered[code].events, i, &popped_event);
          return true;
        }
    }

  // Not found.
  return false;
}

b8
event_fire (u16 code, void *sender, event_context context)
{
  if (!g_state)
    {
      return false;
    }

  // If nothing is registered for the code, boot out.
  if (g_state->registered[code].events == 0)
    {
      return false;
    }

  u64 registered_count = ARRAY_LENGHT (g_state->registered[code].events);
  for (u64 i = 0; i < registered_count; ++i)
    {
      registered_event e = g_state->registered[code].events[i];
      if (e.callback (code, sender, e.listener, context))
        {
          // Message has been handled, do not send to other listeners.
          return true;
        }
    }

  // Not found.
  return false;
}