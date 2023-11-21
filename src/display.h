#ifndef DISPLAY.H
#define DISPLAY.H

#include "stdint.h"

class Display
{
    public:
        Display();
        unsigned long draw_circle(uint16_t x, uint8_t y, uint8_t circle_radius);
        unsigned long clear_circle(uint16_t x, uint8_t y, uint8_t circle_radius);
};

#endif