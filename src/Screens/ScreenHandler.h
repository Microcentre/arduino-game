#ifndef SCREENHANDLER_H
#define SCREENHANDLER_H

#include "PlayerSelectScreen.h"
#include "GameScreen.h"

class ScreenHandler
{
public:
    /// @brief Handles the current screen and switching between screens. Defaults to the player select screen.
    /// @param display the display to draw to.
    /// @param joystick the joystick to read input from.
    ScreenHandler(Display *display, Joystick *joystick);

    /// @brief Switches the screen between the player select screen and the game screen.
    void switch_screen();

    /// @brief Updates the current screen.
    /// @param delta represents the time since the last frame.
    void update(const double &delta);

private:
    Display *display;

    Joystick *joystick;

    GameScreen *game_screen;

    PlayerSelectScreen *select_screen;

    Screen *current_screen;
};

#endif