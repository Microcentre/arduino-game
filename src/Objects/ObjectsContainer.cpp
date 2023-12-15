#include "ObjectsContainer.h"

ObjectsContainer::ObjectsContainer(Display *display, Vector<Object *> objects_array)
{
    this->display = display;

    // array of objects on the screen to be updated & rendered.
    // Vector<> is a custom library that IS dynamic,
    // which for some reason has to be intialised in this hacky way
    this->objects = objects_array;
}

ObjectsContainer::~ObjectsContainer()
{
    for (auto i = this->objects.begin(); i != this->objects.end(); ++i)
    {
        delete (*i);
        (*i) = nullptr;
    }
    this->objects.clear();
}

void ObjectsContainer::add_object(Object *object)
{
    this->objects.push_back(object);
}

void ObjectsContainer::delete_object(Object *object)
{
    uint8_t index = find_object_index(object);
    if (index == -1) // not found
        return;

    object->undraw(this->display);

    this->objects.remove(index);
    delete object;
    object = nullptr;
}

void ObjectsContainer::update_objects(const double &delta)
{
    auto i = this->objects.begin();
    while (i != this->objects.end())
    {
        Object *object = (*i);

        // delete if marked for deletion
        if (object->marked_for_deletion)
        {
            this->delete_object(object);
            continue;
        }

        object->update(delta);
        ++i;
    }
}

void ObjectsContainer::draw_objects(const double &delta)
{
    for (auto i = objects.begin(); i != objects.end(); ++i)
        (*i)->draw(this->display);
}

uint8_t ObjectsContainer::get_size()
{
    return this->objects.size();
}

uint8_t ObjectsContainer::find_object_index(Object *object)
{
    for (uint8_t i = 0; i < this->objects.size(); ++i)
    {
        if (this->objects.at(i) == object)
            return i;
    }

    return -1;
}
