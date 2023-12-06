#include "Screen.h"

Screen::Screen(Display *display, Joystick *joystick)
{
    this->display = display;
    this->joystick = joystick;
}

void Screen::update(const double &delta)
{
    if (this->joystick->store_state())
    {
        this->on_joystick_changed();
    }
}
