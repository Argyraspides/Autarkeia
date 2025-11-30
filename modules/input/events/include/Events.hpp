#include <cstdint>
#include <limits>
enum class EventType
{
    KEYBOARD_PRESS,
    KEYBOARD_RELEASE,
    KEYBOARD_HELD,
    MOUSE_MOVEMENT,
    TOUCHPAD_MOVEMENT,
    TOUCHPAD_ABSOLUTE_X_POS,
    TOUCHPAD_ABSOLUTE_Y_POS,
    MAX,
    INVALID
};

typedef int32_t EventCode;
typedef int32_t EventValue;
constexpr typeof(EventValue) INVALID_EVENT_VALUE = std::numeric_limits< typeof(EventValue) >::min();
struct Event
{
    Event()
          : eventType( EventType::INVALID ),
            eventValue( INVALID_EVENT_VALUE )
    {
    }

    EventType eventType;
    EventValue eventValue; // Trackpad X/Y pos, joystick X/Y pos, mouse relative X/Y movement ...
};
