#ifndef GAMESCREEN_H
#define GAMESCREEN_H

#include <Vector.h>
#include "Joystick.h"
#include "Display.h"
#include "Player.h"
#include "Object.h"
#include "Screen.h"
#include "ObjectsContainer.h"
#include "Score.h"

class GameScreen : public Screen
{
public:
    Player *player;

    ObjectsContainer *asteroid_container;
    ObjectsContainer *bullet_container;
    Score *score;

    GameScreen(Display *display, Joystick *joystick, uint16_t p1_colour, uint16_t p2_colour);
    virtual ~GameScreen();

    /// @brief checks nunchuck and updates all objects in vector array, called every frame
    /// @param delta seconds since last frame
    void update(const double &delta) override;

    /// @brief updates player actions using joystick values
    void on_joystick_changed() override;

    /// @brief checks each bullet for collision with all of the asteroids.
    /// if bullet collides, both bullet and asteroid are removed.
    void check_bullet_asteroid_collision();

    /// @brief checks the player for collision with all of the asteroids.
    /// if player collides, player.hurt() is called
    void check_player_asteroid_collision();

    /// @brief calculate if x,y of bullet are within radius of asteroid.
    /// using pythagoras to calculate the distance between two points if the square root of both distances is less than the radius,
    // the bullet is inside of the asteroid, therefore it has collided.
    /// @param x_bullet x-coordinate of center of bullet
    /// @param y_bullet y-coordinate of center of bullet
    /// @param x_asteroid x-coordinate of center of asteroid
    /// @param y_asteroid y-coordinate of center of asteroid
    /// @return returns true if center of bullet is within radius of asteroid
    bool bullet_asteroid_colliding(uint16_t x_bullet, uint16_t y_bullet, uint16_t x_asteroid, uint16_t y_asteroid);

    /// @brief calculate if x,y of player are within radius of asteroid.
    /// using pythagoras to calculate the distance between two points if the square root of both distances is less than the radius of both the player and the asteroid,
    // the player is inside of the asteroid, therefore it has collided.
    /// @param x_bullet x-coordinate of center of player
    /// @param y_bullet y-coordinate of center of player
    /// @param x_asteroid x-coordinate of center of asteroid
    /// @param y_asteroid y-coordinate of center of asteroid
    /// @return returns true if radius of player is within radius of asteroid
    bool player_asteroid_colliding(uint16_t x_player, uint16_t y_player, uint16_t x_asteroid, uint16_t y_asteroid);

private:
    /// @brief max array size for asteroids and bullet containers
    static constexpr uint8_t MAX_AMOUNT_OF_OBJECTS = 15;

    uint8_t current_wave;

    /// @brief called when an asteroid is destroyed. starts a new wave
    void on_asteroid_destroyed();

    /// @brief start wave by spawning asteroids
    /// @param wave the wave number to start
    void start_wave(uint8_t wave);
};

#endif
