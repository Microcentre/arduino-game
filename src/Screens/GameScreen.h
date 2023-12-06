#ifndef GAMESCREEN_H
#define GAMESCREEN_H

#include <Vector.h>
#include "Joystick.h"
#include "Display.h"
#include "Player.h"
#include "Object.h"
#include "Screen.h"

class GameScreen : public Screen
{
public:
    Player *player;

    GameScreen(Display *display, Joystick *joystick);
    ~GameScreen();

    /// @param object object to add to the list of objects that are updated&drawn every frame
    void add_object(Object *object);

    /// @param object object to delete from memory and from the list of objects
    void delete_object(Object *object);

    /// @brief checks nunchuck and updates all objects in vector array, called every frame
    /// @param delta seconds since last frame
    void update(const double &delta) override;

    /// @brief updates player actions using joystick values
    void on_joystick_changed() override;

private:
    static constexpr uint8_t MAX_AMOUNT_OF_OBJECTS = 15;

    /// @brief Objects are drawn and updated every frame
    Vector<Object *> objects;

    /// @return index of object, or -1 if not found
    uint8_t find_object_index(Object *object);
};

#endif
