#include "Buzzer.h"

Buzzer::Buzzer()
{
    DDRD |= (1 << DD3);//set buzzer port as output
    
    TCCR2B |= (1 << CS21) | (1 << CS20);//1/32 prescaler
    
    TCCR2A |= (0 << WGM21); // CTC mode

    OCR2A = 255;
    OCR2B = 1;
}

void Buzzer::meduim_beep()
{
    TCCR2A |= (1<<COM2B0);//toggle OC2B on compare match
    _delay_ms(200);
    TCCR2A &= ~(1<<COM2B0);//normal operation, OC2B disconnected.
}

void Buzzer::short_beep()
{
    TCCR2A |= (1<<COM2B0);//toggle OC2B on compare match
    _delay_ms(25);
    TCCR2A &= ~(1<<COM2B0);//normal operation, OC2B disconnected.
}