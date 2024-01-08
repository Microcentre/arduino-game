#include "Waves.h"

Waves::Waves(uint8_t max_asteroids)
{
    this->max_asteroids = max_asteroids;
}

void Waves::start_new()
{
    this->wave = 1;
    this->draw_phase = WavePhase::ASTEROID_WARNING;
    this->drawing_text = true;
}

void Waves::next()
{
    this->draw_phase = WavePhase::WAVE_COMPLETED;
    this->drawing_text = true;
}

void Waves::player2_ready(Display *display)
{
    if (this->is_waiting_for_player())
        this->next_phase(display);
}

bool Waves::is_switching_wave()
{
    return this->draw_phase != WavePhase::NONE;
}

bool Waves::is_waiting_for_player()
{
    return this->draw_phase == WavePhase::WAITING_FOR_PLAYER;
}

bool Waves::is_ready_to_continue()
{
    return is_waiting_for_player() || this->draw_phase == WavePhase::CONFIRM_CONTINUE;
}

bool Waves::is_spawning_asteroids()
{
    return this->draw_phase == WavePhase::SPAWN_ASTEROIDS;
}

bool Waves::just_started_new_wave()
{
    return just_started;
}

void Waves::update(Display *display, const double &delta_s, ObjectsContainer *asteroids_container)
{
    // if not switching wave, do nothing
    if (this->draw_phase == WavePhase::NONE)
    {
        if (this->just_started)
            this->just_started = false;
        return;
    }

    // for phases that draw text
    // automatically go to next phase after draw timer is finished
    if (this->drawing_text)
    {
        this->text_time_left -= delta_s;
        if (this->text_time_left <= 0)
            this->next_phase(display);
    }

    // perform action depending on wave phase
    switch (this->draw_phase)
    {
    case WavePhase::WAVE_COMPLETED:
        draw_completed_phase(display);
        break;
    case WavePhase::ASTEROID_WARNING:
        draw_asteroid_warning_phase(display);
        break;
    case WavePhase::WAVE_COMING:
        draw_wave_coming_phase(display);
        break;
    case WavePhase::SPAWN_ASTEROIDS:
        draw_wave_coming_phase(display);
        this->spawn_asteroids(asteroids_container);
        this->next_phase(display);
        break;
    case WavePhase::CONFIRM_CONTINUE:
        draw_wave_coming_phase(display);
        // stay in this phase for a certain amount of frames
        this->confirm_continue_counter++;
        if (this->confirm_continue_counter >= this->CONFIRM_CONTINUE_AMOUNT)
            this->next_phase(display);
        break;
    default:
        break;
    }
}

void Waves::spawn_asteroids(ObjectsContainer *asteroid_container)
{
    // wave 1 starts with 1 asteroid.
    // every wave, 2 more asteroids are added
    uint8_t amount_of_asteroids = ((this->wave - 1) * 2) + 1;
    if (amount_of_asteroids > this->max_asteroids)
        amount_of_asteroids = this->max_asteroids;

    // every 2 waves, the max speed increases by 50
    uint16_t max_asteroid_speed = ((this->wave / 2) + 1) * 50;

    uint16_t random_x_position;
    uint8_t random_y_position;
    uint8_t random_speed;
    for (uint8_t i = 0; i < amount_of_asteroids; ++i)
    {
        // randomize positions
        random_x_position = (uint16_t)rand() % Display::WIDTH_PIXELS + 1;
        random_y_position = rand() % Display::HEIGHT_PIXELS + 1;

        // ensures asteroids always spawn in corners of screen
        if (random_x_position < (Display::WIDTH_PIXELS / 2)) // if x in left half of screen
        {
            if (random_y_position < (Display::HEIGHT_PIXELS / 2)) // if y in top half of screen
            {
                random_y_position = 0;
            }
            else // if y in bottom top of screen
            {
                random_x_position = 0;
            }
        }
        else // if x in right half of screen
        {
            if (random_y_position < (Display::HEIGHT_PIXELS / 2)) // if y in bottom half of screen
            {
                random_y_position = Display::HEIGHT_PIXELS;
            }
            else // if y in bottom top of screen
            {
                random_x_position = Display::WIDTH_PIXELS;
            }
        }

        // store random value within 0.0 and 1/4 of pi (1.57)
        double random_direction = (rand() % M_10_PI_DIV_4) / 10;

        // check which edge of the screen the asteroid was placed,
        // point cone of direction accordingly
        if (random_x_position == 0)
        {
            random_direction += ONE_FOURTH_OF_PI; // 0.785, 1/4 of pi
        }
        else if (random_y_position == 0)
        {
            random_direction += THREE_FOURTH_OF_PI; // 2.335, 3/4 of pi
        }
        else if (random_x_position == Display::WIDTH_PIXELS)
        {
            random_direction += FIVE_FOUTH_OF_PI; // 3.925, 5/4 of pi
        }
        else if (random_y_position == Display::HEIGHT_PIXELS)
        {
            // in order to point cone in top direction, the direction has to be between 0.0 - 0.785 or 5.495 - 6.28
            if (random_direction > ONE_FOURTH_OF_PI) // 0.785, 1/4 of pi
            {
                random_direction += SEVEN_FOURTH_OF_PI; // 5.495, 7/4 of pi
            }
        }

        // random speed with min and max
        random_speed = MIN_ASTEROID_SPEED + rand() % (max_asteroid_speed - MIN_ASTEROID_SPEED + 1);

        // spawn asteroid and add to container
        asteroid_container->add_object(new Asteroid(random_x_position, random_y_position, random_speed, random_direction));
    }
}

void Waves::next_phase(Display *display)
{
    this->text_time_left = Waves::TEXT_TIME;

    switch (this->draw_phase)
    {
    case WavePhase::WAVE_COMPLETED:
        this->draw_completed_phase(display, true); // undraw previous phase
        ++this->wave;                              // mark next wave
        this->draw_phase = WavePhase::ASTEROID_WARNING;
        this->drawing_text = true;
        break;
    case WavePhase::ASTEROID_WARNING:
        this->draw_asteroid_warning_phase(display, true); // undraw previous phase
        this->draw_phase = WavePhase::WAVE_COMING;
        this->drawing_text = true;
        break;
    case WavePhase::WAVE_COMING:
        this->draw_phase = WavePhase::SPAWN_ASTEROIDS;
        this->drawing_text = false;
        break;
    case WavePhase::SPAWN_ASTEROIDS:
        this->draw_phase = WavePhase::WAITING_FOR_PLAYER;
        this->drawing_text = false;
        break;
    case WavePhase::WAITING_FOR_PLAYER:
        this->draw_phase = WavePhase::CONFIRM_CONTINUE;
        this->drawing_text = false;
        this->confirm_continue_counter = 0;
        break;
    case WavePhase::CONFIRM_CONTINUE:
        this->draw_wave_coming_phase(display, true); // undraw text
        this->draw_phase = WavePhase::NONE;
        this->drawing_text = false;
        this->just_started = true;

        break;
    }
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

void Waves::draw_asteroid_warning_phase(Display *display, bool undraw)
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
