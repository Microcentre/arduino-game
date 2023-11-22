#include <IR.h>
#include <avr/interrupt.h>
#include <HardwareSerial.h>

IR::IR()
{
    DDRD |= (1 << DD6);  // set pin D6 (LED) as output
    DDRD &= ~(1 << DD2); // set pin D2 (sensor) as input

    TCCR0A |= (1 << WGM01);  // CTC
    TIMSK0 |= (1 << OCIE0A); // interrupt on comp A
    OCR0A = BLINK_DURATION;

    EIMSK |= (1 << INT0);  // enable interrupts on int0
    EICRA |= (1 << ISC00); // interrupt on any logical change
}

uint8_t IR::is_communicating() {
    return communicating;
}

void IR::set_communicating(uint8_t value) {
    communicating = value;
}

uint8_t IR::is_bit_ready() {
    return bit_ready;
}

void IR::set_bit_ready(uint8_t value) {
    bit_ready = value;
}

void IR::send_data(uint8_t data)
{
    // send start bit, data, (parity bit), stop bit
}

void IR::read_data()
{
    //
}

void IR::start_blinking()
{
    TCCR0B |= (1 << CS00);
    TCNT0 = 0;
}

void IR::start_signal_timer()
{
    TCNT1 = 0;
    TCCR1B |= (1 << CS10); // enable timer1 with no prescaler
}

void IR::read_bit()
{
    TCCR1B &= ~(1 << CS10); // disable timer1
    uint16_t duration = TCNT1;
    Serial.println(duration);
    if (duration == ZERO_DURATION)
    {
        // signal was zero, write to buffer
        input_buffer <<= 1;
    }
    else if (duration == ONE_DURATION)
    {
        // signal was one, write to buffer
        input_buffer <<= 1;
        input_buffer |= 1;
    }
    else
    {
        // signal was junk, disregard
    }
}