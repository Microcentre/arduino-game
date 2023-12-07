#ifndef OBJECTSCONTAINER_H
#define OBJECTSCONTAINER_H

#include <Vector.h>
#include "Object.h"
#include "Display.h"

class ObjectsContainer
{
public:
    ObjectsContainer(Display *display, Vector<Object *>(objects_array));

    /// @param object object to add to the list of objects that are updated&drawn every frame
    void add_object(Object *object);

    /// @param object object to delete from memory and from the list of objects
    void delete_object(Object *object);

    /// @brief call update() on all objects. is called every frame.
    /// @param delta seconds since last frame
    void update_objects(const double &delta);

    /// @brief call draw() on all objects. is called every frame.
    /// @param delta seconds since last frame
    void draw_objects(const double &delta);

private:
    static constexpr uint8_t MAX_AMOUNT_OF_OBJECTS = 15;

    Display *display;

    /// @brief Objects are drawn and updated every frame
    Vector<Object *> objects;

    /// @return index of object, or -1 if not found
    uint8_t find_object_index(Object *object);
};

#endif
