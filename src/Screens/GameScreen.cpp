#include "GameScreen.h"
#include "Bullet.h"
#include "Asteroid.h"
#include "ShowHealthOnSSD.h"

GameScreen::GameScreen(Display *display, Joystick *joystick, IR *infrared, uint16_t p1_colour, uint16_t p2_colour) : Screen(display, joystick, infrared)
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
    // create player 2, processed through IR
    this->player2 = new Player(Display::WIDTH_PIXELS / 2, Display::HEIGHT_PIXELS / 2, 100);
    this->player2->player_colour = p2_colour;
    this->player2->wrap_around_display = true;

    // add health display observer to player
    ShowHealthOnSSD *h1 = new ShowHealthOnSSD(player);
    player->add_hurt_observer(h1);

    // start first wave (won't work in main.cpp for some reason..)
    start_wave(1);
    this->score = new Score(display, Score::X_POS_TEXT, Score::Y_POS_TEXT);
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

    // handle infrared (send and receive)
    this->infrared->send_joystick(this->joystick);

    // process player 2

    // player 2 joystick
    uint16_t joystick2 = infrared->interpret_data(IR::DataIndex::PLAYER_X);
    if (joystick2)
    {
        uint8_t joy2_x_axis = (joystick2 & JOY_MASK_X_AXIS) >> 2;
        this->player->rotate(joy2_x_axis);
        // Z = accelerate
        if (joystick2 & (JOY_MASK_Z_BUTTON))
        {
            this->player->accelerate();
        }

        // C = shoot
        if (joystick2 & JOY_MASK_C_BUTTON)
        {
            if (Bullet::bullet_amount < Bullet::MAX_BULLETS)
            {
                this->bullet_container->add_object(new Bullet(player->get_x_position(), player->get_y_position(), player->facing_direction, player->player_colour));
                Bullet::bullet_amount++;
            }
        }
    }
    this->player2->update(delta);

    if (this->player->health <= this->player->GAME_OVER_HEALTH)
    {
        this->ready_for_screen_switch = true;
    }

    // draw
    this->player->draw(this->display);
    this->player2->draw(this->display);
    this->score->draw(this->display);
    this->asteroid_container->draw_objects(delta);
    this->bullet_container->draw_objects(delta);
}

void GameScreen::check_bullet_asteroid_collision()
{
    for (uint8_t i = 0; i < this->bullet_container->objects.size(); ++i)
    {
        // store bullet x and y
        uint16_t bullet_x = this->bullet_container->objects.at(i)->get_x_position();
        uint16_t bullet_y = this->bullet_container->objects.at(i)->get_y_position();

        for (uint8_t j = 0; j < this->asteroid_container->objects.size(); ++j)
        {
            // store asteroid x and y
            uint16_t asteroid_x = this->asteroid_container->objects.at(j)->get_x_position();
            uint16_t asteroid_y = this->asteroid_container->objects.at(j)->get_y_position();

            // mark colliding bullet and asteroid for deletion
            if (bullet_asteroid_colliding(bullet_x, bullet_y, asteroid_x, asteroid_y))
            {
                this->bullet_container->objects.at(i)->marked_for_deletion = true;
                this->asteroid_container->objects.at(j)->marked_for_deletion = true;
                this->score->add_score(Asteroid::SCORE_ASTEROID);
            }
        }
    }
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
    switch (wave)
    {
    case 1:
        this->asteroid_container->add_object(new Asteroid(50, 00, 40, 0));
        this->asteroid_container->add_object(new Asteroid(150, 50, 80, M_PI));
        this->asteroid_container->add_object(new Asteroid(200, 100, 100, 1));
        this->asteroid_container->add_object(new Asteroid(250, 150, 150, 4));
        break;
    default:
        break;
    }
}
