#ifndef PLAYER_H
#define PLAYER_H

#include "stdint.h"
#include "MovingObject.h"

class Player : public MovingObject
{
public:
    Player();
    /// @param speed pixels per second
    Player(uint16_t x_position, uint16_t y_position, double speed);

    /// @param delta_s time since last frame in seconds
    void update(const double &delta) override;

    /// @brief rotate the player left or right
    /// @param rotation [0..255] where 0=left, 128=no change, 255=right
    void rotate(const uint8_t rotation);

    void accelerate();

    /// @brief call undraw(), then draw()
    /// @param display display to draw on
    void draw(const Display *display) override;

    /// @brief clear drawing at given position
    /// @param display display to draw on
    /// @param x_position X-position of drawing to clear
    /// @param y_position Y-position of the drawing to clear
    void undraw(const Display *display, const uint16_t x_position, const uint16_t y_position) override;

private:
    /// @brief in radians per second (so small numbers)
    static const float TURN_SPEED = 0.15;

    /// @brief the highest value the axis can be
    static const uint8_t MAX_JOYSTICK_AXIS = 255;

    /// @brief acceleration per frame holding the gas button
    static const double ACCEL_RATE = 4.0;
    /// @brief deceleration per frame when not holding the gas button
    static const double DECEL_RATE = 0.5;
    static const double MAX_SPEED = 512;

    double facing_direction;
};

#endif