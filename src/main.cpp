#include <avr/io.h>
#include <avr/interrupt.h>
#include <IR.h>

int main()
{
    sei();
    IR infrared = IR();
    infrared.startBlinking();
    while(1) {
    }
    return 0;
}
