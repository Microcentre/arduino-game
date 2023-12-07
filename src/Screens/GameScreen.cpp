#include "GameScreen.h"
#include "Bullet.h"
#include "Asteroid.h"

GameScreen::GameScreen(Display *display, Joystick *joystick) : Screen(display, joystick)
{
    Object *objects_array1[50];
    Object *objects_array2[50];

    Vector<Object *> vec1 = Vector<Object *>(objects_array1);
    Vector<Object *> vec2 = Vector<Object *>(objects_array2);


    this->asteroid_container = new ObjectsContainer(this->display, vec1);
    this->bullet_container = new ObjectsContainer(this->display, vec2);




    // create player
    this->player = new Player(Display::WIDTH_PIXELS / 2, Display::HEIGHT_PIXELS / 2, 100); // start around the centre
    this->player->wrap_around_display = true;

    // create asteroid
    this->asteroid_container->add_object(new Asteroid(50, 00, 40, 0));
    this->asteroid_container->add_object(new Asteroid(150, 50, 80, M_PI));
    this->asteroid_container->add_object(new Asteroid(200, 100, 100, 1));
    this->asteroid_container->add_object(new Asteroid(250, 150, 150, 4));
    this->asteroid_container->add_object(new Asteroid(50, 200, 130, M_PI_2));
    this->asteroid_container->add_object(new Asteroid(100, 250, 20, M_PI));
    //this->asteroid_container->add_object(new Asteroid(150, 150, 80, M_PI_2));
    this->bullet_container->add_object(new Asteroid(100, 100, 80, 1));
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
    this->player->update(delta);
    this->player->draw(this->display);

    //Serial.println("BULL: ");
    this->bullet_container->update_objects(delta);
    //_delay_ms(100);
    //Serial.println("ASS: ");
    this->asteroid_container->update_objects(delta);
    //_delay_ms(100);

    this->asteroid_container->draw_objects(delta);
    this->bullet_container->draw_objects(delta);
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
        this->bullet_container->add_object(new Bullet(player->get_x_position(), player->get_y_position(), player->facing_direction));
        Bullet::bullet_created = true;
    }
}

bool GameScreen::bullet_asteroid_colliding(uint16_t x_bullet, uint16_t y_bullet, uint16_t x_asteroid, uint16_t y_asteroid){
    uint16_t x_distance = x_bullet - x_asteroid;
    uint16_t y_distance = y_bullet - y_asteroid;    
    return (sq(x_distance) + sq(y_distance)) < sq(ASTEROID_SIZE);
}

