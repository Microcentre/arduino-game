#ifndef PLAYER_H
#define PLAYER_H

#include "stdint.h"
#include "MovingObject.h"

class Player : public MovingObject
{
public:
    /// @param speed pixels per second
    Player(int x_position, int y_position, double speed);

    /// @param delta_s time since last frame in seconds
    void update(double delta) override;
    
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
