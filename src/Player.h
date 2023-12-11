#ifndef PLAYER_H
#define PLAYER_H

#include "stdint.h"
#include "MovingObject.h"

class Player : public MovingObject
{
public:
    /// @brief executes specific behavior when player is hurt
    class HurtObserver
    {
    public:
        /// @brief executes observer behavior
        virtual void update(Player *player) = 0;
    };

    uint8_t health = 3;

    double facing_direction;

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
    void draw(Display *display) override;

    /// @brief clear drawing at given position
    /// @param display display to draw on
    /// @param x_position X-position of drawing to clear
    /// @param y_position Y-position of the drawing to clear
    void undraw(Display *display, const uint16_t x_position, const uint16_t y_position) override;

    /// @brief -1 health, resets player to centre of screen and handles all hurtobservers
    void hurt(Display *display);
    /// @brief adds a new hurtobserver to the observer array
    void add_hurt_observer(Player::HurtObserver *observer);
    /// @return the X position of the front-point of the player
    double get_front_x_position();
    /// @return the Y position of the front-point of the player
    double get_front_y_position();
    /// @brief 0: at this health game restarts
    const uint8_t GAME_OVER_HEALTH = 0;
    
    /// @brief player size from centre to corner, the TOTAL player radius would be 2*PLAYER_SIZE.
    static constexpr uint8_t PLAYER_SIZE = 8;

private:
    /// @brief in radians per second (so small numbers)
    static constexpr float TURN_SPEED = 0.25;

    /// @brief the highest value the axis can be
    static const uint8_t MAX_JOYSTICK_AXIS = 255;

    /// @brief acceleration per frame holding the gas button
    static constexpr double ACCEL_RATE = 15.0;

    HurtObserver *hurt_observers[2];
    uint8_t hurt_observers_size = 0;

    /// @brief deceleration per frame when not holding the gas button
    static constexpr double DECEL_RATE = 2.0;
    /// @brief Max pixels per second the player may go
    static constexpr double MAX_SPEED = 650;

    /// @brief How pointy the front is. 1=normal (equilateral triangle)
    static constexpr double POINTINESS = 2.5;

    /// @brief store previous facing_direction for undraw()
    double previous_facing_direction;

    /// @brief draws the player. used by draw() and undraw()
    void draw(Display *display, const uint16_t x_position, const uint16_t y_position, double facing_direction, uint16_t colour);
};

#endif
