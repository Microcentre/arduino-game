#ifndef RESETARDUINOONHURT_H
#define RESETARDUINOONHURT_H

#include "Player.h"

/// @brief executes game reset behavior when player has lost all lives
class ResetArduinoOnHurt : public Player::HurtObserver
{
public:
    ResetArduinoOnHurt();

    /// @brief resets entire arduino on losing last health point
    /// @param Player
    void update(Player *player) override;

    /// @brief arduino software version of reset button
    void (*resetFunc)(void) = 0;
};

#endif