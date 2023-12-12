#ifndef BUZZER_H
#define BUZZER_H

#include <avr/io.h>
#include <util/delay.h>

class Buzzer{
    public:
        /// @brief initializes portd for buzzer
        Buzzer();
        /// @brief generates a short beep using buzzer portd and delay
        void short_beep();
};

#endif