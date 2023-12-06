#include "Bullet.h"

bool Bullet::bullet_created = false;

Bullet::Bullet(int16_t x_position, int16_t y_position, double direction) : MovingObject(x_position, y_position, speed)
{
    this->direction = direction;
    this->speed = SPEED;
}

Bullet::~Bullet()
{
    Bullet::bullet_created = false; // allow next bullet to be created
}

void Bullet::update(const double &delta)
{
    // delete bullet after a while
    frames_alive++;
    if (frames_alive > 15)
    {
        this->marked_for_deletion = true;
        return;
    }

    MovingObject::update(delta);
}

void Bullet::draw(Display *display)
{
    MovingObject::draw(display);
    display->canvas.fillCircle(this->get_x_position(), this->get_y_position(), 2, ILI9341_RED);
}

void Bullet::undraw(Display *display, const uint16_t x_position, const uint16_t y_position)
{
    display->canvas.fillCircle(x_position, y_position, 2, display->background_colour);
}
