#include "Player.h"

Player::Player(int x_position, int y_position, double speed) : MovingObject(x_position, y_position, speed)
{
}

void Player::update(double delta)
{
    this->direction += 0.1;
    if (this->direction >= 2 * M_PI)
        this->direction -= 2 * M_PI;
    MovingObject::update(delta);
}

void Player::draw(Display display)
{
    MovingObject::draw(display);
    display.canvas.fillCircle(this->get_x_position(), this->get_y_position(), 5, ILI9341_WHITE);
}

void Player::undraw(Display display, int x_position, int y_position)
{
    display.canvas.fillCircle(x_position, y_position, 5, ILI9341_BLACK);
}
