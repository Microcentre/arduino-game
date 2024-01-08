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
    ScreenHandler(Display *display, Joystick *joystick, IR *infrared);

    ~ScreenHandler();

    /// @brief Switches the screen between the player select screen and the game screen.
    void switch_screen();

    /// @brief Updates the current screen.
    /// @param delta represents the time since the last frame.
    void update(const double &delta);

private:
    /// @brief used to show a black screen between switching screens, passed to Screens
    Display *display;

    /// @brief passed to Screens
    Joystick *joystick;

    /// @brief passed to Screens
    IR *infrared;

    /// @brief null when other Screen is active, set when GameScreen is active
    GameScreen *game_screen;

    /// @brief null when other Screen is active, set when PlayerSelectScreen is active
    PlayerSelectScreen *select_screen;

    /// @brief null when other Screen is active, set when HighscoreScreen is active
    HighscoreScreen *highscore_screen;

    /// @brief currently active Screen
    /// points to either game_screen, select_screen or highscore_screen
    Screen *current_screen;

    /// @brief used to store scores. when game ends the new score is added to the ScoreList.
    ScoreList *scores;
};

#endif