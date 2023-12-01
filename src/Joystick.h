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

    /// @return [3...252] where 3=left, 128=centre, 252=right
    uint8_t get_x_axis();

    /// @return [2...253] where 2=bottom, 128=centre, 253=top
    uint8_t get_y_axis();

    /// @return if C button is pressed
    bool is_c_pressed();

    /// @return if Z button is pressed
    bool is_z_pressed();
};

#endif
