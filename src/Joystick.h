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
    uint8_t getX(void);
    uint8_t getY(void);
    private:
    protected:
};
#endif