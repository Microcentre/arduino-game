#include <IR.h>
#include <avr/interrupt.h>
#include <HardwareSerial.h>

volatile int counter = 0;

ISR(TIMER1_COMPA_vect) {
    PORTD ^= (1 << DD6);
}


IR::IR() {
    DDRD |= (1 << DD6); // set pin D6 (LED) as output
    DDRD &= ~(1 << DD2); // set pin D2 (sensor) as input

    TCCR1B |= (1 << WGM12);  // CTC mode
    TIMSK1 |= (1 << OCIE1A); // interrupt on comp A
    OCR1A = 143;
}

void IR::startBlinking() {
    TCCR1B |= (1 << CS10);
    TCNT1 = 0;
}