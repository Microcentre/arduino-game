#include "ScreenHandler.h"

ScreenHandler::ScreenHandler(Display *display, Joystick *joystick)
{
    this->display = display;
    this->joystick = joystick;
    this->select_screen = new PlayerSelectScreen(display, joystick);
    this->current_screen = this->select_screen;
}

void ScreenHandler::switch_screen()
{
    if (this->current_screen == this->select_screen)
    {
        delete this->select_screen;
        this->select_screen = nullptr;
        this->game_screen = new GameScreen(display, joystick);
        this->current_screen = this->game_screen;
    }
    else if(this->current_screen == this->game_screen)
    {
        delete this->game_screen;
        this->game_screen = nullptr;
        this->select_screen = new PlayerSelectScreen(display, joystick);
        this->current_screen = this->select_screen;
    }
    this->display->canvas.fillScreen(this->display->background_colour);
}

void ScreenHandler::update(const double &delta)
{
    if (this->current_screen->ready_for_screen_switch)
    {
        this->switch_screen();
    }
    this->current_screen->update(delta);
}