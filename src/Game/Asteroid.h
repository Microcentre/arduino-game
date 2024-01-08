#ifndef ASTEROID_H
#define ASTEROID_H

#include "../Objects/MovingObject.h"

class Asteroid : public MovingObject
{
public:
    /// @brief How much score the player gets for destroying an asteroid
    static const uint8_t SCORE_ASTEROID = 50;

    /// @brief radius of each asteroid circle
    static const uint8_t ASTEROID_SIZE = 18;

    /// @brief initializes an asteroid
    /// @param x_position start position as x-coordinate
    /// @param y_position start position as y coordinate
    /// @param speed speed of asteroid (pixels per second)
    /// @param direction direction of asteroid in radians. 0=up, M_PI=down
    Asteroid(uint16_t x_position, uint16_t y_position, double speed, double direction);

    /// @brief calls MovingObject::update()
    /// @param delta time since last frame in seconds
    void update(const double &delta) override;

    /// @brief calls undraw(), then draw(). When inheriting call MovingObject::draw() first
    /// @param display display to draw on
    void draw(Display *display) override;

    /// @brief clear asteroid at given position
    /// @param display display to draw on
    /// @param x_position X-position of drawing to clear
    /// @param y_position Y-position of the drawing to clear
    void undraw(Display *display, const uint16_t x_position, const uint16_t y_position) override;
};

#endif