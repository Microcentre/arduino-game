#ifndef JOYSTICK_H
#define JOYSTICK_H

#include <avr/io.h>

class Joystick
{
    public:
        Joystick();
        bool store_state(void);
        uint8_t get_x(void);
        uint8_t get_y(void);
        bool get_c(void);
        bool get_z(void);
};

#endif