#include "Bullet.h"

Bullet::Bullet(uint16_t x_position, uint16_t y_position, double direction) : MovingObject(x_position, y_position, speed)
{
    this->direction = direction;
    this->speed = SPEED;
}

void Bullet::update(const double &delta)
{
    MovingObject::update(delta);
}

void Bullet::draw(Display display)
{
    MovingObject::draw(display);
    display.canvas.fillCircle(this->get_x_position(), this->get_y_position(), 2, ILI9341_RED);
}

void Bullet::undraw(Display display, const uint16_t x_position, const uint16_t y_position)
{
    display.canvas.fillCircle(x_position, y_position, 2, display.background_colour);
}