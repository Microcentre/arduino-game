#ifndef DISPLAY.H
#define DISPLAY.H

#include "stdint.h"

class Display
{
    public:
        Display();
        unsigned long DrawCircle(uint8_t x, uint8_t y);
        unsigned long ClearCircle(uint8_t x, uint8_t y);
};

#endif