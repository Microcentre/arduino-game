#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <Vector.h>

#include "IR.h"
#include "Joystick.h"
#include "Player.h"
#include "Display.h"
#include "MovingObject.h"
#include "Object.h"
#include "Screens/GameScreen.h"

// time to wait between each frame.
// to minimise redraw flicker.
// 50fps if each frame were to instantly generate.
const uint8_t SCREEN_DELAY_MS = 20;
/// @brief approximate delta in seconds (time since last frame)
const double DELTA = (double)SCREEN_DELAY_MS / 1000;

IR *p_infrared;

ISR(TIMER0_COMPA_vect)
{
    PORTD ^= (1 << PD6);
}

ISR(TIMER1_COMPB_vect)
{
    if (p_infrared->get_flags() & IR::Flags::SENDING_MESSAGE)
    {
        // stop bit is 1, so the output buffer will
        // only be 0 if there is nothing left to send
        if (p_infrared->get_output_buffer() == 0)
        {
            p_infrared->clear_flag(IR::Flags::SENDING_MESSAGE);
            p_infrared->stop_blinking();
        }

        // set the rest duration based on what is
        // currently being sent
        if (p_infrared->get_flags() & IR::Flags::SENDING_START)
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
    if (p_infrared->get_flags() & IR::Flags::SENDING_MESSAGE)
    {
        p_infrared->start_blinking();
        if (p_infrared->get_flags() & IR::Flags::SENDING_START)
        {
            p_infrared->clear_flag(IR::Flags::SENDING_START);
        }
        else
        {
            // make room in the output buffer for the next bit
            // by shifting it to the left once
            p_infrared->shift_output_buffer();
        }
    }
    else if (p_infrared->get_flags() & IR::Flags::MESSAGE_PENDING)
    {
        // start sending a message on the next timer cycle
        p_infrared->clear_flag(IR::Flags::MESSAGE_PENDING);
        p_infrared->set_flag(IR::Flags::SENDING_MESSAGE);
        p_infrared->set_flag(IR::Flags::SENDING_START);
        p_infrared->start_blinking();
    }
}

ISR(INT0_vect)
{
    static uint16_t timer_diff;
    if (!(p_infrared->get_flags() & IR::Flags::MESSAGE_RECEIVED))
    {
        if (!(PIND & (1 << PIND2)))
        {
            // signal is low, indicating the start of a pulse burst

            // measure the rest length
            // it's possible the timer was cleared since timer_start was set,
            // indicated by the counter being lower than the start value
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
                // signal is START
                p_infrared->set_received_bits(0);
                p_infrared->set_input_buffer(0);
            }
            else
            {
                if (timer_diff <= ONE_DURATION + SIGNAL_DEVIATION && timer_diff >= ONE_DURATION - SIGNAL_DEVIATION)
                {
                    // signal is ONE
                    p_infrared->push_input_buffer(1);
                }
                else if (timer_diff <= ZERO_DURATION + SIGNAL_DEVIATION && timer_diff >= ZERO_DURATION - SIGNAL_DEVIATION)
                {
                    // signal is ZERO
                    p_infrared->push_input_buffer(0);
                }
                else
                {
                    // signal is junk
                    p_infrared->set_received_bits(0);
                    p_infrared->set_input_buffer(0);
                }
            }

            if (p_infrared->get_received_bits() >= MESSAGE_SIZE)
            {
                p_infrared->set_received_bits(0);
                // message is complete, interpret it
                p_infrared->set_flag(IR::Flags::MESSAGE_RECEIVED);
            }
        }
        else
        {
            // signal is high, indicating the start of a rest
            // store the current timer value to measure the
            // signal length
            p_infrared->set_timer_start(TCNT1);
        }
    }
}

void setup()
{
    p_infrared = new IR(); // created as pointer so the ISRs can access it
    sei();
}

int main()
{
    setup();

    const Display display = Display();
    const Joystick joystick = Joystick();

    GameScreen game = GameScreen(&display,&joystick);

    // game loop
    while (1)
    {
        game.update(DELTA);

        _delay_ms(SCREEN_DELAY_MS);

        // p_infrared->send_data(0b10101011);
        // if (p_infrared->get_flags() & IR::Flags::MESSAGE_RECEIVED)
        // {
        //     p_infrared->interpret_data();
        // }
    }
    return (0);
}
