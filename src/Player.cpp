#include "Player.h"

Player::Player()
{
    // start at center position on display
    player_x = 170;
    player_y = 120;
}

void Player::calculate_position(uint8_t joystick_x, uint8_t joystick_y)
{
    // startvalue, using negative numbers. the joystick x and y values ranges from ~0 to ~255
    int16_t calc_x = joystick_x - 128;
    int8_t calc_y = joystick_y - 128;

    // calculating speed of player
    calc_x /= 25;
    calc_y /= 25;

    // move player and check for collision on display boundaries
    if (player_x + calc_x > PLAYER_RADIUS && player_x + calc_x <= BOUNDARY_HEIGHT - PLAYER_RADIUS)
    {
        player_x += calc_x;
    }
    if (player_y - calc_y > PLAYER_RADIUS && player_y - calc_y <= BOUNDARY_WIDTH - PLAYER_RADIUS)
    {
        //-= is used to invert y axis
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
