#include "display.h"
#include "SPI.h"
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"

// For the Adafruit shield, these are the default.
#define TFT_DC 9
#define TFT_CS 10

// Use hardware SPI (on Uno, #13, #12, #11) and the above for CS/DC
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);

Display::Display()
{

     Serial.println("start");
    //use spi to start communicating with display
    tft.begin();
    
    Serial.println("end!");
    //set horizontal position
    tft.setRotation(1);

    //color full screen black
    tft.fillScreen(ILI9341_BLACK);
    
}

unsigned long Display::DrawCircle(uint8_t x, uint8_t y){
    // start time of function is stored
    unsigned long start = micros();

    uint8_t width = 100;
    uint8_t height = 100;
    uint8_t radius = 5;

    // center of display in position 1: x = 170, y = 120
    tft.fillCircle(x, y, radius, ILI9341_WHITE);

   // return how long the function took to complete
    return micros() - start;
}

unsigned long Display::ClearCircle(uint8_t x, uint8_t y){
    // start time of function is stored
    unsigned long start = micros();

    uint8_t width = 100;
    uint8_t height = 100;
    uint8_t radius = 5;

    // center of display in position 1: x = 170, y = 120
    tft.fillCircle(x, y, radius, ILI9341_BLACK);

   // return how long the function took to complete
    return micros() - start;
}