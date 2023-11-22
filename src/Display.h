#ifndef DISPLAY.H
#define DISPLAY.H

#include "stdint.h"

class Display
{
    public:
        Display();
        void draw_circle(uint16_t x, uint8_t y, uint8_t circle_radius);
        void clear_circle(uint16_t x, uint8_t y, uint8_t circle_radius);
};

#endif
