#ifndef GAMEDATA_H
#define GAMEDATA_H

#include <stdint.h>

class ReceivedGameData
{
public:
    /// @brief don't process player2 data if this isn't set
    bool valid_data;

    uint16_t player_x_position;
    uint8_t player_y_position;
    double player_facing_direction;
    bool player_shot_bullet;
    bool player_died;
    bool switching_wave;
    bool finished_switching_wave;
};

#endif
