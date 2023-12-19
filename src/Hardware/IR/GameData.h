#ifndef GAMEDATA_H
#define GAMEDATA_H

#include "stdint.h"

class GameData
{
public:
    uint16_t pos_x;
    uint8_t pos_y;
    uint16_t dir;
    uint8_t flags;
};

#endif
