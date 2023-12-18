#include "Player.h"

Player::Player() : Player(0, 0, 0)
{
}

Player::Player(uint16_t x_position, uint16_t y_position, double speed) : MovingObject(x_position, y_position, speed)
{
    this->facing_direction = M_PI;
}

void Player::update(const double &delta)
{
    // check if invincible and if so, check if invincibility time is over, resets invincibility if so
    if (is_invincible)
    {
        invincibility_timer -= delta;
        if (invincibility_timer <= 0)
        {
            is_invincible = false;
        }
    }

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
    // this->facing_direction -= rotation_modifier * this->TURN_SPEED;
    double result_direction = this->facing_direction - (rotation_modifier * this->TURN_SPEED);

    // constrain to range [-pi..pi]
    if (result_direction > M_PI)
    {
        this->facing_direction = M_PI * -1;
    }
    else if (result_direction < M_PI * -1)
    {
        this->facing_direction = M_PI;
    }
    else
    {
        this->facing_direction = result_direction;
    }
}

void Player::draw(Display *display)
{
    MovingObject::draw(display);
    // checks if the player is blinking, if not, draw player with the player colour
    is_blinking = (uint16_t)(this->invincibility_timer * 10) % 8;
    if (!is_blinking)
    {
        this->draw(display, this->get_x_position(), this->get_y_position(), this->facing_direction, this->player_colour);
    }
}

void Player::undraw(Display *display, const uint16_t x_position, const uint16_t y_position)
{
    this->undraw(display, x_position, y_position, this->previous_facing_direction);
    this->previous_facing_direction = this->facing_direction;
}

void Player::undraw(Display *display, const uint16_t x_position, const uint16_t y_position, double actual_facing_direction)
{
    this->draw(display, x_position, y_position, actual_facing_direction, display->background_colour);
}

double Player::get_front_x_position()
{
    return this->get_x_position() + (Player::PLAYER_SIZE * sin(this->facing_direction));
}

double Player::get_front_y_position()
{
    return this->get_y_position() + (Player::PLAYER_SIZE * cos(this->facing_direction));
}

void Player::draw(Display *display, const uint16_t x_position, const uint16_t y_position, double facing_direction, uint16_t colour)
{
    // draw a triangle by calculating 3 points:
    // - the front point (right in front of the centre)
    // - the left point (bottom left of the centre)
    // - the right point (bottom right of the centre)

    // front point is right in front of the player
    // based on the POINTINESS variable it gets drawn further away from the centre, making it pointier
    uint16_t front_x = x_position + ((Player::PLAYER_SIZE * Player::POINTINESS) * sin(facing_direction));
    uint16_t front_y = y_position + ((Player::PLAYER_SIZE * Player::POINTINESS) * cos(facing_direction));

    // the right direction is 90 degrees to the right of the facing direction
    double right_direction = facing_direction - M_PI_2;
    // draw point in direction of `right_direction` with the calculated position (player_size offset * angle)
    uint16_t right_x = x_position + (Player::PLAYER_SIZE * sin(right_direction));
    uint16_t right_y = y_position + (Player::PLAYER_SIZE * cos(right_direction));

    double left_direction = facing_direction + M_PI_2;
    // draw point in direction of `left_direction` with the calculated position (player_size offset * angle)
    uint16_t left_x = x_position + (Player::PLAYER_SIZE * sin(left_direction));
    uint16_t left_y = y_position + (Player::PLAYER_SIZE * cos(left_direction));

    display->canvas.drawTriangle(front_x, front_y, right_x, right_y, left_x, left_y, colour);
}

void Player::hurt(Display *display)
{
    health--;

    // reset player
    undraw(display, this->get_x_position(), this->get_y_position(), this->facing_direction);
    set_x_position(Display::WIDTH_PIXELS / 2);
    set_y_position(Display::HEIGHT_PIXELS / 2);
    speed = 0;

    // call all observers
    for (int i = 0; i < hurt_observers_size; ++i)
    {
        hurt_observers[i]->update(this);
    }
}

void Player::add_hurt_observer(Player::HurtObserver *observer)
{
    this->hurt_observers[hurt_observers_size] = observer;
    this->hurt_observers_size++;
}

Player::HurtObserver::~HurtObserver()
{
}
