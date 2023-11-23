#include <avr/io.h>
#include <avr/interrupt.h>
#include <IR.h>
#include <HardwareSerial.h>

IR infrared;
IR *p_infrared;

ISR(TIMER0_COMPA_vect)
{
    PORTD ^= (1 << PD6);
}

ISR(TIMER1_COMPA_vect)
{
    if (p_infrared->get_flags() & IR_FLAG_SENDING_PULSES)
    {
        p_infrared->clear_flag(IR_FLAG_SENDING_PULSES);
    }
    else
    {
        p_infrared->set_flag(IR_FLAG_SENDING_PULSES);
    }
    TCNT1 = 0;
}

ISR(INT0_vect)
{
    // if (!(p_infrared->get_flags() & IR_FLAG_START_READING))
    // {
    //     p_infrared->set_flag(IR_FLAG_START_READING);
    // }
    // if (!(PIND & (1 << PIND2)))
    // {
    //     p_infrared->set_flag(IR_FLAG_BIT_READY);
    // }
    // else
    // {
    //     p_infrared->start_signal_timer();
    // }
}

int main()
{
    IR infrared = IR();
    p_infrared = &infrared;
    sei();
    Serial.begin(9600);
    while (1)
    {
        // infrared.read_data();
        infrared.send_data(0b10101010);
    }
    return 0;
}
