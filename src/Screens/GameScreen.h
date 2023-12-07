#ifndef GAMESCREEN_H
#define GAMESCREEN_H

#include <Vector.h>
#include "Joystick.h"
#include "Display.h"
#include "Player.h"
#include "Object.h"
#include "Screen.h"
#include "ObjectsContainer.h"

class GameScreen : public Screen
{
public:
    Player *player;

    ObjectsContainer *asteroid_container;
    ObjectsContainer *bullet_container;

    GameScreen(Display *display, Joystick *joystick);
    ~GameScreen();

    /// @brief checks nunchuck and updates all objects in vector array, called every frame
    /// @param delta seconds since last frame
    void update(const double &delta) override;

    /// @brief updates player actions using joystick values
    void on_joystick_changed() override;
    
    /// @brief calculate if x,y of bullet are within radius of asteroid.
    /// using pythagoras to calculate the distance between two points if the square root of both distances is less than the radius,
    // the bullet is inside of the asteroid, therefore it has collided.
    /// @param x_bullet x-coordinate of center of bullet
    /// @param y_bullet y-coordinate of center of bullet
    /// @param x_asteroid x-coordinate of center of asteroid
    /// @param y_asteroid y-coordinate of center of asteroid
    /// @return returns true if center of bullet is within radius of asteroid
    bool bullet_asteroid_colliding(uint16_t x_bullet, uint16_t y_bullet, uint16_t x_asteroid, uint16_t y_asteroid);
};

#endif
