#ifndef JOYSTICK_H
#define JOYSTICK_H

#include <avr/io.h>

class Joystick
{
public:
    Joystick();

    /// @brief Update joystick data with new states.
    /// This updates ALL states, including joystick & buttons.
    /// @return true if succeeded, false if failed to read memory
    bool store_state();

    /// @return [-1..1] where -1=left, 0=centre, 1=right
    float get_x_axis();

    /// @return [-1..1] where -1=bottom, 0=centre, 1=top
    float get_y_axis();

    /// @return if C button is pressed
    bool is_c_pressed();

    /// @return if Z button is pressed
    bool is_z_pressed();
private:
    // the highest value the axis can be 
    const uint8_t MAX_AXIS = 255;
    // const uint8_t MAX_X_AXIS = 252;
    // const uint8_t MAX_Y_AXIS = 253;
};

#endif
