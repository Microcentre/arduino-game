#ifndef HIGHSCORESCREEN_H
#define HIGHSCORESCREEN_H

#include "Screen.h"
#include "Score.h"
#include "ScoreList.h"
#include "../Hardware/Buzzer.h"

class HighscoreScreen : public Screen
{

public:
    HighscoreScreen(Display *display, Joystick *joystick, ScoreList *scores);

    virtual ~HighscoreScreen();

    void update(const double &delta) override;

    void drawHud(ScoreList *scores);

    void on_joystick_changed() override;

private:
    uint8_t text_height = 40;

    uint8_t previous_text_height = 0;

    const uint16_t TEXT_COLOUR = ILI9341_WHITE;

    const uint8_t screen_centre_x_pos = Display::WIDTH_PIXELS / 2;

    /// @brief buzzer property
    Buzzer buzzer = Buzzer();
};

#endif