#ifndef SCREEN_H
#define SCREEN_H

#include "Display.h"
#include "Joystick.h"

class Screen{
    public:
        Screen(const Display *display, const Joystick *joystick);
        /// @brief update method, checks if joystick has changed
        /// @param delta time since last frame in seconds
        virtual void update(const double &delta);
        //called whenever the state of the joystick changes, should be implemented in child classes
        virtual void on_joystick_update() = 0;

    protected:
        /// @brief pointer to display property, used for drawing on the screen 
        const Display *display;
        /// @brief pointer to joystick property, used for input
        const Joystick *joystick;
};


#endif