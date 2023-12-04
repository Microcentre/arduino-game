#include "Object.h"

Object::Object(uint16_t x_position, uint16_t y_position)
{
    this->x_position = x_position;
    this->y_position = y_position;
}

void Object::set_x_position(uint16_t position)
{
    this->x_position = position;
}

uint16_t Object::get_x_position()
{
    return this->x_position;
}

void Object::set_y_position(uint16_t position)
{
    this->y_position = position;
}

uint16_t Object::get_y_position()
{
    return this->y_position;
}

void Object::update(double delta)
{
}
