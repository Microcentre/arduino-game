#include "Player.h"

Player::Player() : Player(0, 0, 0)
{
}

Player::Player(uint16_t x_position, uint16_t y_position, double speed) : MovingObject(x_position, y_position, speed)
{
    this->facing_direction = 0;
}

void Player::update(const double &delta)
{
    MovingObject::update(delta);
    speed -= DECEL_RATE;
    if (speed < 0)
        speed = 0;
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
        speed = MAX_SPEED;

    direction = atan2(vectorR_y, vectorR_x);
}

void Player::rotate(const uint8_t rotation)
{
    // normalise from [0..255] to [0..1]
    double rotation_modifier = (double)rotation / this->MAX_JOYSTICK_AXIS;
    // scale to [0..2] and shift to [-1..1]
    rotation_modifier = (rotation_modifier * 2) - 1;
    // [-1..1] where -1=bottom, 0=centre, 1=top
    this->previous_facing_direction = this->facing_direction;
    this->facing_direction -= rotation_modifier * this->TURN_SPEED;
}

void Player::draw(Display *display)
{
    MovingObject::draw(display);
    this->draw(display, this->get_x_position(), this->get_y_position(), this->facing_direction, ILI9341_WHITE);
}

void Player::undraw(Display *display, const uint16_t x_position, const uint16_t y_position)
{
    this->draw(display, x_position, y_position, this->previous_facing_direction, display->background_colour);
}

void Player::draw(Display *display, const uint16_t x_position, const uint16_t y_position, double facing_direction, uint16_t colour)
{
    double pointiness = (double)Player::POINTINESS / 10;
    uint16_t front_x = x_position + ((Player::PLAYER_SIZE * pointiness) * sin(facing_direction));
    uint16_t front_y = y_position + ((Player::PLAYER_SIZE * pointiness) * cos(facing_direction));

    double right_direction = facing_direction + M_PI_2;
    uint16_t right_x = x_position + (Player::PLAYER_SIZE * sin(right_direction));
    uint16_t right_y = y_position + (Player::PLAYER_SIZE * cos(right_direction));

    double left_direction = facing_direction - M_PI_2;
    uint16_t left_x = x_position + (Player::PLAYER_SIZE * sin(left_direction));
    uint16_t left_y = y_position + (Player::PLAYER_SIZE * cos(left_direction));

    display->canvas.drawTriangle(front_x, front_y, right_x, right_y, left_x, left_y, colour);
}
