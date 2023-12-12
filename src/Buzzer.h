#ifndef BUZZER_H
#define BUZZER_H

#include <avr/io.h>
#include <util/delay.h>

class Buzzer{
    public:
        /// @brief initializes timer 2 for buzzer
        Buzzer();
        /// @brief generates a short beep using buzzer
        void short_beep();
        /// @brief generates a very short beep using buzzer
        void bullet_beep();
};

#endif