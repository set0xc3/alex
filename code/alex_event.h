#ifndef ALEX_EVENT_H
#define ALEX_EVENT_H

enum Event_Type
{
    EventType_MouseMoved,
    EventType_MouseScrolled,
    EventType_MouseButtonPressed,
    EventType_MouseButtonReleased,
    
    EventType_KeyPressed,
    EventType_KeyReleased,
    
    EventType_WindowClose,
    EventType_WindowResize,
    EventType_WindowFocus,
    EventType_WindowMoved,
    
};

#endif // ALEX_EVENT_H
