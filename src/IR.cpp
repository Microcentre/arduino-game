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
    
    OCR1B = PULSE_DURATION + ONE_DURATION;
    TCCR1B |= (1 << WGM12); // CTC
    TIMSK1 |= (1 << OCIE1A) | (1 << OCIE1B); // interrupt on comp A and B
    OCR1B = PULSE_DURATION;

    EIMSK |= (1 << INT0);  // enable interrupts on int0
    EICRA |= (1 << ISC00); // interrupt on any logical change
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

uint16_t IR::get_output_buffer()
{
    return output_buffer;
}

void IR::shift_output_buffer()
{
    output_buffer >>= 1;
}

void IR::write_to_input_buffer(uint8_t value)
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
    set_flag(IR_FLAG_SENDING_PULSES);
    clear_flag(IR_FLAG_READY_TO_SEND);
    start_blinking();
    OCR1A = PULSE_DURATION;
    start_signal_timer();
    TIMSK1 |= (1 << OCIE1A);
    do
    {
        PORTD ^= (1 << PD7);
    } while (get_flags() & IR_FLAG_SENDING_PULSES);
    TIMSK1 &= ~(1 << OCIE1A);
    if (bit)
        OCR1A = ONE_DURATION;
    else
        OCR1A = ZERO_DURATION;
    stop_blinking();
    TIMSK1 |= (1 << OCIE1A);
    while (!(get_flags() & IR_FLAG_SENDING_PULSES))
    {
        PORTD ^= (1 << PD7);
    }
    TIMSK1 &= ~(1 << OCIE1A);
    stop_signal_timer();
    set_flag(IR_FLAG_READY_TO_SEND);
}

void IR::read_data()
{
    if (!(get_flags() & IR_FLAG_START_READING))
    {
        return;
    }
    for (int i = 0; i < MESSAGE_SIZE; i++)
    {
        while (!(get_flags() & IR_FLAG_BIT_READY))
        {
        }
        read_bit();
    }
    interpret_data();
    clear_flag(IR_FLAG_START_READING);
}

void IR::send_data(uint8_t data)
{
    const uint8_t DATA_SIZE = sizeof(data) * 8;
    uint8_t set_bits = 0;
    uint8_t parity_bit = 0;
    uint16_t to_send = 0;

    if ((get_flags() & IR_FLAG_READY_TO_SEND)) {
        return;
    }
    for (uint8_t i = 0; i < DATA_SIZE; i++)
    {
        if (data & (1 << i))
        {
            set_bits++;
        }
    }
    parity_bit = set_bits % 2; // 0 if even, 1 if uneven,
                               // so the full data including parity bit should always be even

    // set stop bit, parity bit, data bits and start bit
    // in that order, because they're sent in reverse
    to_send |= STOP_BIT;
    to_send <<= 1;
    to_send |= parity_bit;
    to_send <<= DATA_SIZE;
    to_send |= data;
    to_send <<= 1;
    to_send |= START_BIT;

    output_buffer = to_send;
    start_signal_timer();
    // start_blinking();  
    set_flag(IR_FLAG_READY_TO_SEND);
    // now set up the timer to actually start sending data

    // for (int8_t i = MESSAGE_SIZE - 1; i >= 0; i--)
    // {
    //     send_bit((to_send >> i) & 0x01);
    //     while (~(get_flags() | ~IR_FLAG_READY_TO_SEND))
    //     {
    //     }
    // }
}

void IR::interpret_data()
{
    uint8_t set_bits = 0;
    uint8_t parity_bit = input_buffer & PARITY_MASK;
    uint8_t data = (input_buffer & DATA_MASK) >> 2; // remove start, stop and parity
    const uint8_t DATA_SIZE = sizeof(data) * 8;

    for (uint8_t i = 0; i < DATA_SIZE; i++)
    {
        if (data & (1 << i))
        {
            set_bits++;
        }
    }
    // are stop bit and start bit set?
    if (input_buffer & 0x01 && input_buffer >> (MESSAGE_SIZE - 1) && set_bits % 2 && parity_bit)
    {
        // valid data
        Serial.println(data);
    }
    else
    {
        // invalid data
        Serial.println("garbage");
    }
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
