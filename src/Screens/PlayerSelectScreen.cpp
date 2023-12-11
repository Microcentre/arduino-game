#include "PlayerSelectScreen.h"
#include "Player.h"

PlayerSelectScreen::PlayerSelectScreen(Display *display, Joystick *joystick) : Screen(display, joystick)
{
    // create player icons and selection icon
    this->p1 = new Player(PLAYER_LEFT_X, PLAYER_Y, 0);
    this->p1->player_colour = ILI9341_CYAN;
    this->p2 = new Player(PLAYER_RIGHT_X, PLAYER_Y, 0);
    this->p2->player_colour = ILI9341_ORANGE;
}

PlayerSelectScreen::~PlayerSelectScreen()
{
}

void PlayerSelectScreen::update(const double &delta)
{
    Screen::update(delta);
    drawHud(delta);

    this->p1->update(delta);
    this->p2->update(delta);

    this->p1->draw(this->display);
    this->p2->draw(this->display);
}

void PlayerSelectScreen::drawHud(const double &delta)
{
    Screen::display->canvas.setCursor(TEXT_X, TEXT_Y);
    Screen::display->canvas.setTextColor(ILI9341_WHITE);
    Screen::display->canvas.setTextSize(3);
    Screen::display->canvas.print("SELECT PLAYER");
    if (left_selected)
    {
        Screen::display->canvas.drawRect(SELECT_BOX_X_LEFT, SELECT_BOX_Y, SELECT_BOX_SIZE, SELECT_BOX_SIZE, ILI9341_WHITE);
        Screen::display->canvas.drawRect(SELECT_BOX_X_RIGHT, SELECT_BOX_Y, SELECT_BOX_SIZE, SELECT_BOX_SIZE, ILI9341_BLACK);
    }
    else
    {
        Screen::display->canvas.drawRect(SELECT_BOX_X_LEFT, SELECT_BOX_Y, SELECT_BOX_SIZE, SELECT_BOX_SIZE, ILI9341_BLACK);
        Screen::display->canvas.drawRect(SELECT_BOX_X_RIGHT, SELECT_BOX_Y, SELECT_BOX_SIZE, SELECT_BOX_SIZE, ILI9341_WHITE);
    }
}

void PlayerSelectScreen::on_joystick_changed()
{
    if (left_selected && this->joystick->get_x_axis() > 200)
    {
        left_selected = false;
    }
    else if (!left_selected && this->joystick->get_x_axis() < 70)
    {
        left_selected = true;
    }

    if (this->joystick->is_z_pressed())
    {
        // select this player
        this->ready_for_screen_switch = true;
    }
}
