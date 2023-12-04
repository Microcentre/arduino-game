#include "Game.h"

Game::Game()
{
    this->joystick = new Joystick();
    this->display = new Display();
    this->player = new Player(Display::WIDTH_PIXELS / 2, Display::HEIGHT_PIXELS / 2, 100); // start around the centre
    this->player->wrap_around_display = true;

    // Vector<> is a custom library that IS dynamic,
    // which for some reason has to be intialised in this hacky way
    Object *objects_array[5];
    this->objects = Vector<Object *>(objects_array);

    this->objects.push_back(this->player);
}

Game::~Game()
{
    delete this->joystick;
    delete this->display;
    delete this->player;
}

void Game::update_draw_objects(const double delta)
{
    Serial.println(this->objects.size());
    // update & draw objects
    for (auto iterator = this->objects.begin(); iterator != this->objects.end(); ++iterator)
    {
        (*iterator)->update(delta);
        (*iterator)->draw(this->display);
    }
}
