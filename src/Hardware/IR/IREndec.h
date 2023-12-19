#ifndef IRCODEC_H
#define IRCODEC_H

#include "stdint.h"
#include "GameData.h"

class IREndec
{
public:
    /// @brief Encodes a frame of the game logic (excluding asteroid spawning during wave-switch)
    /// @return encoded 32 bit message containing all given data
    static uint32_t encode_game(uint16_t pos_x, uint8_t pos_y, uint16_t dir, uint8_t flags);
    static GameData *decode_game();
    // uint32_t encode_asteroid();
    // uint32_t encode_ship_select();
private:
    static const uint8_t DATA_POS_X_SIZE = 9;
    static const uint8_t DATA_POS_Y_SIZE = 8;
    static const uint8_t DATA_DIR_SIZE = 9;
    static const uint8_t DATA_FLAGS_SIZE = 3;
};

#endif
