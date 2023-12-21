#include "PlayerSelectScreen.h"

PlayerSelectScreen::PlayerSelectScreen(Display *display, Joystick *joystick, IR *infrared) : Screen(display, joystick, infrared)
{
    // create player icons and selection icon
    this->p1 = new Player(PLAYER_LEFT_X, PLAYER_Y, 0);
    this->p1->draw(display, this->p1->get_x_position(), this->p1->get_y_position(), this->p1->facing_direction, ILI9341_CYAN);
    this->p2 = new Player(PLAYER_RIGHT_X, PLAYER_Y, 0);
    this->p2->draw(display, this->p2->get_x_position(), this->p2->get_y_position(), this->p2->facing_direction, ILI9341_ORANGE);
}

PlayerSelectScreen::~PlayerSelectScreen()
{
    delete this->p1;
    this->p1 = nullptr;
    delete this->p2;
    this->p2 = nullptr;
}

void PlayerSelectScreen::update(const double &delta)
{
    if (display->ts.touched())
    {
        on_screen_touched();
    }
    Screen::update(delta);
    drawHud(delta);
}

void PlayerSelectScreen::drawHud(const double &delta)
{
    // displays the text and selection box
    display->canvas.setTextSize(5);
    display->canvas.setTextWrap(false);
    display->canvas.setTextColor(TITLE_COLOUR);
    display->draw_centred_text("\'ROIDS", SCREEN_CENTRE_X_POS, TITLE_Y);

    display->canvas.setTextSize(2);
    display->canvas.setTextColor(TEXT_COLOUR);
    display->draw_centred_text("SELECT SHIP", SCREEN_CENTRE_X_POS, SELECT_PLAYER_TEXT_Y);

    if (left_selected)
    {
        display->canvas.drawRect(SELECT_BOX_X_LEFT, SELECT_BOX_Y, SELECT_BOX_SIZE, SELECT_BOX_SIZE, ILI9341_WHITE);
        display->canvas.drawRect(SELECT_BOX_X_RIGHT, SELECT_BOX_Y, SELECT_BOX_SIZE, SELECT_BOX_SIZE, ILI9341_BLACK);
        this->p1->player_colour = ILI9341_CYAN;
        this->p2->player_colour = ILI9341_ORANGE;
    }
    else
    {
        display->canvas.drawRect(SELECT_BOX_X_LEFT, SELECT_BOX_Y, SELECT_BOX_SIZE, SELECT_BOX_SIZE, ILI9341_BLACK);
        display->canvas.drawRect(SELECT_BOX_X_RIGHT, SELECT_BOX_Y, SELECT_BOX_SIZE, SELECT_BOX_SIZE, ILI9341_WHITE);
        this->p1->player_colour = ILI9341_ORANGE;
        this->p2->player_colour = ILI9341_CYAN;
    }
}

void PlayerSelectScreen::on_joystick_changed()
{
    if (left_selected && this->joystick->get_x_axis() > 200)
    {
        buzzer.short_beep();
        left_selected = false;
    }
    else if (!left_selected && this->joystick->get_x_axis() < 70)
    {
        buzzer.short_beep();
        left_selected = true;
    }

    if (this->joystick->is_z_pressed())
    {
        buzzer.medium_beep();
        // select this player
        this->ready_for_screen_switch = true;
    }
}

void PlayerSelectScreen::on_screen_touched()
{
    // check if the player has touched the left or right side of the screen
    TS_Point touch_point = display->ts.getPoint();

    // x and y are swapped to match the screen orientation
    uint16_t touch_point_x = Display::WIDTH_PIXELS - touch_point.y; // invert x to account for rotation
    uint16_t touch_point_y = touch_point.x;

    if (touch_point_y > SELECT_BOX_Y && touch_point_y < SELECT_BOX_Y + SELECT_BOX_SIZE)
    {
        if (touch_point_x > SELECT_BOX_X_LEFT && touch_point_x < SELECT_BOX_X_LEFT + SELECT_BOX_SIZE)
        {
            if (left_selected)
            {
                buzzer.medium_beep();
                ready_for_screen_switch = true;
            }
            else
            {
                buzzer.short_beep();
                left_selected = true;
            }
        }
        else if (touch_point_x > SELECT_BOX_X_RIGHT && touch_point_x < SELECT_BOX_X_RIGHT + SELECT_BOX_SIZE)
        {
            if (!left_selected)
            {
                buzzer.medium_beep();
                ready_for_screen_switch = true;
            }
            else
            {
                buzzer.short_beep();
                left_selected = false;
            }
        }
    }
}
