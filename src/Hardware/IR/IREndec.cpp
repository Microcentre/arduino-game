#include "IREndec.h"

/// @param wave_ended wave has ended because all asteroids are destroyed
/// @param player_died game has ended because 0 lives are left
uint32_t IREndec::encode_game(uint16_t player_x_position, uint8_t player_y_position, uint16_t player_direction, bool wave_ended, bool player_died, bool player_shot_bullet)
{
    uint32_t data = 0;
    data |= player_x_position;

    data <<= Y_POSITION_BIT_SIZE;
    data |= player_y_position;

    data <<= FACING_DIRECTION_BIT_SIZE;
    data |= player_direction;

    data <<= WAVE_END_BIT_SIZE;
    data |= wave_ended;

    data <<= PLAYER_DEATH_BIT_SIZE;
    data |= player_died;

    data <<= SHOT_BULLET_BIT_SIZE;
    data |= player_shot_bullet;

    return data;
}

GameData IREndec::decode_game(uint32_t data)
{
    GameData gamedata;

    gamedata.player_x_position = (data & POSITION_X_MASK) >> POSITION_X_SHIFT_OFFSET;
    gamedata.player_y_position = (data & POSITION_Y_MASK) >> POSITION_Y_SHIFT_OFFSET;

    uint16_t facing_direction = (data & FACING_DIRECTION_MASK) >> FACING_DIRECTION_SHIFT_OFFSET;
    // convert sent direction back to double
    gamedata.player_facing_direction = ((double)(facing_direction << 1) / 100) - M_PI;

    gamedata.wave_ended = (data & WAVE_END_MASK) >> WAVE_END_SHIFT_OFFSET;
    gamedata.player_died = (data == PLAYER_DEATH_DATA);
    gamedata.player_shot_bullet = (data & SHOT_BULLET_MASK) >> SHOT_BULLET_SHIFT_OFFSET;
    return gamedata;
}

uint32_t IREndec::encode_game_ended()
{
    return PLAYER_DEATH_DATA;
}
