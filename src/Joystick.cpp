#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
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
    // enable global interrupts
    sei();

    // join I2C bus as master
    Wire.begin();

    // handshake with nunchuk
    if (!Nunchuk.begin(NUNCHUK_ADDRESS))
    {
        return;
    }
}

bool Joystick::store_state(void)
{
    if (!Nunchuk.getState(NUNCHUK_ADDRESS))
    {
        return (false);
    }
    return (true);
}

uint8_t Joystick::get_x()
{
    return Nunchuk.state.joy_x_axis;
}

uint8_t Joystick::get_y()
{
    return Nunchuk.state.joy_y_axis;
}

bool Joystick::get_c()
{
    return Nunchuk.state.c_button;
}

bool Joystick::get_z()
{
    return Nunchuk.state.z_button;
}