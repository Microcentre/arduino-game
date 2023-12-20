#include "Brightness.h"
#include <avr/io.h>

#define ALLADCPINS ((1 << MUX0) | (1 << MUX1) | (1 << MUX2) | (1 << MUX3))

Brightness::Brightness()
{
    init_ADC();
    init_timer_2();
}

void Brightness::init_timer_2()
{
    DDRD |= (1 << DDD5); // set pin 5 as output

    TCCR2B |= (1 << CS21); // 1/8 prescaler

    TCCR2A |= (0 << WGM21); // CTC mode

    TIMSK2 |= (1 << OCIE2A); // enable interrupt
}

void Brightness::init_ADC()
{
    ADMUX &= ~ALLADCPINS;                                    // input channel port A0 for LDR
    ADMUX |= (1 << REFS0);                                   // reference voltage on AVCC
    ADCSRB &= ~((1 << ADTS0) | (1 << ADTS1) | (1 << ADTS2)); // freerunning mode
    ADCSRA |= ((1 << ADPS0) | (1 << ADPS1) | (1 << ADPS2));  // prescaler 128
    ADCSRA |= (1 << ADATE);                                  // auto trigger enable
    ADCSRA |= (1 << ADEN);                                   // enable ADC
    ADCSRA |= (1 << ADSC);                                   // start first ADC conversion
    ADCSRA |= (1 << ADIE);                                   // enable interrupt
    ADMUX |= (1 << ADLAR);                                   // ADC left adjust
}