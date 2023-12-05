#include "GameScreen.h"

GameScreen::GameScreen(const Display *display, const Joystick *joystick) : Screen(display, joystick)
{
    this->player = new Player(Display::WIDTH_PIXELS / 2, Display::HEIGHT_PIXELS / 2, 100); // start around the centre
    this->player->wrap_around_display = true;

    // Vector<> is a custom library that IS dynamic,
    // which for some reason has to be intialised in this hacky way
    Object *objects_array[5];
    this->objects = Vector<Object *>(objects_array);

    this->add_object(this->player);
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
    if(index == -1)
        return;

    this->objects.remove(index);
    delete object;
    object = nullptr;
}

void GameScreen::update(const double &delta)
{
    Screen::update(delta);

    // update & draw objects
    for (auto iterator = this->objects.begin(); iterator != this->objects.end(); ++iterator)
    {
        (*iterator)->update(delta);
        (*iterator)->draw(this->display);
    }
}

void GameScreen::on_joystick_update()
{
    this->player->rotate(this->joystick->get_x_axis());
    if (this->joystick->is_z_pressed())
    {
        this->player->accelerate();
    }
}

uint8_t GameScreen::find_object_index(Object *object)
{
    for(int i=0; i<this->objects.size(); ++i)
    {
        if(this->objects.at(i) == object)
            return i;
    }
    
    return -1;
}
