#ifndef JOYSTICK_H
#define JOYSTICK_H

#include <avr/io.h>

class Joystick
{
    public:
        Joystick();
        bool store_state(void);
        uint8_t get_x_axis(void);
        uint8_t get_y_axis(void);
        bool is_c_pressed(void);
        bool is_z_pressed(void);
};

#endif