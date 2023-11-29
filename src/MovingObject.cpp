#include <math.h>
#include "MovingObject.h"

MovingObject::MovingObject(int x_position, int y_position, double speed) : Object(x_position, y_position)
{
    this->speed = speed;
    this->direction = 0;
}

void MovingObject::update(double delta)
{
    Object::update(delta);
    
    int x_position_offset = (int)this->speed * sin(this->direction) * delta;
    this->set_x_position(this->get_x_position() + x_position_offset);

    int y_position_offset = (int)this->speed * cos(this->direction) * delta;
    this->set_y_position(this->get_y_position() + y_position_offset);
}

void MovingObject::draw(Display display)
{
    this->undraw(display, this->previous_x_position, this->previous_y_position);
}

void MovingObject::set_x_position(int position)
{
    this->previous_x_position = this->get_x_position();
    Object::set_x_position(position);
}

void MovingObject::set_y_position(int position)
{
    this->previous_y_position = this->get_y_position();
    Object::set_y_position(position);
}
