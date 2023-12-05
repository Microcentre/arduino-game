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

    GameScreen(const Display *display, const Joystick *joystick);
    ~GameScreen();

    //adds objects to vector array
    void add_object(Object *object);
    //removes object from vector array
    void delete_object(Object *object);
    
    //checks nunchuck and updates all objects in vector array, called every frame
    void update(const double &delta) override;
    
    /// @brief updates player actions using joystick values
    void on_joystick_update() override;

private:
    /// @brief Objects are drawn and updated every frame
    Vector<Object *> objects;
    /// @brief 
    /// @param object 
    /// @return index of object, or -1 if not found
    uint8_t find_object_index(Object *object);
};

#endif