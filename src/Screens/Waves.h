#ifndef WAVES_H
#define WAVES_H

#include "ObjectsContainer.h"
#include "Display.h"
#include "Asteroid.h"

class Waves
{
public:
    /// @brief current wave
    uint8_t wave = 0;

    Waves();

    /// @brief should be called very frame
    /// @param delta_s time since last frame in seconds
    void update(Display *display, const double &delta_s);

    /// @brief start at wave 1
    void start_new();

    /// @brief go to next wave, with announcements
    void next();

private:
    enum DrawPhase
    {
        NONE,
        WAVE_COMPLETED,
        ASTEROID_WARNING,
        WAVE_COMING
    };

    /// @brief time (in delta seconds) to show text before dissapearing
    const double TEXT_TIME = 5;

    /// @brief what to draw right now
    Waves::DrawPhase draw_phase = Waves::DrawPhase::NONE;
    /// @brief how long the text will remain showing, in (delta) seconds
    double text_time_left = 0;

    void spawn_asteroids(ObjectsContainer *asteroid_container);

    /// @brief draws the text "WARNING: INCOMING ASTEROID"
    /// @param undraw if the warning should be drawn(false) or undrawn(true)
    void draw_warning(Display *display, bool undraw = false);
};

#endif