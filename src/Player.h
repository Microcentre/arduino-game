#ifndef PLAYER.H
#define PLAYER.H

#include "stdint.h"

class Player
{
    public:
        Player();
        void calculate_position(uint8_t joysitck_x, uint8_t joystick_y);
        uint8_t get_player_x();
        uint8_t get_player_y();
    private:
        uint8_t player_x;
        uint8_t player_y;
};

#endif