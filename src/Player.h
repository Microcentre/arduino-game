#ifndef PLAYER_H
#define PLAYER_H

#include "stdint.h"
#include "MovingObject.h"

class Player : public MovingObject
{
public:
    /// @param speed pixels per second
    Player(uint16_t x_position, uint16_t y_position, double speed);

    /// @param delta_s time since last frame in seconds
    void update(double delta) override;

    /// @brief rotate the player left or right
    /// @param rotation [0..255] where 0=left, 128=no change, 255=right
    void rotate(uint8_t rotation);

    /// @brief call undraw(), then draw()
    /// @param display display to draw on
    void draw(Display display) override;

    /// @brief clear drawing at given position
    /// @param display display to draw on
    /// @param x_position X-position of drawing to clear
    /// @param y_position Y-position of the drawing to clear
    void undraw(Display display, uint16_t x_position, uint16_t y_position) override;

private:
    /// @brief in radians per second (so small numbers)
    static const float TURN_SPEED = 0.15;

    /// @brief the highest value the axis can be
    const uint8_t MAX_JOYSTICK_AXIS = 255;
};

#endif
