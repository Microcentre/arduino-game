#include "ShowHealthOnSSD.h"

ShowHealthOnSSD::ShowHealthOnSSD(Player *Player)
{
    update(Player);
}

void ShowHealthOnSSD::update(Player *Player)
{
    Wire.beginTransmission(0x21);               // start transmission to slave (I/O expander)
    Wire.write(DISPLAY_DIGITS[Player->health]); // send digit to display
    Wire.endTransmission();                     // close connection
}