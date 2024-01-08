#include "Screen.h"

Screen::Screen(Display *display, Joystick *joystick, IR *infrared)
{
    this->display = display;
    this->joystick = joystick;
    this->infrared = infrared;
}

void Screen::update(const double &delta)
{
    if (this->joystick->store_state())
        this->on_joystick_changed();
}
