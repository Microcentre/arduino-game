#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <IR.h>
#include <HardwareSerial.h>

IR *p_infrared;

ISR(TIMER0_COMPA_vect)
{
    PORTD ^= (1 << PD6);
}

ISR(TIMER1_COMPB_vect)
{
    if (p_infrared->get_flags() & IR_FLAG_READY_TO_SEND)
    {
        // start bit is 1, so the output buffer will
        // only be 0 if there is nothing left to send
        if (p_infrared->get_output_buffer() == 0)
        {
            p_infrared->clear_flag(IR_FLAG_READY_TO_SEND);
            p_infrared->stop_blinking();
        }

        // what are we sending right now?
        if (p_infrared->get_flags() & IR_FLAG_SENDING_START)
        {
            OCR1A = PULSE_DURATION + START_DURATION;
        }
        else if (p_infrared->get_output_buffer() & 0x01)
        {
            OCR1A = PULSE_DURATION + ONE_DURATION;
        }
        else
        {
            OCR1A = PULSE_DURATION + ZERO_DURATION;
        }
        p_infrared->stop_blinking();
    }
}

ISR(TIMER1_COMPA_vect)
{
    if (p_infrared->get_flags() & IR_FLAG_READY_TO_SEND)
    {
        p_infrared->start_blinking();
        if (p_infrared->get_flags() & IR_FLAG_SENDING_START)
        {
            p_infrared->clear_flag(IR_FLAG_SENDING_START);
        }
        else
        {
            p_infrared->shift_output_buffer();
        }
    }
}

ISR(INT0_vect)
{
    static uint16_t timer_diff;
    if (!(p_infrared->get_flags() & IR_FLAG_MESSAGE_RECEIVED))
    {

        if (!(PIND & (1 << PIND2)))
        {
            if (TCNT1 < p_infrared->get_timer_start())
            {
                timer_diff = (OCR1A - p_infrared->get_timer_start()) + TCNT1;
            }
            else
            {
                timer_diff = TCNT1 - p_infrared->get_timer_start();
            }

            if (timer_diff <= START_DURATION + SIGNAL_DEVIATION && timer_diff >= START_DURATION - SIGNAL_DEVIATION)
            {
                p_infrared->set_flag(IR_FLAG_START_READING);
                p_infrared->set_received_bits(0);
                p_infrared->set_input_buffer(0);
            }
            else
            {
                if (timer_diff <= ONE_DURATION + SIGNAL_DEVIATION && timer_diff >= ONE_DURATION - SIGNAL_DEVIATION)
                {
                    p_infrared->push_input_buffer(1);
                }
                else if (timer_diff <= ZERO_DURATION + SIGNAL_DEVIATION && timer_diff >= ZERO_DURATION - SIGNAL_DEVIATION)
                {
                    p_infrared->push_input_buffer(0);
                }
            }

            if (p_infrared->get_received_bits() >= MESSAGE_SIZE)
            {
                p_infrared->set_received_bits(0);
                // message is complete, interpret it
                p_infrared->set_flag(IR_FLAG_MESSAGE_RECEIVED);
                p_infrared->clear_flag(IR_FLAG_START_READING);
            }
        }
        else
        {
            p_infrared->set_timer_start(TCNT1);
        }
    }
}

void setup()
{
    p_infrared = new IR();
    Serial.begin(9600);
    sei();
}

int main()
{
    setup();
    _delay_ms(20);
    while (1)
    {
        _delay_ms(20);
        p_infrared->send_data(0b11010011);
        _delay_ms(20);
        if (p_infrared->get_flags() & IR_FLAG_MESSAGE_RECEIVED)
        {
            p_infrared->interpret_data();
        }
    }
    return 0;
}
