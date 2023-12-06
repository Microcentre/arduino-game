#include "Player.h"

Player::Player() : Player(0, 0, 0)
{
}

Player::Player(uint16_t x_position, uint16_t y_position, double speed) : MovingObject(x_position, y_position, speed)
{
}

void Player::update(const double &delta)
{
    MovingObject::update(delta);
    speed -= DECEL_RATE;
    if (speed < 0)
    {
        speed = 0;
    }
}

void Player::accelerate()
{
    // add vectors together as shown in TO

    // vector A
    // angle: direction
    // magnitude: speed

    // vector B
    // angle: facing_direction
    // magnitude: ACCEL_BASE_VALUE

    double vectorA_x = speed * cos(direction);
    double vectorA_y = speed * sin(direction);

    double vectorB_x = ACCEL_RATE * cos(facing_direction);
    double vectorB_y = ACCEL_RATE * sin(facing_direction);

    double vectorR_x = vectorA_x + vectorB_x;
    double vectorR_y = vectorA_y + vectorB_y;

    speed = sqrt(sq(vectorR_x) + sq(vectorR_y));
    if (speed > MAX_SPEED)
    {
        speed = MAX_SPEED;
    }
    direction = atan2(vectorR_y, vectorR_x);
}

void Player::rotate(const uint8_t rotation)
{
    // normalise from [0..255] to [0..1]
    double rotation_modifier = (double)rotation / this->MAX_JOYSTICK_AXIS;
    // scale to [0..2] and shift to [-1..1]
    rotation_modifier = (rotation_modifier * 2) - 1;
    // [-1..1] where -1=bottom, 0=centre, 1=top
    this->facing_direction -= rotation_modifier * this->TURN_SPEED;
}

void Player::draw(Display *display)
{
    MovingObject::draw(display);
    display->canvas.fillCircle(this->get_x_position(), this->get_y_position(), 5, ILI9341_WHITE);
}

void Player::undraw(Display *display, const uint16_t x_position, const uint16_t y_position)
{
    display->canvas.fillCircle(x_position, y_position, 5, display->background_colour);
}
