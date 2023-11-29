#include "Player.h"

Player::Player(int x_position, int y_position, double speed, double turn_speed) : MovingObject(x_position, y_position, speed)
{
    this->turn_speed = turn_speed;
}

void Player::update(double delta)
{
    MovingObject::update(delta);
}

void Player::rotate(double rotation)
{
    this->direction -= rotation * turn_speed;
}

void Player::draw(Display display)
{
    MovingObject::draw(display);
    display.canvas.fillCircle(this->get_x_position(), this->get_y_position(), 5, ILI9341_WHITE);
}

void Player::undraw(Display display, int x_position, int y_position)
{
    display.canvas.fillCircle(x_position, y_position, 5, display.background_colour);
}
