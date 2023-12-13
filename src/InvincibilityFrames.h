#ifndef INVINCIBILITYFRAMES_H
#define INVINCIBILITYFRAMES_H

#include "Player.h"

class InvincibilityFrames : public Player::HurtObserver
{
public:
    InvincibilityFrames();

    /// @brief executes observer behavior
    void update(Player *player) override;
};

#endif