#include "Display.h"
#include "SPI.h"
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"

// For the Adafruit shield, these are the default.
#define TFT_DC 9
#define TFT_CS 10

// Use hardware SPI (on Uno, #13, #12, #11) and the above for CS/DC
Adafruit_ILI9341 display = Adafruit_ILI9341(TFT_CS, TFT_DC);

Display::Display()
{
    // use spi to start communicating with display
    display.begin();

    // set horizontal position
    display.setRotation(1);

    // color full screen black
    display.fillScreen(ILI9341_BLACK);
}

void Display::draw_circle(uint16_t x, uint8_t y, uint8_t circle_radius)
{
    display.fillCircle(x, y, circle_radius, ILI9341_WHITE);
}

void Display::clear_circle(uint16_t x, uint8_t y, uint8_t circle_radius)
{
    display.fillCircle(x, y, circle_radius, ILI9341_BLACK);
}
