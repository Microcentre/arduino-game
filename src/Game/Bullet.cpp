#include "Bullet.h"

uint8_t Bullet::bullet_amount = 0;

Bullet::Bullet(int16_t x_position, int16_t y_position, double direction, uint16_t colour) : MovingObject(x_position, y_position, speed)
{
    this->direction = direction;
    this->speed = SPEED;
    this->bullet_colour = colour;
}

Bullet::~Bullet()
{
    if (this->shot_by_player1)
        Bullet::bullet_amount--; // allow next bullet to be created
}

void Bullet::update(const double &delta)
{
    // delete bullet after a while
    frames_alive++;
    if (frames_alive > Bullet::DECAY_FRAMES)
    {
        this->marked_for_deletion = true;
        return;
    }

    MovingObject::update(delta);
}

void Bullet::draw(Display *display)
{
    MovingObject::draw(display);
    display->canvas.fillCircle(this->get_x_position(), this->get_y_position(), 2, this->bullet_colour);
}

void Bullet::undraw(Display *display, const uint16_t x_position, const uint16_t y_position)
{
    display->canvas.fillCircle(x_position, y_position, 2, display->background_colour);
}
