#ifndef GAMESCREEN_H
#define GAMESCREEN_H

#include "../Hardware/Joystick.h"
#include "../Hardware/Display.h"
#include "Player.h"
#include "Screen.h"
#include "../Objects/ObjectsContainer.h"
#include "../Highscore/Score.h"
#include "Waves.h"
#include "../Hardware/Buzzer.h"
#include "../Hardware/ShowHealthOnSSD.h"
#include "InvincibilityFrames.h"
#include "../Hardware/IR/ReceivedGameData.h"

class GameScreen : public Screen
{
public:
    /// @brief player1 is controlled by the current player
    Player *player;

    /// @brief player2 is the other player, who's actions are synced over infrared
    Player *player2;

    /// @brief contains all asteroids currently in the game
    ObjectsContainer *asteroid_container;

    /// @brief contains all bullets either players have shot
    ObjectsContainer *bullet_container;

    /// @brief stores and draws the current score.
    Score *score;

    /// @brief used to draw the score onto the seven-segment-display
    ShowHealthOnSSD *show_health;

    /// @brief makes the player invincible when he's damaged.
    /// Observer thats called when the player is hurt (HurtObserver instance)
    InvincibilityFrames *invincibility;

    GameScreen(Display *display, Joystick *joystick, IR *infrared, uint16_t p1_colour, uint16_t p2_colour);
    virtual ~GameScreen();

    /// @brief checks nunchuck and updates all objects in vector array, called every frame
    /// @param delta seconds since last frame
    void update(const double &delta) override;

    /// @brief updates player actions using joystick values
    void on_joystick_changed() override;

    /// @brief checks each bullet for collision with all of the asteroids.
    /// if bullet collides, both bullet and asteroid are removed.
    void check_bullet_asteroid_collision();

    /// @brief checks the player for collision with all of the asteroids.
    /// if player collides, player.hurt() is called
    void check_player_asteroid_collision();

    /// @brief calculate if x,y of bullet are within radius of asteroid.
    /// using pythagoras to calculate the distance between two points if the square root of both distances is less than the radius,
    // the bullet is inside of the asteroid, therefore it has collided.
    /// @param x_bullet x-coordinate of center of bullet
    /// @param y_bullet y-coordinate of center of bullet
    /// @param x_asteroid x-coordinate of center of asteroid
    /// @param y_asteroid y-coordinate of center of asteroid
    /// @return returns true if center of bullet is within radius of asteroid
    bool bullet_asteroid_colliding(uint16_t x_bullet, uint16_t y_bullet, uint16_t x_asteroid, uint16_t y_asteroid);

    /// @brief calculate if x,y of player are within radius of asteroid.
    /// using pythagoras to calculate the distance between two points if the square root of both distances is less than the radius of both the player and the asteroid,
    // the player is inside of the asteroid, therefore it has collided.
    /// @param x_bullet x-coordinate of center of player
    /// @param y_bullet y-coordinate of center of player
    /// @param x_asteroid x-coordinate of center of asteroid
    /// @param y_asteroid y-coordinate of center of asteroid
    /// @return returns true if radius of player is within radius of asteroid
    bool player_asteroid_colliding(int32_t x_player, int32_t y_player, uint16_t x_asteroid, uint16_t y_asteroid);

private:
    /// @brief max array size for asteroids and bullet containers
    static constexpr uint8_t MAX_AMOUNT_OF_OBJECTS = 15;

    /// @brief used to make a sound when current player shoots
    Buzzer buzzer = Buzzer();

    /// @brief handles the switching of waves
    Waves *waves;

    /// @brief if the player just shot a bullet
    /// used to sync with other player.
    bool shot_bullet = false;

    /// @brief called when an asteroid is destroyed. starts a new wave
    void on_asteroid_destroyed();

    /// @brief update the other player using received infrared data
    void process_player_2(ReceivedGameData);

    /// @brief communicate death to other player
    void send_data();

    /// @brief start a new wave
    void next_wave();

    /// @brief send data indicating player death
    void communicate_game_ended();
};

#endif
