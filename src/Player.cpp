#include "Player.h"

Player::Player()
{
    // start at center position on display
    pos_x = 170;
    pos_y = 120;
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
    if (pos_x + calc_x > PLAYER_RADIUS && pos_x + calc_x <= BOUNDARY_HEIGHT - PLAYER_RADIUS)
    {
        pos_x += calc_x;
    }
    if (pos_y - calc_y > PLAYER_RADIUS && pos_y - calc_y <= BOUNDARY_WIDTH - PLAYER_RADIUS)
    {
        //-= is used to invert y axis
        pos_y -= calc_y;
    }
}

uint16_t Player::get_pos_x()
{
    return pos_x;
}

uint8_t Player::get_pos_y()
{
    return pos_y;
}
