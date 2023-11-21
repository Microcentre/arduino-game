#include "Player.h"

Player::Player()
{
    // center position on display
    player_x = 170;
    player_y = 120;
}

void Player::calculate_position(uint8_t joystick_x, uint8_t joystick_y)
{
    int16_t calc_x = joystick_x - 128;
    int8_t calc_y = joystick_y - 128;

    calc_x /= 25;
    calc_y /= 25;

    if(player_x + calc_x > PLAYER_RADIUS && player_x + calc_x <= BOUNDARY_HEIGHT - PLAYER_RADIUS){
         player_x += calc_x;
    }
    if(player_y - calc_y > PLAYER_RADIUS && player_y - calc_y <= BOUNDARY_WIDTH - PLAYER_RADIUS){
        player_y -= calc_y;
    }
}

uint16_t Player::get_player_x()
{
    return player_x;
}

uint8_t Player::get_player_y()
{
    return player_y;
}
