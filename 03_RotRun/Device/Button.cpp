#include "Button.hpp"

bool Button::isLeftPressed()
{
    hub_button_t pressed;
    hub_button_is_pressed(&pressed);
    return static_cast<bool>(pressed & HUB_BUTTON_LEFT);
}

bool Button::isCenterPressed()
{
    hub_button_t pressed;
    hub_button_is_pressed(&pressed);
    return static_cast<bool>(pressed & HUB_BUTTON_CENTER);
}

bool Button::isRightPressed()
{
    hub_button_t pressed;
    hub_button_is_pressed(&pressed);
    return static_cast<bool>(pressed & HUB_BUTTON_RIGHT);
}

bool Button::isBluetoothPressed()
{
    hub_button_t pressed;
    hub_button_is_pressed(&pressed);
    return static_cast<bool>(pressed & HUB_BUTTON_BT);
}
