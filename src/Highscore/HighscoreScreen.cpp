#include "HighscoreScreen.h"
#include "HardwareSerial.h"

HighscoreScreen::HighscoreScreen(Display *display, Joystick *joystick, ScoreList *scores) : Screen(display, joystick)
{
    drawHud(scores);
}

HighscoreScreen::~HighscoreScreen()
{
}

void HighscoreScreen::update(const double &delta)
{
    Screen::update(delta);
}

void HighscoreScreen::drawHud(ScoreList *scores)
{
    display->canvas.setTextSize(2);
    display->canvas.setTextWrap(false);
    display->canvas.setTextColor(TEXT_COLOUR);

    uint16_t height = 20;

    display->draw_centred_text("Highscores", screen_centre_x_pos, text_height);
    text_height += height;

    display->canvas.setTextSize(1);

    for (uint8_t i = 0; i < scores->size; i++)
    {
        const String text = (i + 1) + ". " + scores->get(i);
        display->draw_centred_text(text, screen_centre_x_pos, text_height);
        text_height += height;
    }

    display->draw_centred_text("Press Z to return to menu", screen_centre_x_pos, text_height + height);
}

void HighscoreScreen::on_joystick_changed()
{
    if (joystick->is_z_pressed())
    {
        buzzer.medium_beep();
        ready_for_screen_switch = true;
    }
}