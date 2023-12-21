#ifndef IRCODEC_H
#define IRCODEC_H

#include <math.h>

#include "stdint.h"
#include "GameData.h"

class IREndec
{
public:
    /// @brief Encodes a frame of the game logic (excluding asteroid spawning during wave-switch)
    /// @param switching_wave wave has ended because all asteroids are destroyed
    /// @param player_died game has ended because 0 lives are left
    /// @return encoded 32 bit message containing all given data
    static uint32_t encode_game(uint16_t player_x_position, uint8_t player_y_position, uint16_t player_direction, bool switching_wave, bool player_died, bool player_shot_bullet);
    static uint32_t encode_game_ended();
    static uint32_t encode_switching_wave();
    static GameData decode_game(uint32_t data);
    // uint32_t encode_asteroid();
    // uint32_t encode_ship_select();
private:
    static const uint8_t X_POSITION_BIT_SIZE = 9;
    static const uint8_t Y_POSITION_BIT_SIZE = 8;
    static const uint8_t FACING_DIRECTION_BIT_SIZE = 9;
    static const uint8_t WAVE_END_BIT_SIZE = 1;
    static const uint8_t PLAYER_DEATH_BIT_SIZE = 1;
    static const uint8_t SHOT_BULLET_BIT_SIZE = 1;

    // once data is received, how many bits to shift back to get the data
    static const uint8_t SHOT_BULLET_SHIFT_OFFSET = 0;
    static const uint8_t PLAYER_DEATH_SHIFT_OFFSET = SHOT_BULLET_BIT_SIZE;
    static const uint8_t WAVE_END_SHIFT_OFFSET = PLAYER_DEATH_BIT_SIZE + PLAYER_DEATH_SHIFT_OFFSET;
    static const uint8_t FACING_DIRECTION_SHIFT_OFFSET = WAVE_END_BIT_SIZE + WAVE_END_SHIFT_OFFSET;
    static const uint8_t POSITION_Y_SHIFT_OFFSET = FACING_DIRECTION_BIT_SIZE + FACING_DIRECTION_SHIFT_OFFSET;
    static const uint8_t POSITION_X_SHIFT_OFFSET = Y_POSITION_BIT_SIZE + POSITION_Y_SHIFT_OFFSET;

    static const uint32_t POSITION_X_MASK = 0b00011111111100000000000000000000;
    static const uint32_t POSITION_Y_MASK = 0b00000000000011111111000000000000;
    static const uint32_t FACING_DIRECTION_MASK = 0b00000000000000000000111111111000;
    static const uint32_t SHOT_BULLET_MASK = 0b00000000000000000000000000000001;

    /// @brief unique data byte that's send when a player dies
    /// This is a random unique byte that must exactly match, to ensure that the player died.
    /// Most importantly is that the second MSB is 1, because this should always be 0 when the player is alive.
    static const uint32_t PLAYER_DEATH_DATA = 0b00000111000111000111000111000111;

    /// @brief unique data byte that's send when a wave ends
    /// This is a random unique byte that must exactly match.
    /// Most importantly is that the third MSB is 1, because this should always be 1 when the wave ends.
    static const uint32_t WAVE_END_DATA = 0b00000100100100100100100100100100;
};

#endif
