#include "Display.h"
#include "Adafruit_ILI9341.h"

Display::Display()
{
    // use spi to start communicating with display
    this->canvas.begin();
    // set horizontal position
    this->canvas.setRotation(1);
    
    // colour entire screen black
    this->background_colour = ILI9341_BLACK;
    this->canvas.fillScreen(this->background_colour);
}
