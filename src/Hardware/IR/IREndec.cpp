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

GameData *IREndec::decode_game()
{
    return nullptr;
}
