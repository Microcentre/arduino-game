#ifndef WAVES_H
#define WAVES_H

#include "../Objects/ObjectsContainer.h"
#include "../Hardware/Display.h"

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

    /// @brief mark other player as ready to continue
    void player2_ready(Display *display);

    /// @return if wave phase is in-game (false) or busy switching wave (true)
    bool is_switching_wave();

    /// @return if finished switching wave but waiting for other player to continue
    /// (in WAITING_FOR_PLAYER phase)
    bool is_waiting_for_player();

    /// @return if finished switching wave but ready to play
    bool is_ready_to_continue();

    /// @return if in the phase of drawing asteroids
    bool is_spawning_asteroids();

    /// @brief true for one frame
    /// @return if a new wave just started
    bool just_started_new_wave();

private:
    enum WavePhase
    {
        NONE,
        WAVE_COMPLETED,
        ASTEROID_WARNING,
        WAVE_COMING,
        SPAWN_ASTEROIDS,
        WAITING_FOR_PLAYER,
        CONFIRM_CONTINUE
    };

    /// @brief time (in delta seconds) to show text before dissapearing
    const double TEXT_TIME = 1;

    // multiply PI by 10, divide by four
    const uint8_t M_10_PI_DIV_4 = (M_PI * 10) / 4;

    /// @brief 1/4 of PI
    const double ONE_FOURTH_OF_PI = 0.785;

    /// @brief 3/4 of PI
    const double THREE_FOURTH_OF_PI = 2.335;

    /// @brief 5/4 of PI
    const double FIVE_FOUTH_OF_PI = 3.925;

    /// @brief 7/4 of PI
    const double SEVEN_FOURTH_OF_PI = 5.495;

    /// @brief minimal asteroid speed
    const uint8_t MIN_ASTEROID_SPEED = 35;

    /// @brief how many times to send the CONTINUE message before continueing
    /// this phase ensures the other player receives the WAITING_FOR_PLAYER continue
    const uint8_t CONFIRM_CONTINUE_AMOUNT = 50;
    uint8_t confirm_continue_counter = 0;

    /// @brief how long the text will remain showing, in (delta) seconds
    double text_time_left = 0;

    /// @brief if the current phase includes drawing text
    /// if this is true, text_time_left is decreased
    /// and the next wave is automatically set when its finished
    bool drawing_text = false;

    /// @brief if a wave just started (true for 1 frame)
    bool just_started = false;

    /// @brief max amount of asteroids that may be spawned
    uint8_t max_asteroids;

    /// @brief what to draw right now
    Waves::WavePhase draw_phase = WavePhase::NONE;

    /// @brief go to the next wave phase and undraw previous phase
    void next_phase(Display *display);

    /// @brief draws the text "WAVE x COMPLETED"
    /// @param undraw if the warning should be drawn(false) or undrawn(true)
    void draw_completed_phase(Display *display, bool undraw = false);

    /// @brief draws the text "WARNING: INCOMING ASTEROID"
    /// @param undraw if the warning should be drawn(false) or undrawn(true)
    void draw_asteroid_warning_phase(Display *display, bool undraw = false);

    /// @brief draws the text "WAVE x"
    /// @param undraw if the warning should be drawn(false) or undrawn(true)
    void draw_wave_coming_phase(Display *display, bool undraw = false);

    /// @brief Spawn asteroids depending on the current wave
    /// @param asteroid_container
    void spawn_asteroids(ObjectsContainer *asteroid_container);
};

#endif