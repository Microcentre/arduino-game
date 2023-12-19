#include "IREndec.h"

uint32_t IREndec::encode_game(uint16_t pos_x, uint8_t pos_y, uint16_t dir, uint8_t flags)
{
    uint32_t data = 0;
    data |= pos_x;
    data <<= DATA_POS_Y_SIZE;
    data |= pos_y;
    data <<= DATA_DIR_SIZE;
    data |= dir;
    data <<= DATA_FLAGS_SIZE;
    data |= flags;
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
