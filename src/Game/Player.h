#ifndef PLAYER_H
#define PLAYER_H

#include "../Objects/MovingObject.h"

class Player : public MovingObject
{
public:
    /// @brief executes specific behavior when player is hurt
    class HurtObserver
    {
    public:
        /// @brief executes observer behavior
        virtual void update(Player *player) = 0;
        virtual ~HurtObserver();
    };

    /// @brief 0: at this health game restarts
    const uint8_t GAME_OVER_HEALTH = 0;

    /// @brief player size from centre to corner, the TOTAL player radius would be 2*PLAYER_SIZE.
    static constexpr uint8_t PLAYER_SIZE = 8;

    /// @brief 16-bit 5-6-5 Colour used when drawn
    uint16_t player_colour;

    /// @brief if the player is currently unkillable
    bool is_invincible = false;

    /// @brief if visually the player is blinking
    bool is_blinking = false;

    /// @brief the amount of time the player has been invincible for
    uint8_t invincibility_timer = 0;

    /// @brief the maximum amount of time the player is invincible for
    static constexpr uint8_t INVINCIBILITY_TIME = 35;

    /// @brief current health of the player. 0=death
    uint8_t health = 3;

    /// @brief [-1..1] where -1=bottom, 0=centre, 1=top
    double facing_direction;

    /// @brief if false, player is not updated or drawn
    bool active = true;

    Player();

    /// @param speed pixels per second
    Player(uint16_t x_position, uint16_t y_position, double speed);

    /// @param delta_s time since last frame in seconds
    void update(const double &delta) override;

    /// @brief rotate the player left or right
    /// @param rotation [0..255] where 0=left, 128=no change, 255=right
    void rotate(const uint8_t rotation);

    /// @brief move player forward in current facing_direction
    void accelerate();

    /// @brief call undraw(), then draw()
    /// @param display display to draw on
    void draw(Display *display) override;

    /// @brief call undraw() using previous_drawing variables
    void undraw(Display *display) override;

    /// @brief clear drawing at given position.
    /// uses the player's previous_drawn_facing_direction for direction
    /// @param display display to draw on
    /// @param x_position X-position of drawing to clear
    /// @param y_position Y-position of the drawing to clear
    void undraw(Display *display, const uint16_t x_position, const uint16_t y_position) override;

    /// @brief clear drawing at given position & rotation
    /// @param display display to draw on
    /// @param x_position X-position of drawing to clear
    /// @param y_position Y-position of the drawing to clear
    void undraw(Display *display, const uint16_t x_position, const uint16_t y_position, double facing_direction);

    /// @brief -1 health, resets player to centre of screen and handles all hurtobservers
    void hurt(Display *display);
    /// @brief adds a new hurtobserver to the observer array
    void add_hurt_observer(Player::HurtObserver *observer);

    /// @return the X position of the front-point of the player
    double get_front_x_position();
    /// @return the Y position of the front-point of the player
    double get_front_y_position();

    /// @brief draws the player. used by draw() and undraw()
    void draw(Display *display, const uint16_t x_position, const uint16_t y_position, double facing_direction, uint16_t colour);

private:
    /// @brief in radians per second (so small numbers)
    static constexpr float TURN_SPEED = 0.25;

    /// @brief the highest value the axis can be
    static const uint8_t MAX_JOYSTICK_AXIS = 255;

    /// @brief acceleration per frame holding the gas button
    static constexpr double ACCEL_RATE = 15.0;

    /// @brief deceleration per frame when not holding the gas button
    static constexpr double DECEL_RATE = 2.0;
    /// @brief Max pixels per second the player may go
    static constexpr double MAX_SPEED = 650;

    /// @brief How pointy the front is. 1=normal (equilateral triangle)
    static constexpr double POINTINESS = 2.5;

    /// @brief array of hurtobservers. Hurtobservers are called when player is hurt.
    /// They include showing health on 7-segment display and handling invincibility of player
    HurtObserver *hurt_observers[2];

    /// @brief size of hurt_observers array
    uint8_t hurt_observers_size = 0;

    /// @brief store previous facing_direction for undraw()
    double previous_draw_facing_direction;
};

#endif
