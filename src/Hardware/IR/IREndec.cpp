#include "IREndec.h"

/// @param wave_ended wave has ended because all asteroids are destroyed
/// @param player_died game has ended because 0 lives are left
uint32_t IREndec::encode_game(uint16_t player_x_position, uint8_t player_y_position, uint16_t player_direction, bool player_shot_bullet, bool player_died, bool wave_ended)
{
    uint32_t data = 0;
    data |= player_x_position;

    data <<= DATA_POS_Y_SIZE;
    data |= player_y_position;

    data <<= DATA_DIR_SIZE;
    data |= player_direction;

    data <<= DATA_WAVE_END_MASK;
    data |= wave_ended;

    data <<= DATA_PLAYER_DEATH_MASK;
    data |= player_died;

    data <<= DATA_SHOT_BULLET_MASK;
    data |= player_shot_bullet;

    return data;
}

GameData IREndec::decode_game(uint32_t data)
{
    GameData gamedata;

    gamedata.player_x_position = (data & (DATA_POS_X_MASK)) >> 20;
    gamedata.player_y_position = (data & (DATA_POS_Y_MASK)) >> 12;
    uint16_t dir = (data & (DATA_DIR_MASK)) >> 3;
    // convert sent direction back to double
    gamedata.player_facing_direction = ((double)(dir << 1) / 100) - M_PI;

    return gamedata;
}

uint32_t IREndec::encode_game_ended()
{
    return encode_game(0, 0, 0, false, true, false);
}
