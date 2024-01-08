#ifndef INVINCIBILITYFRAMES_H
#define INVINCIBILITYFRAMES_H

#include "Player.h"

/// @brief makes the player invincible when he's damaged.
/// Observer thats called when the player is hurt (HurtObserver instance)
class InvincibilityFrames : public Player::HurtObserver
{
public:
    InvincibilityFrames();

    /// @brief executes observer behavior
    void update(Player *player) override;
};

#endif