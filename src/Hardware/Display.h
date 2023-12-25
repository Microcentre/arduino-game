#ifndef DISPLAY_H
#define DISPLAY_H

#include "Adafruit_ILI9341.h"
#include <Adafruit_FT6206.h>

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

    /// @brief library used for reading touch input
    Adafruit_FT6206 touchscreen = Adafruit_FT6206();

    /// @brief use constants prefixed with "ILI9341_", ex "ILI9341_BLACK"
    uint16_t background_colour;

    Display();

    /// @brief HELPER FUNCTION: draw text centered at a given position
    /// @param text characters to display
    /// @param x_pos centered x position of text
    /// @param y_pos centered y position of text
    void draw_centred_text(const String &text, uint16_t x_pos, uint8_t y_pos);
};

#endif
