#ifndef IRCODEC_H
#define IRCODEC_H

#include <math.h>

#include "stdint.h"
#include "GameData.h"

class IREndec
{
public:
    /// @brief Encodes a frame of the game logic (excluding asteroid spawning during wave-switch)
    /// @param wave_ended wave has ended because all asteroids are destroyed
    /// @param player_died game has ended because 0 lives are left
    /// @return encoded 32 bit message containing all given data
    static uint32_t encode_game(uint16_t player_x_position, uint8_t player_y_position, uint16_t player_direction, bool wave_ended, bool player_died, bool player_shot_bullet);
    static GameData decode_game(uint32_t data);
    static uint32_t encode_game_ended();
    // uint32_t encode_asteroid();
    // uint32_t encode_ship_select();
private:
    static const uint8_t DATA_POS_X_SIZE = 9;
    static const uint8_t DATA_POS_Y_SIZE = 8;
    static const uint8_t DATA_DIR_SIZE = 9;

    static const uint32_t DATA_SHOT_BULLET_MASK = 0b10000000000000000000000000000000;
    static const uint32_t DATA_PLAYER_DEATH_MASK = 0b01000000000000000000000000000000;
    static const uint32_t DATA_WAVE_END_MASK = 0b00100000000000000000000000000000;

    static const uint32_t DATA_POS_X_MASK = 0b00011111111100000000000000000000;
    static const uint32_t DATA_POS_Y_MASK = 0b00000000000011111111000000000000;
    static const uint32_t DATA_DIR_MASK = 0b00000000000000000000111111111000;
};

#endif
