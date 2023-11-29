#include <avr/io.h>
#include <util/delay.h>
#include <Wire.h>
#include <HardwareSerial.h>
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

float Joystick::get_x_axis()
{
    // state.joy_x_axis = [3...252] where 3=left, 128=centre, 252=right
    float normalised_x_axis = (float)Nunchuk.state.joy_x_axis / this->MAX_AXIS; // normalise to [0..1]
    return (normalised_x_axis * 2) - 1; // scale to [0..2] and shift to [1..2]
}

float Joystick::get_y_axis()
{
    // state.joy_y_axis = [2...253] where 2=bottom, 128=centre, 253=top
    float normalised_y_axis = (float)Nunchuk.state.joy_y_axis / this->MAX_AXIS; // normalise to [0..1]
    return (normalised_y_axis * 2) - 1; // scale to [0..2] and shift to [1..2]
}

bool Joystick::is_c_pressed()
{
    return Nunchuk.state.c_button;
}

bool Joystick::is_z_pressed()
{
    return Nunchuk.state.z_button;
}
