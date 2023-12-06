#include "GameScreen.h"
#include "Bullet.h"
#include "Asteroid.h"

GameScreen::GameScreen(Display *display, Joystick *joystick) : Screen(display, joystick)
{
    // array of objects on the screen to be updated & rendered.
    // Vector<> is a custom library that IS dynamic,
    // which for some reason has to be intialised in this hacky way
    Object *objects_array[GameScreen::MAX_AMOUNT_OF_OBJECTS];
    this->objects = Vector<Object *>(objects_array);

    // create player
    this->player = new Player(Display::WIDTH_PIXELS / 2, Display::HEIGHT_PIXELS / 2, 100); // start around the centre
    this->player->wrap_around_display = true;
    this->add_object(this->player);

    // create asteroid
    this->add_object(new Asteroid(50, 50, 80, M_PI_2));
}

GameScreen::~GameScreen()
{
    delete this->joystick;
    delete this->display;
    delete this->player;
}

void GameScreen::add_object(Object *object)
{
    this->objects.push_back(object);
}

void GameScreen::delete_object(Object *object)
{
    uint8_t index = find_object_index(object);
    if (index == -1) // not found
        return;

    object->undraw(this->display);

    this->objects.remove(index);
    delete object;
    object = nullptr;
}

void GameScreen::update(const double &delta)
{
    Screen::update(delta);

    // update & draw objects
    auto i = this->objects.begin();
    while (i != this->objects.end())
    {
        if ((*i)->marked_for_deletion)
        {
            this->delete_object((*i));
            continue;
        }

        (*i)->update(delta);
        (*i)->draw(this->display);
        ++i;
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
    if (joystick->is_c_pressed() && Bullet::bullet_created == false)
    {
        this->add_object(new Bullet(player->get_x_position(), player->get_y_position(), player->facing_direction));
        Bullet::bullet_created = true;
    }
}

uint8_t GameScreen::find_object_index(Object *object)
{
    for (int i = 0; i < this->objects.size(); ++i)
    {
        if (this->objects.at(i) == object)
            return i;
    }

    return -1;
}
