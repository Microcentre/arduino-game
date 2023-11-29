#ifndef DISPLAY_H
#define DISPLAY_H

#include "Adafruit_ILI9341.h"

// For the Adafruit Shield, these are the default 
// chip select pin
#define TFT_CS 10
// data/command pin
#define TFT_DC 9 

class Display
{
    public:
        static const uint16_t HEIGHT_PIXELS = 240;
        static const uint16_t WIDTH_PIXELS = 320;

        /// @brief library used for drawing on the screen
        /// Use hardware SPI (on Uno, #13, #12, #11) and the above for CS/DC
        Adafruit_ILI9341 canvas = Adafruit_ILI9341(TFT_CS, TFT_DC);

        /// @brief use constants prefixed with "ILI9341_", ex "ILI9341_BLACK"
        uint16_t background_colour;

        Display();
};

#endif
