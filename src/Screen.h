#ifndef SCREEN_H
#define SCREEN_H

#include "Hardware/Display.h"
#include "Hardware/Joystick.h"
#include "Hardware/IR/IR.h"

class Screen
{
public:
    Screen(Display *display, Joystick *joystick, IR *infrared);

    /// @brief update method, checks if joystick has changed
    /// @param delta time since last frame in seconds
    virtual void update(const double &delta);

    /// @brief called whenever the state of the joystick changes, must be implemented in child classes
    virtual void on_joystick_changed() = 0;

    /// @brief if true, the screen is switched to the next screen
    /// from the PlayerSelectScreen to GameScreen to HighScoreScreen back to PlayerSelectScreen again
    bool ready_for_screen_switch = false;

protected:
    /// @brief pointer to display property, used for drawing on the screen
    Display *display;

    /// @brief pointer to joystick property, used for player input
    Joystick *joystick;

    /// @brief pointer to infrared property, used for communication to other player
    IR *infrared;
};

#endif