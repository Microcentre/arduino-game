#include "GameScreen.h"
#include "Bullet.h"
#include "Asteroid.h"

GameScreen::GameScreen(Display *display, Joystick *joystick) : Screen(display, joystick), ObjectsContainer(display)
{

    // create player
    this->player = new Player(Display::WIDTH_PIXELS / 2, Display::HEIGHT_PIXELS / 2, 100); // start around the centre
    this->player->wrap_around_display = true;
    this->add_object(this->player);

    this->score = new Score(display, Score::X_POS_TEXT, Score::Y_POS_TEXT);
    this->add_object(this->score);

    // create asteroid
    this->add_object(new Asteroid(50, 50, 80, M_PI_2));
}

GameScreen::~GameScreen()
{
    delete Screen::joystick;
    delete Screen::display;
    delete this->player;
    delete this->score;
}

void GameScreen::update(const double &delta)
{
    Screen::update(delta);
    update_objects(delta);
    draw_objects(delta);
}

void GameScreen::on_joystick_changed()
{
    this->player->rotate(this->joystick->get_x_axis());
    // Z = accelerate
    if (this->joystick->is_z_pressed())
    {
        this->player->accelerate();
    }

    // C = shoot
    if (joystick->is_c_pressed() && Bullet::bullet_amount < Bullet::MAX_BULLETS && Bullet::bullet_delay_passed == true)
    {
        Bullet::bullet_delay_passed = false;
        this->add_object(new Bullet(player->get_x_position(), player->get_y_position(), player->facing_direction));
        Bullet::bullet_amount++;
    }
}
