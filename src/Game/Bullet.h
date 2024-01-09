#ifndef BULLET_H
#define BULLET_H

#include "../Objects/MovingObject.h"

class Bullet : public MovingObject
{
public:
    /// @brief how many bullets the current player has shot
    static uint8_t bullet_amount;

    /// @brief the max amount of bullets each player can shoot
    static const uint8_t MAX_BULLETS = 2;

    /// @brief if this bullet is shot by the current player (true) or the other player (false)
    /// if true, bullet_amount
    bool shot_by_player1 = false;

    /// @brief counter for when bullet gets deleted.
    /// Bullets get deleted after an X amount of frames. this is the counter for that.
    uint8_t frames_alive = 0;

    Bullet(int16_t x_position, int16_t y_position, double direction, uint16_t colour);

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

private:
    /// @brief How many frames it takes before the bullet despawns
    static const uint8_t DECAY_FRAMES = 10;

    /// @brief how many frames to wait until the player can shoot again
    static const uint8_t SHOOT_DELAY = 9;

    /// @brief how many pixels per second the bullet moves
    const double SPEED = 1024;

    /// @brief 16-bit 5-6-5 Colour
    uint16_t bullet_colour;
};

#endif
