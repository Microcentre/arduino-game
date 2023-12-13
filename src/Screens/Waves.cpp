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
    this->draw_phase = Waves::DrawPhase::WAVE_COMPLETED;
}

bool Waves::is_drawing()
{
    return this->draw_phase != Waves::DrawPhase::NONE;
}

void Waves::update(Display *display, const double &delta_s, ObjectsContainer *asteroids_container)
{
    // if not drawing, do nothing
    if (this->draw_phase == 0)
        return;

    // go to next phase when ready
    this->text_time_left -= delta_s;
    if (this->text_time_left <= 0)
        this->next_draw_phase(display);

    // draw the correct phase
    switch (this->draw_phase)
    {
    case Waves::DrawPhase::WAVE_COMPLETED:
        draw_completed_phase(display);
        break;
    case Waves::DrawPhase::ASTEROID_WARNING:
        draw_asteroid_warning_phase(display);
        break;
    case Waves::DrawPhase::WAVE_COMING:
        draw_wave_coming_phase(display);
        break;
    case Waves::DrawPhase::SPAWN_ASTEROIDS:
        this->spawn_asteroids(asteroids_container);
        this->text_time_left = 0; // go to next (NONE) phase right away
        break;
    }
}

void Waves::spawn_asteroids(ObjectsContainer *asteroid_container)
{
    for (uint8_t i = 0; i < this->wave; ++i)
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

void Waves::next_draw_phase(Display *display)
{
    switch (this->draw_phase)
    {
    case Waves::DrawPhase::WAVE_COMPLETED:
        this->draw_completed_phase(display, true); // undraw previous phase
        ++this->wave;                              // mark next wave
        this->draw_phase = Waves::DrawPhase::ASTEROID_WARNING;
        break;
    case Waves::DrawPhase::ASTEROID_WARNING:
        this->draw_asteroid_warning_phase(display, true); // undraw previous phase
        this->draw_phase = Waves::DrawPhase::WAVE_COMING;
        break;
    case Waves::DrawPhase::WAVE_COMING:
        this->draw_wave_coming_phase(display, true); // undraw previous phase
        this->draw_phase = Waves::DrawPhase::SPAWN_ASTEROIDS;
        break;
    default:
        this->draw_phase = Waves::DrawPhase::NONE;
    }

    this->text_time_left = Waves::TEXT_TIME;
}

void Waves::draw_completed_phase(Display *display, bool undraw)
{
    // set text properties
    display->canvas.setTextSize(2);
    display->canvas.setTextWrap(false);

    // is not visible when undraw=true.
    // text also blinks depending on the current frame (depending on text_time_left)
    bool is_blinking = (uint16_t)(this->text_time_left * 10) % 4;
    if (undraw || is_blinking)
        display->canvas.setTextColor(display->background_colour);
    else
        display->canvas.setTextColor(ILI9341_WHITE);

    auto screen_centre_x_pos = Display::WIDTH_PIXELS / 2;
    auto screen_centre_y_pos = Display::HEIGHT_PIXELS / 2;

    auto text = "WAVE " + (String)this->wave + " COMPLETED";
    display->draw_centred_text(text, screen_centre_x_pos, screen_centre_y_pos);
}

void Waves::draw_asteroid_warning_phase(Display *display, bool undraw = false)
{
    // set text properties
    display->canvas.setTextSize(2);
    display->canvas.setTextWrap(false);

    auto screen_centre_x_pos = Display::WIDTH_PIXELS / 2;
    auto screen_centre_y_pos = Display::HEIGHT_PIXELS / 2;

    // set colour for "WARNING" text.
    // The text blinks by toggling between it's own colour and the display's background colour,
    // depending on the current frame (dending on this->text_time_left).
    // it also is set to the display's background colour when undrawing the text
    bool is_blinking = (uint16_t)(this->text_time_left * 10) % 2;
    if (undraw || is_blinking)
        display->canvas.setTextColor(display->background_colour);
    else
        display->canvas.setTextColor(ILI9341_RED);

    display->draw_centred_text("WARNING", screen_centre_x_pos, screen_centre_y_pos - 25);

    // to undraw the text
    // we just set the colour to the display's background colour
    if (!undraw)
        display->canvas.setTextColor(ILI9341_WHITE);
    else
        display->canvas.setTextColor(display->background_colour);
    display->draw_centred_text("INCOMING ASTEROIDS", screen_centre_x_pos, screen_centre_y_pos);
}

void Waves::draw_wave_coming_phase(Display *display, bool undraw)
{
    // set text properties
    display->canvas.setTextSize(2);
    display->canvas.setTextWrap(false);

    if (!undraw)
        display->canvas.setTextColor(ILI9341_WHITE);
    else
        display->canvas.setTextColor(display->background_colour);

    auto screen_centre_x_pos = Display::WIDTH_PIXELS / 2;
    auto screen_centre_y_pos = Display::HEIGHT_PIXELS / 2;

    // draw in cetre of screen
    auto text = "WAVE " + (String)this->wave;
    display->draw_centred_text(text, screen_centre_x_pos, screen_centre_y_pos);
}
