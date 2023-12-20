#include "GameScreen.h"
#include "Asteroid.h"

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

    this->player2 = new Player(Display::WIDTH_PIXELS / 2, Display::HEIGHT_PIXELS / 2, 0);
    this->player2->player_colour = p2_colour;
    this->player2->wrap_around_display = true;

    // add health display observer to player
    this->show_health = new ShowHealthOnSSD(player);
    player->add_hurt_observer(show_health);

    // add invincibility frames observer to player
    this->invincibility = new InvincibilityFrames();
    player->add_hurt_observer(invincibility);

    this->score = new Score(display, Score::X_POS_TEXT, Score::Y_POS_TEXT);

    this->waves = new Waves(this->MAX_AMOUNT_OF_OBJECTS);
    this->waves->start_new();
}

GameScreen::~GameScreen()
{
    delete this->asteroid_container;
    this->asteroid_container = nullptr;
    delete this->bullet_container;
    this->bullet_container = nullptr;
    delete this->show_health;
    this->show_health = nullptr;
    delete this->invincibility;
    this->invincibility = nullptr;
    delete this->player;
    this->player = nullptr;
    delete this->score;
    this->score = nullptr;
    delete this->waves;
    this->waves = nullptr;
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

    // handle IR

    // convert direction to uint16_t:
    // - add PI to make it always positive
    // - multiply by 100 so decimals can be safely truncated
    // - shift right to save 1 bit at the cost of accuracy
    // - reverse these steps on receive

    // SPAWNING_ASTEROIDS is the final phase of the Wave switch
    // which is when we stop communicating the wave switch.
    if (this->waves->is_spawning_asteroids())
        this->wave_ended = false;

    uint16_t send_dir = (uint16_t)((this->player->facing_direction + M_PI) * 100) >> 1;
    uint32_t game_data = IREndec::encode_game(
        (uint16_t)this->player->get_x_position(),
        (uint8_t)this->player->get_y_position(),
        send_dir,
        this->wave_ended,
        false, // player death is communicated in the high score screen. so here the player is always considered alive
        this->shot_bullet);
    this->infrared->send_data(game_data);
    // set back to default (false)
    this->shot_bullet = false;

    if (this->player->health <= this->player->GAME_OVER_HEALTH)
    {
        this->ready_for_screen_switch = true;
    }

    if (player2->active)
    {
        this->process_player_2();
    }

    // draw
    this->player->draw(this->display);
    this->score->draw(this->display);
    this->asteroid_container->draw_objects();
    this->bullet_container->draw_objects();

    this->waves->update(display, delta, this->asteroid_container);

    // checks if the wave is about to start spawning asteroids
    // if so, makes the player invincible
    if (this->waves->is_spawning_asteroids())
        this->invincibility->update(this->player);
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
                break; // if bullet has already hit 1 asteroid, break out of asteroid checking loop for this bullet, prevents game crash
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
    {
        this->waves->next();
        this->wave_ended = true;
    }
}

void GameScreen::process_player_2()
{
    uint32_t p2_data = this->infrared->get_received_data();
    if (p2_data == 0)
        return;

    GameData game_data = IREndec::decode_game(p2_data);

    // if other player died, undraw once
    if (game_data.player_died)
    {
        this->player2->undraw(this->display);
        this->player2->active = false;
        return;
    }

    this->player2->set_x_position(game_data.player_x_position);
    this->player2->set_y_position(game_data.player_y_position);
    this->player2->facing_direction = game_data.player_facing_direction;

    if (game_data.player_shot_bullet)
    {
        Bullet *bullet = new Bullet(this->player2->get_x_position(), this->player2->get_y_position(), this->player2->facing_direction, this->player2->player_colour);
        this->bullet_container->add_object(bullet);
    }

    // if wave_ended was given, but we still have asteroids on our side
    // there's a sync issue!
    // fix by removing all asteroids and forcing next wave start.
    if (
        game_data.wave_ended && !this->waves->is_drawing() // already busy switching wave
        && !this->asteroid_container->objects.empty())     // asteroids remaining = sync issue
    {
        this->score->add_score(this->asteroid_container->objects.size() * 50);
        this->asteroid_container->undraw_objects();
        this->asteroid_container->objects.clear();
        this->waves->next();
    }

    this->player2->draw(this->display);
}

void GameScreen::check_player_asteroid_collision()
{
    // calculate and store centered player x and y
    int16_t rear_player_x = this->player->get_x_position();
    int16_t front_player_x = this->player->get_front_x_position();

    int32_t centered_player_x;
    if (rear_player_x > front_player_x)
    {
        centered_player_x = rear_player_x - ((rear_player_x - front_player_x) / 2);
    }
    else
    {
        centered_player_x = rear_player_x + ((front_player_x - rear_player_x) / 2);
    }

    int16_t rear_player_y = this->player->get_y_position();
    int16_t front_player_y = this->player->get_front_y_position();
    int32_t centered_player_y;

    if (rear_player_y > front_player_y)
    {
        centered_player_y = rear_player_y - ((rear_player_y - front_player_y) / 2);
    }
    else
    {
        centered_player_y = rear_player_y + ((front_player_y - rear_player_y) / 2);
    }
    for (uint8_t j = 0; j < this->asteroid_container->objects.size(); ++j)
    {
        // store asteroid x and y
        uint16_t asteroid_x = this->asteroid_container->objects.at(j)->get_x_position();
        uint16_t asteroid_y = this->asteroid_container->objects.at(j)->get_y_position();

        // call player.hurt() if collided

        if (!this->player->is_invincible && player_asteroid_colliding(centered_player_x, centered_player_y, asteroid_x, asteroid_y))
            this->player->hurt(this->display);
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
        if (!joystick->c_pressed_last_frame && Bullet::bullet_amount < Bullet::MAX_BULLETS)
        {
            buzzer.short_beep();
            Bullet::bullet_amount++;
            this->shot_bullet = true;

            Bullet *bullet = new Bullet(player->get_x_position(), player->get_y_position(), player->facing_direction, player->player_colour);
            bullet->shot_by_player1 = true;
            this->bullet_container->add_object(bullet);
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

bool GameScreen::player_asteroid_colliding(int32_t x_player, int32_t y_player, uint16_t x_asteroid, uint16_t y_asteroid)
{
    int32_t x_distance = x_player - x_asteroid;
    int32_t y_distance = y_player - y_asteroid;
    return (sq(x_distance) + sq(y_distance)) < (sq(Asteroid::ASTEROID_SIZE) + sq(Player::PLAYER_SIZE));
}
