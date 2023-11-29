#include "Object.h"

Object::Object(int x_position, int y_position)
{
    this->x_position = x_position;
    this->y_position = y_position;
}

void Object::set_x_position(int position)
{
    this->x_position = position;
}

int Object::get_x_position()
{
    return this->x_position;
}

void Object::set_y_position(int position)
{
    this->y_position = position;
}

int Object::get_y_position()
{
    return this->y_position;
}

void Object::update(double delta)
{

}
