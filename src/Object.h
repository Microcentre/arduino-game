#ifndef OBJECT_H
#define OBJECT_H

#include "stdint.h"
#include "Display.h"

class Object
{
public:
    Object(double x_position, double y_position);

    virtual void set_x_position(const double position);
    double get_x_position();

    virtual void set_y_position(const double position);
    double get_y_position();
    
    /// @brief Make any changes, called before drawing
    /// @param delta_s time since last frame in seconds
    virtual void update(const double &delta_s);

    /// @brief draw the object on the screen
    /// @param display display to draw on
    virtual void draw(Display display);

private:
    double x_position;
    double y_position;
};

#endif
