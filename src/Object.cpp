#include "Object.h"

Object::Object(double x_position, double y_position)
{
    this->x_position = x_position;
    this->y_position = y_position;
}

void Object::set_x_position(double position)
{
    this->x_position = position;
}

double Object::get_x_position()
{
    return this->x_position;
}

void Object::set_y_position(double position)
{
    this->y_position = position;
}

double Object::get_y_position()
{
    return this->y_position;
}

void Object::update(double delta)
{

}
