#include "InvincibilityFrames.h"

InvincibilityFrames::InvincibilityFrames()
{
}

void InvincibilityFrames::update(Player *player)
{
    player->is_invincible = true;
    player->invincibility_timer = Player::INVINCIBILITY_TIME;
}