#ifndef MOVINGOBJECT_H
#define MOVINGOBJECT_H

#include "stdint.h"
#include "Object.h"

class MovingObject : public Object
{
public:
    /// @brief pixels per second
    double speed;

    /// @brief angle in radians. 0=up, M_PI=down
    double direction;

    /// @brief if true, when object reaches border it teleports to the opposite side. TODO: if false, destroys on leaving border.
    bool wrap_around_display = false;

    /// @param speed pixels per second
    MovingObject(int x_position, int y_position, double speed);

    /// @brief clear drawing at given position
    /// @param display display to draw on
    /// @param x_position X-position of drawing to clear
    /// @param y_position Y-position of the drawing to clear
    virtual void undraw(Display display, int x_position, int y_position);
    
    /// @brief calls undraw(), then draw(). When inheriting call MovingObject::draw() first
    /// @param display display to draw on
    void draw(Display display) override;

    /// @brief moves object. When inheriting call MovingObject::update() last
    /// @param delta_s time since last frame in seconds
    void update(double delta) override;

    /// @brief set x_position and update previous_x_position
    void set_x_position(double position) override;

    /// @brief set y_position and update previous_y_position
    void set_y_position(double position) override;
private:
    // drawing a moving object requires undrawing the old drawing.
    // draw() calls undraw() with the below variables before drawing the object
    double previous_x_position;
    double previous_y_position;
};

#endif
