#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <Wire.h>
#include <HardwareSerial.h>
#include <Nunchuk.h>
#include "Joystick.h"

#define NUNCHUK_ADDRESS 0x52
#define BAUDRATE 9600
#define CHUNKSIZE 32
#define BUFFERLEN 256
#define WAIT 1000

//joystick what to show
#define STATE
//#define MEM
// #define CAL

Joystick::Joystick()
{
    // enable global interrupts
    sei();

    // use Serial for printing nunchuk data
    Serial.begin(BAUDRATE);

    // join I2C bus as master
    Wire.begin();

    // handshake with nunchuk
    Serial.print("-------- Connecting to nunchuk at address 0x");
    Serial.println(NUNCHUK_ADDRESS, HEX);
    if (!Nunchuk.begin(NUNCHUK_ADDRESS))
    {
        Serial.println("******** No nunchuk found");
        Serial.flush();
        return;
    }

    /*
     * get identificaton (nunchuk should be 0xA4200000)
     */
    Serial.print("-------- Nunchuk with Id: ");
    Serial.println(Nunchuk.id);
}

bool Joystick::show_memory(void)
{
    // print whole memory
    Serial.println("------ Whole memory------------------------");
    for (uint16_t n = 0; n < BUFFERLEN; n += CHUNKSIZE)
    {
        // read
        if (Nunchuk.read(NUNCHUK_ADDRESS, (uint8_t)n,
                         (uint8_t)CHUNKSIZE) != CHUNKSIZE)
            return (false);

        // print
        Serial.print("0x");
        if (n == 0)
            Serial.print("0");
        Serial.print(n, HEX);
        Serial.print(": ");
        for (uint8_t i = 0; i < CHUNKSIZE; i++)
        {
            if (Nunchuk.buffer[i] == 0)
                Serial.print('0');
            Serial.print(Nunchuk.buffer[i], HEX);
        }
        Serial.println("");
    }

    return (true);
}

bool Joystick::store_state(void)
{
    if (!Nunchuk.getState(NUNCHUK_ADDRESS))
        return (false);
    // Serial.println("------State data--------------------------");
    // Serial.print("Joy X: ");
    // Serial.print(Nunchuk.state.joy_x_axis);
    // Serial.print("\t\tAccel X: ");
    // Serial.print(Nunchuk.state.accel_x_axis, HEX);
    // Serial.print("\t\tButton C: ");
    // Serial.println(Nunchuk.state.c_button, HEX);

    // Serial.print("Joy Y: ");
    // Serial.print(Nunchuk.state.joy_y_axis);
    // Serial.print("\t\tAccel Y: ");
    // Serial.print(Nunchuk.state.accel_y_axis, HEX);
    // Serial.print("\t\tButton Z: ");
    // Serial.println(Nunchuk.state.z_button, HEX);

    // Serial.print("\t\t\tAccel Z: ");
    // Serial.println(Nunchuk.state.accel_z_axis, HEX);

    return (true);
}

uint8_t Joystick::get_x(){
    return Nunchuk.state.joy_x_axis;
}
uint8_t Joystick::get_y(){
    return Nunchuk.state.joy_y_axis;
}

bool Joystick::get_c(){
    return Nunchuk.state.c_button;
}

bool Joystick::get_z(){
    return Nunchuk.state.z_button;
}

bool Joystick::show_state(void)
{
    if (!Nunchuk.getState(NUNCHUK_ADDRESS))
        return (false);
    Serial.println("------State data--------------------------");
    Serial.print("Joy X: ");
    Serial.print(Nunchuk.state.joy_x_axis);
    Serial.print("\t\tAccel X: ");
    Serial.print(Nunchuk.state.accel_x_axis, HEX);
    Serial.print("\t\tButton C: ");
    Serial.println(Nunchuk.state.c_button, HEX);

    Serial.print("Joy Y: ");
    Serial.print(Nunchuk.state.joy_y_axis);
    Serial.print("\t\tAccel Y: ");
    Serial.print(Nunchuk.state.accel_y_axis, HEX);
    Serial.print("\t\tButton Z: ");
    Serial.println(Nunchuk.state.z_button, HEX);

    Serial.print("\t\t\tAccel Z: ");
    Serial.println(Nunchuk.state.accel_z_axis, HEX);

    return (true);
}

bool Joystick::show_calibration(void)
{
    if (!Nunchuk.getCalibration(NUNCHUK_ADDRESS))
        return (false);
    Serial.println("------Calibration data (unused)-----------");
    Serial.print("X-0G: 0x");
    Serial.print(Nunchuk.cal.x0, HEX);
    Serial.print("\tY-0G: 0x");
    Serial.print(Nunchuk.cal.y0, HEX);
    Serial.print("\tZ-0G: 0x");
    Serial.println(Nunchuk.cal.z0, HEX);
    Serial.print("X-1G: 0x");
    Serial.print(Nunchuk.cal.x1, HEX);
    Serial.print("\tY-1G: 0x");
    Serial.print(Nunchuk.cal.y1, HEX);
    Serial.print("\tZ-1G: 0x");
    Serial.println(Nunchuk.cal.z1, HEX);
    Serial.print("xmin: 0x");
    Serial.print(Nunchuk.cal.xmin, HEX);
    Serial.print("\txmax: 0x");
    Serial.print(Nunchuk.cal.xmax, HEX);
    Serial.print("\txcenter: 0x");
    Serial.println(Nunchuk.cal.xcenter, HEX);
    Serial.print("ymin: 0x");
    Serial.print(Nunchuk.cal.ymin, HEX);
    Serial.print("\tymax: 0x");
    Serial.print(Nunchuk.cal.ymax, HEX);
    Serial.print("\tycenter: 0x");
    Serial.println(Nunchuk.cal.ycenter, HEX);
    Serial.print("chksum: 0x");
    Serial.println(Nunchuk.cal.chksum, HEX);

    return (true);
}

void Joystick::show_info(void)
{
#ifdef STATE
    if (!show_state())
    {
        Serial.println("******** No nunchuk found");
        Serial.flush();
        return;
    }
#endif
#ifdef MEM
    if (!show_memory())
    {
        Serial.println("******** No nunchuk found");
        Serial.flush();
        return;
    }
#endif
#ifdef CAL
    if (!show_calibration())
    {
        Serial.println("******** No nunchuk found");
        Serial.flush();
        return;
    }
#endif

    // wait a while
    _delay_ms(WAIT);
}