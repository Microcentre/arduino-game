#ifndef OBJECT_H
#define OBJECT_H

#include "stdint.h"
#include "Display.h"

class Object
{
public:
    Object(double x_position, double y_position);
    virtual ~Object() {}

    /// @brief if the object should be deleted or not
    bool marked_for_deletion = false;

    virtual void set_x_position(const double position);
    double get_x_position();

    virtual void set_y_position(const double position);
    double get_y_position();

    /// @brief Make any changes, called before drawing
    /// @param delta_s time since last frame in seconds
    virtual void update(const double &delta_s);

    /// @brief draw the object on the screen
    /// @param display display to draw on
    virtual void draw(Display *display) = 0;

    /// @brief clear drawing at given position
    /// @param display display to draw on
    /// @param x_position X-position of drawing to clear
    /// @param y_position Y-position of the drawing to clear
    virtual void undraw(Display *display, const uint16_t x_position, const uint16_t y_position) = 0;

    /// @brief Undraw at current position
    /// @param display display to draw on
    void undraw(Display *display);

private:
    double x_position;
    double y_position;
};

#endif
