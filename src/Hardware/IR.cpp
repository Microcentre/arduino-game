#include <avr/interrupt.h>
#include <HardwareSerial.h>

#include "IR.h"

IR::IR()
{
    // initialize properties
    flags = 0;
    input_buffer = 0;
    timer_start = 0;
    received_bits = 0;
    received_data = 0;
    received_message = 0;

    DDRD |= (1 << DD6);  // set pin D6 (LED) as output
    DDRD &= ~(1 << DD2); // set pin D2 (sensor) as input

    // setup timer 0, used for blinking the IR LED
    TCCR0A |= (1 << COM0A0) | (1 << WGM01); // CTC
    OCR0A = BLINK_DURATION;

    // set up timer 1, used for setting and reading IR signal length
    OCR1A = PULSE_DURATION + START_DURATION; // set comp A to the largest real signal
                                             // to ensure it does not trigger prematurely

    TCCR1B |= (1 << WGM12);                  // CTC
    TIMSK1 |= (1 << OCIE1A) | (1 << OCIE1B); // interrupt on comp A and B
    OCR1B = PULSE_DURATION;

    EIMSK |= (1 << INT0);  // enable interrupts on int0
    EICRA |= (1 << ISC00); // interrupt on any logical change

    start_signal_timer();
}

void IR::start_blinking()
{
    TCCR0B |= (1 << CS00); // enable timer0 with no prescaler
    TCNT0 = 0;
}

void IR::stop_blinking()
{
    TCCR0B &= ~(1 << CS00); // disable timer 0
    TCNT0 = 0;
    PORTD &= ~(1 << PD6); // turn the IR LED off
}

void IR::start_signal_timer()
{
    TCNT1 = 0;
    TCCR1B |= (1 << CS10); // enable timer1 with no prescaler
}

void IR::stop_signal_timer()
{
    TCNT1 = 0;
    TCCR1B &= ~(1 << CS10); // disable timer1
}

uint16_t IR::get_output_buffer()
{
    return output_buffer;
}

void IR::shift_output_buffer()
{
    output_buffer >>= 1;
}

uint8_t IR::get_input_buffer()
{
    return input_buffer;
}

void IR::set_input_buffer(uint8_t value)
{
    input_buffer = value;
}

// Shift input_buffer left once, and set LSB to the given value
void IR::push_input_buffer(uint8_t value)
{
    input_buffer <<= 1;
    input_buffer |= value;
    inc_received_bits();
}

uint16_t IR::get_timer_start()
{
    return timer_start;
}

void IR::set_timer_start(uint16_t value)
{
    timer_start = value;
}

uint8_t IR::get_received_bits()
{
    return received_bits;
}

void IR::set_received_bits(uint8_t value)
{
    received_bits = value;
}

void IR::inc_received_bits()
{
    received_bits++;
}

void IR::send_data(uint32_t data)
{
    uint8_t set_bits = 0;
    uint8_t parity_bit = 0;
    uint32_t to_send = 0;

    // if there's already data being sent, don't send new data
    if (get_flags() & IR::Flags::SENDING_MESSAGE || get_flags() & IR::Flags::MESSAGE_PENDING)
    {
        return;
    }

    // check how many bits in the data are set to 1
    for (uint32_t i = 0; i < DATA_SIZE; i++)
    {
        if (data & ((uint32_t)1 << i))
        {
            set_bits++;
        }
    }
    parity_bit = set_bits % 2; // 0 if even, 1 if uneven,
                               // so the full data including parity bit should always be even

    // set stop bit, parity bit, data bits and start bit
    // in that order, because they're sent LSB-first
    to_send |= STOP_BIT;
    to_send <<= 1;
    to_send |= parity_bit;
    to_send <<= DATA_SIZE;
    to_send |= data;
    to_send <<= 1;
    to_send |= START_BIT;
    output_buffer = to_send;
    set_flag(IR::Flags::MESSAGE_PENDING);
}

void IR::send_player_data(uint16_t pos_x, uint8_t pos_y, uint16_t dir, uint8_t flags)
{
    uint32_t data = 0;
    data |= pos_x;
    data <<= DATA_POS_Y_SIZE;
    data |= pos_y;
    data <<= DATA_DIR_SIZE;
    data |= dir;
    data <<= DATA_FLAGS_SIZE;
    data |= flags;
    send_data(data);
}

void IR::interpret_data()
{
    uint8_t set_bits = 0;
    uint8_t parity_bit = (received_message & PARITY_MASK) >> 1;
    uint32_t data = (received_message & RECEIVE_DATA_MASK) >> 2; // remove start, stop and parity

    // check how many bits in the received data are set to 1
    for (uint8_t i = 0; i < DATA_SIZE; i++)
    {
        if (data & ((uint32_t)1 << i))
        {
            set_bits++;
        }
    }
    // are stop bit and start bit set, and does the parity match?
    if (input_buffer & 0x01 && input_buffer >> (MESSAGE_SIZE - 1) && set_bits % 2 == parity_bit)
    {
        // valid data
        received_data = reverse_data(data);
    }
    clear_flag(IR::Flags::MESSAGE_RECEIVED);
    input_buffer = 0;
}

uint32_t IR::reverse_data(uint32_t data)
{
    uint32_t result = 0;

    for (uint8_t i = 0; i < DATA_SIZE; i++)
    {
        result <<= 1;
        result |= data & 0x01;
        data >>= 1;
    }
    return result;
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

void IR::set_received_message_to_input_buffer()
{
    received_message = input_buffer;
}

uint32_t IR::get_received_data()
{
    return received_data;
}

void IR::set_received_data(uint32_t value)
{
    received_data = value;
}
