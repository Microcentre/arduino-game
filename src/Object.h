#ifndef OBJECT_H
#define OBJECT_H

#include "stdint.h"
#include "Display.h"

class Object
{
public:
    Object(uint16_t x_position, uint16_t y_position);

    virtual void set_x_position(uint16_t position);
    uint16_t get_x_position();

    virtual void set_y_position(uint16_t position);
    uint16_t get_y_position();

    /// @brief Make any changes, called before drawing
    /// @param delta_s time since last frame in seconds
    virtual void update(const double &delta_s);

    /// @brief draw the object on the screen
    /// @param display display to draw on
    virtual void draw(Display display);

private:
    uint16_t x_position;
    uint16_t y_position;
};

#endif
