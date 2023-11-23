#include <IR.h>
#include <avr/interrupt.h>
#include <HardwareSerial.h>

IR::IR()
{
    flags = 0;
    DDRD |= (1 << DD6); // set pin D6 (LED) as output
    DDRD |= (1 << DD7);
    DDRD &= ~(1 << DD2); // set pin D2 (sensor) as input

    TCCR0A |= (1 << WGM01);  // CTC
    TIMSK0 |= (1 << OCIE0A); // interrupt on comp A
    OCR0A = BLINK_DURATION;

    EIMSK |= (1 << INT0);  // enable interrupts on int0
    EICRA |= (1 << ISC00); // interrupt on any logical change
}

uint8_t IR::get_flags()
{
    return flags;
}

void IR::set_flag(uint8_t flag)
{
    flags |= flag;
}

void IR::clear_flag(uint8_t flag)
{
    flags &= ~flag;
}

void IR::send_data(uint8_t data)
{
    uint8_t set_bits = 0;
    uint8_t parity_bit = 0;
    uint16_t to_send = 0;

    TIMSK1 |= (1 << OCIE1A);

    // send start bit, data, (parity bit), stop bit
    to_send |= START_BIT;
    to_send <<= (sizeof(data) * 8);
    to_send |= data;
    for (uint8_t i = 0; i < sizeof(data) * 8; i++)
    {
        if (data & (1 << i))
        {
            set_bits++;
        }
    }
    parity_bit = set_bits % 2; // 0 if even, 1 if uneven,
                               // so the full data including parity bit should always be even
    to_send <<= 1;
    to_send |= parity_bit;
    to_send <<= 1;
    to_send |= STOP_BIT;
    for (uint8_t i = 0; i < 10; i++)
    {
        send_bit((to_send >> i) & 0x01);
        while (~(get_flags() | ~IR_FLAG_READY_TO_SEND))
        {
        }
    }
    TIMSK1 &= ~(1 << OCIE1A);
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

void IR::stop_blinking()
{
    TCCR0B &= ~(1 << CS00);
    TCNT0 = 0;
    PORTD &= ~(1 << PD6);
}

void IR::start_signal_timer()
{
    TCNT1 = 0;
    TCCR1B |= (1 << CS10); // enable timer1 with no prescaler
}

void IR::stop_signal_timer()
{
    TCNT1 = 0;
    TCCR1B &= ~(1 << CS10); // disable timer1 with no prescaler
}

void IR::read_bit()
{
    stop_signal_timer();
    uint16_t duration = TCNT1;
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

void IR::send_bit(uint8_t bit)
{
    clear_flag(IR_FLAG_READY_TO_SEND);
    set_flag(IR_FLAG_SENDING_PULSES);
    start_blinking();
    OCR1A = PULSE_DURATION;
    start_signal_timer();

    do
    {
        PORTD ^= (1 << PD7);
    } while (get_flags() & IR_FLAG_SENDING_PULSES);

    if (bit)
        OCR1A = ONE_DURATION;
    else
        OCR1A = ZERO_DURATION;
    stop_blinking();

    while (!(get_flags() & IR_FLAG_SENDING_PULSES))
    {
        PORTD ^= (1 << PD7);
    }
    stop_signal_timer();
    set_flag(IR_FLAG_READY_TO_SEND);
}