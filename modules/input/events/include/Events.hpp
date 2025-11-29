#include <limits>
#include <cstdint>
enum class EventType
{
    KEYBOARD_PRESS,
    KEYBOARD_RELEASE,
    KEYBOARD_HELD,
    MOUSE_MOVEMENT,
    TOUCHPAD_MOVEMENT,
    MAX,
    INVALID
};

struct Event
{
    Event()
        : eventCode( INVALID_EVENT_CODE ),
          eventType( EventType::INVALID )
    {
    }

    int32_t eventCode;
    int32_t eventValue;
    EventType eventType;

    static constexpr int INVALID_EVENT_CODE = std::numeric_limits< int >::min();
};