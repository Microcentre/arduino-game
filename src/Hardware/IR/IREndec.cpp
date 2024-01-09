#include "IREndec.h"

/// @param switching_wave wave has ended because all asteroids are destroyed
/// @param player_died game has ended because 0 lives are left
uint32_t IREndec::encode_game(uint16_t player_x_position, uint8_t player_y_position, uint16_t player_direction, bool switching_wave, bool player_died, bool player_shot_bullet)
{
    uint32_t data = 0;
    data |= player_x_position;

    data <<= Y_POSITION_BIT_SIZE;
    data |= player_y_position;

    data <<= FACING_DIRECTION_BIT_SIZE;
    data |= player_direction;

    data <<= WAVE_END_BIT_SIZE;
    data |= switching_wave;

    data <<= PLAYER_DEATH_BIT_SIZE;
    data |= player_died;

    data <<= SHOT_BULLET_BIT_SIZE;
    data |= player_shot_bullet;

    return data;
}

ReceivedGameData IREndec::decode_game(uint32_t data)
{
    ReceivedGameData gamedata;

    if (data == 0)
    {
        gamedata.valid_data = 0;
        return gamedata;
    }
    gamedata.valid_data = 1;

    gamedata.player_died = (data == PLAYER_DEATH_DATA);
    gamedata.switching_wave = is_switching_wave(data);
    gamedata.finished_switching_wave = (gamedata.switching_wave)
                                           ? IREndec::is_finished_switching_wave(data)
                                           : false;

    // switching_wave and player_died use the entire byte of data
    // so the rest of the data cant/wont be set
    if (gamedata.switching_wave || gamedata.player_died)
        return gamedata;

    gamedata.player_x_position = (data & POSITION_X_MASK) >> POSITION_X_SHIFT_OFFSET;
    gamedata.player_y_position = (data & POSITION_Y_MASK) >> POSITION_Y_SHIFT_OFFSET;

    // convert direction to uint16_t:
    // - add PI to make it always positive
    // - multiply by 100 so decimals can be safely truncated
    // - shift right to save 1 bit at the cost of accuracy
    // - reverse these steps on receive
    uint16_t facing_direction = (data & FACING_DIRECTION_MASK) >> FACING_DIRECTION_SHIFT_OFFSET;
    gamedata.player_facing_direction = ((double)(facing_direction << 1) / 100) - M_PI;

    gamedata.player_shot_bullet = (data & SHOT_BULLET_MASK) >> SHOT_BULLET_SHIFT_OFFSET;
    return gamedata;
}

uint32_t IREndec::encode_game_ended()
{
    return PLAYER_DEATH_DATA;
}

uint32_t IREndec::encode_switching_wave(bool ready_to_play)
{
    return WAVE_END_DATA | ready_to_play;
}

bool IREndec::is_switching_wave(uint32_t data)
{
    // & (~1) forces bit 1 to be 0, allowing us to directly compare it to WAVE_END_DATA
    return WAVE_END_DATA == (data & (~1));
}

bool IREndec::is_finished_switching_wave(uint32_t data)
{
    // first bit is used to specify finished(1) or unfinished(0)
    return (data & 1) == 1;
}
