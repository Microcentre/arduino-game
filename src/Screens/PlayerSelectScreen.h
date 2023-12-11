#ifndef PLAYER_SELECT_SCREEN_H
#define PLAYER_SELECT_SCREEN_H

#include "Screen.h"
#include "ObjectsContainer.h"
#include "Display.h"

class PlayerSelectScreen: public Screen, public ObjectsContainer
{
public:
    PlayerSelectScreen(Display *display, Joystick *joystick);
    virtual ~PlayerSelectScreen();

    void update(const double &delta) override;

    void drawHud(const double &delta);

    void on_joystick_changed() override;

private:
    uint8_t left_selected;

    static const uint8_t TEXT_X = 43;
    static const uint8_t TEXT_Y = 40;

    static const uint8_t SELECT_BOX_SIZE = 100;
    static const uint8_t SELECT_BOX_Y = 100;
    static const uint8_t BOX_SPACING = 60;


    static const uint16_t SELECT_BOX_X_LEFT = (Display::WIDTH_PIXELS - (SELECT_BOX_SIZE*2) - BOX_SPACING)/2;
    static const uint16_t SELECT_BOX_X_RIGHT = SELECT_BOX_X_LEFT + SELECT_BOX_SIZE + BOX_SPACING;

    static const uint16_t PLAYER_LEFT_X = SELECT_BOX_X_LEFT + (SELECT_BOX_SIZE/2);
    static const uint16_t PLAYER_RIGHT_X = SELECT_BOX_X_RIGHT + (SELECT_BOX_SIZE/2);
    static const uint8_t PLAYER_Y = SELECT_BOX_Y + (SELECT_BOX_SIZE/2);
};

#endif