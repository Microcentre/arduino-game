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

void Display::draw_centred_text(Display *display, const String &text, uint16_t x_pos, uint8_t y_pos)
{
    int16_t temp_x_pos;
    int16_t temp_y_pos;
    uint16_t width;
    uint16_t height;
    display->canvas.getTextBounds(text, x_pos, y_pos, &temp_x_pos, &temp_y_pos, &width, &height);

    // calculate centre and set cursor there
    auto new_x_pos = x_pos - (width / 2);
    auto new_y_pos = y_pos - (height / 2);
    display->canvas.setCursor(new_x_pos, new_y_pos);

    // print 😎
    display->canvas.print(text);
}
