#ifndef GAMEDATA_H
#define GAMEDATA_H

#include "stdint.h"

class GameData
{
public:
    uint16_t player_x_position;
    uint8_t player_y_position;
    uint16_t player_facing_direction;
    uint8_t flags;
};

#endif
