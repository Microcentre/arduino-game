#include "Score.h"

int Score::score = 0;

int Score::previous_score = 0;

Score::Score(Display *display, double x_position, double y_position) : Object(x_position, y_position)
{
    display->canvas.setCursor(x_position, y_position);
    display->canvas.setTextSize(2);
}

void Score::draw(Display *display)
{
    Score::undraw(display, Score::X_POS_TEXT, Score::Y_POS_TEXT);
    display->canvas.setCursor(Score::X_POS_TEXT, Score::Y_POS_TEXT);
    display->canvas.setTextColor(ILI9341_DARKGREEN);
    display->canvas.print(score);
}

void Score::undraw(Display *display, const uint16_t x_position, const uint16_t y_position)
{
    display->canvas.setCursor(x_position, y_position);
    display->canvas.setTextColor(display->background_colour);
    display->canvas.print(previous_score);
}

void Score::update(const double &delta)
{
    Object::update(delta);
}