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

class GameScreen : public Screen, public ObjectsContainer
{
public:
    Player *player;

    Score *score;

    GameScreen(Display *display, Joystick *joystick);
    virtual ~GameScreen();

    /// @brief checks nunchuck and updates all objects in vector array, called every frame
    /// @param delta seconds since last frame
    void update(const double &delta) override;

    /// @brief updates player actions using joystick values
    void on_joystick_changed() override;
};

#endif
