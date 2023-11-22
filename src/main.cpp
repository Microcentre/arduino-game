#include <avr/io.h>
#include <avr/interrupt.h>
#include <IR.h>
#include <HardwareSerial.h>

IR infrared;

ISR(TIMER0_COMPA_vect)
{
    PORTD ^= (1 << PD6);
}

ISR(INT0_vect)
{
    if (PIND & (1 <<PIND2))
    {
        infrared.start_signal_timer();
    }
    else
    {
        infrared.read_bit();
    }
}

int main()
{
    sei();
    Serial.begin(9600);
    IR infrared = IR();
    // infrared.start_blinking();
    while (1)
    {
    }
    return 0;
}
