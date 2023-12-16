#include "ScreenHandler.h"

ScreenHandler::ScreenHandler(Display *display, Joystick *joystick)
{
    this->display = display;
    this->joystick = joystick;
    this->select_screen = new PlayerSelectScreen(display, joystick);
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
        this->game_screen = new GameScreen(display, joystick, select_screen->p1->player_colour, select_screen->p2->player_colour);
        this->current_screen = this->game_screen;

        delete this->select_screen;
        this->select_screen = nullptr;
    }
    else if (this->current_screen == this->game_screen)
    {
        auto current_score = this->game_screen->score->score;
        scores->insert(current_score);

        this->highscore_screen = new HighscoreScreen(display, joystick, scores);
        this->current_screen = this->highscore_screen;

        delete this->game_screen;
        this->game_screen = nullptr;
    }
    else if (this->current_screen == this->highscore_screen)
    {
        this->select_screen = new PlayerSelectScreen(display, joystick);
        this->current_screen = this->select_screen;
        
        delete this->highscore_screen;
        this->highscore_screen = nullptr;
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