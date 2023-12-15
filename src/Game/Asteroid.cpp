#include "Asteroid.h"

Asteroid::Asteroid(uint16_t x_position, uint16_t y_position, double speed, double direction) : MovingObject(x_position, y_position, speed)
{
    this->direction = direction;
}

void Asteroid::update(const double &delta)
{
    MovingObject::update(delta);
}

void Asteroid::draw(Display *display)
{
    MovingObject::draw(display);
    display->canvas.drawCircle(this->get_x_position(), this->get_y_position(), ASTEROID_SIZE, ILI9341_WHITE);
}

void Asteroid::undraw(Display *display, const uint16_t x_position, const uint16_t y_position)
{
    display->canvas.drawCircle(x_position, y_position, ASTEROID_SIZE, display->background_colour);
}