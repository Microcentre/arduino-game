#ifndef WAVES_H
#define WAVES_H

#include "../Objects/ObjectsContainer.h"
#include "../Hardware/Display.h"
#include "Asteroid.h"

/// @brief handles waves of asteroids
/// There is a `draw_phase` property which is on NONE by default.
/// When all asteroids are destroyed, it goes to the WAVE_COMPLETED phase, showing "WAVE X COMPLETED".
/// Then it goes into the ASTEROID_WARNING phase, saying "WARNING INCOMING ASTEROIDS"
/// Then the next WAVE_COMING phase announces the next wave "WAVE X"
/// Finally the SPAWN_ASTEROIDS phase spawns the asteroids.
class Waves
{
public:
    /// @brief current wave
    uint8_t wave = 0;

    Waves(uint8_t max_asteroids);

    /// @brief should be called very frame
    /// @param delta_s time since last frame in seconds
    void update(Display *display, const double &delta_s, ObjectsContainer *asteroids_container);

    /// @brief start at wave 1
    void start_new();

    /// @brief go to next wave, with announcements
    void next();

    /// @return if this class is still busy drawing the text
    bool is_drawing();

    enum DrawPhase
    {
        NONE,
        WAVE_COMPLETED,
        ASTEROID_WARNING,
        WAVE_COMING,
        SPAWN_ASTEROIDS
    };

    /// @brief what to draw right now
    Waves::DrawPhase draw_phase = Waves::DrawPhase::NONE;

private:
    /// @brief time (in delta seconds) to show text before dissapearing
    const double TEXT_TIME = 2;

    /// @brief how long the text will remain showing, in (delta) seconds
    double text_time_left = 0;

    uint8_t max_asteroids;

    /// @brief Spawn asteroids depending on the current wave
    /// @param asteroid_container
    void spawn_asteroids(ObjectsContainer *asteroid_container);

    /// @brief draws the text "WAVE x COMPLETED"
    /// @param undraw if the warning should be drawn(false) or undrawn(true)
    void draw_completed_phase(Display *display, bool undraw = false);

    /// @brief draws the text "WARNING: INCOMING ASTEROID"
    /// @param undraw if the warning should be drawn(false) or undrawn(true)
    void draw_asteroid_warning_phase(Display *display, bool undraw = false);

    /// @brief draws the text "WAVE x"
    /// @param undraw if the warning should be drawn(false) or undrawn(true)
    void draw_wave_coming_phase(Display *display, bool undraw = false);

    /// @brief go to the next draw phase and undraw previous phase
    void next_draw_phase(Display *display);
};

#endif