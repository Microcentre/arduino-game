#include "Waves.h"

Waves::Waves()
{
}

void Waves::start_new()
{
    this->wave = 1;
    this->draw_phase = Waves::DrawPhase::ASTEROID_WARNING;
}

void Waves::next()
{
    ++this->wave;
    this->draw_phase = Waves::DrawPhase::WAVE_COMPLETED;
}

void Waves::update(Display *display, const double &delta_s)
{
    if (this->draw_phase == 0)
        return;

    this->text_time_left -= delta_s;

    switch (this->draw_phase)
    {
    case 2:
        draw_warning(display);
        break;
    }
    draw_warning(display);
}

void Waves::spawn_asteroids(ObjectsContainer *asteroid_container)
{
    for (uint8_t i = 0; i < wave; ++i)
    {
        uint16_t screen_width = Display::WIDTH_PIXELS;
        uint8_t screen_height = Display::HEIGHT_PIXELS;
        uint16_t random_x_position = (uint16_t)rand() % screen_width + 1;
        uint8_t random_y_position = rand() % screen_height + 1;
        uint8_t random_speed = rand() % 100 + 1;

        uint16_t m_10_pi = M_PI * 10;
        double random_direction = (rand() % m_10_pi) / 10;

        asteroid_container->add_object(new Asteroid(random_x_position, random_y_position, random_speed, random_direction));
    }
}
void Waves::draw_warning(Display *display, bool undraw = false)
{
    display->canvas.setTextSize(2);
    display->canvas.setTextWrap(false);

    auto screen_centre_x_pos = Display::WIDTH_PIXELS / 2;
    auto screen_centre_y_pos = Display::HEIGHT_PIXELS / 2;

    // WARNING blinks by toggling between it's colour and the display's background colour,
    // depending on the current frame (dending on this->text_time_left).
    bool is_blinking = (uint16_t)(this->text_time_left * 10) % 2;
    if (undraw || is_blinking)
        display->canvas.setTextColor(display->background_colour);
    else
        display->canvas.setTextColor(ILI9341_RED);
    display->draw_centred_text(display, "WARNING", screen_centre_x_pos, screen_centre_y_pos - 25);

    // to undraw the text
    // we just set the colour to the display's background colour
    if (!undraw)
        display->canvas.setTextColor(ILI9341_WHITE);
    else
        display->canvas.setTextColor(display->background_colour);
    display->draw_centred_text(display, "INCOMING ASTEROIDS", screen_centre_x_pos, screen_centre_y_pos);
}
