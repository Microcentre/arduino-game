#ifndef SHOWHEALTHONSSD_H
#define SHOWHEALTHONSSD_H

#include "../Game/Player.h"

/// @brief executes display behavior to show current health of own player
class ShowHealthOnSSD : public Player::HurtObserver
{
public:
    /// @brief executes update once to start showing health when player is created
    /// @param player
    ShowHealthOnSSD(Player *player);

    ~ShowHealthOnSSD();

    /// @brief updates SSD to display current health amount
    /// @param player
    void update(Player *player) override;

private:
    /// @brief contains binary values to display numbers on SSD
    const uint8_t DISPLAY_DIGITS[5] = {
        // 0 = led on, 1 = led off (anode sevenseg display)
        0b11000000, // 0
        0b11111001, // 1
        0b10100100, // 2
        0b10110000, // 3
        0b11111111, // off
    };

    const uint8_t DISPLAY_OFF = 4;
};

#endif