#ifndef SCREEN_H
#define SCREEN_H

#include "Display.h"
#include "Joystick.h"
#include "IR.h"

class Screen
{
public:
    Screen(Display *display, Joystick *joystick, IR *infrared);
    /// @brief update method, checks if joystick has changed
    /// @param delta time since last frame in seconds
    virtual void update(const double &delta);
    // called whenever the state of the joystick changes, should be implemented in child classes
    virtual void on_joystick_changed() = 0;

    bool ready_for_screen_switch = false;

protected:
    /// @brief pointer to display property, used for drawing on the screen
    Display *display;
    /// @brief pointer to joystick property, used for input
    Joystick *joystick;

    IR *infrared;
};

#endif