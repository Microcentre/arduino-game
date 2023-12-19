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
    bool wrap_around_display = true;

    /// @param speed pixels per second
    MovingObject(double x_position, double y_position, double speed);

    /// @brief calls undraw(), then draw(). When inheriting call MovingObject::draw() first
    /// @param display display to draw on
    void draw(Display *display) override;

    /// @brief moves object. When inheriting call MovingObject::update() last
    /// @param delta_s time since last frame in seconds
    void update(const double &delta) override;

    /// @brief set x_position and update previous_x_position
    void set_x_position(const double position) override;

    /// @brief set y_position and update previous_y_position
    void set_y_position(const double position) override;

private:
    // drawing a moving object requires undrawing the old drawing.
    // draw() calls undraw() with the below variables before drawing the object
    uint16_t previous_draw_position_x;
    uint16_t previous_draw_position_y;
};

#endif
