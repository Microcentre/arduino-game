#ifndef OBJECTSCONTAINER_H
#define OBJECTSCONTAINER_H

#include <Vector.h>
#include "Object.h"
#include "../Hardware/Display.h"

class ObjectsContainer
{
public:
    /// @brief list of Objects that are drawn and updated every frame
    Vector<Object *> objects;

    ObjectsContainer(Display *display, Vector<Object *> objects_array);
    ~ObjectsContainer();

    /// @param object object to add to the list of objects that are updated&drawn every frame
    void add_object(Object *object);

    /// @param object object to delete from memory and from the list of objects
    void delete_object(Object *object);

    /// @brief delete all objects from the list and memory
    /// calls delete_object on each object
    void delete_objects();

    /// @brief call update() on all objects. is called every frame.
    /// @param delta seconds since last frame
    void update_objects(const double &delta);

    /// @brief call draw() on all objects. is called every frame.
    void draw_objects();

    /// @brief call undraw() on all objects
    void undraw_objects();

    /// @return count of objects that are not marked_for_deletion
    uint8_t undeleted_count();

    /// @return the amount of objects the ObjectContainer is holding
    uint8_t get_size();

private:
    /// @brief used to draw and undraw objects
    Display *display;

    /// @return index of object, or -1 if not found
    uint8_t find_object_index(Object *object);
};

#endif
