enum EventType
{
    KEYBOARD_PRESS,
    MOUSE_MOVEMENT
};

struct Event
{
    int eventCode;
    EventType eventType;
};