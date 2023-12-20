#include "Buzzer.h"

Buzzer::Buzzer()
{
    DDRD |= (1 << DD3); // set buzzer port as output
}

void Buzzer::medium_beep()
{
    TCCR2A |= (1 << COM2B0); // toggle OC2B on compare match
    _delay_ms(100);
    TCCR2A &= ~(1 << COM2B0); // normal operation, OC2B disconnected.
}

void Buzzer::short_beep()
{
    TCCR2A |= (1 << COM2B0); // toggle OC2B on compare match
    _delay_ms(10);
    TCCR2A &= ~(1 << COM2B0); // normal operation, OC2B disconnected.
}