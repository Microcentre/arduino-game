#ifndef BULLET_H
#define BULLET_H

#include "MovingObject.h"

class Bullet : public MovingObject
{
public:
    Bullet(int16_t x_position, int16_t y_position, double direction);

    /// @param delta_s time since last frame in seconds
    void update(const double &delta) override;

    /// @brief call undraw(), then draw()
    /// @param display display to draw on
    void draw(Display *display) override;

    /// @brief clear drawing at given position
    /// @param display display to draw on
    /// @param x_position X-position of drawing to clear
    /// @param y_position Y-position of the drawing to clear
    void undraw(Display *display, const uint16_t x_position, const uint16_t y_position) override;

    virtual ~Bullet();

    int frames_alive = 0;

    static uint8_t bullet_amount;

    static const uint8_t MAX_BULLETS = 3;

private:
    const double SPEED = 700;

    /// @brief How many frames it takes before the bullet despawns
    static const uint8_t DECAY_FRAMES = 15;

    static const uint8_t SHOOT_DELAY = 10;
};

#endif
