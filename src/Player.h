#ifndef PLAYER.H
#define PLAYER.H

#include "stdint.h"

const uint8_t PLAYER_RADIUS = 5;
const uint16_t BOUNDARY_HEIGHT = 318;
const uint8_t BOUNDARY_WIDTH = 238;

class Player
{
    public:
        Player();
        void calculate_position(uint8_t joysitck_x, uint8_t joystick_y);
        uint16_t get_pos_x();
        uint8_t get_pos_y();
    private:
        uint16_t pos_x;
        uint8_t pos_y;
};

#endif