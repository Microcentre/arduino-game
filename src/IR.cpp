#include <IR.h>
#include <avr/interrupt.h>

volatile int counter = 0;

ISR(TIMER1_COMPA_vect)
{
    PORTD ^= (1 << PD6);
}

ISR(INT0_vect)
{
}

IR::IR()
{
    DDRD |= (1 << DD6);  // set pin D6 (LED) as output
    DDRD &= ~(1 << DD2); // set pin D2 (sensor) as input

    TCCR1B |= (1 << WGM12);  // CTC mode
    TIMSK1 |= (1 << OCIE1A); // interrupt on comp A
    OCR1A = 211; // 16000000/56000 = 421/2 = 211

    EIMSK |= (1 << INT0);
    EICRA |= (1 << ISC00);
}

void IR::startBlinking()
{
    TCCR1B |= (1 << CS10);
    TCNT1 = 0;
}