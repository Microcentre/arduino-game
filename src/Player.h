#ifndef PLAYER_H
#define PLAYER_H

#include "stdint.h"
#include "MovingObject.h"

class Player : public MovingObject
{
public:
    /// @brief in radians per second (so small numbers)
    double turn_speed;

    /// @param speed pixels per second
    Player(int x_position, int y_position, double speed, double turn_speed);

    /// @param delta_s time since last frame in seconds
    void update(double delta) override;

    /// @brief rotate the player left or right
    /// @param rotation [-1..1] where -1=left, 0=no change, 1=right
    void rotate(float rotation);
    
    /// @brief call undraw(), then draw()
    /// @param display display to draw on
    void draw(Display display) override;
    
    /// @brief clear drawing at given position
    /// @param display display to draw on
    /// @param x_position X-position of drawing to clear
    /// @param y_position Y-position of the drawing to clear
    void undraw(Display display, int x_position, int y_position) override;
};

#endif
