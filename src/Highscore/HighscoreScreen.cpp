#include "HighscoreScreen.h"

HighscoreScreen::HighscoreScreen(Display *display, Joystick *joystick, ScoreList *scores) : Screen(display, joystick)
{
    this->scores = scores;
}

HighscoreScreen::~HighscoreScreen()
{
    //Do NOT delete scores* reference!
}

void HighscoreScreen::update(const double &delta)
{
    Screen::update(delta);
    drawHud(this->scores);
}

void HighscoreScreen::drawHud(ScoreList *scores)
{
    text_height = height;
    display->canvas.setTextSize(TITLE_SIZE);
    display->canvas.setTextWrap(false);
    display->canvas.setTextColor(TEXT_COLOUR);

    display->draw_centred_text("Highscores", SCREEN_CENTRE_X_POS, text_height); // title
    text_height += height;

    display->canvas.setTextSize(SCORES_SIZE);

    for (uint8_t i = 0; i < scores->size; i++)
    {
        uint16_t score = scores->get(i); // get score

        auto text = (String)(i + 1) + ": " + (String)score; // convert to string

        display->draw_centred_text(text, SCREEN_CENTRE_X_POS, text_height); // draw scores
        text_height += height;
    }

    display->canvas.setTextSize(CONTINUE_TEXT_SIZE);
    display->draw_centred_text("Press Z to return to menu", SCREEN_CENTRE_X_POS, CONTINUE_TEXT_HEIGHT); // continue text
}

void HighscoreScreen::on_joystick_changed()
{
    if (joystick->is_z_pressed())
    {
        buzzer.medium_beep(); // play sound
        ready_for_screen_switch = true; // switch screen
    }
}