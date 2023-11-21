#ifndef JOYSTICK_H
#define JOYSTICK_H

#include <avr/io.h>

class Joystick
{
    public:
    Joystick();
    bool show_memory(void);
    bool show_state(void);
    bool store_state(void);
    bool show_calibration(void);
    void show_info(void);
    uint8_t get_x(void);
    uint8_t get_y(void);
    bool get_c(void);
    bool get_z(void);
    private:
    protected:
};
#endif