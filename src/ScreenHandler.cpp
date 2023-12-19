#include "ScreenHandler.h"

ScreenHandler::ScreenHandler(Display *display, Joystick *joystick, IR *infrared)
{
    this->display = display;
    this->joystick = joystick;
    this->infrared = infrared;
    this->select_screen = new PlayerSelectScreen(display, joystick, infrared);
    this->current_screen = this->select_screen;
    this->scores = new ScoreList();
}

ScreenHandler::~ScreenHandler()
{
    delete this->select_screen;
    this->select_screen = nullptr;
    delete this->game_screen;
    this->game_screen = nullptr;
    delete this->highscore_screen;
    this->highscore_screen = nullptr;
    delete this->scores;
    this->scores = nullptr;
}

void ScreenHandler::switch_screen()
{
    this->display->canvas.fillScreen(this->display->background_colour);
    if (this->current_screen == this->select_screen)
    {
        this->game_screen = new GameScreen(display, joystick, infrared, select_screen->p1->player_colour, select_screen->p2->player_colour);
        this->current_screen = this->game_screen;

        delete this->select_screen;
        this->select_screen = nullptr;
    }
    else if (this->current_screen == this->game_screen)
    {
        this->scores->insert(this->game_screen->score->score);

        delete this->game_screen;
        this->game_screen = nullptr;

        this->highscore_screen = new HighscoreScreen(display, joystick, infrared, scores);
        this->current_screen = this->highscore_screen;
    }
    else if (this->current_screen == this->highscore_screen)
    {
        delete this->highscore_screen;
        this->highscore_screen = nullptr;

        this->select_screen = new PlayerSelectScreen(display, joystick, infrared);
        this->current_screen = this->select_screen;
    }
}

void ScreenHandler::update(const double &delta)
{
    if (this->current_screen->ready_for_screen_switch)
    {
        this->switch_screen();
    }
    this->current_screen->update(delta);
}