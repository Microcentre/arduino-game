#include <avr/io.h>
#include <util/delay.h>
#include <Wire.h>
#include <Nunchuk.h>

#include "Joystick.h"

#define NUNCHUK_ADDRESS 0x52
#define CHUNKSIZE 32
#define BUFFERLEN 256
#define WAIT 1000

Joystick::Joystick()
{
    // join I2C bus as master
    Wire.begin();

    // handshake with nunchuk
    if (!Nunchuk.begin(NUNCHUK_ADDRESS))
    {
        return;
    }
}

bool Joystick::store_state()
{
    if (!Nunchuk.getState(NUNCHUK_ADDRESS))
        return false;
    return true;
}

uint8_t Joystick::get_x_axis()
{
    return Nunchuk.state.joy_x_axis;
}

uint8_t Joystick::get_y_axis()
{
    return Nunchuk.state.joy_y_axis;
}

bool Joystick::is_c_pressed()
{
    return Nunchuk.state.c_button;
}

bool Joystick::is_c_first_pressed()
{
    return is_c_pressed() && !(c_pressed_last_frame);
}

bool Joystick::is_z_pressed()
{
    return Nunchuk.state.z_button;
}

bool Joystick::is_z_first_pressed()
{
    return is_z_pressed() && !(z_pressed_last_frame);
}
