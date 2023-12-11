#ifndef SCREENHANDLER_H
#define SCREENHANDLER_H

#include "PlayerSelectScreen.h"
#include "GameScreen.h"

class ScreenHandler
{
public:
    ScreenHandler(Display *display, Joystick *joystick);
    void switch_screen();
    void update(const double &delta);

private:
    Display *display;
    Joystick *joystick;
    GameScreen *game_screen;
    PlayerSelectScreen *select_screen;
    Screen *current_screen;
};

#endif