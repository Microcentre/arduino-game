#ifndef PLAYER_SELECT_SCREEN_H
#define PLAYER_SELECT_SCREEN_H

#include "../Screen.h"
#include "../Game/Player.h"
#include "../Hardware/Display.h"
#include "../Hardware/Buzzer.h"

class PlayerSelectScreen : public Screen
{
public:
    /// @brief The left player with colour cyan.
    Player *p1;

    /// @brief The right player with colour orange.
    Player *p2;

    /// @brief Creates the player select screen with the player icons and selection box.
    /// @param display the display to draw to.
    /// @param joystick the joystick to read input from.
    PlayerSelectScreen(Display *display, Joystick *joystick, IR *infrared);

    virtual ~PlayerSelectScreen();

    /// @brief Updates the player select screen and draws the HUD.
    /// @param delta represents the time since the last frame.
    void update(const double &delta) override;

    /// @brief Draws the HUD for the player select screen, including the player icons and selection box.
    /// @param delta represents the time since the last frame.
    void drawHud(const double &delta);

    /// @brief Handles joystick input for the player select screen. When the joystick is moved left or right,
    /// @brief the selection box moves between the two player icons. When the joystick is pressed, the game starts.
    void on_joystick_changed() override;

    /// @brief Handles touch input for the player select screen.
    void on_screen_touched();

private:
    /// @brief Whether the left player is selected.
    uint8_t left_selected = true;
    uint8_t pressed_last_frame = false;

    /// @brief the centre x position of the text
    const uint8_t SCREEN_CENTRE_X_POS = Display::WIDTH_PIXELS / 2;

    const uint16_t TITLE_COLOUR = ILI9341_WHITE;

    /// @brief The y position of the text.
    static const uint8_t TITLE_Y = 30;

    const uint16_t TEXT_COLOUR = ILI9341_GREEN;

    const uint8_t SELECT_PLAYER_TEXT_Y = 80;

    /// @brief The size of the selection box.
    static const uint8_t SELECT_BOX_SIZE = 100;

    /// @brief The y position of the selection box.
    static const uint8_t SELECT_BOX_Y = 100;

    /// @brief The spacing between the two player select boxes.
    static const uint8_t BOX_SPACING = 60;

    /// @brief The x position of the left player select box.
    static const uint16_t SELECT_BOX_X_LEFT = (Display::WIDTH_PIXELS - (SELECT_BOX_SIZE * 2) - BOX_SPACING) / 2;

    /// @brief The x position of the right player select box.
    static const uint16_t SELECT_BOX_X_RIGHT = SELECT_BOX_X_LEFT + SELECT_BOX_SIZE + BOX_SPACING;

    /// @brief The x position of the left player icon.
    static const uint16_t PLAYER_LEFT_X = SELECT_BOX_X_LEFT + (SELECT_BOX_SIZE / 2);

    /// @brief The x position of the right player icon.
    static const uint16_t PLAYER_RIGHT_X = SELECT_BOX_X_RIGHT + (SELECT_BOX_SIZE / 2);

    /// @brief The y position of the player icons.
    static const uint8_t PLAYER_Y = SELECT_BOX_Y + (SELECT_BOX_SIZE / 2);

    /// @brief buzzer property
    Buzzer buzzer = Buzzer();
};

#endif