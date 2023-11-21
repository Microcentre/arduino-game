#ifndef DISPLAY.H
#define DISPLAY.H

#include "stdint.h"

class Display
{
    public:
        Display();
        unsigned long draw_circle(uint8_t x, uint8_t y);
        unsigned long clear_circle(uint8_t x, uint8_t y);
};

#endif