#include "PlayerSelectScreen.h"
#include "Player.h"

PlayerSelectScreen::PlayerSelectScreen(Display *display, Joystick *joystick) : Screen(display, joystick), ObjectsContainer(display)
{
    // create player icons and selection icon
    // Player *p1 = new Player(PLAYER_LEFT_X, PLAYER_Y, 0);
    // Player *p2 = new Player(PLAYER_RIGHT_X, PLAYER_Y, 0);
    // this->add_object(p1);
    // this->add_object(p2);
}

PlayerSelectScreen::~PlayerSelectScreen()
{
}

void PlayerSelectScreen::update(const double &delta)
{
    Screen::update(delta);
    update_objects(delta);
    draw_objects(delta);
    drawHud(delta);
}

void PlayerSelectScreen::drawHud(const double &delta)
{
    Screen::display->canvas.setCursor(TEXT_X, TEXT_Y);
    Screen::display->canvas.setTextColor(ILI9341_WHITE);
    Screen::display->canvas.setTextSize(3);
    Screen::display->canvas.print("SELECT PLAYER");
    if (left_selected) {
        Screen::display->canvas.drawRect(SELECT_BOX_X_LEFT, SELECT_BOX_Y, SELECT_BOX_SIZE, SELECT_BOX_SIZE, ILI9341_WHITE);
        Screen::display->canvas.drawRect(SELECT_BOX_X_RIGHT, SELECT_BOX_Y, SELECT_BOX_SIZE, SELECT_BOX_SIZE, ILI9341_BLACK);
    } else {
        Screen::display->canvas.drawRect(SELECT_BOX_X_LEFT, SELECT_BOX_Y, SELECT_BOX_SIZE, SELECT_BOX_SIZE, ILI9341_BLACK);
        Screen::display->canvas.drawRect(SELECT_BOX_X_RIGHT, SELECT_BOX_Y, SELECT_BOX_SIZE, SELECT_BOX_SIZE, ILI9341_WHITE);
    }
}

void PlayerSelectScreen::on_joystick_changed()
{
    if (left_selected && this->joystick->get_x_axis() > 200) {
        left_selected = false;
    } else if (!left_selected && this->joystick->get_x_axis() < 70) {
        left_selected = true;
    }

    if (this->joystick->is_z_pressed()) {
        // select this player
        this->ready_for_screen_switch = true;
    }
}
