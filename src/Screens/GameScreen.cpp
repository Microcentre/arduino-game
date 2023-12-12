#include "GameScreen.h"
#include "Bullet.h"
#include "Asteroid.h"
#include "ShowHealthOnSSD.h"

GameScreen::GameScreen(Display *display, Joystick *joystick, uint16_t p1_colour, uint16_t p2_colour) : Screen(display, joystick)
{
    // array of objects on the screen to be updated & rendered.
    // Vector<> is a custom library that IS dynamic,
    // which for some reason has to be intialised in this hacky way
    Object *asteroid_array[MAX_AMOUNT_OF_OBJECTS];
    Object *bullet_array[MAX_AMOUNT_OF_OBJECTS];
    Vector<Object *> asteroid_vector = Vector<Object *>(asteroid_array);
    Vector<Object *> bullet_vector = Vector<Object *>(bullet_array);
    this->asteroid_container = new ObjectsContainer(this->display, asteroid_vector);
    this->bullet_container = new ObjectsContainer(this->display, bullet_vector);

    // create player
    this->player = new Player(Display::WIDTH_PIXELS / 2, Display::HEIGHT_PIXELS / 2, 100); // start around the centre
    this->player->player_colour = p1_colour;
    this->player->wrap_around_display = true;

    // add health display observer to player
    ShowHealthOnSSD *h1 = new ShowHealthOnSSD(player);
    player->add_hurt_observer(h1);

    this->score = new Score(display, Score::X_POS_TEXT, Score::Y_POS_TEXT);

    this->current_wave = 1;
    start_wave(this->current_wave);
}

GameScreen::~GameScreen()
{
    delete this->player;
    this->player = nullptr;
    delete this->score;
    this->score = nullptr;
}

void GameScreen::update(const double &delta)
{
    // check for collision
    check_bullet_asteroid_collision();
    check_player_asteroid_collision();

    // update
    Screen::update(delta);
    this->player->update(delta);
    this->score->update(delta);
    this->bullet_container->update_objects(delta);
    this->asteroid_container->update_objects(delta);

    if (this->player->health <= this->player->GAME_OVER_HEALTH)
    {
        this->ready_for_screen_switch = true;
    }

    // draw
    this->player->draw(this->display);
    this->score->draw(this->display);
    this->asteroid_container->draw_objects(delta);
    this->bullet_container->draw_objects(delta);
}

void GameScreen::check_bullet_asteroid_collision()
{
    // for each bullet, check if it collides with any asteroid
    auto i = this->bullet_container->objects.begin();
    while (i != this->bullet_container->objects.end())
    {
        bool deleted = false;
        Object *bullet = (*i);
        uint16_t bullet_x_position = bullet->get_x_position();
        uint8_t bullet_y_position = bullet->get_y_position();

        auto j = this->asteroid_container->objects.begin();
        while (j != this->asteroid_container->objects.end())
        {
            Object *asteroid = (*j);
            uint16_t asteroid_x_position = asteroid->get_x_position();
            uint8_t asteroid_y_position = asteroid->get_y_position();

            // if a bullet is hitting an asteroid
            if (bullet_asteroid_colliding(bullet_x_position, bullet_y_position, asteroid_x_position, asteroid_y_position))
            {
                deleted = true;
                // delete both bullet and asteroid
                this->bullet_container->delete_object(bullet);
                this->asteroid_container->delete_object(asteroid);

                this->on_asteroid_destroyed();
            }
            // only increment if didn't delete asteroid
            else
                ++j;
        }

        // only increment if bullet wasn't deleted
        if (!deleted)
            ++i;
    }
}

void GameScreen::on_asteroid_destroyed()
{
    // add score
    this->score->add_score(Asteroid::SCORE_ASTEROID);

    // start a new wave when no asteroids are left
    if (this->asteroid_container->get_size() <= 0)
        start_wave(++this->current_wave);
}

void GameScreen::check_player_asteroid_collision()
{
    // calculate and store centered player x and y
    uint16_t rear_player_x = this->player->get_x_position();
    uint16_t front_player_x = this->player->get_front_x_position();
    uint16_t centered_player_x = rear_player_x + ((front_player_x - rear_player_x) / 2);

    uint16_t rear_player_y = this->player->get_y_position();
    uint16_t front_player_y = this->player->get_front_y_position();
    uint16_t centered_player_y = rear_player_y + ((front_player_y - rear_player_y) / 2);

    for (uint8_t j = 0; j < this->asteroid_container->objects.size(); ++j)
    {
        // store asteroid x and y
        uint16_t asteroid_x = this->asteroid_container->objects.at(j)->get_x_position();
        uint16_t asteroid_y = this->asteroid_container->objects.at(j)->get_y_position();

        // call player.hurt() if collided
        if (player_asteroid_colliding(centered_player_x, centered_player_y, asteroid_x, asteroid_y))
        {
            this->player->hurt(this->display);
        }
    }
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
    if (joystick->is_c_pressed())
    {
        if (!(joystick->c_pressed_last_frame) && Bullet::bullet_amount < Bullet::MAX_BULLETS)
        {
            this->bullet_container->add_object(new Bullet(player->get_x_position(), player->get_y_position(), player->facing_direction, player->player_colour));
            Bullet::bullet_amount++;
        }
        joystick->c_pressed_last_frame = true;
    }
    else
    {
        joystick->c_pressed_last_frame = false;
    }
}

bool GameScreen::bullet_asteroid_colliding(uint16_t x_bullet, uint16_t y_bullet, uint16_t x_asteroid, uint16_t y_asteroid)
{
    uint16_t x_distance = x_bullet - x_asteroid;
    uint16_t y_distance = y_bullet - y_asteroid;
    return (sq(x_distance) + sq(y_distance)) < sq(Asteroid::ASTEROID_SIZE);
}

bool GameScreen::player_asteroid_colliding(uint16_t x_player, uint16_t y_player, uint16_t x_asteroid, uint16_t y_asteroid)
{
    uint16_t x_distance = x_player - x_asteroid;
    uint16_t y_distance = y_player - y_asteroid;
    return (sq(x_distance) + sq(y_distance)) < sq(Asteroid::ASTEROID_SIZE + Player::PLAYER_SIZE);
}

void GameScreen::start_wave(uint8_t wave)
{
    for (uint8_t i = 0; i < wave; ++i)
    {
        uint16_t screen_width = Display::WIDTH_PIXELS;
        uint8_t screen_height = Display::HEIGHT_PIXELS;
        uint16_t random_x_position = (uint16_t)rand() % screen_width + 1;
        uint8_t random_y_position = rand() % screen_height + 1;
        uint8_t random_speed = rand() % 100 + 1;

        uint16_t m_10_pi = M_PI * 10;
        double random_direction = (rand() % m_10_pi) / 10;

        this->asteroid_container->add_object(new Asteroid(random_x_position, random_y_position, random_speed, random_direction));
    }
}
