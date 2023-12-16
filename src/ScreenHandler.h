#ifndef SCREENHANDLER_H
#define SCREENHANDLER_H

#include "PlayerSelect/PlayerSelectScreen.h"
#include "Game/GameScreen.h"
#include "Highscore/HighscoreScreen.h"

class ScreenHandler
{
public:
    /// @brief Handles the current screen and switching between screens. Defaults to the player select screen.
    /// @param display the display to draw to.
    /// @param joystick the joystick to read input from.
    ScreenHandler(Display *display, Joystick *joystick);

    ~ScreenHandler();

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

    HighscoreScreen *highscore_screen;

    Screen *current_screen;

    ScoreList *scores;
};

#endif