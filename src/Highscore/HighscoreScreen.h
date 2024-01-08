#ifndef HIGHSCORESCREEN_H
#define HIGHSCORESCREEN_H

#include "Screen.h"
#include "ScoreList.h"
#include "../Hardware/Buzzer.h"

class HighscoreScreen : public Screen
{

public:
    HighscoreScreen(Display *display, Joystick *joystick, IR *infrared, ScoreList *scores);

    virtual ~HighscoreScreen();

    /// @brief updates the highscore screen and checks for joystick input
    void update(const double &delta) override;

    /// @brief draws the highscore screen
    void drawHud(ScoreList *scores);

    /// @brief updates player actions using joystick values
    void on_joystick_changed() override;

private:
    /// @brief play a sound on continue
    Buzzer buzzer = Buzzer();

    /// @brief the list of scores to display
    ScoreList *scores;

    /// @brief the beginning height of the text
    uint8_t text_height;

    /// @brief text size of title text
    const uint8_t TITLE_SIZE = 4;

    /// @brief text size of score text
    const uint8_t SCORES_SIZE = 2;

    /// @brief text size of the "Press Z to return to menu" text
    const uint8_t CONTINUE_TEXT_SIZE = 1;

    /// @brief the height of the continue text
    const uint8_t CONTINUE_TEXT_HEIGHT = 220;

    /// @brief the colour of the text
    const uint16_t TEXT_COLOUR = ILI9341_WHITE;

    /// @brief the centre x position of the text
    const uint8_t SCREEN_CENTRE_X_POS = Display::WIDTH_PIXELS / 2;

    /// @brief the height of each line of text
    const uint8_t height = 30;

    /// @brief use infrared to tell the other player you died
    void communicate_game_ended();
};

#endif