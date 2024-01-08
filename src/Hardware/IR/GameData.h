#ifndef GAMEDATA_H
#define GAMEDATA_H

#include <stdint.h>

class GameData
{
public:
    uint16_t player_x_position;
    uint8_t player_y_position;
    double player_facing_direction;
    bool player_shot_bullet;
    bool player_died;
    bool switching_wave;
    bool finished_switching_wave;
};

#endif
