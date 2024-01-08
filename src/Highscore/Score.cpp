#include "Score.h"

uint16_t Score::score = 0;

Score::Score(Display *display, double x_position, double y_position) : Object(x_position, y_position)
{
    score = 0;
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
    // calculate score text width (height is constant)
    uint16_t width;
    display->canvas.getTextBounds(String(score), x_position, y_position, nullptr, nullptr, &width, nullptr);
    display->canvas.fillRect(x_position, y_position, width, SCORE_TEXT_HEIGHT, display->background_colour);
}

void Score::update(const double &delta)
{
    Object::update(delta);
}

void Score::add_score(uint8_t amount)
{
    score += amount;
}
