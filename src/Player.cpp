#include "Player.h"

Player::Player(uint16_t x_position, uint16_t y_position, double speed) : MovingObject(x_position, y_position, speed)
{
}

void Player::update(const double &delta)
{
    MovingObject::update(delta);
}

void Player::rotate(const uint8_t rotation)
{
    // normalise from [0..255] to [0..1]
    double rotation_modifier = (double)rotation / this->MAX_JOYSTICK_AXIS;
    // scale to [0..2] and shift to [-1..1]
    rotation_modifier = (rotation_modifier * 2) - 1;
    // [-1..1] where -1=bottom, 0=centre, 1=top
    this->direction -= rotation_modifier * this->TURN_SPEED;
}

void Player::draw(Display display)
{
    MovingObject::draw(display);
    display.canvas.fillCircle(this->get_x_position(), this->get_y_position(), 5, ILI9341_WHITE);
}

void Player::undraw(Display display, const uint16_t x_position, const uint16_t y_position)
{
    display.canvas.fillCircle(x_position, y_position, 5, display.background_colour);
}
