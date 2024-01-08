#ifndef SCORE_H
#define SCORE_H

#include "../Objects/Object.h"

class Score : public Object
{
public:
    static uint16_t score;

    static const uint8_t X_POS_TEXT = 0;

    static const uint8_t Y_POS_TEXT = 0;

    /// @brief score text height in pixels
    static const uint8_t SCORE_TEXT_HEIGHT = 16;

    Score(Display *display, double x_position, double y_position);

    void add_score(uint8_t amount);

    void draw(Display *display) override;

    void update(const double &delta) override;

    void undraw(Display *display, const uint16_t x_position, const uint16_t y_position) override;
};
#endif