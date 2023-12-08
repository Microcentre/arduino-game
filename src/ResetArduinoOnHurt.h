#ifndef RESETARDUINOONHURT_H
#define RESETARDUINOONHURT_H

#include "Player.h"

class ResetArduinoOnHurt : public Player::HurtObserver
{
public:
    ResetArduinoOnHurt();

    void update(Player *player) override;

    void (*resetFunc)(void) = 0;
};

#endif