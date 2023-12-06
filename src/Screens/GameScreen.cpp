#include "GameScreen.h"
#include "Bullet.h"
#include "Asteroid.h"

GameScreen::GameScreen(Display *display, Joystick *joystick) : Screen(display, joystick), ObjectsContainer(display)
{

    // create player
    this->player = new Player(Display::WIDTH_PIXELS / 2, Display::HEIGHT_PIXELS / 2, 100); // start around the centre
    this->player->wrap_around_display = true;
    this->add_object(this->player);

    // create asteroid
    this->add_object(new Asteroid(50, 50, 80, M_PI_2));
}

GameScreen::~GameScreen()
{
    delete Screen::joystick;
    delete Screen::display;
    delete this->player;
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
    if (joystick->is_c_pressed() && Bullet::bullet_created == false)
    {
        this->add_object(new Bullet(player->get_x_position(), player->get_y_position(), player->facing_direction));
        Bullet::bullet_created = true;
    }
}

bool GameScreen::bullet_asteroid_colliding(uint16_t x_bullet, uint16_t y_bullet, uint16_t x_asteroid, uint16_t y_asteroid){
    uint16_t x_distance = x_bullet - x_asteroid;
    uint16_t y_distance = y_bullet - y_asteroid;    
    return (sq(x_distance) + sq(y_distance)) < sq(ASTEROID_SIZE);
}

