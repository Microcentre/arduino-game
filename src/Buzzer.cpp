#include "Buzzer.h";

Buzzer::Buzzer(){
    DDRD |= (1 << DD3);
}

void Buzzer::short_beep(){
    PORTD |= (1 << PD3);
    _delay_ms(100);
    PORTD &= ~(1 << PD3);
}