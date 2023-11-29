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
    
    // calculate new X position
    int x_position_offset = (int)this->speed * sin(this->direction) * delta;
    int new_x_position = this->get_x_position() + x_position_offset;

    // calculate new Y position
    int y_position_offset = (int)this->speed * cos(this->direction) * delta;
    int new_y_position = this->get_y_position() + y_position_offset;

    // on leaving screen borders, teleport to other side
    if(this->wrap_around_display)
    {
        if(new_x_position < 0)
            new_x_position = Display::WIDTH_PIXELS;
        else if(new_x_position > Display::WIDTH_PIXELS)
            new_x_position = 0;
        if(new_y_position < 0)
            new_y_position = Display::HEIGHT_PIXELS;
        else if(new_y_position > Display::HEIGHT_PIXELS)
            new_y_position = 0;
    }

    // set positions
    this->set_x_position(new_x_position);
    this->set_y_position(new_y_position);
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
