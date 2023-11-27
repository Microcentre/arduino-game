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
    bool store_state(void);

    /// @brief Get the X-axis from the joystick
    /// Update states with store_state() first to get new data.
    /// @return Y-axis from current state
    uint8_t get_x_axis(void);

    /// @brief Get the Y-axis from the joystick
    /// Update states with store_state() first to get new data.
    /// @return Y-axis from current state
    uint8_t get_y_axis(void);

    /// @brief Get the state of the C button
    /// Update states with store_state() first to get new data.
    /// @return if C button is pressed
    bool is_c_pressed(void);

    /// @brief Get the state of the Z button
    /// Update states with store_state() first to get new data.
    /// @return if Z button is pressed
    bool is_z_pressed(void);
};

#endif