#ifndef BUZZER_H
#define BUZZER_H

class Buzzer
{
public:
    /// @brief initializes timer 2 for buzzer
    Buzzer();
    /// @brief play a meduim beep using buzzer
    void medium_beep();
    /// @brief play a short beep using buzzer
    void short_beep();
};

#endif